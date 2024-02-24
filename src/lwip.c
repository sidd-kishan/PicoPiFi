#include "lwip.h"
#include "usbd_core.h"
#include "usbd_rndis.h"
#include "pico/cyw43_arch.h"


/* Macro Definition */
#define LWIP_SYS_TIME_MS 1
#define NUM_DHCP_ENTRY   3
#define PADDR(ptr)       ((ip_addr_t *)ptr)

static uint32_t     sys_tick;

static void  lwip_service_traffic(void);

/* Function Definition */
void sys_timer_callback(void)
{
    sys_tick++;
}

uint32_t sys_now(void)
{
    return sys_tick;
}

static void lwip_service_traffic(void)
{
    //err_t        err;
    struct pbuf *p;

    p = usbd_rndis_eth_rx();

    if (p != NULL) {
        /* entry point to the LwIP stack */
        int eth_frame_send_success=cyw43_send_ethernet(&cyw43_state, CYW43_ITF_STA, p->tot_len, (void*)p, true);
	    //err = netif_data.input(p, &netif_data);
		pbuf_free(p);
		p = (struct pbuf *) eth_frame_send_success;
    }
}