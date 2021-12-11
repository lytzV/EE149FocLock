// Project Geocentric

#include "app_error.h"
#include "app_timer.h"
#include "app_uart.h"
#include "buckler.h"
#include "controller_distance_angle.h"
#include "display.h"
#include "kobukiActuator.h"
#include "kobukiSensorPoll.h"
#include "kobukiSensorTypes.h"
#include "kobukiUtilities.h"

#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_uarte.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
      .bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST};
  error_code = nrf_drv_spi_init(&spi_instance, &spi_config, NULL, NULL);
  APP_ERROR_CHECK(error_code);
  display_init(&spi_instance);
  display_write("Display init!", DISPLAY_LINE_0);
  printf("Display initialized!\n");

  // initialize Kobuki
  kobukiInit();
  printf("Kobuki initialized!\n");

  // configure initial state
  moon_state_t state = OFF;

  // init and un-init each module to avoid conflicting behaviors
  while (1) {

    // gettimeofday(&start, NULL);

    //kobukiUARTUnInit();

    // // distance sensor (event-based, auto) reading
    // printf("***************************************************************\n");
    // uart_init();
    // while (i < 4) {
    //   nrf_delay_ms(1);
    // }
    // app_uart_close();
    // printf("***************************************************************\n");

    // printf("Reading: %f\n", data);
    // i = 0;
    // data = 0;
    // kobukiUARTInit();

    // state update and Kobuki control
    state = controller(state);
    // delay some time between each loop for correct behaviors
    uint32_t interval_uint32 = interval;
    nrf_delay_ms(interval_uint32);
  }
}
