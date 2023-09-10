#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "cgi.h"
#include "cstring"
#include "hardware/gpio.h"
#include "pico/cyw43_arch.h"
#include "pico/bootrom.h"

static int  LED_STATUS = 1;

static const tCGI cgi_handlers[] = {
    {
        /* Html request for "/leds.cgi" will start cgi_handler_basic */
        "/leds.cgi", cgi_handler_basic
    },
    {
        /* Html request for "/leds2.cgi" will start cgi_handler_extended */
        "/leds_ext.cgi", cgi_handler_extended
    },
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

/* cgi-handler triggered by a request for "/leds.cgi" */
const char *
cgi_handler_basic(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    int i=0;

    /* We use this handler for one page request only: "/leds.cgi"
     * and it is at position 0 in the tCGI array (see above).
     * So iIndex should be 0.
     */
    printf("cgi_handler_basic called with index %d\n", iIndex);

    /* All leds off */
    Led_Off(LED1);
    Led_Off(LED2);
    Led_Off(LED3);
    Led_Off(LED4);

    /* Check the query string.
     * A request to turn LED2 and LED4 on would look like: "/leds.cgi?led=2&led=4"
     */
    for (i = 0; i < iNumParams; i++){
        /* check if parameter is "led" */
        if (strcmp(pcParam[i] , "led") == 0){
            /* look ar argument to find which led to turn on */
            if(strcmp(pcValue[i], "1") == 0)
                Led_On(LED1);
            else if(strcmp(pcValue[i], "2") == 0)
                Led_On(LED2);
            else if(strcmp(pcValue[i], "3") == 0)
                Led_On(LED3);
            else if(strcmp(pcValue[i], "4") == 0)
                Led_On(LED4);
        }
    }

    /* Our response to the "SUBMIT" is to simply send the same page again*/
    return "/cgi.html";
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
/* cgi-handler triggered by a request for "/leds_ext.cgi".
 *
 * It is almost identical to cgi_handler_basic().
 * Both handlers could be easily implemented in one function -
 * distinguish them by looking at the iIndex parameter.
 * I left it this way to show how to implement two (or more)
 * enirely different handlers.
 */
const char *
cgi_handler_extended(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    int i=0;

    /* We use this handler for one page request only: "/leds_ext.cgi"
     * and it is at position 1 in the tCGI array (see above).
     * So iIndex should be 1.
     */
    printf("cgi_handler_extended called with index %d\n", iIndex);

    /* All leds off */
    Led_Off(LED1);
    Led_Off(LED2);
    Led_Off(LED3);
    Led_Off(LED4);

    /* Check the query string.
     * A request to turn LED2 and LED4 on would look like: "/leds.cgi?led=2&led=4"
     */
    for (i = 0; i < iNumParams; i++){
        /* check if parameter is "led" */
        if (strcmp(pcParam[i] , "led") == 0){
            /* look ar argument to find which led to turn on */
            if(strcmp(pcValue[i], "1") == 0)
                Led_On(LED1);
            else if(strcmp(pcValue[i], "2") == 0)
                Led_On(LED2);
            else if(strcmp(pcValue[i], "3") == 0)
                Led_On(LED3);
            else if(strcmp(pcValue[i], "4") == 0)
                Led_On(LED4);
        }
    }

    /* Our response to the "SUBMIT" is to send "/ssi_cgi.shtml".
     * The extension ".shtml" tells the server to insert some values
     * which show the user what has been done in response.
     */
    return "/ssi_cgi.shtml";
}

/* initialize the CGI handler */
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


