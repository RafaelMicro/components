/**
 * @file zb_freertos.c
 * @author Rex Huang (rex.huang@rafaelmicro.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//=============================================================================
//                Include
//=============================================================================
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include "log.h"
#include "zb_common.h"
#include "zb_mac_globals.h"
#include "zboss_api.h"
#include "zigbee_platform.h"
#include "fota_define.h"

//=============================================================================
//                Private Definitions of const value
//=============================================================================
#define ZB_TRACE_FILE_ID 294
//=============================================================================
//                Private ENUM
//=============================================================================

//=============================================================================
//                Private Struct
//=============================================================================

//=============================================================================
//                Private Global Variables
//=============================================================================
zb_system_event_t zb_system_event_var = ZB_SYSTEM_EVENT_NONE;
static SemaphoreHandle_t zb_extLock = NULL;
static TaskHandle_t zb_taskHandle = NULL;
uint32_t zboss_start_run = 0;
unsigned char __attribute__((weak)) ZB_RAF_SCAN_DURATION = 5 ;
uint16_t __attribute__((weak)) raf_image_type = 321;
//=============================================================================
//                Functions
//=============================================================================
void zb_reset(zb_uint8_t param) {}

void zigbee_do_factory_reset(void)
{
    static uint8_t reset_start = 0;
    if (!reset_start) {
        reset_start = 1;
        zb_bdb_reset_via_local_action(0);
    }
}
uint8_t SystemReadyToSleep(void)
{
    return zboss_start_run;
}
uint32_t crc32(uint32_t flash_addr, uint32_t data_len)
{
    uint8_t RemainLen = (data_len & (0x3));
    uint32_t i;
    uint16_t j, k;
    uint32_t ChkSum = ~0;
    uint32_t Len = (data_len >> 2), Read;
    uint32_t *FlashPtr = (uint32_t *)flash_addr;

    for (i = 0; i < Len; i ++)
    {
        //get 32 bits at one time
        Read = FlashPtr[i];
        //get the CRC of 32 bits
        for (j = 0; j < 32; j += 8)
        {
            //get the CRC of 8 bits
            ChkSum ^= ((Read >> j) & 0xFF);
            for (k = 0; k < 8; k ++)
            {
                ChkSum = (ChkSum & 1) ? (ChkSum >> 1) ^ 0xedb88320 : ChkSum >> 1;
            }
        }
    }

    /*if data_len not align 4 bytes*/
    if (RemainLen > 0)
    {
        Read = FlashPtr[i];

        //get the CRC of 32 bits
        for (j = 0; j < (RemainLen << 3); j += 8)
        {
            //get the CRC of 8 bits
            ChkSum ^= ((Read >> j) & 0xFF);
            for (k = 0; k < 8; k ++)
            {
                ChkSum = (ChkSum & 1) ? (ChkSum >> 1) ^ 0xedb88320 : ChkSum >> 1;
            }
        }
    }
    ChkSum = ~ChkSum;
    return ChkSum;
}

