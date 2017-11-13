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
#include "io.hpp"
#include "periodic_callback.h"
#include "_can_dbc/generated_can.h"
#include "can.h"
#include "switches.hpp"
#include "string.h"
#include "printf_lib.h"
//#include "obstacle_avoidance.cpp"

Switches& SW_obj = Switches::getInstance();

/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);

SENSOR_SONARS_t sensor_msg_decoded;
const uint32_t            SENSOR_SONARS__MIA_MS = 1000;
const SENSOR_SONARS_t     SENSOR_SONARS__MIA_MSG = { 999 };

MOTOR_SIGNAL_t obstacle_avoidance(SENSOR_SONARS_t sensor_msg_decoded);

/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
    //initializing the CAN bus
    CAN_init(can1, 100, 5, 5, nullptr, nullptr);
    //if receiving enable this code
    CAN_bypass_filter_accept_all_msgs();
    //resetting
    CAN_reset_bus(can1);
    
    //To be removed after integration
    SW_obj.init();
    return true; // Must return true upon success
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

void period_1Hz(uint32_t count)
{
    if(CAN_is_bus_off(can1))
        CAN_reset_bus(can1);
}

bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
{
    can_msg_t msg;
    msg.msg_id = mid;
    msg.frame_fields.data_len = dlc;
    msg.frame_fields.is_29bit = 0;
    msg.frame_fields.is_rtr = 0;
    
    memcpy(msg.data.bytes, bytes, dlc);
    
    return CAN_tx(can1, &msg , 10);
    
}
void period_10Hz(uint32_t count)
{
    
}

void period_100Hz(uint32_t count)
{
    can_msg_t message_recd;
    if (!CAN_is_bus_off(can1)) {
        
        //Receive Sensor Data
        if(CAN_rx(can1, &message_recd, 0))
        {
            dbc_msg_hdr_t can_msg_hdr;
            can_msg_hdr.dlc = message_recd.frame_fields.data_len;
            can_msg_hdr.mid = message_recd.msg_id;
            dbc_decode_SENSOR_SONARS(&sensor_msg_decoded, message_recd.data.bytes,&can_msg_hdr);
            //u0_dbg_printf("%d\n",sensor_msg_decoded.SENSOR_SONARS_left); //Delete this later
            LE.set(1,0);
        }
        else if(dbc_handle_mia_SENSOR_SONARS(&sensor_msg_decoded, 10))
        {
            LE.set(1,1);
            u0_dbg_printf("MIA ");
        }
        //Delete this bit
        /*sensor_msg_decoded.SENSOR_SONARS_left = 130;
         sensor_msg_decoded.SENSOR_SONARS_middle = 25;
         sensor_msg_decoded.SENSOR_SONARS_right = 25;
         */
        //Call for obstacle avoidance
        MOTOR_SIGNAL_t motor_msg_to_send = { 0 };
        motor_msg_to_send = obstacle_avoidance(sensor_msg_decoded);
        
        dbc_encode_and_send_MOTOR_SIGNAL(&motor_msg_to_send);
    }
    else
    {
        CAN_reset_bus(can1);
    }
    
    // LE.toggle(3);
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
    //  LE.toggle(4);
}

static int spC;
static int spM;

