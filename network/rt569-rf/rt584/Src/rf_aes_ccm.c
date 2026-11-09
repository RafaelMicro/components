/**************************************************************************//**
 * @file     rf_aes_ccm.c
 * @version
 * @brief    Local (loop-back) CCM encrypt/decrypt service, offloaded to
 *           the RT569S communication-subsystem security engine instead of
 *           RT584's own crypto (rt_aes.c, CPU + HW AES accelerator) path.
 *
 ******************************************************************************/

#include <string.h>

#include "mcu.h"
#include "rf_mcu.h"
#include "rf_aes_ccm.h"
#include "gpio.h"

/*
 * Wire format written to BMU_TX queue AES_CCM_RF_TXQ_ID (must match the
 * radio-side handler in source/COMMON/ccm_loopback.c in the rt569s
 * firmware repo):
 *
 *   [0]        marker       (RUCI_LOCAL_SEC_CCM_HEADER)
 *   [1  ..13]  nonce        (13 bytes)
 *   [14 ..15]  a_data_len   (LE U16, <= AES_CCM_RF_MAX_PAYLOAD)
 *   [16 ..17]  m_data_len   (LE U16, <= AES_CCM_RF_MAX_PAYLOAD)
 *   [18]       mic_len      (4, 8 or 16 -- the only MIC sizes the RT569S
 *                             security engine's 3-bit level field can
 *                             produce; see eAES_LEVEL / HALSEC_MIC_LEN)
 *   [19 .. )   a_data (hdr) immediately followed by m_data (data)
 *
 * The radio side treats [0..18] as an opaque "bypass" region: it reads the
 * header for parsing, but the HW security engine itself just streams it
 * through unmodified from TXQ to RXQ. So the RXQ result comes back as:
 *   [0..18] header echo || a_data (cleartext) || enc_m_data || mic[mic_len]
 */
#define RUCI_LOCAL_SEC_CCM_HEADER      (0x80)
#define AES_CCM_RF_TXQ_ID              (6)
#define AES_CCM_RF_HDR_LEN             (19)
#define AES_CCM_RF_MAX_PAYLOAD         (2047)      /* HW a_data_len/m_data_len are 11-bit fields */
/* Must fit the worst case: 19-byte header + up to AES_CCM_RF_MAX_PAYLOAD
 * data bytes + up to 16 mic bytes (decrypt's payload_buf also carries the
 * mic as input, same total as encrypt's output). That worst case lands
 * exactly on this sum with zero slack (e.g. hdr_len=0, data_len=2047,
 * mlen=16 in the max-size round-trip self-test), so pad it out to a round
 * number instead of sizing buffers to the exact boundary. */
#define AES_CCM_RF_BUF_LEN             (2112)
#define AES_CCM_RF_TIMING_MEASUREMENT  (FALSE)
#define AES_CCM_RF_TIMING_OVERALL_GPIO (GPIO29)
#define AES_CCM_RF_TIMING_PARTIAL_GPIO (GPIO28)

static uint8_t ccm_in_buf[AES_CCM_RF_BUF_LEN];
static uint8_t ccm_out_buf[AES_CCM_RF_BUF_LEN];

