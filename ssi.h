#ifndef __SSI_H__
#define __SSI_H__
#ifdef __cplusplus
extern char wifi_conn_detail[3][16];
extern "C" {
#endif
u16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen);
void ssi_init();
#ifdef __cplusplus
};
#endif
#endif // __SSI_H__