//Obstacle avoidance algorithm
MOTOR_SIGNAL_t obstacle_avoidance(SENSOR_SONARS_t sensor_msg_decoded)
{
    MOTOR_SIGNAL_t obst_avoided_msg = { 0 };
    
    /* Ranges:     Stop range (0): < 20 inches
     *             FullLeft/FullRight range (1): 21 - 110 inches
     *             SlightLeft/SlightRiht range (2): 111 - 200 inches
     */
    uint16_t left_range = 0;
    uint16_t middle_range = 0 ;
    uint16_t right_range = 0 ;
    //uint16_t rear_range = 0;
    
    //left sensor range calculation
    if(sensor_msg_decoded.SENSOR_SONARS_left>0 && sensor_msg_decoded.SENSOR_SONARS_left<=25)
    {
        left_range = -1;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_left>20 && sensor_msg_decoded.SENSOR_SONARS_left<=45)
    {
        left_range = 0;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_left>45 && sensor_msg_decoded.SENSOR_SONARS_left<=110)
    {
        left_range = 1;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_left > 110)
    {
        left_range = 2;
    }
    
    //middle sensor range calculation
    if(sensor_msg_decoded.SENSOR_SONARS_middle <= 40 && sensor_msg_decoded.SENSOR_SONARS_middle >= 0)
    {
        middle_range = 0;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_middle > 40 && sensor_msg_decoded.SENSOR_SONARS_middle <= 80)
    {
        middle_range = 1;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_middle > 80 && sensor_msg_decoded.SENSOR_SONARS_middle <= 180)
    {
        middle_range = 2;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_middle > 180)
    {
        middle_range = 3;
    }
    
    //right sensor range calculation
    if(sensor_msg_decoded.SENSOR_SONARS_right>0 && sensor_msg_decoded.SENSOR_SONARS_right<=25)
    {
        right_range = -1;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_right>20 && sensor_msg_decoded.SENSOR_SONARS_right<=45)
    {
        right_range = 0;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_right> 45 && sensor_msg_decoded.SENSOR_SONARS_right<=110)
    {
        right_range = 1;
    }
    else if(sensor_msg_decoded.SENSOR_SONARS_right > 110)
    {
        right_range = 2;
    }
    
    
    
    
    //Stop 000
    if(middle_range == 0)
    {
        //Stop
        //set bit, middle range = 3, the bit set to 1.
        spC = 0;
        spM = 0;   //this bit is set to 1, middle-range = 2
        
        obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
        obst_avoided_msg.MOTOR_DRIVE_SPEED = 0;
        u0_dbg_printf(" 0 ");
        
    }
    else if(middle_range == 1)
    {    u0_dbg_printf(" M1 ");
        if(spC == 1)
        {
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 0;
            spC = 0;
        }
        else if(spM == 1)
        {
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
            spM = 0;
        }
        else
        {
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
            
            if(left_range == 0 || left_range == -1)
            {
                obst_avoided_msg.MOTOR_STEER_FULL_RIGHT = 1;
            }
            else if(right_range == 0 || right_range == -1)
            {
                obst_avoided_msg.MOTOR_STEER_FULL_LEFT = 1;
            }
            else
            {
                obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
            }
        }
        
    }
    else if(middle_range == 2)
    {    u0_dbg_printf(" M2 ");
        if(spC == 1)
        {
            
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
            spC = 0;
        }
        else
        {
            
            if(left_range == -1 && right_range == -1)
            {
                obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
                obst_avoided_msg.MOTOR_DRIVE_SPEED = 0;
            }
            else if(left_range == 0 && right_range == 0)
            {
                obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
                obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
            }
            else if((left_range == 0 && right_range == -1) || (left_range == -1 && right_range == 0))
            {
                obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
                obst_avoided_msg.MOTOR_DRIVE_SPEED = 0;
            }
            else if(left_range == 0 || left_range == -1)
            {
                obst_avoided_msg.MOTOR_STEER_SLIGHT_RIGHT = 1;
                obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
                
            }
            else if(right_range == 0 || right_range == -1)
            {
                obst_avoided_msg.MOTOR_STEER_SLIGHT_LEFT = 1;
                obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
                
            }
            else
            {
                obst_avoided_msg.MOTOR_DRIVE_SPEED = 15;
                obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
            }
        }
        spM = 1;
    }
    else if(middle_range == 3)
    {
        u0_dbg_printf(" M3 ");
        
        if(left_range == -1 && right_range == -1)
        {
            obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 0;
        }
        else if(left_range == 0 && right_range == 0)
        {
            obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
        }
        else if((left_range == 0 && right_range == -1) || (left_range == -1 && right_range == 0))
        {
            obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 0;
        }
        else if(left_range == -1)
        {
            obst_avoided_msg.MOTOR_STEER_FULL_RIGHT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
        }
        else if(right_range == -1)
        {
            obst_avoided_msg.MOTOR_STEER_FULL_LEFT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;
        }
        else if(right_range == 0)
        {
            obst_avoided_msg.MOTOR_STEER_SLIGHT_LEFT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;//later make 15
        }
        else if(left_range == 0)
        {
            obst_avoided_msg.MOTOR_STEER_SLIGHT_RIGHT = 1;
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 5;//later make 15
        }
        else
        {
            obst_avoided_msg.MOTOR_DRIVE_SPEED = 15;  // make 25 on testing
            obst_avoided_msg.MOTOR_STEER_STRAIGHT = 1;
            //This block dteer the CAR according to GPS coordinates
        }
        spC = 1;
    }
    
    
    return obst_avoided_msg;
}
