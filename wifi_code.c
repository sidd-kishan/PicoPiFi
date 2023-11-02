#include "tusb_lwip_glue.h"
#include "pico/cyw43_arch.h"
#include "wifi_code.h"

char scan_results[93];
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
    if (len <= MTU) {
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
    } else {
        //DEBUG(("Oversized pkt = %d\n", len));
    }
}

char wifi_conn_detail[3][16];


int scan_result(void *env, const cyw43_ev_scan_result_t *result) {
	//char result_buf[93];
    if (result) { 
	//xSemaphoreTake(wifi_scan_info_mutex, portMAX_DELAY);
        sprintf(scan_results,"{\"ssid\":\"%s\",\"rssi\":\"%4d\",\"chan\":\"%3d\",\"mac\": \"%02x:%02x:%02x:%02x:%02x:%02x\",\"sec\":\"%u\"}",
            result->ssid, result->rssi, result->channel,
            result->bssid[0], result->bssid[1], result->bssid[2], result->bssid[3], result->bssid[4], result->bssid[5],
            result->auth_mode);
			//if (!queue_try_add(&qinbound, result_buf)) {
            //DEBUG(("EQueue full\n"));
			//}
	//xSemaphoreGive(wifi_scan_info_mutex);
    }
    return 0;
}

void core1_entry() {
	cyw43_arch_init_with_country(CYW43_COUNTRY_INDIA);
    cyw43_arch_enable_sta_mode();
	cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));
	cyw43_hal_get_mac(0, macaddr);
	mutex_exit(&wifi_ready);
	while(1){
		if (!link_up) {
			//scan area
			absolute_time_t scan_time = nil_time;
			bool scan_in_progress = false;
			if (absolute_time_diff_us(get_absolute_time(), scan_time) < 0) {
				if (!scan_in_progress) {
					cyw43_wifi_scan_options_t scan_options = {0};
					int err = cyw43_wifi_scan(&cyw43_state, &scan_options, NULL, scan_result);
					if (err == 0) {
						//printf("\nPerforming wifi scan\n");
						scan_in_progress = true;
					} else {
						//printf("Failed to start scan: %d\n", err);
						scan_time = make_timeout_time_ms(10000); // wait 2s and scan again
					}
				} else if (!cyw43_wifi_scan_active(&cyw43_state)) {
					scan_time = make_timeout_time_ms(10000); // wait 2s and scan again
					scan_in_progress = false; 
				}
			}
			//need to send the scan_results
			//scan area end
			//wifi connect
            if (absolute_time_diff_us(get_absolute_time(), next_wifi_try) < 0) {
                cyw43_arch_wifi_connect_async("ssid", "password", CYW43_AUTH_WPA2_AES_PSK);
                next_wifi_try = make_timeout_time_ms(10000);
            }
			//wifi connect end
        } else {
			mutex_enter_blocking(&usb_ready);
			if (received_frame)
			{
				cyw43_send_ethernet(&cyw43_state, CYW43_ITF_STA, received_frame->len, received_frame->payload, false);
			}
			mutex_exit(&usb_ready);
		}
	}
}