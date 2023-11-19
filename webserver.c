#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "tusb_lwip_glue.h"
#include "bsp/board_api.h"
#include "lwipopts.h"
#include "wifi_code.h"

void cdc_task(void);

mutex_t wifi_ready;
uint8_t macaddr[6];
int loop_break=1;
int main()
{
	set_sys_clock_khz(200000, true);
	mutex_init(&wifi_ready);
	mutex_enter_blocking(&wifi_ready);
	multicore_launch_core1(core1_entry);
	watchdog_enable(4000, 1);
	// Initialize tinyusb, lwip, dhcpd and httpd
	mutex_init(&usb_ready);
	
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
		cdc_task();
    }
	loop_break=0;

    return 0;
}


// send characters to both CDC COMs
void echo_all(uint8_t itf, uint8_t buf[], uint32_t count)
{
	
  // echo to cdc
  if ( tud_cdc_connected() )
  {
    for(uint32_t i=0; i<count; i++)
    {
      tud_cdc_n_write_char(itf, buf[i]);

      if ( buf[i] == '\r' ) tud_cdc_n_write_char(itf, '\n');
    }
    tud_cdc_n_write_flush(itf);
  }
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void)
{
  uint8_t itf;

  for (itf = 0; itf < CFG_TUD_CDC; itf++)
  {
    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    // if ( tud_cdc_n_connected(itf) )
    {
      if ( tud_cdc_n_available(itf) )
      {
        uint8_t buf[64];

        uint32_t count = tud_cdc_n_read(itf, buf, sizeof(buf));

        // echo back to both serial ports
        echo_all(0, buf, count);
        //echo_all(1, buf, count);
	  }
    }
  }
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
  (void) itf;

  // connected
  if ( dtr && rts )
  {
    // print initial message when connected
    tud_cdc_write_str("\r\nTinyUSB WebUSB device example\r\n");
  }
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf)
{
  (void) itf;
}