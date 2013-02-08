/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/include/libmaple/bkp.h
 * @brief Backup register support (STM32F1 only).
 */

#ifndef _LIBMAPLE_BKP_H_
#define _LIBMAPLE_BKP_H_

#include <inttypes.h>
#include "config.h"

#if defined(STM32_MEDIUM_DENSITY)
#define BKP_NR_DATA_REGS 10
#elif defined(STM32_HIGH_DENSITY)
#define BKP_NR_DATA_REGS 42
#endif

/** Backup peripheral register map type. */
typedef struct bkp_reg_map {
    const uint32_t RESERVED1;     ///< Reserved
    volatile uint32_t DR1;            ///< Data register 1
    volatile uint32_t DR2;            ///< Data register 2
    volatile uint32_t DR3;            ///< Data register 3
    volatile uint32_t DR4;            ///< Data register 4
    volatile uint32_t DR5;            ///< Data register 5
    volatile uint32_t DR6;            ///< Data register 6
    volatile uint32_t DR7;            ///< Data register 7
    volatile uint32_t DR8;            ///< Data register 8
    volatile uint32_t DR9;            ///< Data register 9
    volatile uint32_t DR10;           ///< Data register 10
    volatile uint32_t RTCCR;          ///< RTC control register
    volatile uint32_t CR;             ///< Control register
    volatile uint32_t CSR;            ///< Control and status register
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    const uint32_t RESERVED2;     ///< Reserved
    const uint32_t RESERVED3;     ///< Reserved
    volatile uint32_t DR11;           ///< Data register 11
    volatile uint32_t DR12;           ///< Data register 12
    volatile uint32_t DR13;           ///< Data register 13
    volatile uint32_t DR14;           ///< Data register 14
    volatile uint32_t DR15;           ///< Data register 15
    volatile uint32_t DR16;           ///< Data register 16
    volatile uint32_t DR17;           ///< Data register 17
    volatile uint32_t DR18;           ///< Data register 18
    volatile uint32_t DR19;           ///< Data register 19
    volatile uint32_t DR20;           ///< Data register 20
    volatile uint32_t DR21;           ///< Data register 21
    volatile uint32_t DR22;           ///< Data register 22
    volatile uint32_t DR23;           ///< Data register 23
    volatile uint32_t DR24;           ///< Data register 24
    volatile uint32_t DR25;           ///< Data register 25
    volatile uint32_t DR26;           ///< Data register 26
    volatile uint32_t DR27;           ///< Data register 27
    volatile uint32_t DR28;           ///< Data register 28
    volatile uint32_t DR29;           ///< Data register 29
    volatile uint32_t DR30;           ///< Data register 30
    volatile uint32_t DR31;           ///< Data register 31
    volatile uint32_t DR32;           ///< Data register 32
    volatile uint32_t DR33;           ///< Data register 33
    volatile uint32_t DR34;           ///< Data register 34
    volatile uint32_t DR35;           ///< Data register 35
    volatile uint32_t DR36;           ///< Data register 36
    volatile uint32_t DR37;           ///< Data register 37
    volatile uint32_t DR38;           ///< Data register 38
    volatile uint32_t DR39;           ///< Data register 39
    volatile uint32_t DR40;           ///< Data register 40
    volatile uint32_t DR41;           ///< Data register 41
    volatile uint32_t DR42;           ///< Data register 42
#endif
} bkp_reg_map;

/** Backup peripheral register map base pointer. */
#define BKP_BASE                        ((struct bkp_reg_map*)0x40006C00)

/** Backup peripheral device type. */
typedef struct bkp_dev {
    bkp_reg_map *regs; /**< Register map */
} bkp_dev;

extern const bkp_dev *BKP;

/*
 * Register bit definitions
 */

/* Data Registers */

#define BKP_DR_D                        0xFFFF

/* RTC Clock Calibration Register */

#define BKP_RTCCR_ASOS_BIT              9
#define BKP_RTCCR_ASOE_BIT              8
#define BKP_RTCCR_CCO_BIT               7

#define BKP_RTCCR_ASOS                  BIT(BKP_RTCCR_ASOS_BIT)
#define BKP_RTCCR_ASOE                  BIT(BKP_RTCCR_ASOE_BIT)
#define BKP_RTCCR_CCO                   BIT(BKP_RTCCR_CCO_BIT)
#define BKP_RTCCR_CAL                   0x7F

/* Backup control register */

#define BKP_CR_TPAL_BIT                 1
#define BKP_CR_TPE_BIT                  0

#define BKP_CR_TPAL                     BIT(BKP_CR_TPAL_BIT)
#define BKP_CR_TPE                      BIT(BKP_CR_TPE_BIT)

/* Backup control/status register */

#define BKP_CSR_TIF_BIT                 9
#define BKP_CSR_TEF_BIT                 8
#define BKP_CSR_TPIE_BIT                2
#define BKP_CSR_CTI_BIT                 1
#define BKP_CSR_CTE_BIT                 0

#define BKP_CSR_TIF                     BIT(BKP_CSR_TIF_BIT)
#define BKP_CSR_TEF                     BIT(BKP_CSR_TEF_BIT)
#define BKP_CSR_TPIE                    BIT(BKP_CSR_TPIE_BIT)
#define BKP_CSR_CTI                     BIT(BKP_CSR_CTI_BIT)
#define BKP_CSR_CTE                     BIT(BKP_CSR_CTE_BIT)

/*
 * Convenience functions
 */

void bkp_init(void);
void bkp_enable_writes(void);
void bkp_disable_writes(void);
uint16_t bkp_read(uint8_t reg);
void bkp_write(uint8_t reg, uint16_t val);

#endif
