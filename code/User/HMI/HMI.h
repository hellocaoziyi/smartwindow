#ifndef __HMI_H
#define __HMI_H

#include "bsp_usart.h"

void HMI(void);
int HMI_Scan(void);
void HMI_clear(void);
void HMI_clearline(int i);
int HMI_get_ip(void);

#endif /* __USART_H */
