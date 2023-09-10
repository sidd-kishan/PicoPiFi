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
#include "strings.h"

static volatile absolute_time_t next_wifi_try;
char wifi_ssid[32]="\0",wifi_key[32]="\0";
int wifi_enc=0;
static volatile bool link_up = false;
static int32_t wifi_status;
static int32_t wifi_rssi, wifi_rate;
static absolute_time_t next_wifi_status = (absolute_time_t)0;
char wifi_conn_detail[3][16];
//static queue_t qinbound; /* eth -> usb */
//static queue_t qoutbound; /* usb -> eth */

void cyw43_cb_tcpip_set_link_up(cyw43_t *self, int itf) {
    link_up = true;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
}

void cyw43_cb_tcpip_set_link_down(cyw43_t *self, int itf) {
    link_up = false;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
}

void cyw43_cb_process_ethernet(void *cb_data, int itf, size_t len, const uint8_t *buf) {
    //pkt_s in_pkt;

    if (len <= MTU) {
        //just coppied code from tusb_lwip_glue.c

        struct pbuf *p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
		
        if (p)
        {
            /* pbuf_alloc() has already initialized struct; all we need to do is copy the data */
            memcpy(p->payload, buf, len);
        
            /* store away the pointer for service_traffic() to later handle */
            received_frame = p;
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
	while(true) {
        if (!link_up&&strlen(wifi_ssid)>1) {
            if (absolute_time_diff_us(get_absolute_time(), next_wifi_try) < 0) {
                cyw43_arch_wifi_connect_async(wifi_ssid, wifi_key, wifi_enc);
                next_wifi_try = make_timeout_time_ms(10000);
            }
			if (absolute_time_diff_us(get_absolute_time(), next_wifi_status) < 0) {
            wifi_status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);
            cyw43_ioctl(&cyw43_state, (uint32_t)WLC_GET_RSSI<<1, sizeof(wifi_rssi), (uint8_t*)&wifi_rssi, CYW43_ITF_STA);
            cyw43_ioctl(&cyw43_state, (uint32_t)WLC_GET_RATE<<1, sizeof(wifi_rate), (uint8_t*)&wifi_rate, CYW43_ITF_STA);
            next_wifi_status = make_timeout_time_ms(500);
			}

			//ip_addr_t ip = cyw43_state.netif[0].ip_addr;
			// Following strings are the components of ifcongig[]
			//strcpy(wifi_conn_detail[0],ip4addr_ntoa(&ip));
			//strcpy(wifi_conn_detail[1],ip4addr_ntoa(&cyw43_state.netif[0].netmask));
			//strcpy(wifi_conn_detail[2],ip4addr_ntoa((ip_addr_t*)&cyw43_state.netif[0].gw.addr));
        }
        //cyw43_poll(); // for max. speed poll and don't wait for background timer
    }
}

int main()
{
	set_sys_clock_khz(200000, true); 
	//queue_init(&qinbound, sizeof(pkt_s), QSIZE);
    //queue_init(&qoutbound, sizeof(pkt_s), QSIZE);
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