uint32_t file_offset_process = 0;
uint32_t file_version_tmp = 0x01010101;
uint32_t file_len = 0;
static uint8_t *p_program_data = NULL;
static fota_information_t t_bootloader_ota_info = {0};
extern uint16_t raf_image_type;
zb_callback_t zigbee_app_device_cb = NULL;
zb_callback_t zigbee_app_zcl_cb = NULL;
void register_app_cb(void* cb) {
    if(cb != NULL) {
        zigbee_app_device_cb = (zb_callback_t) cb;
    }
}
void register_zcl_cb(void* cb) {
    if(cb != NULL) {
        zigbee_app_zcl_cb = (zb_callback_t) cb;
    }
}
void raf_device_cb(zb_uint8_t param)
{
    zb_zcl_device_callback_param_t *device_cb_param = ZB_BUF_GET_PARAM(param, zb_zcl_device_callback_param_t);
    device_cb_param->status = RET_OK;
    zb_uint8_t temp[32];
    zb_uint8_t endpoint;
    zb_zcl_attr_t *attr_desc;
    zb_uint8_t imgstatus = ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_NORMAL;
    zb_uint8_t manuf;

    endpoint = get_endpoint_by_cluster(ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE);

    static uint32_t flash_addr = FOTA_UPDATE_BUFFER_FW_ADDRESS_1MB_UNCOMPRESS;
    zb_uint32_t i;

    switch (device_cb_param->device_cb_id)
    {
    /* It's OTA Upgrade command */
    case ZB_ZCL_OTA_UPGRADE_VALUE_CB_ID:
    {
        zb_zcl_ota_upgrade_value_param_t *ota_upgrade_value = &(device_cb_param->cb_param.ota_value_param);

        switch (ota_upgrade_value->upgrade_status)
        {
        case ZB_ZCL_OTA_UPGRADE_STATUS_START:

            attr_desc = zb_zcl_get_attr_desc_a(endpoint,
                                               ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE, ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_STATUS_ID);
            if (attr_desc)
            {
                imgstatus = ZB_ZCL_GET_ATTRIBUTE_VAL_8(attr_desc);
            }

            attr_desc = zb_zcl_get_attr_desc_a(endpoint,
                                               ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE, ZB_ZCL_ATTR_OTA_UPGRADE_MANUFACTURE_ID);
            if (attr_desc)
            {
                manuf = ZB_ZCL_GET_ATTRIBUTE_VAL_16(attr_desc);
            }

            attr_desc = zb_zcl_get_attr_desc_a(endpoint,
                                               ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE, ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID);
            ZB_ZCL_SET_DIRECTLY_ATTR_VAL16(attr_desc, raf_image_type);

            /* Start OTA upgrade. */
            if (imgstatus == ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_NORMAL
                    && manuf == ota_upgrade_value->upgrade.start.manufacturer
                    && ota_upgrade_value->upgrade.start.image_type == raf_image_type)
            {
                log_info("OTA START");
                file_offset_process = 0;
                file_version_tmp = ota_upgrade_value->upgrade.start.file_version;
                file_len = ota_upgrade_value->upgrade.start.file_length;
                flash_addr = FOTA_UPDATE_BUFFER_FW_ADDRESS_1MB_UNCOMPRESS;
                for (i = 0; i < 0x74; i++)
                {
                    // Page erase (4096 bytes)
                    while (flash_check_busy());
                    taskENTER_CRITICAL();
                    flash_erase(FLASH_ERASE_SECTOR, flash_addr + (0x1000 * i));
                    taskEXIT_CRITICAL();
                }

                /* Accept image */
                ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_OK;
            }
            else if (manuf != ota_upgrade_value->upgrade.start.manufacturer || ota_upgrade_value->upgrade.start.image_type != raf_image_type)
            {
                /* image type or manufacturer error */
                ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_ERROR;
            }
            else
            {
                /* Another download is in progress, deny new image */
                ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_BUSY;
            }
            break;
        case ZB_ZCL_OTA_UPGRADE_STATUS_RECEIVE:
            /* Process image block. */
            if (!p_program_data)
            {
                p_program_data = pvPortMalloc(4 << 10);
            }

            ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_OK;

            if (1) //(ota_upgrade_value->upgrade.receive.file_offset > 32) // && ta_upgrade_value->upgrade.receive.file_offset < file_len-22)
            {
                log_printk(".");
                memcpy(p_program_data + (ota_upgrade_value->upgrade.receive.file_offset % 4096), (uint8_t *)ota_upgrade_value->upgrade.receive.block_data, ota_upgrade_value->upgrade.receive.data_length);
                file_offset_process += ota_upgrade_value->upgrade.receive.data_length;
                if (file_offset_process % 4096 == 0)
                {
                    // page program (256 bytes)
                    for (i = 0; i < (0x1000 >> 8); i++)
                    {
                        log_printk("*");
                        while (flash_check_busy());
                        taskENTER_CRITICAL();
                        flash_write_page((uint32_t) & ((uint8_t *)p_program_data)[i * (0x1 << 8)], flash_addr);
                        taskEXIT_CRITICAL();
                        flash_addr += (0x1 << 8);
                    }
                }
            }
            if (ota_upgrade_value->upgrade.receive.file_offset + 64 >= file_len)
            {
                for (i = 0; i < (0x1000 >> 8); i++)
                {
                    while (flash_check_busy());
                    log_printk("*");
                    taskENTER_CRITICAL();
                    flash_write_page((uint32_t) & ((uint8_t *)p_program_data)[i * (0x1 << 8)], flash_addr);
                    flash_addr += (0x1 << 8);
                    taskEXIT_CRITICAL();
                }
            }
            break;
        case ZB_ZCL_OTA_UPGRADE_STATUS_ABORT:

            attr_desc = zb_zcl_get_attr_desc_a(endpoint,
                                               ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE, ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID);
            ZB_ZCL_SET_DIRECTLY_ATTR_VAL16(attr_desc, 0xFFFF);

            zb_zcl_ota_upgrade_set_ota_status(endpoint, ZB_ZCL_OTA_UPGRADE_IMAGE_STATUS_NORMAL);
            ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_OK;
            break;
        case ZB_ZCL_OTA_UPGRADE_STATUS_CHECK:
            /* Downloading is finished, do additional checks if needed etc before Upgrade End Request. */
            ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_OK;
            break;
        case ZB_ZCL_OTA_UPGRADE_STATUS_APPLY:
            /* Upgrade End Resp is ok, ZCL checks for manufacturer, image type etc are ok.
               Last step before actual upgrade. */
            ota_upgrade_value->upgrade_status = ZB_ZCL_OTA_UPGRADE_STATUS_OK;
            break;
        case ZB_ZCL_OTA_UPGRADE_STATUS_FINISH:
            /* It is time to upgrade FW. */

            attr_desc = zb_zcl_get_attr_desc_a(endpoint,
                                               ZB_ZCL_CLUSTER_ID_OTA_UPGRADE, ZB_ZCL_CLUSTER_CLIENT_ROLE, ZB_ZCL_ATTR_OTA_UPGRADE_IMAGE_TYPE_ID);
            ZB_ZCL_SET_DIRECTLY_ATTR_VAL16(attr_desc, 0xFFFF);

            log_info("FINISH");
            flash_addr = FOTA_UPDATE_BUFFER_FW_ADDRESS_1MB_UNCOMPRESS;

            memcpy(&t_bootloader_ota_info, (uint8_t *)FOTA_UPDATE_BANK_INFO_ADDRESS, sizeof(t_bootloader_ota_info));

            t_bootloader_ota_info.fotabank_ready = FOTA_IMAGE_READY;
            t_bootloader_ota_info.fotabank_startaddr = FOTA_UPDATE_BUFFER_FW_ADDRESS_1MB_UNCOMPRESS + 62;
            t_bootloader_ota_info.fota_image_info = 0;
            t_bootloader_ota_info.signature_len = 0;
            t_bootloader_ota_info.target_startaddr = APP_START_ADDRESS;
            t_bootloader_ota_info.fotabank_datalen = file_len - 62 - 22;
            t_bootloader_ota_info.reserved[0] = file_version_tmp;
            t_bootloader_ota_info.fota_result = 0xFF;
            log_info("File version:0x%x", file_version_tmp);

            if (t_bootloader_ota_info.fotabank_datalen == 0)
            {
                if (p_program_data)
                {
                    vPortFree(p_program_data);
                    p_program_data = NULL;
                }
                break;
            }
            t_bootloader_ota_info.fotabank_crc = crc32(t_bootloader_ota_info.fotabank_startaddr, t_bootloader_ota_info.fotabank_datalen);
            memset(p_program_data, 0xFF, 0x100);
            memcpy(p_program_data, (uint8_t *)&t_bootloader_ota_info, sizeof(fota_information_t));

            //util_log_mem(UTIL_LOG_INFO, "  ", (uint8_t *)p_program_data, sizeof(fota_information_t), 0);
            log_info("Write flash...");
            while (flash_check_busy());
            taskENTER_CRITICAL();
            flash_erase(FLASH_ERASE_SECTOR, FOTA_UPDATE_BANK_INFO_ADDRESS);
            taskEXIT_CRITICAL();
            while (flash_check_busy());
            taskENTER_CRITICAL();
            flash_write_page((uint32_t)p_program_data, FOTA_UPDATE_BANK_INFO_ADDRESS);
            taskEXIT_CRITICAL();
            log_info("done");

            if (p_program_data)
            {
                vPortFree(p_program_data);
                p_program_data = NULL;
            }

            log_info("Reboot device");
            vTaskDelay(300);
            sys_software_reset();
            break;
        }
    }
    break;

    default:
        if(zigbee_app_device_cb != NULL) {
            zigbee_app_device_cb(param);
        }
        break;
    }

    TRACE_MSG(TRACE_APP1, "<< test_device_cb %hd", (FMT__H, device_cb_param->status));
}

