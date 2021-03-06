///*
// *     SocialLedge.com - Copyright (C) 2013
// *
// *     This file is part of free software framework for embedded processors.
// *     You can use it and/or distribute it as long as this copyright header
// *     remains unmodified.  The code is free for personal use and requires
// *     permission to use in a commercial product.
// *
// *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// *
// *     You can reach the author of this software at :
// *          p r e e t . w i k i @ g m a i l . c o m
// */
//
///**
// * @file
// * This contains the period callback functions for the periodic scheduler
// *
// * @warning
// * These callbacks should be used for hard real-time system, and the priority of these
// * tasks are above everything else in the system (above the PRIORITY_CRITICAL).
// * The period functions SHOULD NEVER block and SHOULD NEVER run over their time slot.
// * For example, the 1000Hz take slot runs periodically every 1ms, and whatever you
// * do must be completed within 1ms.  Running over the time slot will reset the system.
// */
//
//#include <stdint.h>
//#include "io.hpp"
//#include "periodic_callback.h"
//
//#include <stdint.h>
//#include <stdio.h>
//#include "io.hpp"
//#include "periodic_callback.h"
//#include "eint.h"
//#include "printf_lib.h"
//#include "gpio.hpp"
//#include "utilities.h"
//#include "can.h"
//#include "_can_dbc/generated_can.h"
////#include "uart3.hpp"
//
//
///// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
//const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
//
///**
// * This is the stack size of the dispatcher task that triggers the period tasks to run.
// * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
// * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
// * printf inside these functions, you need about 1500 bytes minimum
// */
//const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);
//
////Uart3 &u3 = Uart3::getInstance();
///********************/
////void switch_ON(){
////    flag = true;
//////    xSemaphoreGiveFromISR(binary_sem,0);
////}
////
////void switch_OFF(){
////    flag = false;
//////    xSemaphoreGiveFromISR(binary_not, 0);
////}
///********************/
//
//
///// Called once before the RTOS is started, this is a good place to initialize things once
//bool period_init(void)
//{
////    u3.init(9600, 80, 80);
//    CAN_init(can1, 100, 10, 10, NULL, NULL);
//    CAN_bypass_filter_accept_all_msgs();
//    CAN_reset_bus(can1);
//    return true; // Must return true upon success
//}
//
///// Register any telemetry variables
//bool period_reg_tlm(void)
//{
//    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
//    return true; // Must return true upon success
//}
//
//
//
//// The MIA functions require that you define the:
////   - Time when the handle_mia() functions will replace the data with the MIA
////   - The MIA data itself (ie: MOTOR_STATUS__MIA_MSG)
//
//
//const uint32_t            SENSE_LIGHT__MIA_MS = 3000;
//const SENSE_LIGHT_t       SENSE_LIGHT__MIA_MSG = { 17 };
//
//
////const uint32_t            SENSOR_SONARS_m1__MIA_MS = 3000;
////const SENSOR_SONARS_m1_t  SENSOR_SONARS_m1__MIA_MSG = { 0 };
////const uint32_t            MOTOR_STATUS__MIA_MS = 3000;
////const MOTOR_STATUS_t      MOTOR_STATUS__MIA_MSG = { 0 };
//
//// For the sake of example, we use global data storage for messages that we receive
//SENSE_LIGHT_t sense_request = { 0 };
//
//
////MOTOR_STATUS_t motor_status_msg = { 0 };
//
///**
// * Below are your periodic functions.
// * The argument 'count' is the number of times each periodic task is called.
// */
//
//void period_1Hz(uint32_t count)
//{
//    //while(1);
//    if(CAN_is_bus_off(can1) == 1)    CAN_reset_bus(can1);
////    LE.toggle(1);
//}
//
//void period_10Hz(uint32_t count)
//{
////    u0_dbg_printf("received - first");
//
////    char *c = new char[1];
////    if(u3.getChar(c, 70))
////    {
////        printf("%c", *c);
////    }
//
////    can_msg_t ms;
////    ms.msg_id = 0x111;
////    ms.frame_fields.data_len = 2;
////    ms.frame_fields.is_29bit = 0;
////    ms.frame_fields.is_rtr = 0;
////
////    if (SW.getSwitch(2) && !CAN_is_bus_off(can1)){
////        ms.data.qword = 0xAA;
////        bool m = CAN_tx( can1, &ms, 0);
////        if (m)
////        u0_dbg_printf("HALF success");
////        else u0_dbg_printf(" NOT SENT ");
////    }
////    else {
////        if(CAN_is_bus_off(can1) == 1)    CAN_reset_bus(can1);
////        ms.data.qword = 0x00;
////        CAN_tx( can1, &ms, 0);
////    }
////    LE.toggle(2);
//
//    can_msg_t can_msg;
//
//    while(CAN_rx(can1, &can_msg, 0)){
//        dbc_msg_hdr_t can_msg_hdr;
//        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
//        can_msg_hdr.mid = can_msg.msg_id;
//
//        if (dbc_decode_SENSE_LIGHT(&sense_request, can_msg.data.bytes, &can_msg_hdr)){
//            u0_dbg_printf("received \n");
//            u0_dbg_printf("%x  \n", can_msg.data.dwords[0]);
//        }
//    }
//
//    if (dbc_handle_mia_SENSE_LIGHT(&sense_request, 100)){
//        u0_dbg_printf("%x \n", SENSE_LIGHT__MIA_MSG);
//        LE.toggle(2);
//        delay_ms(15);
//        LE.off(2);
//    }
//}
//
//void period_100Hz(uint32_t count)
//{
//    LE.toggle(3);
//}
//
//// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
//// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
//void period_1000Hz(uint32_t count)
//{
//    LE.toggle(4);
//}



















