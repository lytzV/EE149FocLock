// Sensor Reading 
// Read I2C from Lux Sensor 

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "app_util.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "buckler.h"
#include "nrf_twi_mngr.h"

// I2C manager
NRF_TWI_MNGR_DEF(twi_mngr_instance, 5, 0);


int main(void) {
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");

  // initialize the TWIM
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = BUCKLER_SENSORS_SCL;
  i2c_config.sda = BUCKLER_SENSORS_SDA;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  error_code = nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);
  APP_ERROR_CHECK(error_code); 

  // initialize tsl2561 driver
  tsl2561_init(&twi_mngr_instance);
  error_code = tsl2561_config();
  APP_ERROR_CHECK(error_code);

  // loop forever
  while (1) {
    printf("Current reading: %s\n", tsl2561_read_result());

  	nrf_delay_ms(500);
  }
}
