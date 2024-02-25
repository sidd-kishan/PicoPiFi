/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include "board.h"
#include "usbd_core.h"
#include "usbd_rndis.h"
#include "cdc_rndis_device.h"
#include "lwip.h"


static volatile absolute_time_t next_wifi_try;
static volatile absolute_time_t comm_manager;
char connect_ssid[190], connect_ssid_decode[95], connect_password[190], connect_password_decode[95], retry_ms[6], enc_type[1], wifi_configuration[450], wifi_configuration_last[450];
uint8_t rndis_mac[6] = { 0x20, 0x89, 0x84, 0x6A, 0x96, 0xAA };
int wifi_congfig_len=0;
int eth_frame_send_success;

void printline(int cdc,char string[],int len){
	char buf[2048];
	//memcpy(buf,"\r\n",2);
	//memcpy(buf+2,string,len);
	//memcpy(buf+2+len,"\r\n\r\n\0",5);
	sprintf(buf,"\r\n%s\r\n\0",string);
	cdc_acm_data_send_with_dtr(cdc,(uint8_t *)buf,strlen(buf));
}

int hexCharToDecimal(char hexChar) {
    if (hexChar >= '0' && hexChar <= '9') {
        return hexChar - '0';
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return hexChar - 'a' + 10;
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return hexChar - 'A' + 10;
    }
    return -1; // Invalid hex character
}

// Function to decode a hex-encoded string
void hexDecode(const char* input, char* output) {
    int len = strlen(input);

    for (int i = 0, j = 0; i < len; i += 2, j++) {
        int highNibble = hexCharToDecimal(input[i]);
        int lowNibble = hexCharToDecimal(input[i + 1]);

        if (highNibble == -1 || lowNibble == -1) {
            //fprintf(stderr, "Error: Invalid hex characters in the input.\n");
            return;
        }

        output[j] = (char)((highNibble << 4) | lowNibble);
    }
}

void hex_encode(const uint8_t* input, char* output, size_t input_length) {
	for (size_t i = 0; i < input_length; ++i, output += 2) {
        sprintf(output, "%02x", input[i]);
    }
}

static int scan_result(void *env, const cyw43_ev_scan_result_t *result) {
	char wlan_scan_buffer[185],hex_encoded_ssid[65];
    if (result) { 
		hex_encode(result->ssid, hex_encoded_ssid, 32);
        int len = sprintf(wlan_scan_buffer, "ssid: %-64s rssi: %4d chan: %3d mac: %02x:%02x:%02x:%02x:%02x:%02x sec: %u",
            hex_encoded_ssid, result->rssi, result->channel,
            result->bssid[0], result->bssid[1], result->bssid[2], result->bssid[3], result->bssid[4], result->bssid[5],
            result->auth_mode);
		//memcpy(read_queue[0].buffer,wlan_scan_buffer,100);
		//read_queue[0].tail=len;
		printline(2,wlan_scan_buffer,len);
    }
    return 0;
}

