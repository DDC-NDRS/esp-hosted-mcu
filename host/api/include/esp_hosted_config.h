/*
* SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
*
* SPDX-License-Identifier: Apache-2.0
*/

#ifndef __ESP_HOSTED_CONFIG_H__
#define __ESP_HOSTED_CONFIG_H__

#include "sdkconfig.h"
#include "esp_task.h"

#ifdef CONFIG_ESP_HOSTED_ENABLED
  #define H_ESP_HOSTED_HOST 1
#endif

#ifdef CONFIG_ESP_HOSTED_DFLT_TASK_STACK
  #define H_ESP_HOSTED_DFLT_TASK_STACK CONFIG_ESP_HOSTED_DFLT_TASK_STACK
#endif

#define H_TRANSPORT_NONE 0
#define H_TRANSPORT_SDIO 1
#define H_TRANSPORT_SPI_HD 2
#define H_TRANSPORT_SPI 3
#define H_TRANSPORT_UART 4

#ifdef CONFIG_ESP_HOSTED_SDIO_HOST_INTERFACE
  #include "driver/sdmmc_host.h"
#endif

#ifdef CONFIG_ESP_HOSTED_UART_HOST_INTERFACE
  #include "hal/uart_types.h"
#endif

/* This file is to tune the main ESP-Hosted configurations.
 * In case you are not sure of some value, Let it be default.
 **/

#define H_GPIO_LOW                                   0
#define H_GPIO_HIGH                                  1

#define H_ENABLE                                     1
#define H_DISABLE                                    0

enum {
	H_GPIO_INTR_DISABLE = 0,     /*!< Disable GPIO interrupt                             */
	H_GPIO_INTR_POSEDGE = 1,     /*!< GPIO interrupt type : rising edge                  */
	H_GPIO_INTR_NEGEDGE = 2,     /*!< GPIO interrupt type : falling edge                 */
	H_GPIO_INTR_ANYEDGE = 3,     /*!< GPIO interrupt type : both rising and falling edge */
	H_GPIO_INTR_LOW_LEVEL = 4,   /*!< GPIO interrupt type : input low level trigger      */
	H_GPIO_INTR_HIGH_LEVEL = 5,  /*!< GPIO interrupt type : input high level trigger     */
	H_GPIO_INTR_MAX,
};

#if CONFIG_SLAVE_IDF_TARGET_ESP32
  #define H_SLAVE_TARGET_ESP32 1
#elif CONFIG_SLAVE_IDF_TARGET_ESP32S2
  #define H_SLAVE_TARGET_ESP32S2 1
#elif CONFIG_SLAVE_IDF_TARGET_ESP32C3
  #define H_SLAVE_TARGET_ESP32C3 1
#elif CONFIG_SLAVE_IDF_TARGET_ESP32S3
  #define H_SLAVE_TARGET_ESP32S3 1
#elif CONFIG_SLAVE_IDF_TARGET_ESP32C2
  #define H_SLAVE_TARGET_ESP32C2 1
#elif CONFIG_SLAVE_IDF_TARGET_ESP32C6
  #define H_SLAVE_TARGET_ESP32C6 1
#elif CONFIG_SLAVE_IDF_TARGET_ESP32C5
  #define H_SLAVE_TARGET_ESP32C5 1
#else
  #error "Unknown Slave Target"
#endif

#if CONFIG_ESP_HOSTED_USE_MEMPOOL
  #define H_USE_MEMPOOL 1
#endif

#define H_MAX_SYNC_RPC_REQUESTS                      CONFIG_ESP_HOSTED_MAX_SIMULTANEOUS_SYNC_RPC_REQUESTS
#define H_MAX_ASYNC_RPC_REQUESTS                     CONFIG_ESP_HOSTED_MAX_SIMULTANEOUS_ASYNC_RPC_REQUESTS

#undef H_TRANSPORT_IN_USE

