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
    "Hello",    // 0
    "counter",  // 1
    "GPIO",     // 2
    "state1",   // 3
    "state2",   // 4
    "state3",   // 5
    "state4",   // 6
    "bg1",      // 7
    "bg2",      // 8
    "bg3",      // 9
    "bg4",      // 10
	"wifiscan", // 11
	"wifiset",  // 12
	"wifinet",  // 13 
	"pktout"    // 14
};

u16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    switch (iIndex) {
        case 0: /* "Hello" */
            printed = snprintf(pcInsert, iInsertLen, "Hello user number %d!", rand());
            break;
        case 1: /* "counter" */
        {
            static int counter;
            counter++;
            printed = snprintf(pcInsert, iInsertLen, "%d", counter);
        }
            break;
        case 2: /* "GPIO" */
        {
            const float voltage = adc_read() * 3.3f / (1 << 12);
            printed = snprintf(pcInsert, iInsertLen, "%f", voltage);
        }
            break;
        case 3: /* "state1" */
        case 4: /* "state2" */
        case 5: /* "state3" */
        case 6: /* "state4" */
        {
            bool state;
            if(iIndex == 3)
                state = gpio_get(LED1);
            else if(iIndex == 4)
                state = gpio_get(LED2);
            else if(iIndex == 5)
                state = gpio_get(LED3);
            else if(iIndex == 6)
                state = gpio_get(LED4);

            if(state)
                printed = snprintf(pcInsert, iInsertLen, "checked");
            else
                printed = snprintf(pcInsert, iInsertLen, " ");
        }
          break;

        case 7:  /* "bg1" */
        case 8:  /* "bg2" */
        case 9:  /* "bg3" */
        case 10: /* "bg4" */
        {
            bool state;
            if(iIndex == 7)
                state = gpio_get(LED1);
            else if(iIndex == 8)
                state = gpio_get(LED2);
            else if(iIndex == 9)
                state = gpio_get(LED3);
            else if(iIndex == 10)
                state = gpio_get(LED4);

            if(state)
                printed = snprintf(pcInsert, iInsertLen, "\"background-color:green;\"");
            else
                printed = snprintf(pcInsert, iInsertLen, "\"background-color:red;\"");
        }
          break;
		case 11: /* wifiscan */
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
		case 12: /* wifiset */
			printed = snprintf(pcInsert, iInsertLen, "{\"ssid\":\"%s\",\"key\":\"%s\",\"enc\":\"%d\"}", wifi_ssid,wifi_key,wifi_enc);
			break;
		case 13: /* wifinet */
			printed = snprintf(pcInsert, iInsertLen, "{\"ip\":\"%s\",\"netmask\":\"%s\",\"gw\":\"%s\",\"mac\":\"%02x:%02x:%02x:%02x:%02x:%02x\"}", wifi_conn_detail[0],wifi_conn_detail[1],wifi_conn_detail[2], macaddr[0],macaddr[1],macaddr[2],
                                        macaddr[3],macaddr[4],macaddr[5]);
			break;
		case 14: /* pktout */
			{
				static pkt_s temp_pkt;
				while(queue_try_peek(&qinbound, &temp_pkt)) {
					queue_remove_blocking(&qinbound, &temp_pkt);
					printed = snprintf(pcInsert, iInsertLen, "%s%s%s%s%s%s%s",temp_pkt.payload[0],temp_pkt.payload[1],temp_pkt.payload[2],temp_pkt.payload[3],temp_pkt.payload[4],temp_pkt.payload[5],temp_pkt.payload[6]);
				}
				//else {
				//printed = snprintf(pcInsert, iInsertLen, "test");
				//}
			}
			break;
        default: /* unknown tag */
            printed = 0;
            break;
    }
      LWIP_ASSERT("sane length", printed <= 0xFFFF);
      return (u16_t)printed;
}

void ssi_init()
{
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    size_t i;
    for (i = 0; i < LWIP_ARRAYSIZE(ssi_example_tags); i++) {
        LWIP_ASSERT("tag too long for LWIP_HTTPD_MAX_TAG_NAME_LEN",
                    strlen(ssi_example_tags[i]) <= LWIP_HTTPD_MAX_TAG_NAME_LEN);
    }

      http_set_ssi_handler(ssi_handler,
                           ssi_example_tags, LWIP_ARRAYSIZE(ssi_example_tags)
      );
}
