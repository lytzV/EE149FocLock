#include <math.h>
#include <stdio.h>
#include <time.h>
#include "controller.h"
#include "kobukiSensorTypes.h"
#include "display.h"
#include "tsl2561.h"

// configure initial state
KobukiSensors_t sensors = {0};
uint16_t previous_encoderL = 0;
uint16_t previous_encoderR = 0;
float distance = 0;
float prev_dis_error = 0;
float prev_ang_error = 0;
// struct timespec stop, start;
// clock_gettime(CLOCK_MONOTONIC_RAW, &start);
float K_dis_p = 1;
float K_dis_i = 0.5;
float K_dis_d = 0;
float K_ang_p = 1;
float K_ang_i = 0.5;
float K_ang_d = 0;

// measure encoder change and output average distance
// consider as feedback from last period to the PID model
float measure_distance(uint16_t current_encoder, uint16_t previous_encoder) {
  const float CONVERSION = 0.00065;

  float result = 0.0;
  if (current_encoder >= previous_encoder) {
    result = (float)current_encoder - (float)previous_encoder;
  } else {
    result = (float)current_encoder + (0xFFFF - (float)previous_encoder);
  }
  return result = result * CONVERSION;
}

// PID control logic for distance
float pid_dist(float ref, float input, float interval) {
	// calculate time difference for derivative calculation
	//clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
	//uint16_t interval = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_nsec - start.tv_nsec) / 1000;
	// calculate the error terms 
	float error = ref -input;
	float integ_error = integ_error + error * interval;
	float rate_error = (error - prev_dis_error)/interval;

	float output = K_dis_p * error + K_dis_i * integ_error + K_dis_d * rate_error;

	prev_dis_error = error;
	//clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	
	return output;	

}; 

// PID control logic for angle
float pid_ang(float ref, float input, float interval) {
	// calculate time difference for derivative calculation
	//clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
	//uint16_t interval = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_nsec - start.tv_nsec) / 1000;
	// calculate the error terms 
	float error = ref -input;
	float integ_error = integ_error + error * interval;
	float rate_error = (error - prev_dis_error)/interval;

	float output = K_ang_p * error + K_ang_i * integ_error + K_ang_d * rate_error;

	prev_ang_error = error;
	//clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	
	return output;	

}; 

moon_state_t controller(moon_state_t state, float luxVal, float distVal) {
	kobukiSensorPoll(&sensors);

	// read current distances
	float distanceL = measure_distance(sensors.leftWheelEncoder, previous_encoderL);
	float distanceR = measure_distance(sensors.rightWheelEncoder, previous_encoderR);
	printf("Distances: %f, %f\n", distanceL, distanceR);

	// update previous encoder values to current
	previous_encoderL = sensors.leftWheelEncoder;
	previous_encoderR = sensors.rightWheelEncoder; 

	distance = (distanceR + distanceL) / 2;
	char buf[16];
	snprintf(buf, 16, "Distance: %f", distance);
    printf("%s\n", buf);
    // display_write(buf, DISPLAY_LINE_0);

	float sensor_distance = 0.2; // TODO: connect vl531x
	float sensor_angle = 0.15; // reading from 2 lux sensors and compute angle

	float v = pid_dist(sensor_distance, distance, interval); 
	float w = pid_ang(sensor_angle, distance, interval); 

	int wl_speed = (v - w * axleLength / 2) / wheelR;
	int wr_speed = (v + w * axleLength / 2) / wheelR;

	switch (state)
    {

    case OFF:
    {
        // transition logic
        if (is_button_pressed(&sensors))
        {
            state = DRIVING;
            // display_write("DRIVE", DISPLAY_LINE_0);
        }
        else
        {
            // perform state-specific actions here
            kobukiDriveDirect(0, 0);
            state = OFF;
        }
        break;
    }

    case DRIVING:
    {
        // transition logic
        if (is_button_pressed(&sensors)){
            state = OFF;
            kobukiDriveDirect(0, 0);
            // display_write("OFF", DISPLAY_LINE_0);
        } else {
            // do not allow super fast speeds
			if (wl_speed > 30 || wr_speed > 30) {
				kobukiDriveDirect(wl_speed, wr_speed);
			} else {
				kobukiDriveDirect(wl_speed, wr_speed);
			} // update to wheel speed
			printf("Speeds: %d, %d\n", wl_speed, wr_speed);
        }
        break;
    }
    
	}

	return state;
}
