#ifdef __cplusplus
 extern "C" {
#endif
#include "tusb.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "pico/mutex.h"
#define MTU 1500
typedef struct {
    uint16_t len;
    uint8_t payload[MTU];
} pkt_s;
extern pkt_s in_pkt;
extern struct pbuf *out_pkt;
extern mutex_t usb_ready;
extern struct pbuf *received_frame;
void core1_entry();
extern char scan_results[93];
extern char ssid[32],key[32];
#ifdef __cplusplus
 }
#endif