///*
// *     SocialLedge.com - Copyright (C) 2013
// *
// *     This file is part of free software framework for embedded processors.
// *     You can use it and/or distribute it as long as this copyright header
// *     remains unmodified.  The code is free for personal use and requires
// *     permission to use in a commercial product.
// *
// *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// *
// *     You can reach the author of this software at :
// *          p r e e t . w i k i @ g m a i l . c o m
// */
//
///**
// * @file
// * This contains the period callback functions for the periodic scheduler
// *
// * @warning
// * These callbacks should be used for hard real-time system, and the priority of these
// * tasks are above everything else in the system (above the PRIORITY_CRITICAL).
// * The period functions SHOULD NEVER block and SHOULD NEVER run over their time slot.
// * For example, the 1000Hz take slot runs periodically every 1ms, and whatever you
// * do must be completed within 1ms.  Running over the time slot will reset the system.
// */
//
//#include <stdint.h>
//#include <stdio.h>
//#include "io.hpp"
//#include "periodic_callback.h"
//#include "gpio.hpp"
//#include "eint.h"
//#include "can.h"
//#include <string.h>
//#include "printf_lib.h"
//#include "_can_dbc/generated_can.h"
//#include "uart2.hpp"
//
////
////bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
////{
////    can_msg_t can_msg = { 0 };
////    can_msg.msg_id                = mid;
////    can_msg.frame_fields.data_len = dlc;
////    memcpy(can_msg.data.bytes, bytes, dlc);
////
////    return CAN_tx(can1, &can_msg, 0);
////}
//
//Uart2& bluetooth = Uart2::getInstance();
//
//
///// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
//const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
//
///**
// * This is the stack size of the dispatcher task that triggers the period tasks to run.
// * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
// * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
// * printf inside these functions, you need about 1500 bytes minimum
// */
//const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);
//
///// Called once before the RTOS is started, this is a good place to initialize things once
//bool period_init(void)
//{
////    CAN_init(can1,100, 10, 10, NULL, NULL);
////       CAN_bypass_filter_accept_all_msgs();
////       CAN_reset_bus(can1);
//    bluetooth.init(38400, 100, 100);
//    return true; // Must return true upon success
//}
//
///// Register any telemetry variables
//bool period_reg_tlm(void)
//{
//    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
//    return true; // Must return true upon success
//}
//
//
///**
// * Below are your periodic functions.
// * The argument 'count' is the number of times each periodic task is called.
// */
//
//void period_1Hz(uint32_t count)
//{
////    if (CAN_is_bus_off(can1))   CAN_reset_bus(can1);
////    LE.toggle(1);
//    char *c = new char[6];
//
//    if(bluetooth.getRxQueueSize() > 0){
//        while(*c!='\0'){
//
//            bluetooth.getChar(c);
//            printf("%c", *c);
//
//        }
//    }
//}
//
//void period_10Hz(uint32_t count)
//{
//    int p = (int) TS.getCelsius();
//    char data[15];
//    sprintf(data, "%d", p);
//    char *ptr = data;
//    while (*ptr != '\0'){
//        bluetooth.putChar(*ptr);
//        ptr++;
//    }
//    bluetooth.putChar('\0');
//
//
//    //LIGHT_READING_t light_reading;
////        SENSE_LIGHT_t sense_light_cmd = { 0 };
////        sense_light_cmd.do_work = 4;
////
////        if(dbc_encode_and_send_SENSE_LIGHT(&sense_light_cmd))
////            u0_dbg_printf("Transmitted");
//
//    //    can_msg_t can_msg;
//    //    while(CAN_rx(can1, &can_msg, 0))
//    //    {
//    //        dbc_msg_hdr_t can_msg_hdr;
//    //        can_msg_hdr.mid = can_msg.msg_id;
//    //        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
//    //
//    //        dbc_decode_LIGHT_READING(&light_reading, can_msg.data.bytes, &can_msg_hdr);
//    //
//    //        if(dbc_handle_mia_LIGHT_READING(&light_reading, 10))
//
//        //            LE.on(2);
//    //    }
//
//    //LE.toggle(2);
//}
//
//void period_100Hz(uint32_t count)
//{
//    LE.toggle(3);
//}
//
//// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
//// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
//void period_1000Hz(uint32_t count)
//{
//    LE.toggle(4);
//}



































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
#include "gpio.hpp"
#include "eint.h"
#include "can.h"
#include <string.h>
#include "printf_lib.h"
#include "_can_dbc/generated_can.h"
#include "uart2.hpp"

