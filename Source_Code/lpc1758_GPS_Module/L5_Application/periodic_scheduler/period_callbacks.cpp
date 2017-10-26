#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "uart3.hpp"
#include "can.h"
#include "printf_lib.h"
#include "_can_dbc/generated_can.h"

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
can_t can_1 = can1;
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
    LE.toggle(1);
    if(CAN_is_bus_off(can_1))
    {
    CAN_reset_bus(can_1);
    u0_dbg_printf("buss is off, just reseted! \n");
    }
}
void period_10Hz(uint32_t count)
{
    //transmitting current location reading obtained from the gps sensor.
    can_msg_t can_msg_tx;
    dbc_msg_hdr_t tx_msg_hdr;
    //srand((unsigned) time(0));
    //uint32_t rmin = rand() % 100;
    gps_curr.GPS_CURRENT_LOCATION_latitude = 111111;
    gps_curr.GPS_CURRENT_LOCATION_longitude = 1222222;
    tx_msg_hdr = dbc_encode_GPS_CURRENT_LOCATION(can_msg_tx.data.bytes, &gps_curr);
    can_msg_tx.frame_fields.data_len = tx_msg_hdr.dlc;
    can_msg_tx.msg_id = tx_msg_hdr.mid;
    can_msg_tx.frame_fields.is_rtr = 0;
    can_msg_tx.frame_fields.is_29bit = 0;
    if(CAN_tx(can1, &can_msg_tx, 4))
    {
        //u0_dbg_printf("tx\n");
        //LE.toggle(2);
    }
    //receiving the destination location readings obtained
}
void period_100Hz(uint32_t count)
{
    LE.toggle(3);

    can_msg_t can_msg;
    if(CAN_rx(can_1, &can_msg, 2))
    {
    dbc_msg_hdr_t msg_hdr;
    msg_hdr.dlc = can_msg.frame_fields.data_len;
    msg_hdr.mid = can_msg.msg_id;
    dbc_decode_GPS_DESTINATION(&gps_des, can_msg.data.bytes, &msg_hdr);
    u0_dbg_printf("latitude: %f  &  longitude: %f \n",gps_des.GPS_DESTINATION_latitude, gps_des.GPS_DESTINATION_longitude);
    }
    // else
    // {
    //  u0_dbg_printf("count: %d\n", motor_status.mia_info.mia_counter_ms);
    // }
    if(dbc_handle_mia_GPS_DESTINATION(&gps_des, 10))
    {
    LE.toggle(1);
    LE.toggle(2);
    LE.toggle(3);
    LE.toggle(4);
    u0_dbg_printf("latitude-mia: %f  &  longitude-mia: %f \n",gps_des.GPS_DESTINATION_latitude/10000, gps_des.GPS_DESTINATION_longitude/10000);
    }
}
// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
    LE.toggle(4);
}