void core1(){
    //user_init_lwip();
    lwip_init();
	multicore_lockout_victim_init();
	//int wifi_conn_error;
    while(true) {
        /**/
		//printline(2,(char *)read_queue[0].buffer,read_queue[0].tail);
		//read_queue[0].tail=0;
		//memcpy(connect_buf,(char *)read_queue[0].buffer,read_queue[0].tail);
		//read_queue[0].tail=0;
		//sscanf(connect_buf, "ssid: %*s password: %*s sec: %d", connect_ssid, connect_password, &connect_sec);
	
		
		//absolute_time_t start_time = get_absolute_time ();
		//while (absolute_time_diff_us (start_time, get_absolute_time()) < 1000000);
		if (absolute_time_diff_us(get_absolute_time(), next_wifi_try) < 0) {
				if(read_queue[0].tail>0){
				memset(connect_ssid, 0, 190);
				memset(connect_password, 0, 190);
				memset(retry_ms, 0, 6);
				enc_type[0]=0;
				for(int i=0,j=0,connect_config=0;i<read_queue[0].tail;i++){
					if(read_queue[0].buffer[i]==' '){
						connect_config+=1;
						j=0;
					}
					if(read_queue[0].buffer[i] != ' ' && connect_config==0 && i < 190){
						connect_ssid[j++]=read_queue[0].buffer[i];
					} else if(read_queue[0].buffer[i] != ' ' && connect_config==1 && i < 190+190){
						connect_password[j++]=read_queue[0].buffer[i];
					} else  if(read_queue[0].buffer[i] != ' ' && connect_config==2 && i < 190+190+6) {
						retry_ms[j++]=read_queue[0].buffer[i];
					} else if(i < 190+190+6+1) {
						enc_type[0] = read_queue[0].buffer[i];
					}
				}
				if(enc_type[0]=='X') {
					eth_frame_send_success = cyw43_wifi_leave(&cyw43_state, CYW43_ITF_STA);
					wifi_congfig_len = sprintf(wifi_configuration,"s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);
				}
				else if(enc_type[0]=='Y') watchdog_reboot(0,0,0);
				else if(enc_type[0]=='Z') reset_usb_boot(0, 0);
				read_queue[0].tail=0;
			}
			next_wifi_try = make_timeout_time_ms(1000);
		}
    }
}

int main(void)
{
    set_sys_clock_khz(200000, true);
	memset(wifi_configuration_last,0,450);
	memset(wifi_configuration,0,450);
	memcpy(wifi_configuration, flash_target_contents, sizeof(wifi_configuration));
	memcpy(wifi_configuration_last,wifi_configuration,450);
	sscanf(wifi_configuration,"s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);
	cyw43_arch_init_with_country(CYW43_COUNTRY_INDIA);
    cyw43_arch_enable_sta_mode();
	cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));
	cyw43_hal_get_mac(0, rndis_mac);
	//sscanf(wifi_configuration,"s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);

    cdc_rndis_init(rndis_mac);
	
	multicore_launch_core1(core1);
	
	absolute_time_t scan_time = nil_time;
    bool scan_in_progress = false;
	next_wifi_try = nil_time;
	
	while (1) {
		if (!link_up) {
			if (absolute_time_diff_us(get_absolute_time(), scan_time) < 0) {
				if (!scan_in_progress) {
					cyw43_wifi_scan_options_t scan_options = {0};
					int err = cyw43_wifi_scan(&cyw43_state, &scan_options, NULL, scan_result);
					if (err == 0) {
						//printf("\nPerforming wifi scan\n");
						scan_in_progress = true;
					} else {
						//printf("Failed to start scan: %d\n", err);
						scan_time = make_timeout_time_ms(2000); // wait 2s and scan again
					}
				} else if (!cyw43_wifi_scan_active(&cyw43_state)) {
					scan_time = make_timeout_time_ms(2000); // wait 2s and scan again
					scan_in_progress = false; 
				}
			}
            if (absolute_time_diff_us(get_absolute_time(), next_wifi_try) < 0) {
                //cyw43_arch_wifi_connect_async("ssid", "password", CYW43_AUTH_WPA2_AES_PSK);
				//connect_buf_len = sprintf(connect_buf, "ssid: %*s password: %*s sec: %d", connect_ssid, connect_password, connect_sec);
				//connect_buf[connect_buf_len+1]=' ';
				//printline(2,"----------",10);
				hexDecode(connect_ssid, connect_ssid_decode);
				//printline(2,connect_ssid_decode,strlen(connect_ssid_decode));
				hexDecode(connect_password, connect_password_decode);
				//printline(2,connect_password_decode,strlen(connect_password_decode));
				if(enc_type[0]=='7'){
					eth_frame_send_success = cyw43_arch_wifi_connect_async(connect_ssid_decode, connect_password_decode, CYW43_AUTH_WPA2_MIXED_PSK);
					wifi_congfig_len = sprintf(wifi_configuration,"s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);
					//wifi_configuration[wifi_congfig_len]=' ';
					//wifi_configuration[wifi_congfig_len+1]=' ';
					//printline(2,wifi_configuration,wifi_congfig_len-1);
				}else if(enc_type[0]=='5'){
					eth_frame_send_success = cyw43_arch_wifi_connect_async(connect_ssid_decode, connect_password_decode, CYW43_AUTH_WPA2_AES_PSK);
					wifi_congfig_len = sprintf(wifi_configuration, "s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);
					//wifi_configuration[wifi_congfig_len]=' ';
					//wifi_configuration[wifi_congfig_len+1]=' ';
					//printline(2,wifi_configuration,wifi_congfig_len-1);
				}else if(enc_type[0]=='3'){
					eth_frame_send_success = cyw43_arch_wifi_connect_async(connect_ssid_decode, connect_password_decode, CYW43_AUTH_WPA_TKIP_PSK);
					wifi_congfig_len = sprintf(wifi_configuration, "s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);
					//wifi_configuration[wifi_congfig_len]=' ';
					//wifi_configuration[wifi_congfig_len+1]=' ';
					//printline(2,wifi_configuration,wifi_congfig_len-1);
				}else if(enc_type[0]=='0'){
					eth_frame_send_success = cyw43_arch_wifi_connect_async(connect_ssid_decode, connect_password_decode, CYW43_AUTH_OPEN);
					wifi_congfig_len = sprintf(wifi_configuration, "s_a: %s p_a: %s r_a: %s c_a: %s ",connect_ssid,connect_password,retry_ms,enc_type);
					//wifi_configuration[wifi_congfig_len]=' ';
					//wifi_configuration[wifi_congfig_len+1]=' ';
					//printline(2,wifi_configuration,wifi_congfig_len-1);
				}
				//printline(2,enc_type,1);
				//printline(2,"----------",10);
                next_wifi_try = make_timeout_time_ms(10000);
            }
        } else {
			struct pbuf *p;
			p = usbd_rndis_eth_rx();
			if (p != NULL) {
				/* entry point to the LwIP stack */
				eth_frame_send_success=cyw43_send_ethernet(&cyw43_state, CYW43_ITF_STA, p->tot_len, (void*)p, true);
				//err = netif_data.input(p, &netif_data);
				pbuf_free(p);
				p = (struct pbuf *) eth_frame_send_success;
				p = NULL;
			}
			//if(link_up){
		//}
		}
    }
    return 0;
}

