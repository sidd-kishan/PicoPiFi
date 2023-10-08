#ifdef __cplusplus
 extern "C" {
#endif
#include "tusb.h"
#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "pico/util/queue.h"
#include "pico/mutex.h"
#define QSIZE 16
#define MTU 1500
static queue_t qinbound; /* eth -> usb */
static queue_t qoutbound; /* usb -> eth */
typedef struct {
    uint16_t len;
    uint8_t payload[MTU];
} pkt_s;
extern int packet_stat_rx;
extern int packet_stat_tx;
extern char packet_dump_msg[8000];
extern int packet_last_len;
extern pkt_s in_pkt;
extern struct pbuf *out_pkt;
extern mutex_t usb_ready;
extern struct pbuf *received_frame;
void run_udp_beacon();
void core1_entry();

#define UDP_PORT 4444
#define BEACON_MSG_LEN_MAX 127
#define BEACON_TARGET "255.255.255.255"
#define BEACON_INTERVAL_MS 1000

#ifdef __cplusplus
 }
#endif