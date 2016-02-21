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

#include "wrd-sensor-gyroscope/BMG160.h"

BMG160::BMG160(I2CEx& _i2c, DigitalOutEx& _enable, InterruptInEx& _irq)
    :   i2c(_i2c),
        enable(_enable),
        irq(_irq)
{
    minar::Scheduler::postCallback(this, &BMG160::init)
        .tolerance(1);
}

void BMG160::init()
{
    i2c.frequency(400000);

    powerOn();
}

void BMG160::powerOn()
{
    enable.write(1, this, &BMG160::powerOnDone);
}

void BMG160::powerOnDone()
{
    minar::Scheduler::postCallback(this, &BMG160::sleep)
        .delay(minar::milliseconds(10))
        .tolerance(1);
}

void BMG160::sleep()
{
    memoryWrite[0] = LPM1_DEEP_SUSPEND;

    i2c.write(BMG160::ADDRESS, REG_LPM1, memoryWrite, 1, this, &BMG160::sleepDone);
}

void BMG160::sleepDone()
{

}
