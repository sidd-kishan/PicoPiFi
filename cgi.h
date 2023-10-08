#ifndef __CGI_H__
#define __CGI_H__
extern char wifi_ssid[32],wifi_key[32];
extern int wifi_enc;
#ifdef __cplusplus
extern "C" {
#endif
// GPIOs for Leds
#define LED1	18
#define LED2	19
#define LED3	20
#define LED4	21

/* initialize the CGI handler */
void  cgi_init();

static const char *cgi_toggle_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

static const char *cgi_reset_usb_boot(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

const char *
wifi_cred_set(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

extern uint8_t macaddr[6];

/* led control and debugging info */
void Led_On(int led);
void Led_Off(int led);

#ifdef __cplusplus
};
#endif
#endif // __CGI_H__
