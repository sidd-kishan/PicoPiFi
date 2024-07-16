#include "lwip.h"
#include "pico/cyw43_arch.h"

#include "usbd_core.h"
#include "usbd_rndis.h"

struct pbuf *out_pkt;
struct pbuf *out_pkt_dma;
struct pbuf *out_pkt_dma_2;
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
		/*if((dma_hw->ch[chan].ctrl_trig & DMA_CH0_CTRL_TRIG_BUSY_BITS)&&(dma_hw->ch[chan_2].ctrl_trig & DMA_CH0_CTRL_TRIG_BUSY_BITS)){
			
		} else*/ if(!(dma_hw->ch[chan].ctrl_trig & DMA_CH0_CTRL_TRIG_BUSY_BITS)) {
			out_pkt_dma = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
			//memcpy(out_pkt->payload, buf, len);
			//pbuf_take(out_pkt, buf, len);
			int transfer = (len%2==0)?(len/2):((len+1)/2);
			dma_channel_config c = dma_channel_get_default_config(chan);
			channel_config_set_transfer_data_size(&c, DMA_SIZE_16);
			channel_config_set_read_increment(&c, true);
			channel_config_set_write_increment(&c, true);

			dma_channel_configure(
				chan,            // Channel to be configured
				&c,              // The configuration we just created
				out_pkt_dma->payload,// The initial write address
				buf,             // The initial read address
				transfer,             // Number of transfers; in this case each is 1 byte.
				true             // Start immediately.
			);
			}
			else if(!(dma_hw->ch[chan_2].ctrl_trig & DMA_CH0_CTRL_TRIG_BUSY_BITS)){
				out_pkt_dma_2 = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
				//memcpy(out_pkt->payload, buf, len);
				//pbuf_take(out_pkt, buf, len);
				int transfer_2 = (len%2==0)?(len/2):((len+1)/2);
				dma_channel_config c_2 = dma_channel_get_default_config(chan_2);
				channel_config_set_transfer_data_size(&c_2, DMA_SIZE_16);
				channel_config_set_read_increment(&c_2, true);
				channel_config_set_write_increment(&c_2, true);

				dma_channel_configure(
					chan_2,            // Channel to be configured
					&c_2,              // The configuration we just created
					out_pkt_dma_2->payload,// The initial write address
					buf,             // The initial read address
					transfer_2,             // Number of transfers; in this case each is 1 byte.
					true             // Start immediately.
				);
			} else {
				out_pkt = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
				out_pkt->payload = buf;
				int ret = usbd_rndis_eth_tx(out_pkt);
				//if (0 != ret) {
				//	ret = ERR_BUF;
				//}
				pbuf_free(out_pkt);
			}
}

void dma_handler() {
	int ret = usbd_rndis_eth_tx(out_pkt_dma);
	if (0 != ret) {
		ret = ERR_BUF;
	}
	pbuf_free(out_pkt_dma);
    dma_hw->ints0 = 1u << chan;
}

void dma_handler_2() {
	int ret = usbd_rndis_eth_tx(out_pkt_dma_2);
	if (0 != ret) {
		ret = ERR_BUF;
	}
	pbuf_free(out_pkt_dma_2);
    dma_hw->ints1 = 1u << chan_2;
}