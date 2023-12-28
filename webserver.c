#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "tusb_lwip_glue.h"
#include "lwipopts.h"
#include "wifi_code.h"


mutex_t wifi_ready;
uint8_t macaddr[6];
int loop_break=1;
int main()
{
	set_sys_clock_khz(200000, true);
	mutex_init(&wifi_ready);
	mutex_enter_blocking(&wifi_ready);
	multicore_launch_core1(core1_entry);
	// Initialize tinyusb, lwip, dhcpd and httpd
	
    init_lwip();
    wait_for_netif_is_up();
    //dhcpd_init();
    //httpd_init();
    //ssi_init();
    //cgi_init();
    
    while (loop_break)
    {
        tud_task();
        service_traffic();
		//sleep_us(1);
    }
	loop_break=0;

    return 0;
}