#ifdef CONFIG_ESP_HOSTED_SPI_HOST_INTERFACE
  #define H_TRANSPORT_IN_USE H_TRANSPORT_SPI
  /*  -------------------------- SPI Master Config start ----------------------  */
  /*  Pins in use. The SPI Master can use the GPIO mux,
      so feel free to change these if needed.
  */


  /* SPI config */

  #ifdef CONFIG_ESP_HOSTED_HS_ACTIVE_LOW
    #define H_HANDSHAKE_ACTIVE_HIGH 0
  #else
    /* Default HS: Active High */
    #define H_HANDSHAKE_ACTIVE_HIGH 1
  #endif

  #ifdef CONFIG_ESP_HOSTED_DR_ACTIVE_LOW
    #define H_DATAREADY_ACTIVE_HIGH 0
  #else
    /* Default DR: Active High */
    #define H_DATAREADY_ACTIVE_HIGH 1
  #endif

  #if H_HANDSHAKE_ACTIVE_HIGH
    #define H_HS_VAL_ACTIVE                            H_GPIO_HIGH
    #define H_HS_VAL_INACTIVE                          H_GPIO_LOW
    #define H_HS_INTR_EDGE                             H_GPIO_INTR_POSEDGE
  #else
    #define H_HS_VAL_ACTIVE                            H_GPIO_LOW
    #define H_HS_VAL_INACTIVE                          H_GPIO_HIGH
    #define H_HS_INTR_EDGE                             H_GPIO_INTR_NEGEDGE
  #endif

  #if H_DATAREADY_ACTIVE_HIGH
    #define H_DR_VAL_ACTIVE                            H_GPIO_HIGH
    #define H_DR_VAL_INACTIVE                          H_GPIO_LOW
    #define H_DR_INTR_EDGE                             H_GPIO_INTR_POSEDGE
  #else
    #define H_DR_VAL_ACTIVE                            H_GPIO_LOW
    #define H_DR_VAL_INACTIVE                          H_GPIO_HIGH
    #define H_DR_INTR_EDGE                             H_GPIO_INTR_NEGEDGE
  #endif

  #define H_GPIO_HANDSHAKE_Port                        NULL
  #define H_GPIO_HANDSHAKE_Pin                         CONFIG_ESP_HOSTED_SPI_GPIO_HANDSHAKE
  #define H_GPIO_DATA_READY_Port                       NULL
  #define H_GPIO_DATA_READY_Pin                        CONFIG_ESP_HOSTED_SPI_GPIO_DATA_READY



  #define H_GPIO_MOSI_Port                             NULL
  #define H_GPIO_MOSI_Pin                              CONFIG_ESP_HOSTED_SPI_GPIO_MOSI
  #define H_GPIO_MISO_Port                             NULL
  #define H_GPIO_MISO_Pin                              CONFIG_ESP_HOSTED_SPI_GPIO_MISO
  #define H_GPIO_SCLK_Port                             NULL
  #define H_GPIO_SCLK_Pin                              CONFIG_ESP_HOSTED_SPI_GPIO_CLK
  #define H_GPIO_CS_Port                               NULL
  #define H_GPIO_CS_Pin                                CONFIG_ESP_HOSTED_SPI_GPIO_CS

  #define H_SPI_TX_Q                                   CONFIG_ESP_HOSTED_SPI_TX_Q_SIZE
  #define H_SPI_RX_Q                                   CONFIG_ESP_HOSTED_SPI_RX_Q_SIZE

  #define H_SPI_MODE                                   CONFIG_ESP_HOSTED_SPI_MODE
  #define H_SPI_FD_CLK_MHZ                           CONFIG_ESP_HOSTED_SPI_CLK_FREQ

  /*  -------------------------- SPI Master Config end ------------------------  */
#endif

