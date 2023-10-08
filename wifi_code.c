#include "tusb_lwip_glue.h"
#include "pico/cyw43_arch.h"
#include "wifi_code.h"

pkt_s in_pkt;
struct pbuf *out_pkt;
static volatile bool link_up = false;
static volatile absolute_time_t next_wifi_try;

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
        //in_pkt.magic = MAGIC;
		out_pkt = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
        memcpy(out_pkt->payload, buf, len);
		if (tud_network_can_xmit(out_pkt->tot_len))
        {
			tud_network_xmit(out_pkt, 0 /* unused for this example */);
			//return ERR_OK;
        }
    
        /* transfer execution to TinyUSB in the hopes that it will finish transmitting the prior packet */
        tud_task();
		pbuf_free(out_pkt);
		out_pkt = NULL;
		//for(size_t i=0;i<len;i++)if(in_pkt.payload[i]==0)in_pkt.payload[i]='a';

        //if (!queue_try_add(&qinbound, &in_pkt)) {
            //DEBUG(("EQueue full\n"));
        //}
    } else {
        //DEBUG(("Oversized pkt = %d\n", len));
    }
}

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

void core1_entry() {
    cyw43_arch_init_with_country(CYW43_COUNTRY_INDIA);
    cyw43_arch_enable_sta_mode();
	cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));
	//cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
	cyw43_hal_get_mac(0, macaddr);
	while(1){
		if (!link_up) {
            if (absolute_time_diff_us(get_absolute_time(), next_wifi_try) < 0) {
                cyw43_arch_wifi_connect_async("ssid", "password", CYW43_AUTH_WPA2_AES_PSK);
                next_wifi_try = make_timeout_time_ms(10000);
            }
        }
		
		mutex_enter_blocking(&usb_ready);
		if (received_frame)
		{
			//in_pkt.len = received_frame->len;
			//memcpy(in_pkt.payload, received_frame->payload, received_frame->len);
			//if(in_pkt.len>200){
				//convertToHex(in_pkt.payload, in_pkt.len, packet_dump_msg);
				//packet_last_len=in_pkt.len;
			//}
			cyw43_send_ethernet(&cyw43_state, CYW43_ITF_STA, received_frame->len, received_frame->payload, false);
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