/*
* SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
*
* SPDX-License-Identifier: Apache-2.0
*/

#ifndef __ESP_HOSTED_INTERFACE_H__
#define __ESP_HOSTED_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

// https://github.com/espressif/esp-hosted-mcu
// 7.2 Interface Types
typedef enum {
    ESP_INVALID_IF,             // Invalid interface
    ESP_STA_IF,                 // Station frame
    ESP_AP_IF,                  // SoftAP frame
    ESP_SERIAL_IF,              // Control frame
    ESP_HCI_IF,                 // Bluetooth Hosted HCI frame
    ESP_PRIV_IF,                // Private communication between slave and host
    ESP_TEST_IF,                // Test interface
    ESP_ETH_IF,                 // Ethernet frame (Invalid)
    ESP_MAX_IF,                 // Type mentioned in dummy or empty frame
} esp_hosted_if_type_t;

#ifdef __cplusplus
}
#endif

#endif
