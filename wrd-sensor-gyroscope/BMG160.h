/*
 * Copyright (c) 2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __WRD_BOSH_BMG160_H__
#define __WRD_BOSH_BMG160_H__

#include "mbed-drivers/mbed.h"

#include "gpio-switch/DigitalOutEx.h"
#include "gpio-switch/InterruptInEx.h"
#include "wrd-utilities/I2CEx.h"
#include "wrd-utilities/SharedModules.h"

class BMG160
{
public:
    BMG160(I2CEx& _i2c, DigitalOutEx& _enable, InterruptInEx& _irq);

    void sleep(void);

private:

    typedef enum {
        ADDRESS     = 0xD0
    } address_t;

    typedef enum {
        REG_LPM1    = 0x11
    } registers_t;

    typedef enum {
        LPM1_SLEEP_DUR_MASK = (7 << 1),
        LPM1_DEEP_SUSPEND   = (1 << 5),
        LPM1_SUSPEND        = (1 << 7)
    } values_t;

    void init(void);
    void powerOn(void);
    void powerOnDone(void);
    void sleepDone(void);

    I2CEx& i2c;
    DigitalOutEx enable;
    InterruptInEx irq;

    char memoryWrite[4];
};

#endif // __WRD_BOSH_BMG160_H__
