/**************************************************************************//**
 * @file     rf_aes_ccm.h
 * @version
 * @brief    Local (loop-back) CCM encrypt/decrypt service, offloaded to
 *           the RT569S communication-subsystem security engine instead of
 *           RT584's own crypto (rt_aes.c) path.
 *
 ******************************************************************************/

#ifndef __RF_AES_CCM_H__
#define __RF_AES_CCM_H__

#include "mcu.h"
#include "rf_mcu_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * BMU TX queue AES_CCM_RF_TXQ_ID (6, see rf_aes_ccm.c) is a normal
 * dynamically-assignable "Physical Link" queue, not one reserved
 * exclusively for this feature (that's SECLB_TXQ_ID=7 on the radio side,
 * used only by its own MAC DTM self-test). Requests are tagged with a
 * marker byte so the radio-side dispatcher (source/COMMON/ccm_loopback.c
 * in the rt569s firmware repo) can tell a loop-back request apart from
 * ordinary connection data that also happens to land in queue 6, and
 * route anything else through unchanged. See rf_aes_ccm.c for the full
 * wire format.
 *
 * This only supports mic_len (mlen) in {4, 8, 16}: the RT569S security
 * engine's 3-bit level field can't produce other sizes. Callers needing
 * other MIC sizes (6,10,12,14 -- valid for the local aes_ccm_encryption()
 * host path, CPU + HW AES accelerator) must keep using that path instead.
 *
 * None of these are safe to call concurrently with live RF: enabling
 * loopback mode on the radio side redirects the shared BMU<->MAC mux away
 * from real MAC Tx/Rx for the duration of the operation (see RT569x BMU
 * User Guide, "Rx Security Loopback" diagram), regardless of which queue
 * carried the request. Bench/idle-time only.
 *
 * IMPORTANT: this depends on the RT569S radio running firmware built from
 * the rt569s Trunk repo with the ccm_loopback.c feature. The RT569 image
 * bundled in this SDK's rt569-fw component was not built from that
 * patched source and will not recognize these markers -- the radio must
 * be flashed separately with a matching firmware build for this to work.
 */
struct aes_ccm_encryption_packet_rf
{
    uint8_t   *nonce;      /*!< Nonce N -- must be 13 bytes. */

    uint8_t   *hdr;        /*!< Additional data authenticated but not encrypted (a_data) */
    uint32_t  hdr_len;     /*!< a_data length */

    uint8_t   *data;       /*!< message to be encrypted (m_data) */
    uint32_t  data_len;    /*!< m_data length */

    uint32_t  mlen;        /*!< MAC length. Only 4, 8 or 16 are supported by this HW path. */

    uint8_t   *out_buf;       /*!< ccm output message buffer: hdr || enc_data || mic */
    uint32_t  *out_buf_len;   /*!< number of valid bytes written to out_buf */
};

extern bool aes_ccm_encryption_rf(struct aes_ccm_encryption_packet_rf *ccm_packet);

/* Loads a known AES key into the RT569S security engine before calling
 * aes_ccm_encryption_rf()/aes_ccm_decryption_rf(), so their result can be
 * compared against RT584's local host CCM path (rt_aes.c / the
 * hosal_crypto_aes_ccm wrapper) for the same key/nonce/data. keybits
 * follows the local aes_key_init()/HOSAL convention: 128, 192 or 256. See
 * rf_aes_ccm.c for details.
 */
extern bool aes_ccm_key_set_rf(uint32_t keybits, const uint8_t *key);

/* Decrypt-and-verify counterpart to aes_ccm_encryption_rf(), using the
 * RT569S security engine's decrypt-loopback mode. Field layout mirrors
 * the local host struct aes_ccm_decryption_packet (rt_aes.h):
 * payload_buf is the combined hdr||enc_data||mic buffer (exactly what
 * aes_ccm_encryption_rf() / aes_ccm_encryption() produce as output), and
 * on success out_buf receives just the decrypted data (data_len bytes).
 * Returns false both on a HW/framing error and on a genuine MIC mismatch
 * -- see rf_aes_ccm.c. Only mlen in {4, 8, 16} is supported, bench/idle-
 * time only.
 */
struct aes_ccm_decryption_packet_rf
{
    uint8_t   *payload_buf;   /*!< combined hdr || enc_data || mic buffer to decrypt/verify */

    uint8_t   *nonce;         /*!< Nonce N -- must be 13 bytes. */

    uint32_t  hdr_len;        /*!< a_data length */
    uint32_t  data_len;       /*!< ciphertext (m_data) length, excludes mic */
    uint32_t  mlen;           /*!< MAC length. Only 4, 8 or 16 are supported by this HW path. */

    uint8_t   *out_buf;       /*!< decrypted data only, on success */
    uint32_t  *out_buf_len;   /*!< number of valid bytes written to out_buf */
};

extern bool aes_ccm_decryption_rf(struct aes_ccm_decryption_packet_rf *ccm_packet);

#ifdef __cplusplus
}
#endif

#endif /* __RF_AES_CCM_H__ */