void zigbee_app_zcl_send_command(zcl_data_req_t* pt_data_req) {
    uint16_t dstAddr = pt_data_req->dstAddr;
    zb_bufid_t buffer = 0;
    zb_uint8_t* ptr;
    ZB_THREAD_SAFE(do {
        buffer = zb_buf_get_any();

        if (buffer == 0)
            break;

        ptr = zb_zcl_start_command_header(
            buffer,
            ZB_ZCL_CONSTRUCT_FRAME_CONTROL(
                pt_data_req->specific, (pt_data_req->manuCode == 0) ? 0 : 1,
                pt_data_req->direction, pt_data_req->disableDefaultRsp),
            pt_data_req->manuCode, pt_data_req->cmd, NULL);
        if (pt_data_req->specific_seq_num == 1)
        {
            *(ptr - 2) = pt_data_req->seq_num;
        }
        memcpy(ptr, pt_data_req->cmdFormat, pt_data_req->cmdFormatLen);
        ptr += pt_data_req->cmdFormatLen;

        ZB_ZCL_FINISH_PACKET((buffer), ptr)
        ZB_ZCL_SEND_COMMAND_SHORT(
            buffer, dstAddr, pt_data_req->addrmode, pt_data_req->dstEndpint,
            pt_data_req->srcEndPoint, 0x0104, pt_data_req->clusterID, zigbee_app_zcl_cb);
        ZB_APP_NOTIFY(ZB_SYSTEM_EVENT_APP);
    } while (0););
}
__weak void zboss_signal_handler(zb_uint8_t param) {
    zb_zdo_app_signal_hdr_t* sg_p = NULL;
    zb_zdo_app_signal_t sig = zb_get_app_signal(param, &sg_p);
    zb_ret_t z_ret = ZB_GET_APP_SIGNAL_STATUS(param);
    zb_zdo_signal_device_annce_params_t* dev_annce_params;

    log_info(">>zdo_signal_handler: status %d signal %d", z_ret, sig);
    do {
        if (z_ret != 0) {
            break;
        }
        switch (sig) {
            case ZB_ZDO_SIGNAL_SKIP_STARTUP: zboss_start_continue(); break;

            case ZB_BDB_SIGNAL_STEERING:
                log_info("Successfull steering, start f&b target\n");
                break;

            case ZB_COMMON_SIGNAL_CAN_SLEEP: {

            } break;

            case ZB_NLME_STATUS_INDICATION: {

            } break;
            case ZB_ZDO_SIGNAL_PERMIT_JOIN: {
            } break;

            default: break;
        }
    } while (0);

    if (sig == ZB_BDB_SIGNAL_DEVICE_FIRST_START
        || sig == ZB_BDB_SIGNAL_STEERING) {
        if (z_ret == 0 && sig == ZB_BDB_SIGNAL_DEVICE_FIRST_START) {
            bdb_start_top_level_commissioning(ZB_BDB_NETWORK_STEERING);
        }
    } else if (sig == ZB_BDB_SIGNAL_DEVICE_REBOOT) {
    }

    if (param) {
        zb_buf_free(param);
    }
}