bool aes_ccm_encryption_rf(struct aes_ccm_encryption_packet_rf *ccm_packet)
{
    uint8_t             *p;
    uint32_t            tx_len, expect_rx_len, rx_len, tx_queue_empty;
    RF_MCU_RXQ_ERROR    rx_err;

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_set(AES_CCM_RF_TIMING_OVERALL_GPIO);
    gpio_pin_set(AES_CCM_RF_TIMING_PARTIAL_GPIO);
#endif

    if ((ccm_packet->mlen != 4) && (ccm_packet->mlen != 8) && (ccm_packet->mlen != 16))
    {
        /* RT569S HW security levels only produce MIC in {4, 8, 16} bytes */
        return false;
    }

    if ((ccm_packet->hdr_len > AES_CCM_RF_MAX_PAYLOAD) || (ccm_packet->data_len > AES_CCM_RF_MAX_PAYLOAD))
    {
        return false;
    }

    tx_len = AES_CCM_RF_HDR_LEN + ccm_packet->hdr_len + ccm_packet->data_len;

    if ((ccm_packet->out_buf == NULL) ||
            (*(ccm_packet->out_buf_len) < (ccm_packet->hdr_len + ccm_packet->data_len + ccm_packet->mlen)) ||
            (tx_len > AES_CCM_RF_BUF_LEN))
    {
        return false;
    }

    /* Pack the loop-back request */
    p = ccm_in_buf;
    *p++ = RUCI_LOCAL_SEC_CCM_HEADER;
    memcpy(p, ccm_packet->nonce, 13);
    p += 13;
    *p++ = (uint8_t)(ccm_packet->hdr_len & 0xFF);
    *p++ = (uint8_t)((ccm_packet->hdr_len >> 8) & 0xFF);
    *p++ = (uint8_t)(ccm_packet->data_len & 0xFF);
    *p++ = (uint8_t)((ccm_packet->data_len >> 8) & 0xFF);
    *p++ = (uint8_t)(ccm_packet->mlen);
    memcpy(p, ccm_packet->hdr, ccm_packet->hdr_len);
    p += ccm_packet->hdr_len;
    memcpy(p, ccm_packet->data, ccm_packet->data_len);

    do
    {
        RfMcu_MemoryGet(0x0048, (uint8_t *)&tx_queue_empty, 4);
    } while (!(tx_queue_empty & (1UL << AES_CCM_RF_TXQ_ID)));

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
    gpio_pin_set(AES_CCM_RF_TIMING_PARTIAL_GPIO);
#endif

    if (RfMcu_TxQueueSendById(AES_CCM_RF_TXQ_ID, ccm_in_buf, tx_len) != RF_MCU_TXQ_SET_SUCCESS)
    {
        return false;
    }

    /* Synchronous wait for the loop-back result committed to the RX queue */
    expect_rx_len = tx_len + ccm_packet->mlen;

    while (!RfMcu_RxQueueCheck())
    {
    }

    rx_len = RfMcu_RxQueueRead(ccm_out_buf, &rx_err);

    if ((rx_err != RF_MCU_RXQ_GET_SUCCESS) || (rx_len != expect_rx_len))
    {
        return false;
    }

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
    gpio_pin_set(AES_CCM_RF_TIMING_PARTIAL_GPIO);
#endif

    /* out_buf layout matches the local aes_ccm_encryption(): hdr || enc_data || mic */
    memcpy(ccm_packet->out_buf, ccm_packet->hdr, ccm_packet->hdr_len);
    memcpy(ccm_packet->out_buf + ccm_packet->hdr_len,
           ccm_out_buf + AES_CCM_RF_HDR_LEN + ccm_packet->hdr_len, ccm_packet->data_len);
    memcpy(ccm_packet->out_buf + ccm_packet->hdr_len + ccm_packet->data_len,
           ccm_out_buf + AES_CCM_RF_HDR_LEN + ccm_packet->hdr_len + ccm_packet->data_len, ccm_packet->mlen);

    *(ccm_packet->out_buf_len) = ccm_packet->hdr_len + ccm_packet->data_len + ccm_packet->mlen;

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
    gpio_pin_clear(AES_CCM_RF_TIMING_OVERALL_GPIO);
#endif

    return true;
}


/*
 * Companion "set AES key" request for aes_ccm_encryption_rf()/
 * aes_ccm_decryption_rf() above -- see the matching handler and wire
 * format doc comment in source/COMMON/ccm_loopback.c (rt569s firmware
 * repo): comm_isr_ccm_lb_key_set_process(). The CCM wire format carries
 * no key on purpose, so this gives the host an explicit way to load a
 * known key into the RT569S security engine before issuing CCM requests
 * -- e.g. so a bench self-test can compare this HW path against RT584's
 * local host CCM path (rt_aes.c / hosal_crypto_aes_ccm) using the
 * same key/nonce/data. keybits matches that path's convention
 * (128/192/256), not RT569S's internal 0/1/2 encoding.
 *
 * Fire-and-forget: just a HW register write on the radio side, no RX
 * queue response. Bench/idle-time only, same as aes_ccm_encryption_rf().
 */
#define RUCI_LOCAL_SEC_KEY_HEADER      (0x81)
#define RUCI_LOCAL_SEC_DECRY_HEADER    (0x82)

bool aes_ccm_key_set_rf(uint32_t keybits, const uint8_t *key)
{
    uint8_t buf[2 + 32];
    uint8_t key_type;
    uint8_t key_len;
    uint32_t tx_queue_empty;

    switch (keybits)
    {
    case 128:
        key_type = 0;
        key_len = 16;
        break;
    case 192:
        key_type = 1;
        key_len = 24;
        break;
    case 256:
        key_type = 2;
        key_len = 32;
        break;
    default:
        return false;
    }

    if (key == NULL)
    {
        return false;
    }

    buf[0] = RUCI_LOCAL_SEC_KEY_HEADER;
    buf[1] = key_type;
    memcpy(&buf[2], key, key_len);

    do
    {
        RfMcu_MemoryGet(0x0048, (uint8_t *)&tx_queue_empty, 4);
    } while (!(tx_queue_empty & (1UL << AES_CCM_RF_TXQ_ID)));

    return (RfMcu_TxQueueSendById(AES_CCM_RF_TXQ_ID, buf, (uint32_t)(2 + key_len)) == RF_MCU_TXQ_SET_SUCCESS);
}


/*
 * Decrypt-and-verify counterpart to aes_ccm_encryption_rf() above, using
 * the RT569S security engine's decrypt-loopback mode. See the matching
 * handler and wire format doc comment in source/COMMON/ccm_loopback.c
 * (rt569s firmware repo): comm_isr_tx_decry_process().
 *
 * Field layout mirrors the local host path's
 * struct aes_ccm_decryption_packet (rt_aes.h): payload_buf is the
 * combined hdr||enc_data||mic buffer -- exactly the out_buf layout
 * aes_ccm_encryption_rf()/aes_ccm_encryption() produce -- and on success
 * out_buf receives just the decrypted data (data_len bytes), not hdr+data.
 *
 * Unlike the local host path, MIC verification happens on the RT569S
 * HW engine itself (HALSEC_MIC_STATUS_GET() on the radio side), not by
 * recomputing and comparing on the host CPU here. This returns false and
 * zeroes out_buf_len both on a HW/framing error and on a genuine MIC
 * mismatch -- callers cannot tell those two apart from the return value
 * alone, matching aes_ccm_decryption_verification()'s STATUS_ERROR
 * contract (also a single failure return for both cases).
 *
 * Only mlen in {4, 8, 16} is supported, and this is bench/idle-time only,
 * same as aes_ccm_encryption_rf().
 */
