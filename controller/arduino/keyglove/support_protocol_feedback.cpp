// Keyglove controller source code - KGAPI "feedback" protocol command parser implementation
// 2015-07-03 by Jeff Rowberg <jeff@rowberg.net>

/*
================================================================================
Keyglove source code is placed under the MIT license
Copyright (c) 2015 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

================================================================================
*/

/**
 * @file support_protocol_feedback.cpp
 * @brief KGAPI "feedback" protocol command parser implementation
 * @author Jeff Rowberg
 * @date 2015-07-03
 *
 * This file implements subsystem-specific command processing functions for the
 * "feedback" part of the KGAPI protocol.
 *
 * This file is autogenerated. Normally it is not necessary to edit this file.
 */

#include "keyglove.h"
#include "support_feedback.h"
#include "support_feedback_blink.h"
#include "support_feedback_piezo.h"
#include "support_feedback_vibrate.h"
#include "support_feedback_rgb.h"
#include "support_protocol.h"
#include "support_protocol_feedback.h"

/**
 * @brief Command processing routine for "feedback" packet class
 * @param[in] rxPacket Incoming KGAPI packet buffer
 * @return Protocol error, if any (0 for success)
 * @see protocol_parse()
 * @see KGAPI command: kg_cmd_feedback_get_blink_mode()
 * @see KGAPI command: kg_cmd_feedback_set_blink_mode()
 * @see KGAPI command: kg_cmd_feedback_get_piezo_mode()
 * @see KGAPI command: kg_cmd_feedback_set_piezo_mode()
 * @see KGAPI command: kg_cmd_feedback_get_vibrate_mode()
 * @see KGAPI command: kg_cmd_feedback_set_vibrate_mode()
 * @see KGAPI command: kg_cmd_feedback_get_rgb_mode()
 * @see KGAPI command: kg_cmd_feedback_set_rgb_mode()
 */
