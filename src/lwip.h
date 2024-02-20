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

// We're going to erase and reprogram a region 256k from the start of flash.
// Once done, we can access this at XIP_BASE + 256k.
#define FLASH_TARGET_OFFSET (1280 * 1024)

extern const uint8_t *flash_target_contents;

extern struct pbuf *out_pkt;
extern bool link_up;
static void  lwip_service_traffic(void);
void printline(int cdc,char string[],int len);

extern char connect_ssid[190], connect_ssid_decode[95], connect_password[190], connect_password_decode[95], retry_ms[6], enc_type[1], wifi_configuration[450], 	wifi_configuration_last[450];
extern int wifi_congfig_len;