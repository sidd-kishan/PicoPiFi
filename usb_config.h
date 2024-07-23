/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef CHERRYUSB_CONFIG_H
#define CHERRYUSB_CONFIG_H

#define CHERRYUSB_VERSION 0x000700

/* ================ USB common Configuration ================ */

#define CONFIG_USB_PRINTF(...) printf(__VA_ARGS__)

#define usb_malloc(size) malloc(size)
#define usb_free(ptr)    free(ptr)

#ifndef CONFIG_USB_DBG_LEVEL
#define CONFIG_USB_DBG_LEVEL USB_DBG_INFO
#endif

#ifndef CONFIG_USBDEV_MAX_BUS
#define CONFIG_USBDEV_MAX_BUS 1
#endif

#ifndef CONFIG_USBDEV_MSC_MAX_LUN
#define CONFIG_USBDEV_MSC_MAX_LUN 1
#endif

#ifndef CONFIG_USBDEV_EP_NUM
#define CONFIG_USBDEV_EP_NUM 8
#endif

/* Enable print with color */
#define CONFIG_USB_PRINTF_COLOR_ENABLE

/* data align size when use dma */
#ifndef CONFIG_USB_ALIGN_SIZE
#define CONFIG_USB_ALIGN_SIZE 4
#endif

/* attribute data into no cache ram */
// #define USB_NOCACHE_RAM_SECTION __attribute__((section(".noncacheable")))
#define USB_NOCACHE_RAM_SECTION
/* ================= USB Device Stack Configuration ================ */

/* Ep0 max transfer buffer, specially for receiving data from ep0 out */
#ifndef CONFIG_USBDEV_REQUEST_BUFFER_LEN
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN 1024
#endif

/* Setup packet log for debug */
// #define CONFIG_USBDEV_SETUP_LOG_PRINT

/* Check if the input descriptor is correct */
// #define CONFIG_USBDEV_DESC_CHECK

/* Enable test mode */
// #define CONFIG_USBDEV_TEST_MODE

#ifndef CONFIG_USBDEV_MSC_BLOCK_SIZE
#define CONFIG_USBDEV_MSC_BLOCK_SIZE 512
#endif

#ifndef CONFIG_USBDEV_MSC_MANUFACTURER_STRING
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_PRODUCT_STRING
#define CONFIG_USBDEV_MSC_PRODUCT_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_VERSION_STRING
#define CONFIG_USBDEV_MSC_VERSION_STRING "0.01"
#endif

// #define CONFIG_USBDEV_MSC_THREAD

#ifdef CONFIG_USBDEV_MSC_THREAD
#ifndef CONFIG_USBDEV_MSC_STACKSIZE
#define CONFIG_USBDEV_MSC_STACKSIZE 2048
#endif

#ifndef CONFIG_USBDEV_MSC_PRIO
#define CONFIG_USBDEV_MSC_PRIO 4
#endif
#endif

#ifndef CONFIG_USBDEV_AUDIO_VERSION
#define CONFIG_USBDEV_AUDIO_VERSION 0x0100
#endif

#ifndef CONFIG_USBDEV_AUDIO_MAX_CHANNEL
#define CONFIG_USBDEV_AUDIO_MAX_CHANNEL 8
#endif

#ifndef CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE
#define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE 128
#endif

#ifndef CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE
#define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE 1500
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_ID
#define CONFIG_USBDEV_RNDIS_VENDOR_ID 0x0000ffff
#endif

#ifndef CONFIG_USBDEV_RNDIS_VENDOR_DESC
#define CONFIG_USBDEV_RNDIS_VENDOR_DESC "CherryUSB"
#endif

#ifndef CONFIG_USBDEV_MSC_MAX_BUFSIZE
#define CONFIG_USBDEV_MSC_MAX_BUFSIZE 512
#endif


/* ================ USB HOST Stack Configuration ================== */

#define CONFIG_USBHOST_MAX_RHPORTS          1
#define CONFIG_USBHOST_MAX_EXTHUBS          1
#define CONFIG_USBHOST_MAX_EHPORTS          4
#define CONFIG_USBHOST_MAX_INTERFACES       6
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS 1
#define CONFIG_USBHOST_MAX_ENDPOINTS        4

#define CONFIG_USBHOST_DEV_NAMELEN 16

#ifndef CONFIG_USBHOST_PSC_PRIO
#define CONFIG_USBHOST_PSC_PRIO 4
#endif
#ifndef CONFIG_USBHOST_PSC_STACKSIZE
#define CONFIG_USBHOST_PSC_STACKSIZE 2048
#endif

//#define CONFIG_USBHOST_GET_STRING_DESC

