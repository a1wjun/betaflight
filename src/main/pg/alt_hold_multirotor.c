/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "platform.h"

#ifndef USE_WING

#ifdef USE_ALTITUDE_HOLD

#include "flight/alt_hold.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "alt_hold.h"

PG_REGISTER_WITH_RESET_TEMPLATE(altHoldConfig_t, altHoldConfig, PG_ALTHOLD_CONFIG, 4);

PG_RESET_TEMPLATE(altHoldConfig_t, altHoldConfig,
    .climbRate = 50, // max vertical velocity change at full/zero throttle. 50 means 5 m/s
    .deadband = 20, // throttle deadband in percent of stick travel
);
#endif

#endif // USE_WING
