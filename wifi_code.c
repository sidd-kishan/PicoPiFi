#include "tusb_lwip_glue.h"
#include "pico/cyw43_arch.h"
#include "wifi_code.h"
pkt_s in_pkt;
void convertToHex(uint8_t* byteArray, uint16_t size, char* hexString) {
    hexString[0] = '\0';
    for (uint16_t i = 0; i < size; i++) {
        unsigned char value = byteArray[i];

        char hex[4] = {0, 0,' ', '\0'};
        char* hex_p = hex;

        uint8_t TEMP_byte = 0;

        TEMP_byte = (value >> 4) & 0x0F;  // Extract most significant nibble

        if (TEMP_byte < 10) {
            *hex_p = 48 + TEMP_byte;
        } else {
            *hex_p = 55 + TEMP_byte;
        }

        hex_p++;

        TEMP_byte = value & 0x0F;  // Extract least significant nibble

        if (TEMP_byte < 10) {
            *hex_p = 48 + TEMP_byte;
        } else {
            *hex_p = 55 + TEMP_byte;
        }

        strcat(hexString, hex);
    }
}


char wifi_conn_detail[3][16];
char packet_dump_msg[8000];
int packet_last_len;

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
	//cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
	cyw43_hal_get_mac(0, macaddr);
	while(1){
		mutex_enter_blocking(&usb_ready);
		if (received_frame)
		{
			in_pkt.len = received_frame->len;
			memcpy(in_pkt.payload, received_frame->payload, received_frame->len);
			//if(in_pkt.len>200){
				convertToHex(in_pkt.payload, in_pkt.len, packet_dump_msg);
				packet_last_len=in_pkt.len;
			//}
			//cyw43_send_ethernet(&cyw43_state, CYW43_ITF_STA, received_frame->len, received_frame->payload, false);
		}
		mutex_exit(&usb_ready);
		
	}
    //char ssid[32] = "SSS_EXT"; // Global variable to store ssid
	//char key[64] = "1234567890";  // Global variable to store key
	//while(cyw43_arch_wifi_connect_timeout_ms(ssid, key, CYW43_AUTH_WPA2_AES_PSK, 10000));
	//ip_addr_t ip = cyw43_state.netif[0].ip_addr;
	// Following strings are the components of ifcongig[]
	//strcpy(wifi_conn_detail[0],ip4addr_ntoa(&ip));
	//strcpy(wifi_conn_detail[1],ip4addr_ntoa(&cyw43_state.netif[0].netmask));
	//strcpy(wifi_conn_detail[2],ip4addr_ntoa((ip_addr_t*)&cyw43_state.netif[0].gw.addr));
	//run_udp_beacon();
}