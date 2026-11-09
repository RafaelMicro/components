# Globs only the 10 subdirectories actually referenced by sdk_library_add_sources()
# below, not the whole tree -- zboss/ also vendors application/, devtools/, ncp/,
# macsplit/, tests/, zll/ etc. with .c files that are never compiled, so a
# whole-tree glob stays non-empty (wrongly picking the source branch) even
# after a release strips just the 10 compiled directories.
file(GLOB_RECURSE ZBOSS_SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/commissioning/*.c
    ${CMAKE_CURRENT_LIST_DIR}/aps/*.c
    ${CMAKE_CURRENT_LIST_DIR}/common/*.c
    ${CMAKE_CURRENT_LIST_DIR}/mac/*.c
    ${CMAKE_CURRENT_LIST_DIR}/nwk/*.c
    ${CMAKE_CURRENT_LIST_DIR}/secur/*.c
    ${CMAKE_CURRENT_LIST_DIR}/zcl/*.c
    ${CMAKE_CURRENT_LIST_DIR}/zdo/*.c
    ${CMAKE_CURRENT_LIST_DIR}/zgp/*.c
    ${CMAKE_CURRENT_LIST_DIR}/zse/*.c
)

set(ZBOSS_RFD_LIBS
    zboss_commissioning_rfd zboss_aps_rfd zboss_common_rfd zboss_mac_rfd
    zboss_nwk_rfd zboss_secure_rfd zboss_zcl_rfd zboss_zdo_rfd zboss_zgp_rfd zboss_zse_rfd
)
set(ZBOSS_FFD_LIBS
    zboss_commissioning_ffd zboss_aps_ffd zboss_common_ffd zboss_mac_ffd
    zboss_nwk_ffd zboss_secure_ffd zboss_zcl_ffd zboss_zdo_ffd zboss_zgp_ffd zboss_zse_ffd
)
if(CONFIG_HOSAL_SOC_IDLE_SLEEP)
    set(ZBOSS_VARIANT_LIBS ${ZBOSS_RFD_LIBS})
else()
    set(ZBOSS_VARIANT_LIBS ${ZBOSS_FFD_LIBS})
endif()
set(ZBOSS_PREBUILT_COMPLETE TRUE)
foreach(ZBOSS_LIB ${ZBOSS_VARIANT_LIBS})
    if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/lib${ZBOSS_LIB}.a)
        set(ZBOSS_PREBUILT_COMPLETE FALSE)
    endif()
endforeach()

if(ZBOSS_SRC_FILES)
    sdk_add_compile_options(
        -Wno-implicit-fallthrough
    )

    sdk_add_compile_options($<$<COMPILE_LANGUAGE:C>:-Wno-pointer-to-int-cast>)

    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
        message(STATUS "build for zigbee sleepy device")
        add_definitions(
            -DZB_LIMIT_VISIBILITY
            -DZB_ED_ROLE
            -DZB_USE_SLEEP
            -DAPS_FRAGMENTATION
            -DZB_CONFIGURABLE_MEM
            -DZB_SOFT_SECURITY
            -DZB_MAC_RX_QUEUE_CAP=4
            -DZB_LITTLE_ENDIAN
            -DZB_NEED_ALIGN
            -DZB_AUTO_ACK_TX
            -DZB_TEST_PROFILE
        )
    else()
        message(STATUS "build for FFD device")
        add_definitions(
            -DZB_LIMIT_VISIBILITY
            -DAPS_FRAGMENTATION
            -DZB_CONFIGURABLE_MEM
            -DZB_SOFT_SECURITY
            -DZB_MAC_RX_QUEUE_CAP=4
            -DZB_LITTLE_ENDIAN
            -DZB_NEED_ALIGN
            -DZB_AUTO_ACK_TX
            -DZB_TEST_PROFILE
        )
    endif()
    add_definitions(
        -DTRACE_PRINT
        -DZB_TRACE_TO_PORT
        -DZB_TRACE_LEVEL=0
        -DZB_TRACE_MASK=0x0000
        )
    sdk_add_include_directories(
        aps
        common
    )
    ###########################################
    ##      ZBOSS Commissioning Library      ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_commissioning_rfd)
    else()
    sdk_generate_library(zboss_commissioning_ffd)
    endif()
    sdk_library_add_sources(
        commissioning/bdb/bdb_finding_binding.c
        commissioning/bdb/bdb_touchlink.c
        commissioning/bdb/zdo_commissioning_bdb.c
        commissioning/bdb/zdo_commissioning_bdb_formation.c
        commissioning/legacy/zdo_commissioning_classic.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        include/zll
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()

    ###########################################
    ##           ZBOSS APS Library           ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_aps_rfd)
    else()
    sdk_generate_library(zboss_aps_ffd)
    endif()
    sdk_library_add_sources(
        aps/aps_aib.c
        aps/aps_bind.c
        aps/aps_commands.c
        aps/aps_dups.c
        aps/aps_interpan.c
        aps/aps_main.c
        aps/aps_nwk_confirm.c
        aps/aps_group_table.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        aps
        nwk
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()


    ###########################################
    ##         ZBOSS Common Library         ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_common_rfd)
    else()
    sdk_generate_library(zboss_common_ffd)
    endif()
    sdk_library_add_sources(
        common/zb_24bit_math.c
        common/zb_48bit_math.c
        common/zb_address.c
        common/zb_bufpool_mult.c
        common/zb_bufpool_mult_storage.c
        common/zb_channel_page.c
        common/zb_debug.c
        common/zb_error_indication.c
        common/zb_init_common.c
        common/zb_init_default.c
        common/zb_nvram.c
        common/zb_nvram_custom_handlers.c
        common/zb_random.c
        common/zb_scheduler.c
        common/zb_scheduler_init.c
        common/zb_serial_trace_bin.c
        common/zb_sleep.c
        common/zb_time.c
        common/zb_trace_common.c
        common/zb_watchdog.c
        common/zb_signal_common.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        common
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()

    ###########################################
    ##           ZBOSS Mac Library           ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_mac_rfd)
    else()
    sdk_generate_library(zboss_mac_ffd)
    endif()
    sdk_library_add_sources(
        mac/mac.c
        mac/mac_api_trace.c
        mac/mac_associate.c
        mac/mac_common.c
        mac/mac_cr_associate.c
        mac/mac_cr_coordinator.c
        mac/mac_cr_data.c
        mac/mac_data.c
        mac/mac_dump.c
        mac/mac_fcs.c
        mac/mac_optional.c
        mac/mac_pib.c
        mac/mac_scan.c
        mac/mac_visibility.c
        mac/mac_zcl_diagnostic.c
        mac/mac_zgp.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        mac
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()


    ###########################################
    ##         ZBOSS Network Library         ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_nwk_rfd)
    else()
    sdk_generate_library(zboss_nwk_ffd)
    endif()
    sdk_library_add_sources(
        nwk/nwk_address_assign.c
        nwk/nwk_address_conflict.c
        nwk/nwk_broadcasting.c
        nwk/nwk_cr_formation.c
        nwk/nwk_cr_join.c
        nwk/nwk_cr_mesh_routing.c
        nwk/nwk_cr_parent.c
        nwk/nwk_cr_permit_join.c
        nwk/nwk_cr_route_discovery.c
        nwk/nwk_cr_tree_routing.c
        nwk/nwk_discovery.c
        nwk/nwk_formation.c
        nwk/nwk_join.c
        nwk/nwk_link_status.c
        nwk/nwk_main.c
        nwk/nwk_mm.c
        nwk/nwk_neighbor.c
        nwk/nwk_neighbor_utility.c
        nwk/nwk_nlme.c
        nwk/nwk_panid_conflict.c
        nwk/nwk_srouting.c
        nwk/zb_nwk_ed_aging.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        nwk
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()


    ###########################################
    ##         ZBOSS Secure Library          ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_secure_rfd)
    else()
    sdk_generate_library(zboss_secure_ffd)
    endif()
    sdk_library_add_sources(
        secur/aps_secur.c
        secur/apsme_secur.c
        secur/bdb_secur.c
        secur/ic_secur.c
        secur/mac_secur.c
        secur/nwk_secur.c
        secur/secur_ccm.c
        secur/secur_formation.c
        secur/zb_ecc.c
        secur/zdo_secur.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        aps
        secur
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()

    ###########################################
    ##          ZBOSS ZCL Library            ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_zcl_rfd)
    else()
    sdk_generate_library(zboss_zcl_ffd)
    endif()
    sdk_library_add_sources(
        zcl/ha_sas.c
        zcl/zcl_alarms_commands.c
        zcl/zcl_attr_value.c
        zcl/zcl_basic_commands.c
        zcl/zcl_color_control_commands.c
        zcl/zcl_common.c
        zcl/zcl_continuous_value_change_commands.c
        zcl/zcl_custom_cluster_commands.c
        zcl/zcl_diagnostics_commands.c
        zcl/zcl_fan_control.c
        zcl/zcl_general_commands.c
        zcl/zcl_groups.c
        zcl/zcl_ias_ace_commands.c
        zcl/zcl_ias_wd_commands.c
        zcl/zcl_ias_zone_commands.c
        zcl/zcl_identify_commands.c
        zcl/zcl_illuminance_measurement.c
        zcl/zcl_ir_blaster.c
        zcl/zcl_level_control_commands.c
        zcl/zcl_main.c
        zcl/zcl_on_off_commands.c
        zcl/zcl_on_off_switch_config.c
        zcl/zcl_ota_upgrade_commands.c
        zcl/zcl_ota_upgrade_common.c
        zcl/zcl_ota_upgrade_minimal.c
        zcl/zcl_ota_upgrade_srv_commands.c
        zcl/zcl_poll_control_client.c
        zcl/zcl_poll_control_commands.c
        zcl/zcl_power_config_commands.c
        zcl/zcl_reporting.c
        zcl/zcl_scenes.c
        zcl/zcl_shade_config_commands.c
        zcl/zcl_temp_measurement.c
        zcl/zcl_door_lock.c
        zcl/zcl_time.c
        zcl/zcl_tunnel.c
        zcl/zcl_window_covering.c
        zcl/zcl_nvram.c
        zcl/zcl_rel_humidity.c
        zcl/zcl_s_metering.c
        zcl/zcl_thermostat_commands.c
        zcl/zcl_el_measurement.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        zcl
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()


    ###########################################
    ##           ZBOSS ZDO Library           ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_zdo_rfd)
    else()
    sdk_generate_library(zboss_zdo_ffd)
    endif()
    sdk_library_add_sources(
        zdo/af_descriptor.c
        zdo/af_interpan.c
        zdo/af_rx.c
        zdo/test_profile.c
        zdo/zb_zboss_api_common.c
        zdo/zb_zboss_api_default.c
        zdo/zdo_app.c
        zdo/zdo_app_common.c
        zdo/zdo_app_join.c
        zdo/zdo_app_leave.c
        zdo/zdo_app_prod_conf.c
        zdo/zdo_bind_manage.c
        zdo/zdo_channel_manager.c
        zdo/zdo_commissioning.c
        zdo/zdo_common.c
        zdo/zdo_diagnostics.c
        zdo/zdo_disc_cli.c
        zdo/zdo_disc_srv.c
        zdo/zdo_ed_aging.c
        zdo/zdo_formation.c
        zdo/zdo_nwk_manage_cli.c
        zdo/zdo_nwk_manage_srv.c
        zdo/zdo_poll.c
        zdo/zdo_resp_validate.c
        zdo/zdo_rx.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        include/zgp
        nwk
        zdo
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()


    ###########################################
    ##          ZBOSS ZGP Library            ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_zgp_rfd)
    else()
    sdk_generate_library(zboss_zgp_ffd)
    endif()
    sdk_library_add_sources(
        zgp/zgp_cluster.c
        zgp/zgp_cluster_gp.c
        zgp/zgp_common.c
        zgp/zgp_helper.c
        zgp/zgp_proxy_table.c
        zgp/zgp_secur.c
        zgp/zgp_sink.c
        zgp/zgp_stub.c
        zgp/zgp_tx_queue.c
        zgp/zgp_zgpd.c
        zgp/zgp_zgpd_app_table.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        include/zgp
        zgp
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()

    ###########################################
    ##          ZBOSS ZSE Library            ##
    ###########################################
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    sdk_generate_library(zboss_zse_rfd)
    else()
    sdk_generate_library(zboss_zse_ffd)
    endif()
    sdk_library_add_sources(
        zse/zse_aps_key_est.c
        zse/zse_certdb.c
        zse/zse_common.c
        zse/zse_kec_cluster.c
        zse/zse_sas.c
        zse/zse_service_discovery.c
        zse/zse_steady_state.c
    )
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # zboss/include and zboss_port/include are published bare by the parent
    # components/network/zigbee/CMakeLists.txt -- declared directly since there's
    # no real CMake target to depends_on() for them. Real include set measured
    # via `ninja -t deps` across a FFD and an RFD zigbee example build.
    sdk_add_private_include_directories(
        include
        include/ha
        include/zcl
        zse
        ${CMAKE_CURRENT_LIST_DIR}/../zboss_port/include
    )
    sdk_library_depends_on(sdk::soc_driver log lmac15p4)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()
elseif(ZBOSS_PREBUILT_COMPLETE)
    if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
        sdk_add_static_library(zboss_commissioning_rfd)
        sdk_add_static_library(zboss_aps_rfd)
        sdk_add_static_library(zboss_common_rfd)
        sdk_add_static_library(zboss_mac_rfd)
        sdk_add_static_library(zboss_nwk_rfd)
        sdk_add_static_library(zboss_secure_rfd)
        sdk_add_static_library(zboss_zcl_rfd)
        sdk_add_static_library(zboss_zdo_rfd)
        sdk_add_static_library(zboss_zgp_rfd)
        sdk_add_static_library(zboss_zse_rfd)
    else()
        sdk_add_static_library(zboss_commissioning_ffd)
        sdk_add_static_library(zboss_aps_ffd)
        sdk_add_static_library(zboss_common_ffd)
        sdk_add_static_library(zboss_mac_ffd)
        sdk_add_static_library(zboss_nwk_ffd)
        sdk_add_static_library(zboss_secure_ffd)
        sdk_add_static_library(zboss_zcl_ffd)
        sdk_add_static_library(zboss_zdo_ffd)
        sdk_add_static_library(zboss_zgp_ffd)
        sdk_add_static_library(zboss_zse_ffd)
    endif()
else()
    message(FATAL_ERROR "[zboss] No source and no prebuilt lib found!")
endif()
