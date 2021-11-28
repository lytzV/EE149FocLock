#include <math.h>
#include <stdio.h>
#include "controller.h"
#include "kobukiSensorTypes.h"
#include "display.h"

// sensors
KobukiSensors_t sensors = {0};

// variables (input)
float sensor_lum_front = 0;
float sensor_lum_back = 0;
float sensor_distance = 0;
float sensor_camera = 0;
// variables (describe current state)
float tilt = 0;     // negative -> driving outward, positive -> driving inward
float distance = 0; // between moon and earth
int zone = 0;       // currently not used, use color to determine which part of trajectory
// variables (output)
float wheel_left = 0;  // left wheel speed
float wheel_right = 0; // right wheel speed
// constants
int driving_speed = 10; // kobuki speed unit
int changing_speed = 1;
int desired_distance = 50;  // cm
int distance_tolerance = 2; // cm
int desired_tilt = 0;       // arbitrary unit
int tilt_tolerance = 1;     // arbitrary unit

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
    return 0;
}

// utilize distance sensor and/or luminosity sensors to measure distance from earth
static float calculate_distance()
{
    // TODO: implement
    return 50;
}

// utilize 6-color LED to determine which part of the trajectory the moon is at
static int determine_zone()
{
    // TODO: implement
    return 0;
}

moon_state_t controller(moon_state_t state)
{
    // read sensors from robot
    kobukiSensorPoll(&sensors);
    sensor_lum_front = get_luminosity();
    sensor_lum_back = get_luminosity();
    sensor_distance = get_distance();
    sensor_camera = get_camera();
    // calculate values
    tilt = measure_tilt();
    distance = measure_distance();
    zone = determine_zone();

    // delay before continuing
    // Note: removing this delay will make responses quicker, but will result
    //  in printf's in this loop breaking JTAG
    //nrf_delay_ms(1);
    // char buf[16];
    // snprintf(buf, 16, "%f", distance);
    // display_write(buf, DISPLAY_LINE_1);

    // handle states
    switch (state)
    {

    case OFF:
    {
        // transition logic
        if (is_button_pressed(&sensors))
        {
            state = DRIVING;
            wheel_left = driving_speed;
            wheel_right = driving_speed;
        }
        else
        {
            // perform state-specific actions here
            display_write("OFF", DISPLAY_LINE_0);
            kobukiDriveDirect(0, 0);
            state = OFF;
        }
        break;
    }

    case DRIVING:
    {
        // transition logic
        if (is_button_pressed(&sensors))
        {
            state = OFF;
        }
        else if (distance < desired_distance - distance_tolerance || distance > desired_distance + distance_tolerance)
        {
            // TODO: add another state to adjust to desired distance
        }
        else
        {
            if (tilt < desired_tilt - tilt_tolerance)
            {
                // TODO: driving outward, either increase left (out) wheel speed, or decrease right wheel speed
            }
            else if (tilt > desired_tilt + tilt_tolerance)
            {
                // TODO: driving inward, either decrease left (out) wheel speed, or increase right wheel speed
            }
            else
            {
                // keep driving as is
            }
            // perform state-specific actions here
            display_write("DRIVING", DISPLAY_LINE_0);
            kobukiDriveDirect(wheel_left, wheel_right);
            state = DRIVING;
        }
        break;
    }
    }

    // add other cases here
    return state;
}