bool aes_ccm_decryption_rf(struct aes_ccm_decryption_packet_rf *ccm_packet)
{
    uint8_t             *p;
    uint32_t            tx_len, expect_rx_len, rx_len, tx_queue_empty;
    RF_MCU_RXQ_ERROR    rx_err;
    uint8_t             mic_status;

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_set(AES_CCM_RF_TIMING_OVERALL_GPIO);
    gpio_pin_set(AES_CCM_RF_TIMING_PARTIAL_GPIO);
#endif

    if ((ccm_packet->mlen != 4) && (ccm_packet->mlen != 8) && (ccm_packet->mlen != 16))
    {
        /* RT569S HW security levels only support MIC in {4, 8, 16} bytes */
        return false;
    }

    if ((ccm_packet->hdr_len > AES_CCM_RF_MAX_PAYLOAD) || (ccm_packet->data_len > AES_CCM_RF_MAX_PAYLOAD))
    {
        return false;
    }

    tx_len = AES_CCM_RF_HDR_LEN + ccm_packet->hdr_len + ccm_packet->data_len + ccm_packet->mlen;

    if ((ccm_packet->out_buf == NULL) ||
            (*(ccm_packet->out_buf_len) < ccm_packet->data_len) ||
            (tx_len > AES_CCM_RF_BUF_LEN))
    {
        *(ccm_packet->out_buf_len) = 0;
        return false;
    }

    /* Pack the loop-back request: header, then payload_buf (hdr||enc_data||mic) verbatim */
    p = ccm_in_buf;
    *p++ = RUCI_LOCAL_SEC_DECRY_HEADER;
    memcpy(p, ccm_packet->nonce, 13);
    p += 13;
    *p++ = (uint8_t)(ccm_packet->hdr_len & 0xFF);
    *p++ = (uint8_t)((ccm_packet->hdr_len >> 8) & 0xFF);
    *p++ = (uint8_t)(ccm_packet->data_len & 0xFF);
    *p++ = (uint8_t)((ccm_packet->data_len >> 8) & 0xFF);
    *p++ = (uint8_t)(ccm_packet->mlen);
    memcpy(p, ccm_packet->payload_buf, ccm_packet->hdr_len + ccm_packet->data_len + ccm_packet->mlen);

    do
    {
        RfMcu_MemoryGet(0x0048, (uint8_t *)&tx_queue_empty, 4);
    } while (!(tx_queue_empty & (1UL << AES_CCM_RF_TXQ_ID)));

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
    gpio_pin_set(AES_CCM_RF_TIMING_PARTIAL_GPIO);
#endif

    if (RfMcu_TxQueueSendById(AES_CCM_RF_TXQ_ID, ccm_in_buf, tx_len) != RF_MCU_TXQ_SET_SUCCESS)
    {
        *(ccm_packet->out_buf_len) = 0;
        return false;
    }

    /* Synchronous wait for the loop-back result committed to the RX queue */
    expect_rx_len = tx_len;

    while (!RfMcu_RxQueueCheck())
    {
    }

    rx_len = RfMcu_RxQueueRead(ccm_out_buf, &rx_err);

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
    gpio_pin_set(AES_CCM_RF_TIMING_PARTIAL_GPIO);
#endif

    if ((rx_err != RF_MCU_RXQ_GET_SUCCESS) || (rx_len != expect_rx_len))
    {
        *(ccm_packet->out_buf_len) = 0;
        return false;
    }

    /* ccm_out_buf[0] is the MIC pass/fail flag comm_isr_tx_decry_process()
     * wrote over the (otherwise meaningless, echoed) request marker byte:
     * 0 = verified OK, 1 = mismatch. */
    mic_status = ccm_out_buf[0];

    if (mic_status != 0)
    {
        *(ccm_packet->out_buf_len) = 0;

#if (AES_CCM_RF_TIMING_MEASUREMENT)
        gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
        gpio_pin_clear(AES_CCM_RF_TIMING_OVERALL_GPIO);
#endif
        return false;
    }

    memcpy(ccm_packet->out_buf, ccm_out_buf + AES_CCM_RF_HDR_LEN + ccm_packet->hdr_len, ccm_packet->data_len);
    *(ccm_packet->out_buf_len) = ccm_packet->data_len;

#if (AES_CCM_RF_TIMING_MEASUREMENT)
    gpio_pin_clear(AES_CCM_RF_TIMING_PARTIAL_GPIO);
    gpio_pin_clear(AES_CCM_RF_TIMING_OVERALL_GPIO);
#endif

    return true;
}