#ifdef CONFIG_ESP_HOSTED_SDIO_HOST_INTERFACE
  #define H_TRANSPORT_IN_USE H_TRANSPORT_SDIO
  /*  -------------------------- SDIO Host Config start -----------------------  */

  #ifdef CONFIG_SOC_SDMMC_USE_GPIO_MATRIX
    #define H_SDIO_SOC_USE_GPIO_MATRIX
  #endif

  #define H_SDIO_CLOCK_FREQ_KHZ                        CONFIG_ESP_HOSTED_SDIO_CLOCK_FREQ_KHZ
  #define H_SDIO_BUS_WIDTH                             CONFIG_ESP_HOSTED_SDIO_BUS_WIDTH
  #define H_SDMMC_HOST_SLOT                            CONFIG_ESP_HOSTED_SDIO_SLOT

  #ifdef H_SDIO_SOC_USE_GPIO_MATRIX
    #define H_SDIO_PIN_CLK                             CONFIG_ESP_HOSTED_SDIO_PIN_CLK
    #define H_SDIO_PIN_CMD                             CONFIG_ESP_HOSTED_SDIO_PIN_CMD
    #define H_SDIO_PIN_D0                              CONFIG_ESP_HOSTED_SDIO_PIN_D0
    #define H_SDIO_PIN_D1                              CONFIG_ESP_HOSTED_SDIO_PIN_D1
    #if (H_SDIO_BUS_WIDTH == 4)
      #define H_SDIO_PIN_D2                            CONFIG_ESP_HOSTED_SDIO_PIN_D2
      #define H_SDIO_PIN_D3                            CONFIG_ESP_HOSTED_SDIO_PIN_D3
    #else
      #define H_SDIO_PIN_D2                            -1
      #define H_SDIO_PIN_D3                            -1
    #endif
  #else
    #define H_SDIO_PIN_CLK                             -1
    #define H_SDIO_PIN_CMD                             -1
    #define H_SDIO_PIN_D0                              -1
    #define H_SDIO_PIN_D1                              -1
    #if (H_SDIO_BUS_WIDTH == 4)
      #define H_SDIO_PIN_D2                            -1
      #define H_SDIO_PIN_D3                            -1
    #else
      #define H_SDIO_PIN_D2                            -1
      #define H_SDIO_PIN_D3                            -1
    #endif
  #endif

  #define H_SDIO_TX_Q                                  CONFIG_ESP_HOSTED_SDIO_TX_Q_SIZE
  #define H_SDIO_RX_Q                                  CONFIG_ESP_HOSTED_SDIO_RX_Q_SIZE

  #define H_SDIO_CHECKSUM                              CONFIG_ESP_HOSTED_SDIO_CHECKSUM

  #define H_SDIO_HOST_STREAMING_MODE 1
  #define H_SDIO_ALWAYS_HOST_RX_MAX_TRANSPORT_SIZE 2
  #define H_SDIO_OPTIMIZATION_RX_NONE 3

  #ifdef CONFIG_ESP_HOSTED_SDIO_OPTIMIZATION_RX_STREAMING_MODE
    #define H_SDIO_HOST_RX_MODE H_SDIO_HOST_STREAMING_MODE
  #elif defined(CONFIG_ESP_HOSTED_SDIO_OPTIMIZATION_RX_MAX_SIZE)
    #define H_SDIO_HOST_RX_MODE H_SDIO_ALWAYS_HOST_RX_MAX_TRANSPORT_SIZE
  #else
    /* Use this if unsure */
    #define H_SDIO_HOST_RX_MODE H_SDIO_OPTIMIZATION_RX_NONE
  #endif

  // Pad transfer len for host operation
  #define H_SDIO_TX_LEN_TO_TRANSFER(x) ((x + 3) & (~3))
  #define H_SDIO_RX_LEN_TO_TRANSFER(x) ((x + 3) & (~3))

  /* Do Block Mode only transfers
   *
   * When enabled, SDIO only uses block mode transfers for higher
   * throughput. Data lengths are padded to multiples of ESP_BLOCK_SIZE.
   *
   * This is safe for the SDIO slave:
   * - for Host Tx: slave will ignore extra data sent by Host
   * - for Host Rx: slave will send extra 0 data, ignored by Host
   */
  #define H_SDIO_TX_BLOCK_ONLY_XFER (1)
  #define H_SDIO_RX_BLOCK_ONLY_XFER (1)

  // workarounds for some SDIO transfer errors that may occur
  #if 0
    /* Below workarounds could be enabled for non-ESP MCUs to test first
     * Once everything is stable, can disable workarounds and test again
     * */
    #define H_SDIO_TX_LIMIT_XFER_SIZE_WORKAROUND // limit transfer to one ESP_BLOCK_SIZE at a time
    #define H_SDIO_RX_LIMIT_XFER_SIZE_WORKDAROUND // limit transfer to one ESP_BLOCK_SIZE at a time
  #endif

  #if defined(H_SDIO_TX_LIMIT_XFER_SIZE_WORKAROUND)
    #define H_SDIO_TX_BLOCKS_TO_TRANSFER(x) (1)
  #else
    #define H_SDIO_TX_BLOCKS_TO_TRANSFER(x) (x / ESP_BLOCK_SIZE)
  #endif

  #if defined(H_SDIO_RX_LIMIT_XFER_SIZE_WORKDAROUND)
    #define H_SDIO_RX_BLOCKS_TO_TRANSFER(x) (1)
  #else
    #define H_SDIO_RX_BLOCKS_TO_TRANSFER(x) (x / ESP_BLOCK_SIZE)
  #endif

  /*  -------------------------- SDIO Host Config end -------------------------  */
