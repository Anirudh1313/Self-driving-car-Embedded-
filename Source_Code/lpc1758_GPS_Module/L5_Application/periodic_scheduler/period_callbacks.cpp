// #include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include "io.hpp"
// #include "periodic_callback.h"
// #include "uart3.hpp"
// #include "can.h"
// #include "printf_lib.h"
// #include "_can_dbc/generated_can.h"

// /// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
// const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
// /**
//  * This is the stack size of the dispatcher task that triggers the period tasks to run.
//  * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
//  * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
//  * printf inside these functions, you need about 1500 bytes minimum
//  */
// const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);
// const uint32_t GPS_DESTINATION__MIA_MS = 3000;
// const GPS_DESTINATION_t GPS_DESTINATION__MIA_MSG = {333333 , 212121, 1, 0}; //mia message
// GPS_DESTINATION_t gps_des;
// GPS_CURRENT_LOCATION_t gps_curr;
// can_t can_1 = can1;
// /// Called once before the RTOS is started, this is a good place to initialize things once
// bool period_init(void)
// {
//     if(CAN_init(can_1, 100, 500, 500, NULL, NULL))
//     {
//     u0_dbg_printf("init up\n");
//     CAN_reset_bus(can_1);
//     CAN_bypass_filter_accept_all_msgs();
//     }
//     gps_des.GPS_DESTINATION_latitude = 343246;
//     gps_des.GPS_DESTINATION_longitude = 204160;
//     gps_des.mia_info.is_mia = false;
//     gps_des.mia_info.mia_counter_ms = 0;
//     return true; // Must return true upon success
// }
// /// Register any telemetry variables
// bool period_reg_tlm(void)
// {
//     // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
//     return true; // Must return true upon success
// }

// /**
//  * Below are your periodic functions.
//  * The argument 'count' is the number of times each periodic task is called.
//  */
// void period_1Hz(uint32_t count)
// {
//     LE.toggle(1);
//     if(CAN_is_bus_off(can_1))
//     {
//     CAN_reset_bus(can_1);
//     u0_dbg_printf("buss is off, just reseted! \n");
//     }
// }
// void period_10Hz(uint32_t count)
// {
//     //transmitting current location reading obtained from the gps sensor.
//     can_msg_t can_msg_tx;
//     dbc_msg_hdr_t tx_msg_hdr;
//     //srand((unsigned) time(0));
//     //uint32_t rmin = rand() % 100;
//     gps_curr.GPS_CURRENT_LOCATION_latitude = 111111;
//     gps_curr.GPS_CURRENT_LOCATION_longitude = 1222222;
//     tx_msg_hdr = dbc_encode_GPS_CURRENT_LOCATION(can_msg_tx.data.bytes, &gps_curr);
//     can_msg_tx.frame_fields.data_len = tx_msg_hdr.dlc;
//     can_msg_tx.msg_id = tx_msg_hdr.mid;
//     can_msg_tx.frame_fields.is_rtr = 0;
//     can_msg_tx.frame_fields.is_29bit = 0;
//     if(CAN_tx(can1, &can_msg_tx, 4))
//     {
//         //u0_dbg_printf("tx\n");
//         //LE.toggle(2);
//     }
//     //receiving the destination location readings obtained
// }
// void period_100Hz(uint32_t count)
// {
//     LE.toggle(3);

//     can_msg_t can_msg;
//     if(CAN_rx(can_1, &can_msg, 2))
//     {
//     dbc_msg_hdr_t msg_hdr;
//     msg_hdr.dlc = can_msg.frame_fields.data_len;
//     msg_hdr.mid = can_msg.msg_id;
//     dbc_decode_GPS_DESTINATION(&gps_des, can_msg.data.bytes, &msg_hdr);
//     u0_dbg_printf("latitude: %f  &  longitude: %f \n",gps_des.GPS_DESTINATION_latitude, gps_des.GPS_DESTINATION_longitude);
//     }
//     // else
//     // {
//     //  u0_dbg_printf("count: %d\n", motor_status.mia_info.mia_counter_ms);
//     // }
//     if(dbc_handle_mia_GPS_DESTINATION(&gps_des, 10))
//     {
//     LE.toggle(1);
//     LE.toggle(2);
//     LE.toggle(3);
//     LE.toggle(4);
//     u0_dbg_printf("latitude-mia: %f  &  longitude-mia: %f \n",gps_des.GPS_DESTINATION_latitude/10000, gps_des.GPS_DESTINATION_longitude/10000);
//     }
// }
// // 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// // scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
// void period_1000Hz(uint32_t count)
// {
//     LE.toggle(4);
// }



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
#include "uart3.hpp"
#include "switches.hpp"
#include "string.h"
#include "printf_lib.h"
#include "source/gps_module.h"
#include "source/i2cMagmtr.h"
//#include "obstacle_avoidance.cpp"


