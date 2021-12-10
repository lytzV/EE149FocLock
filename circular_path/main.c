// Project Geocentric

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "app_timer.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_spi.h"

#include "buckler.h"
#include "display.h"
#include "kobukiActuator.h"
#include "kobukiSensorPoll.h"
#include "kobukiSensorTypes.h"
#include "kobukiUtilities.h"
#include "tsl2561.h"
#include "controller.h"

// I2C manager
NRF_TWI_MNGR_DEF(twi_mngr_instance, 5, 0);

int mean(int len, int buf[]) {
  int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += buf[i] / len;
  }
  return sum;
}

int main(void) {
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");

  // initialize display
  nrf_drv_spi_t spi_instance = NRF_DRV_SPI_INSTANCE(1);
  nrf_drv_spi_config_t spi_config = {
    .sck_pin = BUCKLER_LCD_SCLK,
    .mosi_pin = BUCKLER_LCD_MOSI,
    .miso_pin = BUCKLER_LCD_MISO,
    .ss_pin = BUCKLER_LCD_CS,
    .irq_priority = NRFX_SPI_DEFAULT_CONFIG_IRQ_PRIORITY,
    .orc = 0,
    .frequency = NRF_DRV_SPI_FREQ_4M,
    .mode = NRF_DRV_SPI_MODE_2,
    .bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST
  };
  error_code = nrf_drv_spi_init(&spi_instance, &spi_config, NULL, NULL);
  APP_ERROR_CHECK(error_code);
  display_init(&spi_instance);
  display_write("Display init!", DISPLAY_LINE_0);
  printf("Display initialized!\n");

  // initialize i2c master (two wire interface)
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = BUCKLER_SENSORS_SCL;
  i2c_config.sda = BUCKLER_SENSORS_SDA;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  error_code = nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);
  APP_ERROR_CHECK(error_code);
  display_write("I2C init!", DISPLAY_LINE_0);
  printf("I2C initialized!\n");

  // init luminosity sensor 
  tsl2561_init(&twi_mngr_instance);
  display_write("Lum init!", DISPLAY_LINE_0);
  printf("Lum initialized!\n");  

  // initialize Kobuki
  kobukiInit();
  display_write("Kobuki init!", DISPLAY_LINE_0);
  printf("Kobuki initialized!\n");

  // configure initial state
  KobukiSensors_t sensors = {0};

  moon_state_t state = OFF;
  while (1) {

    kobukiUARTUnInit();
    
    // luminosity sensor
    tsl2561_config();
    float luxAngle = tsl2561_read_angle();
    float luxRadian = luxAngle * 0.0014 + 0.15;
    char buf[16];
    snprintf(buf, 16, "Angle:%f", luxAngle);
    display_write(buf, DISPLAY_LINE_1);
    printf(buf);
    tsl2561_shutdown();

    // update through controller
    kobukiUARTInit();
    state = controller(state, luxRadian, 0.2);

    nrf_delay_ms(interval);
  }
}
