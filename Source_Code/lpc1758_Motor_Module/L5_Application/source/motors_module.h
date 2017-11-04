/*
 * motors_moddule.h
 *
 *  Created on: Oct 23, 2017
 *      Author: Jigar
 */

#ifndef L5_APPLICATION_SOURCE_MOTORS_MODULE_H_
#define L5_APPLICATION_SOURCE_MOTORS_MODULE_H_

typedef enum  {
    left_dir = 0,
    straight_dir,
    right_dir,
    no_of_directions
}motor_steer;

typedef enum  {
    forward_drive = 0,
    neutral_drive,
    reverse_drive,
    no_of_drive
}motor_drive;

bool servo_motor_steer_angle (motor_steer,int angle); // angle data-type to be  fixed
bool dc_motor_drive (motor_drive, int speed);

#endif /* L5_APPLICATION_SOURCE_MOTORS_MODULE_H_ */
