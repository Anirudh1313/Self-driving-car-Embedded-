/*
 * gps_module.h
 *
 *  Created on: Oct 31, 2017
 *      Author: sushm
 */

#ifndef L5_APPLICATION_SOURCE_GPS_MODULE_H_
#define L5_APPLICATION_SOURCE_GPS_MODULE_H_

float bearing_angle(float lat1, float long1, float lat2, float long2);

float heading_angle(float x, float y, float z);

float distance(float lat1, float long1, float lat2, float long2);




#endif /* L5_APPLICATION_SOURCE_GPS_MODULE_H_ */
