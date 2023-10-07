#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/watchdog.h"
#include "hardware/structs/watchdog.h"
#include "pico/cyw43_arch.h"
#include "tusb_lwip_glue.h"
#include "lwipopts.h"
#include "cgi.h"
#include "ssi.h"
#include "wifi_code.h"
#include "lwip/dns.h"



uint8_t macaddr[6];

int main()
{
	set_sys_clock_khz(200000, true); 
	multicore_launch_core1(core1_entry);
	// Initialize tinyusb, lwip, dhcpd and httpd
	queue_init(&qinbound, sizeof(pkt_s), QSIZE);
    queue_init(&qoutbound, sizeof(pkt_s), QSIZE);
	mutex_init(&usb_ready);
	
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