/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "usbd_core.h"
#include "usbd_rndis.h"
#include "usbd_cdc.h"
#include "usb_rp2040_reg.h"

/*!< endpoint address */
#define CDC_IN_EP  0x81
#define CDC_OUT_EP 0x01
#define CDC_INT_EP 0x85

#define CDC_IN_EP2  0x82
#define CDC_OUT_EP2 0x02
#define CDC_INT_EP2 0x86

#define CDC_IN_EP3  0x83
#define CDC_OUT_EP3 0x03
#define CDC_INT_EP3 0x87

#define CDC_IN_EP4  0x84
#define CDC_OUT_EP4 0x04
#define CDC_INT_EP4 0x88


#define USBD_VID           0xEFFF
#define USBD_PID           0xEFFF
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 0x0409
/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_RNDIS_DESCRIPTOR_LEN + CDC_ACM_DESCRIPTOR_LEN * 3)

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif
/*!< global descriptor */
static const uint8_t cdc_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x08, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_RNDIS_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, CDC_MAX_MPS, 0x01),
	CDC_ACM_DESCRIPTOR_INIT(0x02, CDC_INT_EP2, CDC_OUT_EP2, CDC_IN_EP2, CDC_MAX_MPS, 0x04),
    CDC_ACM_DESCRIPTOR_INIT(0x04, CDC_INT_EP3, CDC_OUT_EP3, CDC_IN_EP3, CDC_MAX_MPS, 0x02),
    CDC_ACM_DESCRIPTOR_INIT(0x06, CDC_INT_EP4, CDC_OUT_EP4, CDC_IN_EP4, CDC_MAX_MPS, 0x03),
    /*
     * string0 descriptor
     */
    USB_LANGID_INIT(USBD_LANGID_STRING),
    /*
     * string1 descriptor
     */
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'P', 0x00,                  /* wcChar0 */
    'i', 0x00,                  /* wcChar1 */
    'c', 0x00,                  /* wcChar2 */
    'o', 0x00,                  /* wcChar3 */
    ' ', 0x00,                  /* wcChar4 */
    'P', 0x00,                  /* wcChar5 */
    'i', 0x00,                  /* wcChar6 */
    'F', 0x00,                  /* wcChar7 */
    'i', 0x00,                  /* wcChar8 */
    /*
     * string2 descriptor
     */
    0x18,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'E', 0x00,                  /* wcChar0 */
    'C', 0x00,                  /* wcChar1 */
    'H', 0x00,                  /* wcChar2 */
    'O', 0x00,                  /* wcChar3 */
    ' ', 0x00,                  /* wcChar4 */
    'C', 0x00,                  /* wcChar5 */
    'D', 0x00,                  /* wcChar6 */
    'C', 0x00,                  /* wcChar7 */
    ' ', 0x00,                  /* wcChar8 */
    '#', 0x00,                  /* wcChar9 */
    '1', 0x00,                  /* wcChar10 */
    /*
     * string3 descriptor
     */
    0x18,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'E', 0x00,                  /* wcChar11 */
    'C', 0x00,                  /* wcChar12 */
    'H', 0x00,                  /* wcChar13 */
    'O', 0x00,                  /* wcChar14 */
    ' ', 0x00,                  /* wcChar15 */
    'C', 0x00,                  /* wcChar16 */
    'D', 0x00,                  /* wcChar17 */
    'C', 0x00,                  /* wcChar18 */
    ' ', 0x00,                  /* wcChar19 */
    '#', 0x00,                  /* wcChar20 */
    '2', 0x00,                  /* wcChar21 */
    /*
     * string4 descriptor
     */
    0x2E,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'P', 0x00,                  /* wcChar0 */
    'i', 0x00,                  /* wcChar1 */
    'c', 0x00,                  /* wcChar2 */
    'o', 0x00,                  /* wcChar3 */
    'P', 0x00,                  /* wcChar4 */
    'i', 0x00,                  /* wcChar5 */
    'F', 0x00,                  /* wcChar6 */
    'i', 0x00,                  /* wcChar7 */
    ' ', 0x00,                  /* wcChar8 */
    'C', 0x00,                  /* wcChar9 */
    'o', 0x00,                  /* wcChar10 */
    'n', 0x00,                  /* wcChar11 */
	't', 0x00,                  /* wcChar10 */
    'r', 0x00,                  /* wcChar11 */
    'o', 0x00,                  /* wcChar7 */
    'l', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'P', 0x00,                  /* wcChar10 */
    'a', 0x00,                  /* wcChar11 */
	'n', 0x00,                  /* wcChar10 */
    'e', 0x00,                  /* wcChar11 */
    'l', 0x00,                  /* wcChar11 */
#ifdef CONFIG_USB_HS
    /*
     * device qualifier descriptor
     */
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[3][2048];
struct circular_queue {
    uint8_t buffer[2048];
    uint32_t tail;
};

struct circular_queue read_queue[3];


volatile bool ep_tx_busy_flag = false;

void usbd_rndis_data_recv_done(void)
{
}

void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
    case USBD_EVENT_RESET:
        break;
    case USBD_EVENT_CONNECTED:
        break;
    case USBD_EVENT_DISCONNECTED:
        break;
    case USBD_EVENT_RESUME:
        break;
    case USBD_EVENT_SUSPEND:
        break;
    case USBD_EVENT_CONFIGURED:
		/* setup first out ep read transfer */
            usbd_ep_start_read(0, CDC_OUT_EP2, read_buffer[0], 2048);
            usbd_ep_start_read(0, CDC_OUT_EP3, read_buffer[1], 2048);
            usbd_ep_start_read(0, CDC_OUT_EP4, read_buffer[2], 2048);
        break;
    case USBD_EVENT_SET_REMOTE_WAKEUP:
        break;
    case USBD_EVENT_CLR_REMOTE_WAKEUP:
        break;

    default:
        break;
    }
}