#endif

#ifdef CONFIG_ESP_HOSTED_SPI_HD_HOST_INTERFACE
  #define H_TRANSPORT_IN_USE H_TRANSPORT_SPI_HD
  /*  -------------------------- SPI_HD Host Config start -----------------------  */

  #define H_SPI_HD_HOST_INTERFACE 1

  enum {
    H_SPI_HD_CONFIG_2_DATA_LINES,
    H_SPI_HD_CONFIG_4_DATA_LINES,
  };

  #if CONFIG_ESP_HOSTED_SPI_HD_DR_ACTIVE_HIGH
    #define H_SPI_HD_DATAREADY_ACTIVE_HIGH 1
  #else
    #define H_SPI_HD_DATAREADY_ACTIVE_HIGH 0
  #endif

  #if H_SPI_HD_DATAREADY_ACTIVE_HIGH
    #define H_SPI_HD_DR_VAL_ACTIVE                     H_GPIO_HIGH
    #define H_SPI_HD_DR_VAL_INACTIVE                   H_GPIO_LOW
    #define H_SPI_HD_DR_INTR_EDGE                      H_GPIO_INTR_POSEDGE
  #else
    #define H_SPI_HD_DR_VAL_ACTIVE                     H_GPIO_LOW
    #define H_SPI_HD_DR_VAL_INACTIVE                   H_GPIO_HIGH
    #define H_SPI_HD_DR_INTR_EDGE                      H_GPIO_INTR_NEGEDGE
  #endif

  #define H_SPI_HD_HOST_NUM_DATA_LINES                 CONFIG_ESP_HOSTED_SPI_HD_INTERFACE_NUM_DATA_LINES

  #define H_SPI_HD_PIN_D0                              CONFIG_ESP_HOSTED_SPI_HD_GPIO_D0
  #define H_SPI_HD_PIN_D1                              CONFIG_ESP_HOSTED_SPI_HD_GPIO_D1
  #if (CONFIG_ESP_HOSTED_SPI_HD_INTERFACE_NUM_DATA_LINES == 4)
    #define H_SPI_HD_PIN_D2                              CONFIG_ESP_HOSTED_SPI_HD_GPIO_D2
    #define H_SPI_HD_PIN_D3                              CONFIG_ESP_HOSTED_SPI_HD_GPIO_D3
  #else
    #define H_SPI_HD_PIN_D2                              -1
    #define H_SPI_HD_PIN_D3                              -1
  #endif

  #define H_SPI_HD_PIN_CS                              CONFIG_ESP_HOSTED_SPI_HD_GPIO_CS
  #define H_SPI_HD_PIN_CLK                             CONFIG_ESP_HOSTED_SPI_HD_GPIO_CLK
  #define H_SPI_HD_GPIO_DATA_READY_Port                NULL
  #define H_SPI_HD_PIN_DATA_READY                      CONFIG_ESP_HOSTED_SPI_HD_GPIO_DATA_READY

  #define H_SPI_HD_CLK_MHZ                             CONFIG_ESP_HOSTED_SPI_HD_CLK_FREQ
  #define H_SPI_HD_MODE                                CONFIG_ESP_HOSTED_SPI_HD_MODE
  #define H_SPI_HD_TX_QUEUE_SIZE                       CONFIG_ESP_HOSTED_SPI_HD_TX_Q_SIZE
  #define H_SPI_HD_RX_QUEUE_SIZE                       CONFIG_ESP_HOSTED_SPI_HD_RX_Q_SIZE

  #define H_SPI_HD_CHECKSUM                            CONFIG_ESP_HOSTED_SPI_HD_CHECKSUM

  #define H_SPI_HD_NUM_COMMAND_BITS                    8
  #define H_SPI_HD_NUM_ADDRESS_BITS                    8
  #define H_SPI_HD_NUM_DUMMY_BITS                      8

