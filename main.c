/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

/**
 *  @file main.c
 *
 *  @brief main loop and calling any hardware init stuff. timing hacks for EEPROM
 *  writes not to block usb interrupts. logic to handle 2 second timeout then
 *  jump to user code.
 *
 */

#include "common.h"
#include "bkp.h"

void delay() {
    u32 c;
    for(c=0; c < 1000000; c++) {
        asm volatile("nop");
    }
}

int main() {
    u32 c;

    systemReset(); // peripherals but not PC
    setupCLK();
    setupLED();
    setupBUTTON();
    bkp_init();

    uint16_t val = bkp_read(BOOTLOADER_BKP_REG);
    if (val == BOOTLOADER_BKP_MAGIC) {
        bkp_enable_writes();
        delay();
        bkp_write(BOOTLOADER_BKP_REG, 0);
        bkp_disable_writes();
    } else {
        // Wait for button pullup to charge capacitance
        // of wiring leading to button (should be a few
        // millisecond delay)
        delay();

        // If button is not pressed
        if (readPin(BUTTON_BANK, BUTTON)) {
            // and if user code is valid
            if (checkUserCode(USER_CODE_FLASH)) {
                // run user code
                jumpToUser(USER_CODE_FLASH);
            }
        }
    }

    // otherwise finish initializing and run the bootloader
    setupUSB();
    setupFLASH();

    strobePin(LED_BANK, LED, STARTUP_BLINKS, BLINK_FAST);

    while (1) {

        strobePin(LED_BANK, LED, 1, BLINK_SLOW);

        if (dfuUploadStarted()) {
            dfuFinishUpload(); // systemHardReset from DFU once done
        }
    }

}
