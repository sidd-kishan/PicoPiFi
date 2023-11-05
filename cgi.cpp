#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "cgi.h"
#include "cstring"
#include "hardware/gpio.h"
#include "pico/cyw43_arch.h"
#include "pico/bootrom.h"

static int  LED_STATUS = 1;
char wifi_ssid[32],wifi_key[32];
int wifi_enc;
static const tCGI cgi_handlers[] = {
	{
		"/toggle_led", cgi_toggle_led
	},
    {
		"/reset_usb_boot", cgi_reset_usb_boot
    },
	{
		"/wifi_set", wifi_cred_set
	}
};

// let our webserver do some dynamic handling
static const char *cgi_toggle_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
	LED_STATUS=!LED_STATUS;
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, LED_STATUS);
    return "/index.html";
}

static const char *cgi_reset_usb_boot(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    reset_usb_boot(0, 0);
    return "/index.html";
}

const char *
wifi_cred_set(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    for (int i = 0; i < iNumParams; i++){
        /* check if parameter is "led" */
        if (strcmp(pcParam[i] , "ssid") == 0){
            strcpy(wifi_ssid, pcValue[i]);
        } else if(strcmp(pcParam[i] , "key") == 0){
			strcpy(wifi_key, pcValue[i]);
		} else if(strcmp(pcParam[i] , "enc") == 0){
			wifi_enc=((int)pcValue[i][0])-48;
		}
    }

    /* Our response to the "SUBMIT" is to send "/ssi_cgi.shtml".
     * The extension ".shtml" tells the server to insert some values
     * which show the user what has been done in response.
     */
    return "/wificred.shtml";
}

/* initialize the CGI handler CYW43_ARRAY_SIZE LWIP_ARRAYSIZE*/
void
cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, CYW43_ARRAY_SIZE(cgi_handlers));

    for(int i = LED1; i <= LED4; i++){
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, 0);
    }
}

/* led control and debugging info */
void
Led_On(int led)
{
    printf("GPIO%d on\n", led);
    gpio_put(led, 1);
}

void
Led_Off(int led)
{
    printf("GPIO%d off\n", led);
    gpio_put(led, 0);
}


