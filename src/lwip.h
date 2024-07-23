#include "lwip/init.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/pbuf.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/cyw43_arch.h"
#include "hardware/watchdog.h"
#include "pico/bootrom.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

// We're going to erase and reprogram a region 256k from the start of flash.
// Once done, we can access this at XIP_BASE + 256k.
#define FLASH_TARGET_OFFSET (1280 * 1024)

extern const uint8_t *flash_target_contents;

extern struct pbuf *out_pkt;
extern bool link_up;
static void  lwip_service_traffic(void);
void printline(int cdc,char string[],int len);
void dma_handler();
extern int chan;
extern int chan_2;
extern int dma_memset_0;
extern int dma_align_cpy_head;
extern int dma_align_cpy;
extern int dma_align_cpy_tail;
extern int dma_usb_cpy;

extern dma_channel_config c;
extern dma_channel_config c_2;
extern dma_channel_config memset_0;
extern dma_channel_config align_cpy_head;
extern dma_channel_config align_cpy;
extern dma_channel_config align_cpy_tail;
extern dma_channel_config usb_cpy;

extern int dma_memset_0_flag, chan_flag, chan_2_flag, dma_usb_cpy_flag, dma_align_cpy_head_flag, dma_align_cpy_flag, dma_align_cpy_tail_flag;

extern char connect_ssid[190], connect_ssid_decode[95], connect_password[190], connect_password_decode[95], retry_ms[6], enc_type[1], wifi_configuration[450], 	wifi_configuration_last[450];
extern int wifi_congfig_len;