#ifndef _TUSB_LWIP_GLUE_H_
#define _TUSB_LWIP_GLUE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "tusb.h"
#include "usb_descriptors.h"
#include "dhserver.h"
#include "dnserver.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "lwip/apps/httpd.h"

void init_lwip();
void wait_for_netif_is_up();
void dhcpd_init();
void service_traffic();
extern mutex_t wifi_ready;
extern uint8_t macaddr[6];
void webserial_task(void);
void cdc_task(void);
void echo_all(uint8_t buf[], uint32_t count);

#ifdef __cplusplus
 }
#endif

#endif