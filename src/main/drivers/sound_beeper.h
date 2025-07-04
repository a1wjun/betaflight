/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "drivers/io_types.h"

#ifdef USE_BEEPER
#define BEEP_TOGGLE              systemBeepToggle()
#define BEEP_OFF                 systemBeep(false)
#define BEEP_ON                  systemBeep(true)
#else
#define BEEP_TOGGLE do {} while (0)
#define BEEP_OFF    do {} while (0)
#define BEEP_ON     do {} while (0)
#endif

void systemBeep(bool on);
void systemBeepToggle(void);
struct beeperDevConfig_s;
void beeperInit(const struct beeperDevConfig_s *beeperDevConfig);

// platform implementation
void pwmWriteBeeper(bool on);
void pwmToggleBeeper(void);
void beeperPwmInit(const ioTag_t tag, uint16_t frequency);
