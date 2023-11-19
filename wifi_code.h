#ifdef __cplusplus
 extern "C" {
#endif
#include "tusb.h"
#include "lwip/init.h"
#include "pico/mutex.h"
#include "hardware/watchdog.h"
#define MTU 1500
typedef struct {
    uint16_t len;
    uint8_t payload[MTU];
} pkt_s;
extern pkt_s in_pkt;
extern struct pbuf *out_pkt;
extern mutex_t usb_ready;
extern struct pbuf *received_frame;
extern volatile bool link_up;
void core1_entry();
extern int loop_break;
#ifdef __cplusplus
 }
#endif