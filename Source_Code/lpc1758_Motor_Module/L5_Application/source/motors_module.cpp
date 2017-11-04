/*
 * motors_module.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: Jigar
 */

#include "motors_module.h"
#include "_can_dbc/generated_can.h"
#include "lpc_pwm.hpp"
#include "io.hpp"
#include "gpio.hpp"
#include "utilities.h"



PWM servo_motors(PWM::pwm1, 9.915);
PWM dc_motors(PWM::pwm2, 9.915);

bool servo_motor_steer_angle (motor_steer direction,int angle) // angle data-type to be  fixed
{
//    bool ret_status = 1;

    switch (direction){
        case left_dir       : servo_motors.set(angle);break;
        case right_dir      : servo_motors.set(angle);break;
        case straight_dir   : servo_motors.set(angle); break;
        default             : {
                                servo_motors.set(angle);
                                return false;
                              }
        }

    return true;
}
bool dc_motor_drive (motor_drive drive, int speed)
{
//    bool ret_status = 1;
    switch (drive){
        case forward_drive  : dc_motors.set(speed);break;
        case neutral_drive  : dc_motors.set(speed);break;
        case reverse_drive  : dc_motors.set(speed); break;
        default             : {
                                dc_motors.set(speed);
                                return false;
                              }
        }

    return true;
}


