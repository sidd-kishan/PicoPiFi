#ifndef __CGI_H__
#define __CGI_H__
#include "pico/types.h"
extern char wifi_ssid[32],wifi_key[32];
extern int wifi_enc;
static int32_t wifi_status;
static int32_t wifi_rssi, wifi_rate;
#ifdef __cplusplus
extern "C" {
#endif
// GPIOs for Leds
#define LED1	18
#define LED2	19
#define LED3	20
#define LED4	21
#define WLC_GET_RATE                       ( (uint32_t)12 )
#define WLC_GET_RSSI                       ( (uint32_t)127 )

/* initialize the CGI handler */
void  cgi_init();

static const char *cgi_toggle_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

static const char *cgi_reset_usb_boot(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
static const char *cgi_reset_usb_boot(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
/* CGI handler for LED control */
const char * cgi_handler_basic(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
/* CGI handler for LED control with feedback*/
const char * cgi_handler_extended(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

const char *
wifi_cred_set(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

/* led control and debugging info */
void Led_On(int led);
void Led_Off(int led);
static absolute_time_t next_wifi_status;
static volatile absolute_time_t next_wifi_try;
#ifdef __cplusplus
};
#endif
#endif // __CGI_H__
