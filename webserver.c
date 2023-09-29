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


char wifi_conn_detail[3][16];
#define UDP_PORT 4444
#define BEACON_MSG_LEN_MAX 127
#define BEACON_TARGET "255.255.255.255"
#define BEACON_INTERVAL_MS 1000
void run_udp_beacon() {
    struct udp_pcb* pcb = udp_new();

    ip_addr_t addr;
    ipaddr_aton(BEACON_TARGET, &addr);

    int counter = 0;
    while (true) {
		struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, BEACON_MSG_LEN_MAX+1, PBUF_RAM);
        char *req = (char *)p->payload;
        memset(req, 0, BEACON_MSG_LEN_MAX+1);
        snprintf(req, BEACON_MSG_LEN_MAX, "%d\n", counter);
        err_t er = udp_sendto(pcb, p, &addr, UDP_PORT);
        pbuf_free(p);
        if (er != ERR_OK) {
            //printf("Failed to send UDP packet! error=%d", er);
        } else {
            //printf("Sent packet %d\n", counter);
            counter++;
        }

        // Note in practice for this simple UDP transmitter,
        // the end result for both background and poll is the same

		#if PICO_CYW43_ARCH_POLL
        // if you are using pico_cyw43_arch_poll, then you must poll periodically from your
        // main loop (not from a timer) to check for Wi-Fi driver or lwIP work that needs to be done.
        cyw43_arch_poll();
        sleep_ms(BEACON_INTERVAL_MS);
		#else
        // if you are not using pico_cyw43_arch_poll, then WiFI driver and lwIP work
        // is done via interrupt in the background. This sleep is just an example of some (blocking)
        // work you might be doing.
        sleep_ms(BEACON_INTERVAL_MS);
		#endif
    }
}
void core1_entry() {
    cyw43_arch_init_with_country(CYW43_COUNTRY_INDIA);
    cyw43_arch_enable_sta_mode();
	cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
	
	char ssid[32] = "SSS_EXT"; // Global variable to store ssid
	char key[64] = "1234567890";  // Global variable to store key
	while(cyw43_arch_wifi_connect_timeout_ms(ssid, key, CYW43_AUTH_WPA2_AES_PSK, 10000));
	ip_addr_t ip = cyw43_state.netif[0].ip_addr;
	// Following strings are the components of ifcongig[]
	strcpy(wifi_conn_detail[0],ip4addr_ntoa(&ip));
	strcpy(wifi_conn_detail[1],ip4addr_ntoa(&cyw43_state.netif[0].netmask));
	strcpy(wifi_conn_detail[2],ip4addr_ntoa((ip_addr_t*)&cyw43_state.netif[0].gw.addr));
	//run_udp_beacon();
}

int main()
{
	set_sys_clock_khz(200000, true); 
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