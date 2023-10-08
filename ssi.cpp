#include "hardware/adc.h"
#include "lwip/apps/httpd.h"
#include "hardware/gpio.h"
#include "lwip/def.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"
#include "cstring"
#include "pico/cyw43_arch.h"
#include "wifi_code.h"
char scan_results[93];

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
// max length of the tags defaults to be 8 chars
// LWIP_HTTPD_MAX_TAG_NAME_LEN
const char * __not_in_flash("httpd") ssi_example_tags[] = {
	"wifiscan", // 0
	"wifiset",  // 1
	"wifinet",  // 2 
	"pktout"    // 3
};

void convertToHex(uint8_t* byteArray, uint16_t size, char* hexString) {
    for (uint16_t i = 0; i < size; i++) {
        unsigned char value = byteArray[i];

        char hex[4] = {0, 0, ' ', '\0'};
        char* hex_p = hex;

        unsigned char TEMP_byte = 0;

        TEMP_byte = value / 16;

        if (TEMP_byte < 10) {
            *hex_p = 48 + TEMP_byte;
        } else {
            *hex_p = 55 + TEMP_byte;
        }

        hex_p++;

        TEMP_byte = value % 16;

        if (TEMP_byte < 10) {
            *hex_p = 48 + TEMP_byte;
        } else {
            *hex_p = 55 + TEMP_byte;
        }

        strcat(hexString, hex);
    }
}


u16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    switch (iIndex) {
		case 0: /* wifiscan */
		{
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
			printed = snprintf(pcInsert, iInsertLen, "%s", scan_results);
		}
			break;
		case 1: /* wifiset */
			printed = snprintf(pcInsert, iInsertLen, "{\"ssid\":\"%s\",\"key\":\"%s\",\"enc\":\"%d\"}", wifi_ssid,wifi_key,wifi_enc);
			break;
		case 2: /* wifinet */
			printed = snprintf(pcInsert, iInsertLen, "{\"ip\":\"%s\",\"netmask\":\"%s\",\"gw\":\"%s\",\"mac\":\"%02x:%02x:%02x:%02x:%02x:%02x\"}", wifi_conn_detail[0],wifi_conn_detail[1],wifi_conn_detail[2], macaddr[0],macaddr[1],macaddr[2],
                                        macaddr[3],macaddr[4],macaddr[5]);
			break;
		case 3: /* pktout */
			{
				//int output_index = queue_get_level(&qinbound); // Keep track of the current index in dmp_output

				//char hexString[3000] = ""; // Make sure it's large enough to hold the result
				//convertToHex(in_pkt.payload, in_pkt.len, hexString);

				//dmp_output[3000]=0;
				//printed = snprintf(pcInsert, iInsertLen, "%s",packet_stat_msg);
				//for(int i=0;i<in_pkt.len;i++)if(!in_pkt.payload[i])in_pkt.payload[i]='a';
				printed = snprintf(pcInsert, iInsertLen, "%d %s",packet_last_len,packet_dump_msg);
				//in_pkt.len=0;
			}
			break;
        default: /* unknown tag */
            printed = 0;
            break;
    }
      //LWIP_ASSERT("sane length", printed <= 0xFFFF);
      return (u16_t)printed;
}

void ssi_init()
{
    //adc_init();
    //adc_gpio_init(26);
    //adc_select_input(0);
    size_t i;
    for (i = 0; i < LWIP_ARRAYSIZE(ssi_example_tags); i++) {
        LWIP_ASSERT("tag too long for LWIP_HTTPD_MAX_TAG_NAME_LEN",
                    strlen(ssi_example_tags[i]) <= LWIP_HTTPD_MAX_TAG_NAME_LEN);
    }

      http_set_ssi_handler(ssi_handler,
                           ssi_example_tags, LWIP_ARRAYSIZE(ssi_example_tags)
      );
}
