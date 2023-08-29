#ifndef __SSI_H__
#define __SSI_H__
#ifdef __cplusplus
extern "C" {
#endif
u16_t __time_critical_func(ssi_handler)(int iIndex, char *pcInsert, int iInsertLen);
void ssi_init();
#ifdef __cplusplus
};
#endif
#endif // __SSI_H__
