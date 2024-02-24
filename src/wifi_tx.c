#include "lwip.h"
#include "pico/cyw43_arch.h"

#include "usbd_core.h"
#include "usbd_rndis.h"

struct pbuf *out_pkt;
bool link_up = false;


const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);


void cyw43_cb_tcpip_set_link_up(cyw43_t *self, int itf) {
    if(link_up==0 && (memcmp(wifi_configuration_last, wifi_configuration, 450))!=0){
		link_up=1;
		uint8_t* myDataAsBytes = (uint8_t*) wifi_configuration;
		int myDataSize = sizeof(wifi_configuration);
		
		int writeSize = (myDataSize / FLASH_PAGE_SIZE) + 1; // how many flash pages we're gonna need to write
		int sectorCount = ((writeSize * FLASH_PAGE_SIZE) / FLASH_SECTOR_SIZE) + 1; // how many flash sectors we're gonna need to erase
			
		//printf("Programming flash target region...\n");

		uint32_t interrupts = save_and_disable_interrupts();
		
		multicore_lockout_start_blocking();
		
		flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE * sectorCount);
		flash_range_program(FLASH_TARGET_OFFSET, myDataAsBytes, FLASH_PAGE_SIZE * writeSize);
		
		multicore_lockout_end_blocking();
		
		restore_interrupts(interrupts);
		
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
		watchdog_reboot(0,0,0);
	} else if(link_up==0){
		link_up=1;
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
	}
}

void cyw43_cb_tcpip_set_link_down(cyw43_t *self, int itf) {
    if(link_up && enc_type[0]=='X'){
		link_up = 0;
		uint8_t* myDataAsBytes = (uint8_t*) wifi_configuration;
		int myDataSize = sizeof(wifi_configuration);
		
		int writeSize = (myDataSize / FLASH_PAGE_SIZE) + 1; // how many flash pages we're gonna need to write
		int sectorCount = ((writeSize * FLASH_PAGE_SIZE) / FLASH_SECTOR_SIZE) + 1; // how many flash sectors we're gonna need to erase
			
		//printf("Programming flash target region...\n");

		uint32_t interrupts = save_and_disable_interrupts();
		
		multicore_lockout_start_blocking();
		
		flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE * sectorCount);
		flash_range_program(FLASH_TARGET_OFFSET, myDataAsBytes, FLASH_PAGE_SIZE * writeSize);
		
		multicore_lockout_end_blocking();
		
		restore_interrupts(interrupts);
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
		watchdog_reboot(0,0,0);
	} else if(link_up){
		link_up = 0;
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, link_up);
	}
}

void cyw43_cb_process_ethernet(void *cb_data, int itf, size_t len, const uint8_t *buf) {
	if (len <= 1500) {
		out_pkt = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
		//memcpy(out_pkt->payload, buf, len);
		pbuf_take(out_pkt, buf, len);
		int ret = usbd_rndis_eth_tx(out_pkt);
		if (0 != ret) {
			ret = ERR_BUF;
		}
		pbuf_free(out_pkt);
		out_pkt = NULL;
	}
}