/*  -------------------------- SPI_HD Host Config end -------------------------  */
#else
  #define H_SPI_HD_HOST_INTERFACE 0
#endif

#ifdef CONFIG_ESP_HOSTED_UART_HOST_INTERFACE
  #define H_TRANSPORT_IN_USE H_TRANSPORT_UART
  /*  -------------------------- UART Host Config start -------------------------  */

  #define H_UART_HOST_TRANSPORT 1

  #define H_UART_PORT                                  CONFIG_ESP_HOSTED_UART_PORT
  #define H_UART_NUM_DATA_BITS                         CONFIG_ESP_HOSTED_UART_NUM_DATA_BITS
  #define H_UART_PARITY                                CONFIG_ESP_HOSTED_UART_PARITY
  #define H_UART_START_BITS                            1
  #define H_UART_STOP_BITS                             CONFIG_ESP_HOSTED_UART_STOP_BITS
  #define H_UART_FLOWCTRL                              UART_HW_FLOWCTRL_DISABLE
  #define H_UART_CLK_SRC                               UART_SCLK_DEFAULT

  #define H_UART_CHECKSUM                              CONFIG_ESP_HOSTED_UART_CHECKSUM
  #define H_UART_BAUD_RATE                             CONFIG_ESP_HOSTED_UART_BAUDRATE
  #define H_UART_TX_PIN                                CONFIG_ESP_HOSTED_UART_PIN_TX
  #define H_UART_RX_PIN                                CONFIG_ESP_HOSTED_UART_PIN_RX
  #define H_UART_TX_QUEUE_SIZE                         CONFIG_ESP_HOSTED_UART_TX_Q_SIZE
  #define H_UART_RX_QUEUE_SIZE                         CONFIG_ESP_HOSTED_UART_RX_Q_SIZE

  /*  -------------------------- UART Host Config end -------------------------  */
#else
  #define H_UART_HOST_TRANSPORT 0
#endif

/* Generic reset pin config */
#define H_GPIO_PIN_RESET_Port                        NULL
#define H_GPIO_PIN_RESET_Pin                         CONFIG_ESP_HOSTED_GPIO_SLAVE_RESET_SLAVE

/* If Reset pin is Enable, it is Active High.
 * If it is RST, active low */