uint8_t process_protocol_command_feedback(uint8_t *rxPacket) {
    // check for valid command IDs
    uint8_t protocol_error = 0;
    switch (rxPacket[3]) {
        #if KG_FEEDBACK & KG_FEEDBACK_BLINK
        case KG_PACKET_ID_CMD_FEEDBACK_GET_BLINK_MODE: // 0x01
            // feedback_get_blink_mode()(uint8_t mode)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                /*uint16_t result =*/ kg_cmd_feedback_get_blink_mode(&mode);
        
                // build response
                uint8_t payload[1] = { mode };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 1, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_BLINK
        
        #if KG_FEEDBACK & KG_FEEDBACK_BLINK
        case KG_PACKET_ID_CMD_FEEDBACK_SET_BLINK_MODE: // 0x02
            // feedback_set_blink_mode(uint8_t mode)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_blink_mode(rxPacket[4]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_BLINK
        
        #if KG_FEEDBACK & KG_FEEDBACK_PIEZO
        case KG_PACKET_ID_CMD_FEEDBACK_GET_PIEZO_MODE: // 0x03
            // feedback_get_piezo_mode(uint8_t index)(uint8_t mode, uint8_t duration, uint16_t frequency)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                uint8_t duration;
                uint16_t frequency;
                /*uint16_t result =*/ kg_cmd_feedback_get_piezo_mode(rxPacket[4], &mode, &duration, &frequency);
        
                // build response
                uint8_t payload[4] = { mode, duration, (uint8_t)(frequency & 0xFF), (uint8_t)((frequency >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 4, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO
        
        #if KG_FEEDBACK & KG_FEEDBACK_PIEZO
        case KG_PACKET_ID_CMD_FEEDBACK_SET_PIEZO_MODE: // 0x04
            // feedback_set_piezo_mode(uint8_t index, uint8_t mode, uint8_t duration, uint16_t frequency)(uint16_t result)
            // parameters = 5 bytes
            if (rxPacket[1] != 5) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_piezo_mode(rxPacket[4], rxPacket[5], rxPacket[6], rxPacket[7] | (rxPacket[8] << 8));
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO
        
        #if KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        case KG_PACKET_ID_CMD_FEEDBACK_GET_VIBRATE_MODE: // 0x05
            // feedback_get_vibrate_mode(uint8_t index)(uint8_t mode, uint8_t duration)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                uint8_t duration;
                /*uint16_t result =*/ kg_cmd_feedback_get_vibrate_mode(rxPacket[4], &mode, &duration);
        
                // build response
                uint8_t payload[2] = { mode, duration };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        
        #if KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        case KG_PACKET_ID_CMD_FEEDBACK_SET_VIBRATE_MODE: // 0x06
            // feedback_set_vibrate_mode(uint8_t index, uint8_t mode, uint8_t duration)(uint16_t result)
            // parameters = 3 bytes
            if (rxPacket[1] != 3) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_vibrate_mode(rxPacket[4], rxPacket[5], rxPacket[6]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE
        
        #if KG_FEEDBACK & KG_FEEDBACK_RGB
        case KG_PACKET_ID_CMD_FEEDBACK_GET_RGB_MODE: // 0x07
            // feedback_get_rgb_mode(uint8_t index)(uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode_red;
                uint8_t mode_green;
                uint8_t mode_blue;
                /*uint16_t result =*/ kg_cmd_feedback_get_rgb_mode(rxPacket[4], &mode_red, &mode_green, &mode_blue);
        
                // build response
                uint8_t payload[3] = { mode_red, mode_green, mode_blue };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 3, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_RGB
        
        #if KG_FEEDBACK & KG_FEEDBACK_RGB
        case KG_PACKET_ID_CMD_FEEDBACK_SET_RGB_MODE: // 0x08
            // feedback_set_rgb_mode(uint8_t index, uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue)(uint16_t result)
            // parameters = 4 bytes
            if (rxPacket[1] != 4) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_feedback_set_rgb_mode(rxPacket[4], rxPacket[5], rxPacket[6], rxPacket[7]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        #endif // KG_FEEDBACK & KG_FEEDBACK_RGB
        
        default:
            protocol_error = KG_PROTOCOL_ERROR_INVALID_COMMAND;
    }
    return protocol_error;
}

/* ============================= */
/* KGAPI COMMAND IMPLEMENTATIONS */
/* ============================= */

#if KG_FEEDBACK & KG_FEEDBACK_BLINK

/**
 * @brief Get current blink feedback mode
 * @param[out] mode Current blink feedback mode
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_get_blink_mode(uint8_t *mode) {
    *mode = feedbackBlinkMode;
    return 0; // success
}

/**
 * @brief Set new blink feedback mode
 * @param[in] mode New blink feedback mode to set
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_set_blink_mode(uint8_t mode) {
    if (mode >= KG_BLINK_MODE_MAX) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    } else {
        feedback_set_blink_mode((feedback_blink_mode_t)mode);

        // send kg_evt_feedback_blink_mode packet (if we aren't setting it from an API command)
        if (!inBinPacket) {
            uint8_t payload[1] = { mode };
            skipPacket = 0;
            if (kg_evt_feedback_blink_mode) skipPacket = kg_evt_feedback_blink_mode(mode);
            if (!skipPacket) send_keyglove_packet(KG_PACKET_TYPE_EVENT, 1, KG_PACKET_CLASS_FEEDBACK, KG_PACKET_ID_EVT_FEEDBACK_BLINK_MODE, payload);
        }
    }
    return 0; // success
}

#endif // KG_FEEDBACK & KG_FEEDBACK_BLINK

#if KG_FEEDBACK & KG_FEEDBACK_PIEZO

/**
 * @brief Get current feedback mode for a piezo buzzer
 * @param[in] index Index of piezo device for which to get the current mode
 * @param[out] mode Current feedback mode for specified piezo device
 * @param[out] duration Duration to maintain tone
 * @param[out] frequency Frequency of tone to generate
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_get_piezo_mode(uint8_t index, uint8_t *mode, uint8_t *duration, uint16_t *frequency) {
    // "index" is currently ignored, as there is only one piezo device in the design
    *mode = feedbackPiezoMode;
    *duration = feedbackPiezoDuration;
    *frequency = feedbackPiezoFrequency;
    return 0; // success
}

/**
 * @brief Set a new piezo feedback mode for a piezo buzzer
 * @param[in] index Index of piezo device for which to set a new mode
 * @param[in] mode New feedback mode to set for specified piezo device
 * @param[in] duration Duration to maintain tone
 * @param[in] frequency Frequency of tone to generate
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_set_piezo_mode(uint8_t index, uint8_t mode, uint8_t duration, uint16_t frequency) {
    if (mode >= KG_PIEZO_MODE_MAX) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    } else {
        // "index" is currently ignored, as there is only one piezo device in the design
        feedback_set_piezo_mode((feedback_piezo_mode_t)mode, duration, frequency);

        // send kg_evt_feedback_piezo_mode packet (if we aren't setting it from an API command)
        if (!inBinPacket) {
            uint8_t payload[5] = { index, mode, duration, (uint8_t)(frequency & 0xFF), (uint8_t)(frequency >> 8) };
            skipPacket = 0;
            if (kg_evt_feedback_piezo_mode) skipPacket = kg_evt_feedback_piezo_mode(index, mode, duration, frequency);
            if (!skipPacket) send_keyglove_packet(KG_PACKET_TYPE_EVENT, 5, KG_PACKET_CLASS_FEEDBACK, KG_PACKET_ID_EVT_FEEDBACK_PIEZO_MODE, payload);
        }
    }
    return 0; // success
}

#endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO

#if KG_FEEDBACK & KG_FEEDBACK_VIBRATE

/**
 * @brief Get current feedback mode for a vibration motor
 * @param[in] index Index of vibration device for which to get the current mode
 * @param[out] mode Current feedback mode for specified vibration device
 * @param[out] duration Duration to maintain vibration
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_get_vibrate_mode(uint8_t index, uint8_t *mode, uint8_t *duration) {
    // "index" is currently ignored, as there is only one vibration device in the design
    *mode = feedbackVibrateMode;
    *duration = feedbackVibrateDuration;
    return 0; // success
}

/**
 * @brief Set a new vibration motor feedback mode
 * @param[in] index Index of vibration device for which to set a new mode
 * @param[in] mode New feedback mode to set for specified vibration device
 * @param[in] duration Duration to maintain vibration
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_set_vibrate_mode(uint8_t index, uint8_t mode, uint8_t duration) {
    if (mode >= KG_VIBRATE_MODE_MAX) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    } else {
        // "index" is currently ignored, as there is only one vibration device in the design
        feedback_set_vibrate_mode((feedback_vibrate_mode_t)mode, duration);

        // send kg_evt_feedback_vibrate_mode packet (if we aren't setting it from an API command)
        if (!inBinPacket) {
            uint8_t payload[3] = { index, mode, duration };
            skipPacket = 0;
            if (kg_evt_feedback_vibrate_mode) skipPacket = kg_evt_feedback_vibrate_mode(index, mode, duration);
            if (!skipPacket) send_keyglove_packet(KG_PACKET_TYPE_EVENT, 3, KG_PACKET_CLASS_FEEDBACK, KG_PACKET_ID_EVT_FEEDBACK_PIEZO_MODE, payload);
        }
    }
    return 0; // success
}

#endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE

#if KG_FEEDBACK & KG_FEEDBACK_RGB

/**
 * @brief Get current feedback mode for an RGB LED
 * @param[in] index Index of RGB device for which to get the current mode
 * @param[out] mode_red Current feedback mode for specified RGB device red LED
 * @param[out] mode_green Current feedback mode for specified RGB device green LED
 * @param[out] mode_blue Current feedback mode for specified RGB device blue LED
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_get_rgb_mode(uint8_t index, uint8_t *mode_red, uint8_t *mode_green, uint8_t *mode_blue) {
    // "index" is currently ignored, as there is only one RGB device in the design
    *mode_red = feedbackRGBMode[0];
    *mode_green = feedbackRGBMode[1];
    *mode_blue = feedbackRGBMode[2];
    return 0; // success
}

/**
 * @brief Set a new RGB LED feedback mode
 * @param[in] index Index of RGB device for which to set a new mode
 * @param[in] mode_red New feedback mode to set for specified RGB device red LED
 * @param[in] mode_green New feedback mode to set for specified RGB device green LED
 * @param[in] mode_blue New feedback mode to set for specified RGB device blue LED
 * @return Result code (0=success)
 */
uint16_t kg_cmd_feedback_set_rgb_mode(uint8_t index, uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue) {
    if (mode_red >= KG_RGB_MODE_MAX || mode_green >= KG_RGB_MODE_MAX || mode_blue >= KG_RGB_MODE_MAX) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    } else {
        // "index" is currently ignored, as there is only one RGB device in the design
        feedback_set_rgb_mode((feedback_rgb_mode_t)mode_red, (feedback_rgb_mode_t)mode_green, (feedback_rgb_mode_t)mode_blue);

        // send kg_evt_feedback_rgb_mode packet (if we aren't setting it from an API command)
        if (!inBinPacket) {
            uint8_t payload[4] = { index, mode_red, mode_green, mode_blue };
            skipPacket = 0;
            if (kg_evt_feedback_rgb_mode) skipPacket = kg_evt_feedback_rgb_mode(index, mode_red, mode_green, mode_blue);
            if (!skipPacket) send_keyglove_packet(KG_PACKET_TYPE_EVENT, 4, KG_PACKET_CLASS_FEEDBACK, KG_PACKET_ID_EVT_FEEDBACK_RGB_MODE, payload);
        }
    }
    return 0; // success
}

#endif // KG_FEEDBACK & KG_FEEDBACK_RGB

/* ==================== */
/* KGAPI EVENT POINTERS */
/* ==================== */

#if KG_FEEDBACK & KG_FEEDBACK_BLINK
/* 0x01 */ uint8_t (*kg_evt_feedback_blink_mode)(uint8_t mode);
#endif // KG_FEEDBACK & KG_FEEDBACK_BLINK
#if KG_FEEDBACK & KG_FEEDBACK_PIEZO
/* 0x02 */ uint8_t (*kg_evt_feedback_piezo_mode)(uint8_t index, uint8_t mode, uint8_t duration, uint16_t frequency);
#endif // KG_FEEDBACK & KG_FEEDBACK_PIEZO
#if KG_FEEDBACK & KG_FEEDBACK_VIBRATE
/* 0x03 */ uint8_t (*kg_evt_feedback_vibrate_mode)(uint8_t index, uint8_t mode, uint8_t duration);
#endif // KG_FEEDBACK & KG_FEEDBACK_VIBRATE
#if KG_FEEDBACK & KG_FEEDBACK_RGB
/* 0x04 */ uint8_t (*kg_evt_feedback_rgb_mode)(uint8_t index, uint8_t mode_red, uint8_t mode_green, uint8_t mode_blue);
#endif // KG_FEEDBACK & KG_FEEDBACK_RGB

