typedef enum
{
    OFF,
    DRIVING,
} moon_state_t;

static float measure_distance(uint16_t current_encoder, uint16_t previous_encoder);

moon_state_t controller(moon_state_t state);