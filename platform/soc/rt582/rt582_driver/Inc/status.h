/**
 * \file            status.h
 * \brief           Status header file
 */
/*
 * Copyright (c) 2024 Rafal Micro
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

#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           Define return Status
 */
#define STATUS_SUCCESS         (0UL)            /*!< */
#define STATUS_INVALID_PARAM   (1UL)            /*!< Invalid Parameter. */
#define STATUS_INVALID_REQUEST (2UL)            /*!< Invalid Request. */
#define STATUS_EBUSY           (3UL)            /*!< Device is busy now. */
#define STATUS_NO_INIT         (4UL)            /*!< Device should be init first. */
#define STATUS_ERROR           (5UL)            /*!< ERROR */
#define STATUS_TIMEOUT         (6UL)            /*!< TIMEOUT */

#ifdef __cplusplus
}
#endif

#endif /* End of STATUS_H */
