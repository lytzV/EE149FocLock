// Project Geocentrics
#include "app_error.h"
#include "app_timer.h"
#include "app_uart.h"
#include "buckler.h"
// #include "controller_distance_angle.h"
// #include "display.h"
// #include "kobukiActuator.h"
// #include "kobukiSensorPoll.h"
// #include "kobukiSensorTypes.h"
// #include "kobukiUtilities.h"
#include "nrf_twi_mngr.h"

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

#include "nrf_drv_twis.h"
#include "app_config.h"

static const nrf_drv_twis_t m_twis = NRF_DRV_TWIS_INSTANCE(1);

static uint8_t rxbuff[6] = {0,0,0,0,0,0};
float *distance = &(rxbuff[2]);
uint16_t pixy = &(rxbuff[0]);

#define I2C_DEVICE_ID 0x66

static void twis_event_handler(nrf_drv_twis_evt_t const * const p_event) {
  switch (p_event->type) {
    case TWIS_EVT_READ_REQ:
      break;
    case TWIS_EVT_READ_DONE:
      break;
    case TWIS_EVT_WRITE_REQ:
      if (p_event->data.buf_req) {
        nrf_drv_twis_rx_prepare(&m_twis, rxbuff, 6);
      }
      break;
    case TWIS_EVT_WRITE_DONE:
        printf("**********************\n");
        // Distance sensor should only output values between 0 and 400 (inches, in a room)
        printf("Distance: %f\n", *distance);
        // Pixy should only output values between 0 and 316 (horizontal position in camera)
        printf("Pixy: %d\n", *pixy);
      break;

    case TWIS_EVT_READ_ERROR:
    case TWIS_EVT_WRITE_ERROR:
    case TWIS_EVT_GENERAL_ERROR:
      printf("TWIS ERROR\n");
      break;
    default:
      break;
  }
}

int main(void) {
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized\n");
  
  const nrf_drv_twis_config_t twis_config =
  {
      .addr               = {I2C_DEVICE_ID, 0},
      .scl                = BUCKLER_SENSORS_SCL,
      .scl_pull           = NRF_GPIO_PIN_PULLUP,
      .sda                = BUCKLER_SENSORS_SDA,
      .sda_pull           = NRF_GPIO_PIN_PULLUP,
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH
  };

  error_code = nrf_drv_twis_init(&m_twis, &twis_config, &twis_event_handler);
  APP_ERROR_CHECK(error_code);

  nrf_drv_twis_enable(&m_twis);

  // loop forever
  while (1) {
    __WFI();
  }
}
