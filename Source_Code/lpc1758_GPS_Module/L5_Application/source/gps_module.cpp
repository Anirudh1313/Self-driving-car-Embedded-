/*
 * gps_module.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: sushm
 */



/*

 * gps_module.cpp

 *

 *  Created on: Oct 25, 2017

 *      Author: krish

 */

#include "gps_module.h"
#include <math.h>


float bearing_angle(float lat1, float long1, float lat2, float long2)
{
// lat1 = lat1*3.14159265/180;

// long1 = long1*3.14159265/180;

// lat2 = lat2*3.14159265/180;

// long2 = long2*3.14159265/180;


float long_diff = long2*3.14159265/180 - long1*3.14159265/180;

float x = cos(lat2*3.14159265/180) * sin(long_diff);

float y = cos(lat1*3.14159265/180) * sin(lat2*3.14159265/180) - sin(lat1*3.14159265/180)*cos(lat2*3.14159265/180)*cos(long_diff);



//double x = sin(90*3.14159265/180);

float bearing = atan2(x,y);


return bearing*180/3.14159265;

}



float heading_angle(float x, float y, float z)
{
	return x+y+z; //returning just
}



float distance(float lat1, float long1, float lat2, float long2)
{

	float radius = 6371000;   //in metres



	//converting degrees to radians

	//calculating the diff of latitudes and longitudes

	float long_diff = long2*3.14159265/180 - long1*3.14159265/180;

	float lat_diff = lat2*3.14159265/180 - lat1*3.14159265/180;


	lat1 = lat1*3.14159265/180;

	long1 = long1*3.14159265/180;

	lat2 = lat2*3.14159265/180;

	long2 = long2*3.14159265/180;


	float a = sin(lat_diff/2)*sin(lat_diff/2) + cos(lat1)*cos(lat2)*sin(long_diff/2)*sin(long_diff/2);
	float c = 2*atan2(sqrt(a), sqrt(1-a));
	float distance = radius*c;



	return distance;

}

