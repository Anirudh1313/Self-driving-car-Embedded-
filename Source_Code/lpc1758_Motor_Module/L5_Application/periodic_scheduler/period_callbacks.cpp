/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */
/**
 * @file
 * This contains the period callback functions for the periodic scheduler
 *
 * @warning
 * These callbacks should be used for hard real-time system, and the priority of these
 * tasks are above everything else in the system (above the PRIORITY_CRITICAL).
 * The period functions SHOULD NEVER block and SHOULD NEVER run over their time slot.
 * For example, the 1000Hz take slot runs periodically every 1ms, and whatever you
 * do must be completed within 1ms.  Running over the time slot will reset the system.
 */
#include <stdint.h>
#include <stdio.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "uart3.hpp"
#include "can.h"
#include "printf_lib.h"
#include "_can_dbc/generated_can.h"
#include "lpc_pwm.hpp"
#include "gpio.hpp"
#include "utilities.h"
#include "stdio.h"
PWM servo_motor(PWM::pwm1, 9.915); //servo motor on P2.0 and 50Hz.
PWM DC_motor(PWM::pwm2, 100); //servo motor on P2.0 and 50Hz
/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);
//MOTOR_STATUS_T create_struct(uint8_t error, float speed, uint32_t isMia, uint32_t miaCountMS)
//{
// MOTOR_STATUS_t motor_status1;
// motor_status1.MOTOR_STATUS_speed_kph = speed;
// motor_status1.MOTOR_STATUS_wheel_error = error;
// motor_status1.mia_info.is_mia = isMia;
// motor_status1.mia_info.mia_counter_ms = miaCountMS;
//
// return motor_status1;
//}
const uint32_t MOTOR_SIGNAL__MIA_MS = 3000;
const MOTOR_SIGNAL_t MOTOR_SIGNAL__MIA_MSG = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
MOTOR_SIGNAL_t motor_signal;
can_t can_1 = can1;
//Uart3 &u3 = Uart3::getInstance();
/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
    if(CAN_init(can_1, 100, 80, 80, NULL, NULL))
    {
        u0_dbg_printf("init up\n");
        CAN_reset_bus(can_1);
        CAN_bypass_filter_accept_all_msgs();
    }
    motor_signal.mia_info.is_mia = false;
    motor_signal.mia_info.mia_counter_ms = 0;
    // MOTOR_STATUS__MIA_MSG.MOTOR_STATUS_speed_kph = 115.6;
    // MOTOR_STATUS__MIA_MSG.MOTOR_STATUS_wheel_error = 0;
    // MOTOR_STATUS__MIA_MSG.mia_info.is_mia = true;
    // MOTOR_STATUS__MIA_MSG.mia_info.mia_counter_ms = 3000;
    return true; // Must return true upon success
    //u3.init(38400, 500, 500);
}
/// Register any telemetry variables
bool period_reg_tlm(void)
{
    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
    return true; // Must return true upon success
}
/**
 * Below are your periodic functions.
 * The argument 'count' is the number of times each periodic task is called.
 */
int k = 0;
void period_1Hz(uint32_t count)
{
    if(CAN_is_bus_off(can_1))
    {
        CAN_reset_bus(can_1);
        u0_dbg_printf("buss is off, just reseted! \n");
    }
    //LE.off(1);
}
void period_10Hz(uint32_t count)
{
    // if(k == 1)
    // {
    //  DC_motor.set(16);
    // }
    // else if(k == 2)
    // {
    //  LE.toggle(3);
    //  DC_motor.set(15.3);
    //  k = 2;
    // }
}
void period_100Hz(uint32_t count)
{
    can_msg_t can_msg;
    if(CAN_rx(can_1, &can_msg, 0))
    {
        dbc_msg_hdr_t msg_hdr;
        msg_hdr.dlc = can_msg.frame_fields.data_len;
        msg_hdr.mid = can_msg.msg_id;
        LE.toggle(2);
        dbc_decode_MOTOR_SIGNAL(&motor_signal, can_msg.data.bytes, &msg_hdr);
    }
    else if(dbc_handle_mia_MOTOR_SIGNAL(&motor_signal, 10))
    {
        if(motor_signal.MOTOR_DRIVE_REVERSE == 1)
        {
            LD.setLeftDigit(1);
        }
        LE.toggle(4);
    }
    // dc motor
    
    if(motor_signal.MOTOR_DRIVE_SPEED == 0)
    {
        DC_motor.set(10.1);
    }
    else if(motor_signal.MOTOR_DRIVE_SPEED == 5)
    {
        DC_motor.set(17.16);
    }
    else if(motor_signal.MOTOR_DRIVE_SPEED == 15)
    {
        DC_motor.set(17.26);
    }
    else if(motor_signal.MOTOR_DRIVE_SPEED == 25)
    {
        DC_motor.set(17.33);
    }
    
    //servo motor
    if(motor_signal.MOTOR_STEER_FULL_LEFT)
    {
        servo_motor.set(10.1);
    }
    else if(motor_signal.MOTOR_STEER_FULL_RIGHT)
    {
        servo_motor.set(19.8);
    }
    else if(motor_signal.MOTOR_STEER_STRAIGHT)
    {
        servo_motor.set(15.4);
    }
    else if(motor_signal.MOTOR_STEER_SLIGHT_LEFT)
    {
        servo_motor.set(13.4);
    }
    else if(motor_signal.MOTOR_STEER_SLIGHT_RIGHT)
    {
        servo_motor.set(17.4);
    }
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
}
