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

typedef enum {
  DISTANCE,
  PIXY,
} sensor_type_t;

// UART configurations: Pin and buffer size
#define UART_RX_DISTANCE NRF_GPIO_PIN_MAP(0, 15)
#define UART_TX_DISTANCE NRF_GPIO_PIN_MAP(0, 16)
#define UART_RX_PIXY NRF_GPIO_PIN_MAP(0, 8)
#define UART_TX_PIXY NRF_GPIO_PIN_MAP(0, 6)
#define UART_TX_BUF_SIZE 128
#define UART_RX_BUF_SIZE 128

// Variables for reading sensor output
float data;
uint8_t *data_array = (uint8_t *)&data;
uint32_t r_error = 0;
int i = 0;

// Event handler for UART
void uart_event_handle(app_uart_evt_t *p_event) {
  if (p_event->evt_type == APP_UART_DATA) {
    uint8_t r_data = 0;
    r_error = app_uart_get(&r_data);
    if (r_error == NRF_SUCCESS && i < 4) {
      data_array[i] = r_data;
      printf("%d\n", i);
    } else {
      printf("Reading ends!");
    }
    i++;
  } else if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR) {
    // commented out because of initializing errors
    // APP_ERROR_HANDLER(p_event->data.error_communication);
  } else if (p_event->evt_type == APP_UART_FIFO_ERROR) {
    APP_ERROR_HANDLER(p_event->data.error_code);
  }
}

// initialization of UART
void uart_init(sensor_type_t sensor_type) {
  uint32_t err_code;
  const app_uart_comm_params_t comm_params_distance = {
      UART_RX_DISTANCE,
      UART_TX_DISTANCE,
      0,
      0,
      APP_UART_FLOW_CONTROL_DISABLED,
      false,
      NRF_UARTE_BAUDRATE_115200};
  const app_uart_comm_params_t comm_params_pixy = {
      UART_RX_PIXY,
      UART_TX_PIXY,
      0,
      0,
      APP_UART_FLOW_CONTROL_DISABLED,
      false,
      NRF_UARTE_BAUDRATE_115200};

  switch (sensor_type) {
    case DISTANCE: {
      APP_UART_FIFO_INIT(&comm_params_distance, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                         uart_event_handle, APP_IRQ_PRIORITY_LOW, err_code);
      break;
    }
    case PIXY: {
      APP_UART_FIFO_INIT(&comm_params_pixy, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                         uart_event_handle, APP_IRQ_PRIORITY_LOW, err_code);
      break;
    }
  }

  APP_ERROR_CHECK(err_code);
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
    //kobukiUARTUnInit();

    // // distance sensor (event-based, auto) reading
    // printf("**********************\n");
    // uart_init(DISTANCE);
    // while (i < 4) {
    //   nrf_delay_ms(1);
    // }
    // app_uart_close();
    // printf("**********************\n");

    // printf("Reading distance: %f\n", data);
    // i = 0;
    // data = 0;

    // // pixy camera (event-based, auto) reading
    // printf("######################\n");
    // uart_init(PIXY);
    // while (i < 4) {
    //   nrf_delay_ms(1);
    // }
    // app_uart_close();
    // printf("######################\n");

    // printf("Reading angle: %f\n", data);
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
