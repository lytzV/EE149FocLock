#include "controller_distance_angle.h"

//#include "tsl2561.h"

KobukiSensors_t sensors = {0};

float period = 66;
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

// sensor readings that are passed into this controller
float luminosity;
float distance;
uint16_t pixy;

// utilize luminosity sensors to determine how tilting the moon is
static float calculate_tilt() {
  // TODO: implement
  float proportional = distance * 0.00714 - 0.16095;
  float side_length = pixy * proportional;
  double angle = atan(side_length / distance);
  return angle;
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
// center tilt == 158.
uint16_t tilt_threshold = 20;
bool adjusting = false;
int16_t wl_speed_1 = 0;
int16_t wr_speed_1 = 0;

moon_state_t controller(moon_state_t state, float dist, uint16_t pix) {
  int16_t wl_speed;
  int16_t wr_speed;
  distance = dist;
  pixy = pix;
  // ONLY consider errors and adjust wheel speeds in driving state
  if (state == DRIVING) {
    float angular_velocity = 2 * M_PI / period;
    float ideal_vl = angular_velocity * (ideal_distance - (axleLength / 2));
    float ideal_vr = angular_velocity * (ideal_distance + (axleLength / 2));

    if (mode == 0) {
      float error_tilt = 0;
      if (fabs(calculate_tilt()) <= 5 / 180 * M_PI) {
        float error_tilt = pid_tilt(ideal_tilt, calculate_tilt());
      }
      float error_dist = pid_dist(ideal_distance, distance);

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
      if (adjusting == true) {
        if (158 - tilt_threshold < pixy && pixy < 158 + tilt_threshold) {
          adjusting = false;
          wl_speed_1 = ceilf(ideal_vl * 1000);
          wr_speed_1 = ceilf(ideal_vr * 1000);
        } else {
          wl_speed_1 = 40;
          wr_speed_1 = -40;
        }
      } else {
        if (158 - tilt_threshold < pixy && pixy < 158 + tilt_threshold) {
          adjusting = false;
        } else if (158 + tilt_threshold < pixy && pixy < 250) {
          wl_speed_1 += 1;
        } else if (70 < pixy && pixy < 158 - tilt_threshold) {
          wl_speed_1 -= 1;
        } else {
          adjusting = true;
        }
      }
      wl_speed = wl_speed_1;
      wr_speed = wr_speed_1;
      printf("wl_speed: %d, wr_speed: %d, pixy: %u\n", wl_speed, wr_speed, pixy);
    }
  }

  kobukiSensorPoll(&sensors);

  switch (state) {
    case OFF: {
      // transition logic
      if (is_button_pressed(&sensors)) {
        printf("OFF TO DRIVING");
        state = DRIVING;
      } else {
        // perform state-specific actions here
        //("OFF", DISPLAY_LINE_0);
        kobukiDriveDirect(0, 0);
        printf("OFF TO OFF");
        state = OFF;
      }
      break; // each case needs to end with break!
    }

    case DRIVING: {
      // transition logic
      if (is_button_pressed(&sensors)) {
        printf("DRIVING TO OFF");
        state = OFF;
      } else {
        // perform state-specific actions here
        //display_write("DRIVING", DISPLAY_LINE_0);
        char buf[16];
        //snprintf(buf, 16, "%d", pixy);
        //display_write(buf, DISPLAY_LINE_1);
        kobukiDriveDirect(wl_speed, wr_speed);
        printf("DRIVING TO DRIVING");
        state = DRIVING;
      }
      break; // each case needs to end with break!
    }
  }

  return state;
}
