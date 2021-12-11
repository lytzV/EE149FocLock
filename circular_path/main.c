// Project Geocentric

#include "app_error.h"
#include "app_timer.h"
#include "app_uart.h"
#include "buckler.h"
#include "controller.h"
#include "display.h"
#include "kobukiActuator.h"
#include "kobukiSensorPoll.h"
#include "kobukiSensorTypes.h"
#include "kobukiUtilities.h"
#include "mpu9250.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_power.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_uarte.h"
#include "tsl2561.h"
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// UART configurations: Pin and buffer size
#define UART_RX NRF_GPIO_PIN_MAP(0, 15)
#define UART_TX NRF_GPIO_PIN_MAP(0, 16)
#define UART_TX_BUF_SIZE 128
#define UART_RX_BUF_SIZE 128

// Variables for reading distance sensor output
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
void uart_init(void) {
  uint32_t err_code;

  // configure RX and TX pins
  // no RTS or CTS pins with flow control disabled
  // no parity
  // baudrate 115200
  const app_uart_comm_params_t comm_params = {
      UART_RX,
      UART_TX,
      0,
      0,
      APP_UART_FLOW_CONTROL_DISABLED,
      false,
      NRF_UARTE_BAUDRATE_115200};

  // actually initialize UART
  APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                     uart_event_handle, APP_IRQ_PRIORITY_LOW, err_code);
  APP_ERROR_CHECK(err_code);
}

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
      .bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST};
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
  printf("I2C initialized!\n");

  // init luminosity sensor

  // tsl2561_init(&twi_mngr_instance);
  // printf("Lum initialized!\n");


  // initialize Kobuki
  kobukiInit();
  printf("Kobuki initialized!\n");

  // configure initial state
  KobukiSensors_t sensors = {0};
  moon_state_t state = OFF;

  // init and un-init each module to avoid conflicting behaviors
  int i = 0;
  while (i < 1) {

  

    state = controller(state, 0, 0.2);
    i ++;
  
   
  }
}
