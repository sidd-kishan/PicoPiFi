/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef CDC_RNDIS_DEVICE_H
#define CDC_RNDIS_DEVICE_H

struct circular_queue {
    uint8_t buffer[2048];
    uint32_t tail;
};

extern USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[3][2048];
extern struct circular_queue read_queue[3];
extern volatile bool ep_tx_busy_flag;
void cdc_rndis_init(uint8_t mac[]);
void cdc_acm_data_send_with_dtr(int ep, uint8_t write_buffer[], int len);

#endif
