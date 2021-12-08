// constant parameters for hardware
static float wheelR = 0.035; // wheel radius
static float axleLength = 0.23; // distance between wheels
static float ticksPerRot = 2578.33; // ticks per rotation for encoders
static float Ts = 0.01; // sample time
static int interval = 5; // in ms

// method to update driving trajactory with sensor inputs only
void controller(void);