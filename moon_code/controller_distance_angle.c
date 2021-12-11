#include <math.h>
#include <stdio.h>
#include "controller_distance_angle.h"
#include "kobukiSensorTypes.h"
#include "display.h"
//#include "tsl2561.h"

KobukiSensors_t sensors = {0};
// configure initial state
float period = 16 * 2; 

float ideal_distance = 0.5;
float ideal_tilt = M_PI_2;

float integ_dis_error = 0;
float integ_tilt_error = 0;
float prev_dis_error = 0;
float prev_tilt_error = 0;

float K_dis_p = 1;
float K_dis_i = 0;
float K_dis_d = 0;
float K_ang_p = 1;
float K_ang_i = 0;
float K_ang_d = 0;



// luminosity values
static float get_luminosity()
{
    // TODO: implement
    return 0;
}

// sparkfun distance value
static float get_distance()
{
    // TODO: implement
    return 0;
}

// camera value
static float get_camera()
{
    // TODO: implement
    return 0;
}

// utilize luminosity sensors to determine how tilting the moon is
static float calculate_tilt()
{
    // TODO: implement
    return M_PI_2;
}

// utilize distance sensor and/or luminosity sensors to measure distance from earth
static float calculate_distance()
{
    // TODO: implement
    return 0.5;
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
float pid_tilt(float ref, float input) {
	// calculate the error terms 
	float error = ref - input;
	integ_tilt_error = error + integ_tilt_error;
	float rate_error = error - prev_tilt_error;

	float output = K_ang_p * error + K_ang_i * integ_tilt_error + K_ang_d * rate_error;

	prev_tilt_error = error;
	
	return output;	
}; 

moon_state_t controller(moon_state_t state) {

	kobukiSensorPoll(&sensors);

	float angular_velocity = 2 * M_PI / period;
	float ideal_vl = angular_velocity * (ideal_distance - (axleLength / 2));
	float ideal_vr = angular_velocity * (ideal_distance + (axleLength / 2));
	//float error_distance = pid_dist(ideal_distance, distance);
	float error_tilt = pid_tilt(ideal_tilt, calculate_tilt());
	float error_dist = pid_dist(ideal_distance, calculate_distance());

	float wl_speed_f = ideal_vl + error_tilt * (axleLength / 2) / ((float) interval / 1000); //m/s
	float wr_speed_f = ideal_vr - error_tilt * (axleLength / 2) / ((float) interval / 1000); //m/s
	int16_t wl_speed = ceilf(wl_speed_f * 1000); //mm/s
	int16_t wr_speed = ceilf(wr_speed_f * 1000); //mm/s
	printf("wl_speed: %d, wr_speed: %d, error_tilt: %f\n", wl_speed, wr_speed, error_tilt);

	switch(state) {
    
	    case OFF: {
	      // transition logic
	      if (is_button_pressed(&sensors)) {
	        state = DRIVING;
	      } else {
	        // perform state-specific actions here
	        display_write("OFF", DISPLAY_LINE_0);
	        kobukiDriveDirect(0,0);
	        state = OFF;
	      }
	      break; // each case needs to end with break!
	    }

	    case DRIVING: {
	      // transition logic
	      if (is_button_pressed(&sensors)) {
	        state = OFF;
	      } else {
	        // perform state-specific actions here
	        display_write("DRIVING", DISPLAY_LINE_0);
			kobukiDriveDirect(wl_speed, wr_speed);
	        state = DRIVING;
	      }
	      break; // each case needs to end with break!
	    }
  	}

	return state;
}