//
//bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8])
//{
//    can_msg_t can_msg = { 0 };
//    can_msg.msg_id                = mid;
//    can_msg.frame_fields.data_len = dlc;
//    memcpy(can_msg.data.bytes, bytes, dlc);
//

//    return CAN_tx(can1, &can_msg, 0);
//}

Uart2& bluetooth = Uart2::getInstance();


/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);

/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
//    CAN_init(can1,100, 10, 10, NULL, NULL);
//       CAN_bypass_filter_accept_all_msgs();
//       CAN_reset_bus(can1);
    bluetooth.init(9600, 100, 100);
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
//    if (CAN_is_bus_off(can1))   CAN_reset_bus(can1);
     LE.toggle(1);





}

void period_10Hz(uint32_t count)
{




//    char* c = "9";
//    if(bluetooth.putChar(*c))
//    u0_dbg_printf("\t transmit");



    //LIGHT_READING_t light_reading;
//        SENSE_LIGHT_t sense_light_cmd = { 0 };
//        sense_light_cmd.do_work = 4;
//
//        if(dbc_encode_and_send_SENSE_LIGHT(&sense_light_cmd))
//            u0_dbg_printf("Transmitted");

    //    can_msg_t can_msg;
    //    while(CAN_rx(can1, &can_msg, 0))
    //    {
    //        dbc_msg_hdr_t can_msg_hdr;
    //        can_msg_hdr.mid = can_msg.msg_id;
    //        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
    //
    //        dbc_decode_LIGHT_READING(&light_reading, can_msg.data.bytes, &can_msg_hdr);
    //
    //        if(dbc_handle_mia_LIGHT_READING(&light_reading, 10))

        //            LE.on(2);
    //    }

    //LE.toggle(2);
}

void period_100Hz(uint32_t count)
{

    //float p = TS.getCelsius();
     float p1= 54.893241;
     float p2 = -132.955443;

     char s[50];
     sprintf(s, "#%f@%f", p1, p2);
     u0_dbg_printf("%s", s);

     char *ptr = s;
     while (*ptr != '\0'){
         if(bluetooth.putChar(*ptr))
         u0_dbg_printf("\n transmit");
         ptr++;
     }
     bluetooth.putChar('\n');

    char *c = new char[10];

    if(bluetooth.getRxQueueSize() > 0)
    {
       bluetooth.getChar(c);
     if(*c == '*')
     {
         bluetooth.getChar(c);
         u0_dbg_printf("\n %c", *c);
     }
 }
   // LE.toggle(3);
//    char *c = new char[2];
//    if(bluetooth.getRxQueueSize() > 0){
//
//           bluetooth.getChar(c);
//           u0_dbg_printf("first %c",*c);
//               if(*c=='*')
//               {
//                   bluetooth.getChar(c);
//                   u0_dbg_printf("second %c",*c);
//                 if(*c=='1')
//                 {
//                     u0_dbg_printf("3");
//                       bluetooth.getChar(c);
//
//                     u0_dbg_printf("Receive data from android");
//                     u0_dbg_printf("\n %c", *c);
//
//                 }
//                 else if(*c == '0')
//                 {
//                      u0_dbg_printf("send message to driver to stop");
//                 }
//               }
//           }
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
    LE.toggle(4);
}
