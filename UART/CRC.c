

#include "CRC.h"

u16 CalcCRCModBus(u8 cDataIn, u16 wCRCIn)     
{   
	  int i;
    u16 wCheck = 0;     
    wCRCIn = wCRCIn ^ cDataIn;        
    for(i = 0; i < 8; i++)     
    {     
        wCheck = wCRCIn & 1;     
        wCRCIn = wCRCIn >> 1;     
        wCRCIn = wCRCIn & 0x7fff;        
        if(wCheck == 1)     
        {     
            wCRCIn = wCRCIn ^ 0xa001;     
        }     
        wCRCIn = wCRCIn & 0xffff;     
    }        
    return wCRCIn;     
} 
// CRC MODBUS 效验     
// 输入参数: pDataIn: 数据地址     
//           iLenIn: 数据长度                
// 输出参数: pCRCOut: 2字节校验值      
void CheckCRCModBus(u8* pDataIn, int iLenIn, u8 * pCRCOut)     
{    
	int i; 
    u16 wHi = 0;     
    u16  wLo = 0;     
    u16  wCRC;     
    wCRC = 0xFFFF;     
    
    for (i = 0; i < iLenIn; i++)     
    {     
        wCRC = CalcCRCModBus(*pDataIn, wCRC);     
        pDataIn++;     
    }     
    wHi = wCRC / 256;     
    wLo = wCRC % 256;        
    //wCRC = (wHi << 8) | wLo;      
    *pCRCOut = wLo;   
    *(pCRCOut+1) = wHi;		
}     
    
   