/**
 * \file            chip_define.h
 * \brief            Chip definition file.
 *        Define software build code based on chip type and chip version.
 *        Please change the definition of CHIP_TYPE and CHIP_VERSION to match real product IC.
 *        User can redefine CHIP_TYPE and CHIP_VERSION by one of two options:
 *          1. Select Target in Keil IDE will change CHIP_TYPE and CHIP_VERSION definitions in the Preprocessor Symbols field.
 *          2. User can define CHIP_TYPE and CHIP_VERSION in this file if they are not defined in the Preprocessor Symbols field.
 *        User can use the CHIP_MODEL definition which is defined by CHIP_TYPE and CHIP_VERSION.
 */

/*
 * Copyright (c) 2024 Rafael Micro
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:     
 */

#ifndef CHIP_DEFINE_H
#define CHIP_DEFINE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define RT581 0x01            /* CHIP_TYPE definition for chip RT581 */
#define RT582 0x02            /* CHIP_TYPE definition for chip RT582 */
#define RT583 0x03            /* CHIP_TYPE definition for chip RT583 */
#define RT584 0x04            /* CHIP_TYPE definition for chip RT584 */

#define RT58X_SHUTTLE 0x00            /* CHIP_VERSION definition for 
                                        RT58x series Shuttle version */
#define RT58X_MPA     0x01            /* CHIP_VERSION definition for 
                                        RT58x series MPA version */
#define RT58X_MPB     0x02            /* CHIP_VERSION definition for 
                                        RT58x series MPB version */
#define RT58X_MPC     0x03            /* CHIP_VERSION definition for 
                                        RT58x series MPC version */


#define CHIP_ID(TYPE, VER) ((TYPE << 8) | VER)


#define RT581_SHUTTLE                                                          \
    CHIP_ID(                                                                   \
        RT581,                                                                 \
        RT58X_SHUTTLE) /*CHIP_MODEL definition for chip RT581 Shuttle version*/
#define RT581_MPA                                                              \
    CHIP_ID(RT581,                                                             \
            RT58X_MPA) /*CHIP_MODEL definition for chip RT581 MPA version*/
#define RT581_MPB                                                              \
    CHIP_ID(RT581,                                                             \
            RT58X_MPB) /*CHIP_MODEL definition for chip RT581 MPB version*/
#define RT582_SHUTTLE                                                          \
    CHIP_ID(                                                                   \
        RT582,                                                                 \
        RT58X_SHUTTLE) /*CHIP_MODEL definition for chip RT582 Shuttle version*/
#define RT582_MPA                                                              \
    CHIP_ID(RT582,                                                             \
            RT58X_MPA) /*CHIP_MODEL definition for chip RT582 MPA version*/
#define RT582_MPB                                                              \
    CHIP_ID(RT582,                                                             \
            RT58X_MPB) /*CHIP_MODEL definition for chip RT582 MPB version*/
#define RT582_MPC                                                              \
    CHIP_ID(RT582,                                                             \
            RT58X_MPC) /*CHIP_MODEL definition for chip RT582 MPB version*/
#define RT583_SHUTTLE                                                          \
    CHIP_ID(                                                                   \
        RT583,                                                                 \
        RT58X_SHUTTLE) /*CHIP_MODEL definition for chip RT583 Shuttle version*/
#define RT583_MPA                                                              \
    CHIP_ID(RT583,                                                             \
            RT58X_MPA) /*CHIP_MODEL definition for chip RT583 MPA version*/
#define RT583_MPB                                                              \
    CHIP_ID(RT583,                                                             \
            RT58X_MPB) /*CHIP_MODEL definition for chip RT583 MPB version*/
#define RT584_SHUTTLE                                                          \
    CHIP_ID(                                                                   \
        RT584,                                                                 \
        RT58X_SHUTTLE) /*CHIP_MODEL definition for chip RT584 Shuttle version*/
#define RT584_MPA                                                              \
    CHIP_ID(RT584,                                                             \
            RT58X_MPA) /*CHIP_MODEL definition for chip RT584 MPA version*/
#define RT584_MPB                                                              \
    CHIP_ID(RT584,                                                             \
            RT58X_MPB) /*CHIP_MODEL definition for chip RT584 MPB version*/

/**
 * \brief           User can define CHIP_TYPE and CHIP_VERSION to match real
 *                  product IC if they are not defined in the Preprocessor 
 *                  Symbols field
 */
#ifndef CHIP_TYPE
#define CHIP_TYPE RT581
#endif

#ifndef CHIP_VERSION
#define CHIP_VERSION RT58X_MPB
#endif

/**
 * \brief           User can use the CHIP_MODEL definition which is defined by 
 *                  CHIP_TYPE and CHIP_VERSION
 */
#define CHIP_MODEL CHIP_ID(CHIP_TYPE, CHIP_VERSION)

#ifdef __cplusplus
}
#endif

#endif /* End of GPIO_REG_H */