#ifdef CONFIG_ESP_HOSTED_RESET_GPIO_ACTIVE_LOW
  #define H_RESET_ACTIVE_HIGH                        0
#else
  #define H_RESET_ACTIVE_HIGH                        1
#endif

#if H_RESET_ACTIVE_HIGH
  #define H_RESET_VAL_ACTIVE                         H_GPIO_HIGH
  #define H_RESET_VAL_INACTIVE                       H_GPIO_LOW
#else
  #define H_RESET_VAL_ACTIVE                         H_GPIO_LOW
  #define H_RESET_VAL_INACTIVE                       H_GPIO_HIGH
#endif

/* --------------------- Common slave reset strategy ------------------- */

#if defined(CONFIG_ESP_HOSTED_SLAVE_RESET_ON_EVERY_HOST_BOOTUP)
  /* Always reset the slave when host boots up
   * This ensures a clean transport state and prevents any inconsistent states,
   * but causes the slave to reboot every time the host boots up
   */
  #define H_SLAVE_RESET_ON_EVERY_HOST_BOOTUP 1
  #define H_SLAVE_RESET_ONLY_IF_NECESSARY 0
#elif defined(CONFIG_ESP_HOSTED_SLAVE_RESET_ONLY_IF_NECESSARY)
  /* Only reset the slave if initialization fails
   * This reduces slave reboots but assumes the slave interface is in a consistent state.
   * If initialization fails, the host will assume the slave is in an inconsistent
   * or deinitialized state and will reset it.
   */
  #define H_SLAVE_RESET_ON_EVERY_HOST_BOOTUP 0
  #define H_SLAVE_RESET_ONLY_IF_NECESSARY 1
#else
  /* Default to always reset for backward compatibility */
  #define H_SLAVE_RESET_ON_EVERY_HOST_BOOTUP 1
  #define H_SLAVE_RESET_ONLY_IF_NECESSARY 0
#endif

#if !defined(CONFIG_ESP_SDIO_HOST_INTERFACE) && H_SLAVE_RESET_ONLY_IF_NECESSARY
#error "Invalid combination. H_SLAVE_RESET_ONLY_IF_NECESSARY is only supported for SDIO host interface, for now"
#endif

/* Auto-restart on communication failure */
#ifdef CONFIG_ESP_HOSTED_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE
  /* Enable host auto-restart if communication with slave is lost
   * When enabled, the host will reset itself to recover the connection
   * if the slave becomes non-responsive for the configured timeout period.
   * This acts as a safeguard in case the slave does not issue the first event.
   */
  #define H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE 1
#else
  /* Disable host auto-restart on communication failure */
  #define H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE 0
#endif

#if defined(CONFIG_ESP_HOSTED_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE_TIMEOUT)
  /* Timeout in seconds before host restarts due to no communication
   * Maximum time that the host will wait for a response from the slave
   * before triggering an automatic restart.
   */
  #define H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE_TIMEOUT CONFIG_ESP_HOSTED_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE_TIMEOUT
#else
  /* Default timeout value (-1 means disabled) */
  #define H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE_TIMEOUT -1
#endif

#if H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE && H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE_TIMEOUT == -1
  #error "Invalid combination. Host Restart No Communication With Slave is enabled but timeout is not configured"
#endif

#if H_SLAVE_RESET_ON_EVERY_HOST_BOOTUP && H_SLAVE_RESET_ONLY_IF_NECESSARY
  #error "Invalid combination. Reset on every bootup and reset only if necessary cannot be enabled at the same time"
#endif

#if H_SLAVE_RESET_ON_EVERY_HOST_BOOTUP && H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE
  #error "Invalid combination. H_HOST_RESTART_NO_COMMUNICATION_WITH_SLAVE should not be logically required if H_SLAVE_RESET_ONLY_IF_NECESSARY is enabled"
#endif


#define TIMEOUT_PSERIAL_RESP                         30


