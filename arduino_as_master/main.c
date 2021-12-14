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

static uint8_t txbuff[1] = {1};

typedef enum {
  DISTANCE,
  PIXY,
} sensor_type_t;
sensor_type_t sensor_type = DISTANCE;
float distance;
uint8_t *distance_array = (uint8_t *)&distance;
uint16_t pixy;
uint8_t *pixy_array = (uint8_t *)&pixy;
uint32_t sensor_error = 0;

#define I2C_DEVICE_ID 0x66

static void twis_event_handler(nrf_drv_twis_evt_t const * const p_event) {
  switch (p_event->type) {
    case TWIS_EVT_READ_REQ:
      if (p_event->data.buf_req) {
          nrf_drv_twis_tx_prepare(&m_twis, txbuff, 1);
          //printf("Preparing to send\n");
      }
      break;
    case TWIS_EVT_READ_DONE:
      //printf("Total bytes sent %d\n", p_event->data.tx_amount);
      break;
    case TWIS_EVT_WRITE_REQ:
      if (p_event->data.buf_req) {
        if (sensor_type == PIXY) {
            nrf_drv_twis_rx_prepare(&m_twis, pixy_array, 2);
        } else {
            nrf_drv_twis_rx_prepare(&m_twis, distance_array, 4);
        }
        //printf("Preparing to read\n");
      }
      break;
    case TWIS_EVT_WRITE_DONE:
    //   printf("Total bytes received %d\n", p_event->data.rx_amount);
    //   if (sensor_type == PIXY) {
    //         printf("PIXY: %d\n", pixy);
    //     } else {
    //         printf("Distance: %f\n", distance);
    //     }
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
    printf("**********************\n");
    sensor_type = DISTANCE;
    txbuff[0] = 1;
    // Distance sensor should only output values between 0 and 400 (inches, in a room)
    printf("Distance: %f\n", distance);
    sensor_type = PIXY;
    txbuff[0] = 0;
    // Pixy should only output values between 0 and 316 (horizontal position in camera)
    printf("Pixy: %d\n", pixy);
    __WFI();
  }
}