void zbSysEventSignalPending(void) {
    if (xPortIsInsideInterrupt()) {
        BaseType_t pxHigherPriorityTaskWoken = pdTRUE;
        vTaskNotifyGiveFromISR(zb_taskHandle, &pxHigherPriorityTaskWoken);
    } else {
        xTaskNotifyGive(zb_taskHandle);
    }
}

void zbLock(void) {
    if (zb_extLock) {
        if(zb_taskHandle == NULL || (xSemaphoreGetMutexHolder(zb_extLock) != xTaskGetCurrentTaskHandle()))
        xSemaphoreTake(zb_extLock, portMAX_DELAY);
    }
}

void zbUnlock(void) {
    if (zb_extLock) {
        xSemaphoreGive(zb_extLock);
    }
}

static void zbSysProcessDrivers(void) {
    zb_system_event_t sevent = ZB_SYSTEM_EVENT_NONE;

    ZB_GET_NOTIFY(sevent);
    zb_radioTask(sevent);
}

// this function is defined in zigbee_app.c, it should be inclued in the project header file
extern int zigbee_app_init(void);

static void zbStackTask(void* aContext) {
    ZB_THREAD_SAFE(
        ZB_INIT("RafaelZBee");
    );
    ZB_ZCL_REGISTER_DEVICE_CB(raf_device_cb);
    while (!zb_sheduler_is_stop()) {
        if (ulTaskNotifyTake(pdFALSE, portMAX_DELAY) != 0) {
            ZB_THREAD_SAFE(zbSysProcessDrivers(); if (zboss_start_run) {
                zboss_main_loop_iteration();
            });
        }
    }

    vTaskDelete(NULL);
}

void zbStartRun(void) {
    zboss_start_run = 1;
    zboss_start();
    zigbee_timer_init();
    zigbee_timer_start();
    ZB_APP_NOTIFY(ZB_SYSTEM_EVENT_APP);
}
void zbStart(void) {
    static StackType_t zb_stackTask_stack[ZB_TASK_SIZE];
    static StaticTask_t zb_task;
    static StaticQueue_t stackLock;

    zb_extLock = xSemaphoreCreateMutexStatic(&stackLock);
    configASSERT(zb_extLock != NULL);
    zb_taskHandle = xTaskCreateStatic(
    zbStackTask, "zb-thread", ZB_TASK_SIZE, NULL,
    E_TASK_PRIORITY_ZIGBEE, zb_stackTask_stack, &zb_task);
}

void zboss_suspend(void)
{
    vTaskSuspend(zb_taskHandle);
}

void zboss_resume(void)
{
    vTaskResume(zb_taskHandle);
}
