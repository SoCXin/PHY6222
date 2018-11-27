#ifndef __CRC16_H__
#define __CRC16_H__


#include <stdio.h>
#include "stm32f10x.h"

void CheckCRCModBus(u8* pDataIn, int iLenIn, u8 * pCRCOut);
u16 CalcCRCModBus(u8 cDataIn, u16 wCRCIn);

#endif

