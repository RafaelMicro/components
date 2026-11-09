/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * \file           XDMA.h
 * \brief          XDMA definition header file
 */
/*
 * This file is part of library_name.
 * Author: 
 */


#ifndef XDMA_H
#define XDMA_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "sysctrl.h"

/**
 * \defgroup        XDMA XDma
 * \ingroup         RT584_DRIVER
 * \brief           Define XDma definitions, structures, and functions
 * @{
 */


/**
* \brief            Xdma_enable
*/
__STATIC_INLINE void xdma_enable(void) {
    XDMA->xdma_ctl0 |= XDMA_ENABLE;
}

/**
 * \brief           Xdma_disable
 */
__STATIC_INLINE void xdma_disable(void) {
    XDMA->xdma_ctl0 &= ~XDMA_ENABLE;
}

/**
 * \brief           Xdma_reset
 */
__STATIC_INLINE void xdma_reset(void) {
    XDMA->xdma_ctl1 |= XDMA_RESET;
}

/**
 * \brief           Xdma_init
 */
__STATIC_INLINE void xdma_init(void) {
    enable_perclk(XDMA_CLK);
}

/*@}*/ /* end of RT584_DRIVER XDMA */

#ifdef __cplusplus
}
#endif

#endif /* End of XDMA_H */