#define PRE_FORMAT_NEWLINE_CHAR                      ""
#define POST_FORMAT_NEWLINE_CHAR                     "\n"

#define USE_STD_C_LIB_MALLOC                         0

#ifdef CONFIG_HOST_TO_ESP_WIFI_DATA_THROTTLE
  #define H_WIFI_TX_DATA_THROTTLE_LOW_THRESHOLD        CONFIG_ESP_HOSTED_TO_WIFI_DATA_THROTTLE_LOW_THRESHOLD
  #define H_WIFI_TX_DATA_THROTTLE_HIGH_THRESHOLD       CONFIG_ESP_HOSTED_TO_WIFI_DATA_THROTTLE_HIGH_THRESHOLD
#else
  #define H_WIFI_TX_DATA_THROTTLE_LOW_THRESHOLD        0
  #define H_WIFI_TX_DATA_THROTTLE_HIGH_THRESHOLD       0
#endif

#define H_PKT_STATS                                  CONFIG_ESP_HOSTED_PKT_STATS

/* Raw Throughput Testing */
#define H_TEST_RAW_TP     CONFIG_ESP_HOSTED_RAW_THROUGHPUT_TRANSPORT

#if H_TEST_RAW_TP

  #define H_RAW_TP_REPORT_INTERVAL                     CONFIG_ESP_HOSTED_RAW_TP_REPORT_INTERVAL
  #define H_RAW_TP_PKT_LEN                             CONFIG_ESP_HOSTED_RAW_TP_HOST_TO_ESP_PKT_LEN

  #if CONFIG_ESP_HOSTED_RAW_THROUGHPUT_TX_TO_SLAVE
    #define H_TEST_RAW_TP_DIR (ESP_TEST_RAW_TP__HOST_TO_ESP)
  #elif CONFIG_ESP_HOSTED_RAW_THROUGHPUT_RX_FROM_SLAVE
    #define H_TEST_RAW_TP_DIR (ESP_TEST_RAW_TP__ESP_TO_HOST)
  #elif CONFIG_ESP_HOSTED_RAW_THROUGHPUT_BIDIRECTIONAL
    #define H_TEST_RAW_TP_DIR (ESP_TEST_RAW_TP__BIDIRECTIONAL)
  #else
    #error Test Raw TP direction not defined
  #endif

#else
  #define H_TEST_RAW_TP_DIR (ESP_TEST_RAW_TP_NONE)
#endif

/* ----------------------- Enable packet stats ------------------------------- */
#ifdef CONFIG_ESP_PKT_STATS
  #define ESP_PKT_STATS 1
  #define ESP_PKT_STATS_REPORT_INTERVAL  CONFIG_ESP_PKT_STATS_INTERVAL_SEC
#endif

/* ----------------- Host to slave Wi-Fi flow control ------------------------ */
/* Bit0: slave request host to enable flow control */
#define H_EVTGRP_BIT_FC_ALLOW_WIFI BIT(0)


/* --------------------- Host Power saving ----------------------------------- */

#if defined(CONFIG_ESP_HOSTED_HOST_POWER_SAVE_ENABLED)
  #if defined(CONFIG_ESP_HOSTED_HOST_DEEP_SLEEP_ALLOWED)
    #define H_HOST_PS_ALLOWED 1
    #define H_HOST_PS_ALLOWED_LIGHT_SLEEP 0
  #else
    #define H_HOST_PS_ALLOWED 0
  #endif

  /* Amend later for light sleep */
#else
    #define H_HOST_PS_ALLOWED 0
#endif

#if defined(CONFIG_ESP_HOSTED_HOST_WAKEUP_GPIO)
  #define H_HOST_WAKEUP_GPIO_PORT NULL
  #define H_HOST_WAKEUP_GPIO CONFIG_ESP_HOSTED_HOST_WAKEUP_GPIO
#else
  #define H_HOST_WAKEUP_GPIO -1
#endif