/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);
const uint32_t GPS_DESTINATION__MIA_MS = 3000;
const GPS_DESTINATION_t GPS_DESTINATION__MIA_MSG = {333333 , 212121, 1, 0}; //mia message
GPS_DESTINATION_t gps_des;
GPS_CURRENT_LOCATION_t gps_curr;

GPS_CAR_RUNNING_t gps_dir;
GPS_BEARING_HEADING_t gps_angle;


can_t can_1 = can1;

Uart3& u3 = u3.getInstance();
/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
    
    if(CAN_init(can_1, 100, 500, 500, NULL, NULL))
    {
        u0_dbg_printf("init up\n");
        CAN_reset_bus(can_1);
        CAN_bypass_filter_accept_all_msgs();
    }
    
    gps_des.GPS_DESTINATION_latitude = 343246;
    gps_des.GPS_DESTINATION_longitude = 204160;
    gps_des.mia_info.is_mia = false;
    gps_des.mia_info.mia_counter_ms = 0;
    
    u3.init(9600, 1000, 1000);
    
    
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
    
}


void period_10Hz(uint32_t count)
{
    
}

void period_100Hz(uint32_t count)
{
    
    can_msg_t gps_dest_msg;
    
    //Receiving the destination gps lat long from the bridge module.
    if(CAN_rx(can_1, &gps_dest_msg, 0))
    {
        dbc_msg_hdr_t des_hdr;
        des_hdr.dlc = gps_dest_msg.frame_fields.data_len;
        des_hdr.mid = gps_dest_msg.msg_id;
        dbc_decode_GPS_DESTINATION(&gps_des, gps_dest_msg.data.bytes, &des_hdr);
    }
    else
    {
        if(dbc_handle_mia_GPS_DESTINATION(&gps_des, 10))
        {
            LE.toggle(2);
        }
    }
    
    
    float lat1, long1, long2, lat2;
    
    lat2 = gps_des.GPS_DESTINATION_latitude;
    long2 = gps_des.GPS_DESTINATION_longitude;
    
    float bAngle, hAngle;
    LE.toggle(3);
    char *c = new char[1];
    u3.getChar(c, 0);
    //    char *latq;
    //    char *lonq;
    int g;
    int div = 1;
    int lat_G = 0;
    int long_G = 0;
    //u0_dbg_printf("%c", *c);
    if(*c == '$')
    {
        // while(*c != ',')
        // {
        u3.getChar(c, 0);
        if(*c == 'G')
        {
            u3.getChar(c, 0);
            if(*c == 'P')
            {
                u3.getChar(c, 0);
                if(*c == 'G')
                {
                    u3.getChar(c, 0);
                    if(*c == 'G')
                    {
                        u3.getChar(c, 0);
                        if(*c == 'A')
                        {
                            u3.getChar(c, 0);
                            if(*c == ',')
                            {
                                u3.getChar(c, 0);
                                while(*c != ',')
                                {
                                    u3.getChar(c, 0);
                                }
                                if(*c == ',')
                                {
                                    u3.getChar(c, 0);
                                    while(*c != ',')
                                    {
                                        //u0_dbg_printf("%c", *c);
                                        if(*c != '.')
                                        {
                                            g = *c-'0';
                                            lat_G += g*10000000/div;
                                            div *= 10;
                                        }
                                        
                                        u3.getChar(c, 0);
                                    }
                                    //u0_dbg_printf("\n");
                                    //getting the current latitude from the gps sensor **********************
                                    lat_G += 134828;
                                    if(*c == ',')
                                    {
                                        u3.getChar(c,0);
                                        u3.getChar(c,0);
                                        u3.getChar(c,0);
                                        LD.setLeftDigit(*c);
                                        div = 1;
                                        
                                        while(*c != ',')
                                        {
                                            if(*c != '.')
                                            {
                                                g = *c-'0';
                                                long_G += g*100000000/div;
                                                div *= 10;
                                            }
                                            
                                            u3.getChar(c,0);
                                        } 
                                        
                                        //getting the current longitude from the gps sensor ***********************
                                        long_G += 352825;
                                       
                                        lat1 = static_cast<double>(lat_G)/1000000;
                                        long1 = -1*static_cast<double>(long_G)/1000000;
                                        
                                        u0_dbg_printf("lat1: %f   , long1: %f", lat1, long1);
                                        
                                        
//                                         long2 = -121.881100;
//                                         lat2 = 37.336947;
                                        
                                        //calculating the bearing angle *******************************************
                                        bAngle = bearing_angle(lat1, long1, lat2, long2);
                                        
                                        u0_dbg_printf("   angle: %lf \n", bAngle);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    // transmitting the current location to the bridge controller to display it on the LCD
    can_msg_t can_msg_tx;
    dbc_msg_hdr_t tx_msg_hdr;
    
    //srand((unsigned) time(0));
    //    uint32_t rmin = rand() % 100;
    gps_curr.GPS_CURRENT_LOCATION_latitude = lat_G;
    gps_curr.GPS_CURRENT_LOCATION_longitude = long_G;
    
    tx_msg_hdr = dbc_encode_GPS_CURRENT_LOCATION(can_msg_tx.data.bytes, &gps_curr);
    can_msg_tx.frame_fields.data_len = tx_msg_hdr.dlc;
    can_msg_tx.msg_id = tx_msg_hdr.mid;
    can_msg_tx.frame_fields.is_rtr = 0;
    can_msg_tx.frame_fields.is_29bit = 0;
    
    if(CAN_tx(can1, &can_msg_tx, 0))
    {
        u0_dbg_printf("tx - lat long\n");
        //LE.toggle(2);
    }
    
    
    float x = 0, y = 0, z = 0;
    //calculating the heading angle from the x,y,z values obtained from the compass
    hAngle = heading_angle(x, y, z);
    
    
    can_msg_t angle_msg;
    dbc_msg_hdr_t angle_msg_hdr;
    
    gps_angle.GPS_BEARING_angle = bAngle;
    gps_angle.GPS_HEADING_angle = hAngle;
    
    angle_msg_hdr = dbc_encode_GPS_BEARING_HEADING(angle_msg.data.bytes, &gps_angle);
    angle_msg.frame_fields.data_len = angle_msg_hdr.dlc;
    angle_msg.msg_id = angle_msg_hdr.mid;
    angle_msg.frame_fields.is_rtr = 0;
    angle_msg.frame_fields.is_29bit = 0;
    
    if(CAN_tx(can1, &angle_msg, 0))
    {
        u0_dbg_printf("tx - angles\n");
        //LE.toggle(2);
    }
    
    
    float degree = hAngle - bAngle;
    uint8_t dir_msg;
    
    //calculating the distance between the current location to the destination.
    float dist = distance(lat1, long1, lat2, long2);
    
    //   dir msg
    //      0 = full left
    //      1 = middle left
    //      2 = slight left
    //      3 = straight
    //      4 = slight right
    //      5 = middle right
    //      6 = full right
    //      7 = stop the motors
    
    //algorithm to decide how much the servo motor has to turn to make a perfect turning, depending on heading angle and bearing angle.
    if((0 < degree && degree <= 5) || (-360 <= degree && degree < -355))
    {
        dir_msg = 3;  //go straight
    }
    else if((5 < degree && degree <= 15) || (-355 <= degree && degree < -345))
    {
        dir_msg = 2;   // slight left :   5 degrees
    }
    else if((15 < degree && degree <= 60) || (-345 <= degree && degree < -300))
    {
        dir_msg = 1;   // mid left : 15 degrees
    }
    else if((60 < degree && degree <= 180) || (-300 <= degree && degree < -180))
    {
        dir_msg = 0;    // full left : 60 degrees
    }
    else if((355 < degree && degree <= 360) || (-5 <= degree && degree < 0))
    {
        dir_msg = 3;  //go straight
    }
    else if((345 < degree && degree <= 355) || (-15 <= degree && degree < -5))
    {
        dir_msg = 4;   // slight right :   5 degrees
    }
    else if((300 < degree && degree <= 345) || (-60 <= degree && degree < -15))
    {
        dir_msg = 5;   // mid right : 15 degrees
    }
    else if((180 < degree && degree <= 300) || (-180 <= degree && degree <= -60))
    {
        dir_msg = 6;    // full right : 60 degrees
    }
    else
    {
        dir_msg = 7;    // stop the motors, not able to calaculate correct angle to turn
    }
    
    
    
    // transmitting the direction msg to motor module.
    can_msg_t motor_msg;
    dbc_msg_hdr_t motor_msg_hdr;
    
    gps_dir.GPS_CAR_ANGLE_TURN_dirmsg = dir_msg;
    gps_dir.GPS_CAR_DISTANCE_to_destination = dist;
    
    motor_msg_hdr = dbc_encode_GPS_CAR_RUNNING(motor_msg.data.bytes, &gps_dir);
    motor_msg.frame_fields.data_len = motor_msg_hdr.dlc;
    motor_msg.msg_id = motor_msg_hdr.mid;
    motor_msg.frame_fields.is_rtr = 0;
    motor_msg.frame_fields.is_29bit = 0;
    
    if(CAN_tx(can1, &motor_msg, 0))
    {
        u0_dbg_printf("tx - dir & dist\n");
        //LE.toggle(2);
    }
    
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
    //  LE.toggle(4);
}

