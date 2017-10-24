/// DBC file: ../../alpha_dbc.dbc    Self node: 'DRIVER'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENEARTED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
    uint32_t is_mia : 1;          ///< Missing in action flag
    uint32_t mia_counter_ms : 31; ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct { 
    uint32_t mid; ///< Message ID of the message
    uint8_t  dlc; ///< Data length of the message
} dbc_msg_hdr_t; 

static const dbc_msg_hdr_t MOTOR_SIGNAL_HDR =                     {  100, 3 };




/// Message: MOTOR_SIGNAL from 'DRIVER', DLC: 3 byte(s), MID: 100
typedef struct {
    uint8_t MOTOR_STEER_FULL_LEFT : 1;        ///< B0:0   Destination: MOTOR
    uint8_t MOTOR_STEER_SLIGHT_LEFT : 1;      ///< B1:1   Destination: MOTOR
    uint8_t MOTOR_STEER_FULL_RIGHT : 1;       ///< B2:2   Destination: MOTOR
    uint8_t MOTOR_STEER_SLIGHT_RIGHT : 1;     ///< B3:3   Destination: MOTOR
    uint8_t MOTOR_STEER_STRAIGHT : 1;         ///< B4:4   Destination: MOTOR
    uint8_t MOTOR_DRIVE_FORWARD : 1;          ///< B5:5   Destination: MOTOR
    uint8_t MOTOR_DRIVE_REVERSE : 1;          ///< B6:6   Destination: MOTOR
    uint8_t MOTOR_DRIVE_NEUTRAL : 1;          ///< B7:7   Destination: MOTOR
    uint8_t MOTOR_DRIVE_SPEED;                ///< B13:8  Min: 0 Max: 60   Destination: MOTOR
    uint8_t MOTOR_STEER_ANGLE;                ///< B20:14  Min: 10 Max: 20   Destination: MOTOR

    // No dbc_mia_info_t for a message that we will send
} MOTOR_SIGNAL_t;


/// @{ These 'externs' need to be defined in a source file of your project
/// @}


/// Encode DRIVER's 'MOTOR_SIGNAL' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_MOTOR_SIGNAL(uint8_t bytes[8], MOTOR_SIGNAL_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->MOTOR_STEER_FULL_LEFT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01)); ///< 1 bit(s) starting from B0

    raw = ((uint32_t)(((from->MOTOR_STEER_SLIGHT_LEFT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 1); ///< 1 bit(s) starting from B1

    raw = ((uint32_t)(((from->MOTOR_STEER_FULL_RIGHT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 2); ///< 1 bit(s) starting from B2

    raw = ((uint32_t)(((from->MOTOR_STEER_SLIGHT_RIGHT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 3); ///< 1 bit(s) starting from B3

    raw = ((uint32_t)(((from->MOTOR_STEER_STRAIGHT)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 4); ///< 1 bit(s) starting from B4

    raw = ((uint32_t)(((from->MOTOR_DRIVE_FORWARD)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 5); ///< 1 bit(s) starting from B5

    raw = ((uint32_t)(((from->MOTOR_DRIVE_REVERSE)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 6); ///< 1 bit(s) starting from B6

    raw = ((uint32_t)(((from->MOTOR_DRIVE_NEUTRAL)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01) << 7); ///< 1 bit(s) starting from B7

    // Not doing min value check since the signal is unsigned already
    if(from->MOTOR_DRIVE_SPEED > 60) { from->MOTOR_DRIVE_SPEED = 60; } // Max value: 60
    raw = ((uint32_t)(((from->MOTOR_DRIVE_SPEED)))) & 0x3f;
    bytes[1] |= (((uint8_t)(raw) & 0x3f)); ///< 6 bit(s) starting from B8

    if(from->MOTOR_STEER_ANGLE < 10) { from->MOTOR_STEER_ANGLE = 10; } // Min value: 10
    if(from->MOTOR_STEER_ANGLE > 20) { from->MOTOR_STEER_ANGLE = 20; } // Max value: 20
    raw = ((uint32_t)(((from->MOTOR_STEER_ANGLE)))) & 0x7f;
    bytes[1] |= (((uint8_t)(raw) & 0x03) << 6); ///< 2 bit(s) starting from B14
    bytes[2] |= (((uint8_t)(raw >> 2) & 0x1f)); ///< 5 bit(s) starting from B16

    return MOTOR_SIGNAL_HDR;
}

/// Encode and send for dbc_encode_MOTOR_SIGNAL() message
static inline bool dbc_encode_and_send_MOTOR_SIGNAL(MOTOR_SIGNAL_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_MOTOR_SIGNAL(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_decode_MOTOR_SIGNAL() since 'DRIVER' is not the recipient of any of the signals

#endif
