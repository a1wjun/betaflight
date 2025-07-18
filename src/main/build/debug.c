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

#include "platform.h"

#include "debug.h"

int16_t debug[DEBUG16_VALUE_COUNT];
uint8_t debugMode;

// Please ensure that these names are aligned with the enum values defined in 'debug.h' - for OSD be sure the name is unique with 12 chars.
const char * const debugModeNames[DEBUG_COUNT] = {
    [DEBUG_NONE] = "NONE",
    [DEBUG_CYCLETIME] = "CYCLETIME",
    [DEBUG_BATTERY] = "BATTERY",
    [DEBUG_GYRO_FILTERED] = "GYRO_FILTERED",
    [DEBUG_ACCELEROMETER] = "ACCELEROMETER",
    [DEBUG_PIDLOOP] = "PIDLOOP",
    [DEBUG_RC_INTERPOLATION] = "RC_INTERPOLATION",
    [DEBUG_ANGLERATE] = "ANGLERATE",
    [DEBUG_ESC_SENSOR] = "ESC_SENSOR",
    [DEBUG_SCHEDULER] = "SCHEDULER",
    [DEBUG_STACK] = "STACK",
    [DEBUG_ESC_SENSOR_RPM] = "ESC_SENSOR_RPM",
    [DEBUG_ESC_SENSOR_TMP] = "ESC_SENSOR_TMP",
    [DEBUG_ALTITUDE] = "ALTITUDE",
    [DEBUG_FFT] = "FFT",
    [DEBUG_FFT_TIME] = "FFT_TIME",
    [DEBUG_FFT_FREQ] = "FFT_FREQ",
    [DEBUG_RX_FRSKY_SPI] = "RX_FRSKY_SPI",
    [DEBUG_RX_SFHSS_SPI] = "RX_SFHSS_SPI",
    [DEBUG_GYRO_RAW] = "GYRO_RAW",
    [DEBUG_MULTI_GYRO_RAW] = "MULTI_GYRO_RAW",
    [DEBUG_MULTI_GYRO_DIFF] = "MULTI_GYRO_DIFF",
    [DEBUG_MAX7456_SIGNAL] = "MAX7456_SIGNAL",
    [DEBUG_MAX7456_SPICLOCK] = "MAX7456_SPICLOCK",
    [DEBUG_SBUS] = "SBUS",
    [DEBUG_FPORT] = "FPORT",
    [DEBUG_RANGEFINDER] = "RANGEFINDER",
    [DEBUG_RANGEFINDER_QUALITY] = "RANGEFINDER_QUALITY",
    [DEBUG_OPTICALFLOW] = "OPTICALFLOW",
    [DEBUG_LIDAR_TF] = "LIDAR_TF",
    [DEBUG_ADC_INTERNAL] = "ADC_INTERNAL",
    [DEBUG_RUNAWAY_TAKEOFF] = "RUNAWAY_TAKEOFF",
    [DEBUG_SDIO] = "SDIO",
    [DEBUG_CURRENT_SENSOR] = "CURRENT_SENSOR",
    [DEBUG_USB] = "USB",
    [DEBUG_SMARTAUDIO] = "SMARTAUDIO",
    [DEBUG_RTH] = "RTH",
    [DEBUG_ITERM_RELAX] = "ITERM_RELAX",
    [DEBUG_ACRO_TRAINER] = "ACRO_TRAINER",
    [DEBUG_RC_SMOOTHING] = "RC_SMOOTHING",
    [DEBUG_RX_SIGNAL_LOSS] = "RX_SIGNAL_LOSS",
    [DEBUG_RC_SMOOTHING_RATE] = "RC_SMOOTHING_RATE",
    [DEBUG_ANTI_GRAVITY] = "ANTI_GRAVITY",
    [DEBUG_DYN_LPF] = "DYN_LPF",
    [DEBUG_RX_SPEKTRUM_SPI] = "RX_SPEKTRUM_SPI",
    [DEBUG_DSHOT_RPM_TELEMETRY] = "DSHOT_RPM_TELEMETRY",
    [DEBUG_RPM_FILTER] = "RPM_FILTER",
    [DEBUG_D_MAX] = "D_MAX",
    [DEBUG_AC_CORRECTION] = "AC_CORRECTION",
    [DEBUG_AC_ERROR] = "AC_ERROR",
    [DEBUG_MULTI_GYRO_SCALED] = "MULTI_GYRO_SCALED",
    [DEBUG_DSHOT_RPM_ERRORS] = "DSHOT_RPM_ERRORS",
    [DEBUG_CRSF_LINK_STATISTICS_UPLINK] = "CRSF_LINK_STATISTICS_UPLINK",
    [DEBUG_CRSF_LINK_STATISTICS_PWR] = "CRSF_LINK_STATISTICS_PWR",
    [DEBUG_CRSF_LINK_STATISTICS_DOWN] = "CRSF_LINK_STATISTICS_DOWN",
    [DEBUG_BARO] = "BARO",
    [DEBUG_AUTOPILOT_ALTITUDE] = "AUTOPILOT_ALTITUDE",
    [DEBUG_DYN_IDLE] = "DYN_IDLE",
    [DEBUG_FEEDFORWARD_LIMIT] = "FEEDFORWARD_LIMIT",
    [DEBUG_FEEDFORWARD] = "FEEDFORWARD",
    [DEBUG_BLACKBOX_OUTPUT] = "BLACKBOX_OUTPUT",
    [DEBUG_GYRO_SAMPLE] = "GYRO_SAMPLE",
    [DEBUG_RX_TIMING] = "RX_TIMING",
    [DEBUG_D_LPF] = "D_LPF",
    [DEBUG_VTX_TRAMP] = "VTX_TRAMP",
    [DEBUG_GHST] = "GHST",
    [DEBUG_GHST_MSP] = "GHST_MSP",
    [DEBUG_SCHEDULER_DETERMINISM] = "SCHEDULER_DETERMINISM",
    [DEBUG_TIMING_ACCURACY] = "TIMING_ACCURACY",
    [DEBUG_RX_EXPRESSLRS_SPI] = "RX_EXPRESSLRS_SPI",
    [DEBUG_RX_EXPRESSLRS_PHASELOCK] = "RX_EXPRESSLRS_PHASELOCK",
    [DEBUG_RX_STATE_TIME] = "RX_STATE_TIME",
    [DEBUG_GPS_RESCUE_VELOCITY] = "GPS_RESCUE_VELOCITY",
    [DEBUG_GPS_RESCUE_HEADING] = "GPS_RESCUE_HEADING",
    [DEBUG_GPS_RESCUE_TRACKING] = "GPS_RESCUE_TRACKING",
    [DEBUG_GPS_CONNECTION] = "GPS_CONNECTION",
    [DEBUG_ATTITUDE] = "ATTITUDE",
    [DEBUG_VTX_MSP] = "VTX_MSP",
    [DEBUG_GPS_DOP] = "GPS_DOP",
    [DEBUG_FAILSAFE] = "FAILSAFE",
    [DEBUG_GYRO_CALIBRATION] = "GYRO_CALIBRATION",
    [DEBUG_ANGLE_MODE] = "ANGLE_MODE",
    [DEBUG_ANGLE_TARGET] = "ANGLE_TARGET",
    [DEBUG_CURRENT_ANGLE] = "CURRENT_ANGLE",
    [DEBUG_DSHOT_TELEMETRY_COUNTS] = "DSHOT_TELEMETRY_COUNTS",
    [DEBUG_RPM_LIMIT] = "RPM_LIMIT",
    [DEBUG_RC_STATS] = "RC_STATS",
    [DEBUG_MAG_CALIB] = "MAG_CALIB",
    [DEBUG_MAG_TASK_RATE] = "MAG_TASK_RATE",
    [DEBUG_EZLANDING] = "EZLANDING",
    [DEBUG_TPA] = "TPA",
    [DEBUG_S_TERM] = "S_TERM",
    [DEBUG_SPA] = "SPA",
    [DEBUG_TASK] = "TASK",
    [DEBUG_GIMBAL] = "GIMBAL",
    [DEBUG_WING_SETPOINT] = "WING_SETPOINT",
    [DEBUG_AUTOPILOT_POSITION] = "AUTOPILOT_POSITION",
    [DEBUG_CHIRP] = "CHIRP",
};
