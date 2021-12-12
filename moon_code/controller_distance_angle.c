#include "controller_distance_angle.h"
#include "display.h"
#include "kobukiSensorTypes.h"
#include <math.h>
#include <stdio.h>
//#include "tsl2561.h"

KobukiSensors_t sensors = {0};
// configure initial state
float period = 16 * 2;

float period = 16 * 2 * M_PI;
float ideal_distance = 0.5;
float ideal_tilt = 0;

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
static float get_luminosity() {
  // TODO: implement
  return 0;
}

// sparkfun distance value
static float get_distance() {
  // TODO: implement
  return 1;
}

// camera value
static float get_camera() {
  // TODO: implement
  return 0;
}

// utilize luminosity sensors to determine how tilting the moon is
static float calculate_tilt() {
  // TODO: implement
  float proportional = get_distance() * 0.00714 - 0.16095;
  float side_length = get_camera() * proportional;
  double angle = atan(side_length / get_distance());
  return angle;
}

// utilize distance sensor and/or luminosity sensors to measure distance from earth
static float calculate_distance() {
  return 1;
  // TODO: implement
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

// 0 == PID. 1 == heuristic.
int mode = 1;
int tilt_threshold = 10;
int16_t wl_speed_1 = 0;
int16_t wr_speed_1 = 0;

moon_state_t controller(moon_state_t state, float distance, uint16_t tilt) {

  // ONLY consider errors and adjust wheel speeds in driving state
  if (state == DRIVING) {
    float angular_velocity = 2 * M_PI / period;
    float ideal_vl = angular_velocity * (ideal_distance - (axleLength / 2));
    float ideal_vr = angular_velocity * (ideal_distance + (axleLength / 2));

    int16_t wl_speed;
    int16_t wr_speed;
    if (mode == 0) {
      float error_tilt = 0;
      if (fabs(calculate_tilt()) <= 5 / 180 * M_PI) {
        float error_tilt = pid_tilt(ideal_tilt, calculate_tilt());
      }
      float error_dist = pid_dist(ideal_distance, get_distance());

      float wl_speed_f = ideal_vl + error_tilt * (axleLength / 2) / ((float)interval / 1000); //m/s
      float wr_speed_f = ideal_vr - error_tilt * (axleLength / 2) / ((float)interval / 1000); //m/s
      wl_speed = ceilf(wl_speed_f * 1000);                                                    //mm/s
      wr_speed = ceilf(wr_speed_f * 1000);                                                    //mm/s
      printf("wl_speed: %d, wr_speed: %d, error_tilt: %f\n", wl_speed, wr_speed, error_tilt);
    } else {
      if (wl_speed_1 == 0 || wr_speed_1 == 0) {
        wl_speed_1 = ceilf(ideal_vl * 1000);
        wr_speed_1 = ceilf(ideal_vr * 1000);
      }
      if (tilt > 158 + tilt_threshold) {
        wl_speed_1 += 1;
        wr_speed_1 -= 2;
      } else if (tilt < 158 - tilt_threshold) {
        wl_speed_1 -= 1;
        wr_speed_1 += 2;
      }
      wl_speed = wl_speed_1;
      wr_speed = wr_speed_1;
      printf("wl_speed: %d, wr_speed: %d, tilt: %u\n", wl_speed, wr_speed, tilt);
    }
  }

  kobukiSensorPoll(&sensors);

  switch (state) {
    case OFF: {
      // transition logic
      if (is_button_pressed(&sensors)) {
        state = DRIVING;
      } else {
        // perform state-specific actions here
        display_write("OFF", DISPLAY_LINE_0);
        kobukiDriveDirect(0, 0);
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