/* Ep0 max transfer buffer */
#define CONFIG_USBHOST_REQUEST_BUFFER_LEN 512

#ifndef CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT
#define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT 500
#endif

#ifndef CONFIG_USBHOST_MSC_TIMEOUT
#define CONFIG_USBHOST_MSC_TIMEOUT 5000
#endif

/* ================ USB Device Port Configuration ================*/

//#define USBD_IRQHandler USBD_IRQHandler
//#define USB_BASE (0x40080000UL)
//#define USB_NUM_BIDIR_ENDPOINTS 4

// #define USBD_IRQHandler USB_IRQHandler
// #define USB_BASE (0x40000C00U)



/* ================ USB Host Port Configuration ==================*/

#define CONFIG_USBHOST_PIPE_NUM 10

/* ================ EHCI Configuration ================ */

#define CONFIG_USB_EHCI_HCCR_BASE   (0x20072000)
#define CONFIG_USB_EHCI_HCOR_BASE   (0x20072000 + 0x10)
#define CONFIG_USB_EHCI_FRAME_LIST_SIZE 1024
// #define CONFIG_USB_EHCI_INFO_ENABLE
// #define CONFIG_USB_ECHI_HCOR_RESERVED_DISABLE
// #define CONFIG_USB_EHCI_CONFIGFLAG
// #define CONFIG_USB_EHCI_PORT_POWER

#endif


/* ================= enabling the lwip ================ */
#define CONFIG_USBDEV_RNDIS_USING_LWIP 1

#define USB_MEMCPY_H 1

#include "lwip.h"
#include <stdint.h>
#include <stddef.h>
#define IS_ALIGNED_DWORD(x) (((uintptr_t)(x) & (sizeof(uint32_t) - 1)) == 0)

static inline void *usb_memcpy(void *dest, const void *src, size_t n)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;

    // Handle the initial misaligned bytes, if any
    size_t leading_bytes = (uintptr_t)d & 3;
    if (leading_bytes) {
        leading_bytes = 4 - leading_bytes;
        if (n < leading_bytes) {
            leading_bytes = n;
        }
        //memcpy(d, s, leading_bytes);
		if(!dma_align_cpy_head_flag){
		dma_channel_configure(
					dma_align_cpy_head,            // Channel to be configured
					&align_cpy_head,              // The configuration we just created
					d,// The initial write address
					s,             // The initial read address
					leading_bytes,             // Number of transfers; in this case each is 1 byte.
					true             // Start immediately.
				);
		dma_align_cpy_head_flag = 1;
		} else {
			dma_channel_set_read_addr(dma_align_cpy_head, s, false);
			dma_channel_set_write_addr(dma_align_cpy_head, d, false);
			dma_channel_set_trans_count(dma_align_cpy_head,leading_bytes, true);
		}
        d += leading_bytes;
        s += leading_bytes;
        n -= leading_bytes;
    }

    // Copy 32-bit words
    uint32_t *dw = (uint32_t *)d;
    const uint32_t *sw = (const uint32_t *)s;
    size_t word_count = n / 4;
    /*
	for (size_t i = 0; i < word_count; ++i) {
        dw[i] = sw[i];
    }*/
	if(!dma_align_cpy_flag){
		dma_channel_configure(
						dma_align_cpy,            // Channel to be configured
						&align_cpy,              // The configuration we just created
						dw,// The initial write address
						sw,             // The initial read address
						word_count,             // Number of transfers; in this case each is 1 byte.
						true             // Start immediately.
					);
		dma_align_cpy_flag = 1;
	} else {
		dma_channel_set_read_addr(dma_align_cpy, sw, false);
		dma_channel_set_write_addr(dma_align_cpy, dw, false);
		dma_channel_set_trans_count(dma_align_cpy,word_count, true);
	}

    // Update pointers and remaining byte count
    d = (char *)(dw + word_count);
    s = (const char *)(sw + word_count);
    n -= word_count * 4;

    // Copy remaining bytes
    if (n > 0) {
        //memcpy(d, s, n);
		if(!dma_align_cpy_tail_flag){
		dma_channel_configure(
					dma_align_cpy_tail,            // Channel to be configured
					&align_cpy_tail,              // The configuration we just created
					d,// The initial write address
					s,             // The initial read address
					n,             // Number of transfers; in this case each is 1 byte.
					true             // Start immediately.
				);
			dma_align_cpy_tail_flag = 1;
		} else {
			dma_channel_set_read_addr(dma_align_cpy_tail, s, false);
			dma_channel_set_write_addr(dma_align_cpy_tail, d, false);
			dma_channel_set_trans_count(dma_align_cpy_tail,n, true);
		}
    }
	//dma_channel_wait_for_finish_blocking(dma_align_cpy);

    return dest;
}