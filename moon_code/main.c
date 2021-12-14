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

typedef enum {
  DISTANCE,
  PIXY,
} sensor_type_t;

// UART configurations: Pin and buffer size
#define UART_RX_DISTANCE NRF_GPIO_PIN_MAP(0, 15)
#define UART_TX_DISTANCE NRF_GPIO_PIN_MAP(0, 16)
#define UART_RX_PIXY NRF_GPIO_PIN_MAP(0, 19)
#define UART_TX_PIXY NRF_GPIO_PIN_MAP(0, 6)
#define UART_TX_BUF_SIZE 128
#define UART_RX_BUF_SIZE 128

// I2C Manager
NRF_TWI_MNGR_DEF(twi_mngr_instance, 5, 0);
static const nrf_twi_mngr_t *twi_mngr = &twi_mngr_instance;

// Variables for reading sensor output
sensor_type_t sensor_type;
float distance;
uint8_t *distance_array = (uint8_t *)&distance;
uint16_t pixy;
uint8_t *pixy_array = (uint8_t *)&pixy;
uint32_t sensor_error = 0;
int i = 0;

uint16_t i2c_read_reg(uint8_t i2c_addr, uint8_t reg_addr) {
  uint16_t rx_buf = 0;
  nrf_twi_mngr_transfer_t const read_transfer[] = {
      NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
      NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 2, 0),
  };
  ret_code_t error_code = nrf_twi_mngr_perform(twi_mngr, NULL, read_transfer, 2, NULL);

  uint8_t temp = rx_buf & 0xFF;
  rx_buf >>= 8;
  rx_buf |= (temp << 8);
  return rx_buf;
}

// Event handler for UART
void uart_event_handle(app_uart_evt_t *p_event) {
  if (p_event->evt_type == APP_UART_DATA) {
    if (sensor_type == DISTANCE) {
      uint8_t data = 0;
      sensor_error = app_uart_get(&data);
      if (sensor_error == NRF_SUCCESS && i < 4) {
        distance_array[i] = data;
        // TODO: delete this debug print if everything works
        printf("%d\n", i);
      } else {
        // TODO: delete this debug print if everything works
        printf("Reading distance ends or errors!");
      }
    } else if (sensor_type == PIXY) {
      uint8_t data = 0;
      sensor_error = app_uart_get(&data);
      if (sensor_error == NRF_SUCCESS && i < 2) {
        pixy_array[i] = data;
        // TODO: delete this debug print if everything works
        printf("%d\n", i);
      } else {
        // TODO: delete this debug print if everything works
        printf("Reading pixy ends or errors!");
      }
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

  if (sensor_type == DISTANCE) {
    APP_UART_FIFO_INIT(&comm_params_distance, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                       uart_event_handle, APP_IRQ_PRIORITY_LOW, err_code);
  } else if (sensor_type == PIXY) {
    APP_UART_FIFO_INIT(&comm_params_pixy, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                       uart_event_handle, APP_IRQ_PRIORITY_LOW, err_code);
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

  // initialize i2c master (two wire interface)
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = BUCKLER_SENSORS_SCL;
  i2c_config.sda = BUCKLER_SENSORS_SDA;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  error_code = nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);
  APP_ERROR_CHECK(error_code);
  printf("I2C initialized!\n");

  // initialize Kobuki
  kobukiInit();
  printf("Kobuki initialized!\n");

  // configure initial state
  moon_state_t state = OFF;

  // init and un-init each module to avoid conflicting behaviors
  while (1) {

    // distance sensor (event-based, auto) reading
    // printf("**********************\n");
    // sensor_type = DISTANCE;
    // distance = -1;
    // uart_init();
    // // Distance sensor should only output values between 0 and 400 (inches, in a room)
    // while (distance < 0 || distance > 400) {
    //   while (i < 4) {
    //     nrf_delay_ms(1);
    //   }
    //   i = 0;
    //   // TODO: delete this debug print if everything works
    //   printf("Invalid distance reading: %f\n", distance);
    // }
    // app_uart_close();
    // printf("Distance: %f\n", distance);
    // printf("**********************\n");

    // pixy camera (event-based, auto) reading
    // printf("######################\n");
    // sensor_type = PIXY;
    // pixy = 410;
    // uart_init(DISTANCE);
    // // Pixy should only output values between 0 and 316 (horizontal position in camera)
    // while (pixy > 316) {
    //   while (i < 2) {
    //     nrf_delay_ms(1);
    //   }
    //   i = 0;
    //   // TODO: delete this debug print if everything works
    //   printf("Invalid pixy reading: %u\n", pixy);
    // }
    // app_uart_close();
    // printf("Pixy: %f\n", pixy);
    // printf("######################\n");

    // reading from i2c
    uint16_t i2c_result = i2c_read_reg(0x4, 10);
    uint8_t pixy = i2c_result >> 8;
    printf("Pixy: %d\n", pixy);

    // state update and Kobuki control
    //state = controller(state, 0, pixy);

    // delay some time between each loop for correct behaviors
    uint32_t interval_uint32 = interval;
    nrf_delay_ms(interval_uint32);
  }
}
