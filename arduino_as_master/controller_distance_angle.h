#include <stdint.h>
#include "display.h"
#include "kobukiSensorTypes.h"
#include "display.h"
#include "kobukiSensorTypes.h"

typedef enum {
  OFF,
  DRIVING,
} moon_state_t;

// constant values for hardware
static float wheelR = 0.035;        // wheel radius
static float axleLength = 0.23;     // distance between wheels
static float ticksPerRot = 2578.33; // ticks per rotation for encoders
static float Ts = 0.01;             // sample time
static int interval = 2;           // in ms

moon_state_t controller(moon_state_t state, float distance, uint16_t tilt);
