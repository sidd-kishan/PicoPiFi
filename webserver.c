#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/watchdog.h"
#include "hardware/structs/watchdog.h"
#include "pico/cyw43_arch.h"
#include "tusb_lwip_glue.h"
#include "lwipopts.h"
#include "cgi.h"
#include "ssi.h"
#include "lwip/dns.h"
#include "lwip/sys.h"

static volatile bool link_up = false;
char wifi_conn_detail[3][16];
static queue_t qinbound; /* eth -> usb */
static queue_t qoutbound; /* usb -> eth */

void cyw43_cb_tcpip_set_link_up(cyw43_t *self, int itf) {
    link_up = true;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
}

void cyw43_cb_tcpip_set_link_down(cyw43_t *self, int itf) {
    link_up = false;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
}

void cyw43_cb_process_ethernet(void *cb_data, int itf, size_t len, const uint8_t *buf) {
    pkt_s in_pkt;

    if (len <= MTU) {
        in_pkt.len = len;
        memcpy(in_pkt.payload, buf, len);

        if (!queue_try_add(&qinbound, &in_pkt)) {
            //DEBUG(("EQueue full\n"));
        }
    } else {
        //DEBUG(("Oversized pkt = %d\n", len));
    }
}

void core1_entry() {
    cyw43_arch_init_with_country(CYW43_COUNTRY_INDIA);
    cyw43_arch_enable_sta_mode();
	cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
	
	//char ssid[32] = "SSS_EXT"; // Global variable to store ssid
	//char key[64] = "1234567890";  // Global variable to store key
	//while(cyw43_arch_wifi_connect_timeout_ms(ssid, key, CYW43_AUTH_WPA2_AES_PSK, 10000));
	//ip_addr_t ip = cyw43_state.netif[0].ip_addr;
	// Following strings are the components of ifcongig[]
	//strcpy(wifi_conn_detail[0],ip4addr_ntoa(&ip));
	//strcpy(wifi_conn_detail[1],ip4addr_ntoa(&cyw43_state.netif[0].netmask));
	//strcpy(wifi_conn_detail[2],ip4addr_ntoa((ip_addr_t*)&cyw43_state.netif[0].gw.addr));
}

int main()
{
	set_sys_clock_khz(200000, true); 
	queue_init(&qinbound, sizeof(pkt_s), QSIZE);
    queue_init(&qoutbound, sizeof(pkt_s), QSIZE);
	multicore_launch_core1(core1_entry);
	// Initialize tinyusb, lwip, dhcpd and httpd
    init_lwip();
    wait_for_netif_is_up();
    dhcpd_init();
    httpd_init();
    ssi_init();
    cgi_init();
    
    while (true)
    {
        tud_task();
        service_traffic();
    }

    return 0;
}