#if defined(CONFIG_ESP_HOSTED_HOST_WAKEUP_GPIO_LEVEL)
  #define H_HOST_WAKEUP_GPIO_LEVEL CONFIG_ESP_HOSTED_HOST_WAKEUP_GPIO_LEVEL
#else
  #define H_HOST_WAKEUP_GPIO_LEVEL 1 /* High */
#endif

/* Conflict checks for host power save configuration */
#if (H_HOST_PS_ALLOWED == 1)
  #if (H_HOST_WAKEUP_GPIO == -1)
    #error "Conflict: Host wake-up GPIO is mandatory when deep sleep is allowed"
  #endif
#endif

/* --------------------- Host CLI -------------------------------------------- */
#ifdef CONFIG_ESP_HOSTED_CLI_ENABLED
  #define H_ESP_HOSTED_CLI_ENABLED 1
#endif

/*  ---------------------- ESP-IDF Specific Config start --------------------  */
/* This section is for ESP-IDF specific support.
 * Can be ignored on other hosts MCUs.
 */

/* Controls whether an Internal LDO powers the SDIO connection */
#if CONFIG_ESP_HOSTED_SD_PWR_CTRL_LDO_INTERNAL_IO
  #define H_SDIO_PWR_CTRL_LDO                          1
  #define H_SDIO_PWR_CTRL_LDO_ID                       CONFIG_ESP_HOSTED_SD_PWR_CTRL_LDO_IO_ID
#else
  #define H_SDIO_PWR_CTRL_LDO                          0
#endif

/*  ---------------------- ESP-IDF Specific Config end ----------------------  */

/* --------------------- Network Split -------------------------------------- */
#ifdef CONFIG_ESP_HOSTED_NETWORK_SPLIT_ENABLED
  #define H_NETWORK_SPLIT_ENABLED 1
#else
  #define H_NETWORK_SPLIT_ENABLED 0
#endif

#if H_NETWORK_SPLIT_ENABLED
#if !defined(CONFIG_LWIP_TCP_LOCAL_PORT_RANGE_START) || \
    !defined(CONFIG_LWIP_TCP_LOCAL_PORT_RANGE_END)   || \
    !defined(CONFIG_LWIP_UDP_LOCAL_PORT_RANGE_START) || \
    !defined(CONFIG_LWIP_UDP_LOCAL_PORT_RANGE_END)
#error "LWIP ports at host need to configured, ensure they are exclusive and different from slave"
#endif

#define H_HOST_TCP_LOCAL_PORT_RANGE_START CONFIG_LWIP_TCP_LOCAL_PORT_RANGE_START
#define H_HOST_TCP_LOCAL_PORT_RANGE_END CONFIG_LWIP_TCP_LOCAL_PORT_RANGE_END
#define H_HOST_UDP_LOCAL_PORT_RANGE_START CONFIG_LWIP_UDP_LOCAL_PORT_RANGE_START
#define H_HOST_UDP_LOCAL_PORT_RANGE_END CONFIG_LWIP_UDP_LOCAL_PORT_RANGE_END

#define H_SLAVE_TCP_REMOTE_PORT_RANGE_START CONFIG_LWIP_TCP_REMOTE_PORT_RANGE_START
#define H_SLAVE_TCP_REMOTE_PORT_RANGE_END CONFIG_LWIP_TCP_REMOTE_PORT_RANGE_END
#define H_SLAVE_UDP_REMOTE_PORT_RANGE_START CONFIG_LWIP_UDP_REMOTE_PORT_RANGE_START
#define H_SLAVE_UDP_REMOTE_PORT_RANGE_END CONFIG_LWIP_UDP_REMOTE_PORT_RANGE_END

#endif


#define H_HOST_USES_STATIC_NETIF 0 /* yet unsupported */

esp_err_t esp_hosted_set_default_config(void);
bool esp_hosted_is_config_valid(void);

#endif /*__ESP_HOSTED_CONFIG_H__*/
