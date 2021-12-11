#include <math.h>
#include <stdio.h>
#include "controller.h"
#include "kobukiSensorTypes.h"
#include "display.h"
#include "tsl2561.h"
#include "nrf_delay.h"

// configure initial state
KobukiSensors_t sensors = {0};
uint16_t previous_encoderL = 0;
uint16_t previous_encoderR = 0;
float distance = 0;
float angle = 0;
float integ_dis_error = 0;
float integ_angle_error = 0;

float prev_dis_error = 0;
float prev_ang_error = 0;
float K_dis_p = 1;
float K_dis_i = 0;
float K_dis_d = 0;
float K_ang_p = 1;
float K_ang_i = 0;
float K_ang_d = 0;

// measure encoder change and output average distance
// consider as feedback from last period to the PID model
float measure_distance(uint16_t current_encoder, uint16_t previous_encoder) {
  const float CONVERSION = 0.0000855;

  float result = 0.0;
  if (current_encoder >= previous_encoder) {
    result = (float)current_encoder - (float)previous_encoder;
  } else {
    result = (float)current_encoder + (0xFFFF - (float)previous_encoder);
  }
  return result = result * CONVERSION;
}

// PID control logic for distance
float pid_dist(float ref, float input) {
	// calculate the error terms 
	float error = ref - input;
	integ_dis_error = error + integ_dis_error;
	float rate_error = error - prev_dis_error;

	float output = K_dis_p * error + K_dis_i * integ_dis_error + K_dis_d * rate_error;

	prev_dis_error = error;
	
	return output;	

}; 

// PID control logic for angle
float pid_ang(float ref, float input) {
	// calculate the error terms 
	float error = ref - input;
	integ_angle_error = error + integ_angle_error;
	float rate_error = error - prev_ang_error;

	float output = K_ang_p * error + K_ang_i * integ_angle_error + K_ang_d * rate_error;

	prev_ang_error = error;
	
	return output;	

}; 

moon_state_t controller(moon_state_t state, float luxVal, float distVal) {
	integ_dis_error = 0;
	integ_angle_error = 0;
	float sensor_distance = 1; // TODO: connect vl531x
	float sensor_angle = 0; // reading from 2 lux sensors and compute angle
	prev_dis_error = 0;
	prev_ang_error = 0;
	printf("%f\n", fabs(distance - sensor_distance));
	printf("%f\n", fabs(distance - sensor_distance)/sensor_distance);
	printf("%f\n", fabs(angle - sensor_angle)/(sensor_angle+0.00001));

	while(fabs(distance - sensor_distance)/sensor_distance > 0.1 || fabs(angle - sensor_angle)/(sensor_angle+0.00001) > 0.1){
		kobukiSensorPoll(&sensors);

		// read current distances
		float distanceL = measure_distance(sensors.leftWheelEncoder, previous_encoderL);
		float distanceR = measure_distance(sensors.rightWheelEncoder, previous_encoderR);
		printf("Encoder Value: %d\n", sensors.leftWheelEncoder);
		printf("Distances: %f, %f\n", distanceL, distanceR);
		distance = (distanceR + distanceL) / 2;
		char buf[16];
		snprintf(buf, 16, "Total distance: %f", distance);
	    printf("%s\n", buf);
	    angle = (distanceR - distanceL) / axleLength;
	    // display_write(buf, DISPLAY_LINE_0);

		

		
		float v = pid_dist(sensor_distance, distance);
		float w = pid_ang(sensor_angle, angle);
		printf("V: %f, W: %f\n", v, w);

		float wl_speed_f = (v - w * axleLength / 2) / wheelR;
		float wr_speed_f = (v + w * axleLength / 2) / wheelR;
		printf("wl_speed_f: %f, wr_speed_f: %f\n", wl_speed_f, wr_speed_f);
		int16_t wl_speed = ceilf(wl_speed_f);
		int16_t wr_speed = ceilf(wr_speed_f);
		kobukiDriveDirect(wl_speed, wr_speed);
		// printf("wl_speed: %d, wr_speed: %d\n", wl_speed, wr_speed);

		// switch (state){

		//     case OFF:
		//     {
		//         // transition logic
		//         if (is_button_pressed(&sensors))
		//         {
		//             state = DRIVING;
		//             // display_write("DRIVE", DISPLAY_LINE_0);
		//         }
		//         else
		//         {
		//             // perform state-specific actions here
		//             kobukiDriveDirect(0, 0);
		//             state = OFF;
		//         }
		//         break;
		//     }

		//     case DRIVING:
		//     {
		//         // transition logic
		//         if (is_button_pressed(&sensors)){
		//             state = OFF;
		//             kobukiDriveDirect(0, 0);
		//             // display_write("OFF", DISPLAY_LINE_0);
		//         } else {
		//             // do not allow super fast speeds
					
		// 			kobukiDriveDirect(wl_speed, wr_speed);
					
		// 			printf("Speeds: %d, %d\n", wl_speed, wr_speed);
		//         }
		//         break;
		//     }
		    
		// 	}
			//nrf_delay_ms(50);

		}
	

	// update previous encoder values to current
	previous_encoderL = sensors.leftWheelEncoder;
	previous_encoderR = sensors.rightWheelEncoder; 

	

	return state;
}