void usbd_cdc_acm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    //USB_LOG_RAW("actual out len:%d\r\n", nbytes);
    /* setup next out ep read transfer */
	//if(nbytes<2048){
	if(ep == CDC_OUT_EP2){
		usbd_ep_start_read(0, CDC_OUT_EP2, read_buffer[0], 2048);
		for (int i = 0; i < nbytes; i++) {
			read_queue[0].buffer[read_queue[0].tail] = read_buffer[0][i];
			read_queue[0].tail = (read_queue[0].tail + 1) % 2048;
		}
		usbd_ep_start_write(0, CDC_IN_EP2, read_buffer[0], nbytes);
	}
	else if(ep == CDC_OUT_EP3){
		usbd_ep_start_read(0, CDC_OUT_EP3, read_buffer[1], 2048);
		for (int i = 0; i < nbytes; i++) {
			read_queue[1].buffer[read_queue[1].tail] = read_buffer[1][i];
			read_queue[1].tail = (read_queue[1].tail + 1) % 2048;
		}
		usbd_ep_start_write(0, CDC_IN_EP3, read_buffer[1], nbytes);
	}
	else{
		usbd_ep_start_read(0, CDC_OUT_EP4, read_buffer[2], 2048);
		for (int i = 0; i < nbytes; i++) {
			read_queue[2].buffer[read_queue[2].tail] = read_buffer[2][i];
			read_queue[2].tail = (read_queue[2].tail + 1) % 2048;
		}
		usbd_ep_start_write(0, CDC_IN_EP4, read_buffer[2], nbytes);
	}
}

void usbd_cdc_acm_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    //USB_LOG_RAW("actual in len:%d\r\n", nbytes);

    if ((nbytes % CDC_MAX_MPS) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(0, ep, NULL, 0);
    } else {
        ep_tx_busy_flag = false;
    }
}

struct usbd_endpoint cdc_out_ep2 = {
    .ep_addr = CDC_OUT_EP2,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep2 = {
    .ep_addr = CDC_IN_EP2,
    .ep_cb = usbd_cdc_acm_bulk_in
};

struct usbd_endpoint cdc_out_ep3 = {
    .ep_addr = CDC_OUT_EP3,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep3 = {
    .ep_addr = CDC_IN_EP3,
    .ep_cb = usbd_cdc_acm_bulk_in
};

struct usbd_endpoint cdc_out_ep4 = {
    .ep_addr = CDC_OUT_EP4,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep4 = {
    .ep_addr = CDC_IN_EP4,
    .ep_cb = usbd_cdc_acm_bulk_in
};

struct usbd_interface intf0;
struct usbd_interface intf1;
struct usbd_interface intf2;
struct usbd_interface intf3;
struct usbd_interface intf4;
struct usbd_interface intf5;
struct usbd_interface intf6;
struct usbd_interface intf7;

void cdc_rndis_init(uint8_t mac[])
{
    usbd_desc_register(0, cdc_descriptor);
    usbd_add_interface(0, (struct usbd_interface *)usbd_rndis_init_intf(&intf0, CDC_OUT_EP, CDC_IN_EP, CDC_INT_EP, mac));
    usbd_add_interface(0, (struct usbd_interface *)usbd_rndis_init_intf(&intf1, CDC_OUT_EP, CDC_IN_EP, CDC_INT_EP, mac));
	
	usbd_add_interface(0, (struct usbd_interface *)usbd_cdc_acm_init_intf(0, &intf2));
    usbd_add_interface(0, (struct usbd_interface *)usbd_cdc_acm_init_intf(0, &intf3));
    usbd_add_endpoint(0, &cdc_out_ep2);
    usbd_add_endpoint(0, &cdc_in_ep2);

    usbd_add_interface(0, (struct usbd_interface *)usbd_cdc_acm_init_intf(0, &intf4));
    usbd_add_interface(0, (struct usbd_interface *)usbd_cdc_acm_init_intf(0, &intf5));
    usbd_add_endpoint(0, &cdc_out_ep3);
    usbd_add_endpoint(0, &cdc_in_ep3);

    usbd_add_interface(0, (struct usbd_interface *)usbd_cdc_acm_init_intf(0, &intf6));
    usbd_add_interface(0, (struct usbd_interface *)usbd_cdc_acm_init_intf(0, &intf7));
    usbd_add_endpoint(0, &cdc_out_ep4);
    usbd_add_endpoint(0, &cdc_in_ep4);
    usbd_initialize(0,USBCTRL_REGS_BASE,usbd_event_handler);
}

volatile uint8_t dtr_enable = 0;

void usbd_cdc_acm_set_dtr(uint8_t busid, uint8_t intf, bool dtr)
{
    if (dtr) {
        dtr_enable = 1;
    } else {
        dtr_enable = 0;
    }
}

void cdc_acm_data_send_with_dtr(int ep, uint8_t write_buffer[], int len)
{
    if (dtr_enable) {
        ep_tx_busy_flag = true;
		if (ep == 2) {
			usbd_ep_start_write(0, CDC_IN_EP2, write_buffer, len);
		} else if (ep == 3) {
			usbd_ep_start_write(0, CDC_IN_EP3, write_buffer, len);
		} else {
			usbd_ep_start_write(0, CDC_IN_EP4, write_buffer, len);
		}
        while (ep_tx_busy_flag) {
        }
    }
}