#ifndef __DATA_GRAM_H__
#define __DATA_GRAM_H__

#include "stm32f10x.h"
#include <stdio.h>
#include "string.h"

#define TLV_DATA_TYPE_END     		  0
#define TLV_DATA_TYPE_CHECKSUM		  1

#define TLV_CHECKSUM_VALUE_LEN 	  	1
#define TVL_DATA_MAX_LEN       	  250

#define TLV_SUCCESS 1
#define TLV_ERROR   0

/*
约定：
1、第一个TLV固定放CHECKSUM，type=TLV_DATA_TYPE_CHECKSUM,len=1,value=1个字节的check值
2、整个报文的长度不能超过TVL_DATA_MAX_LEN个字节，包含头和尾
3、报文类型除TLV_DATA_TYPE_END外，其它类型的len域必须大于0
*/

typedef struct DATA_TLV_S_ 
{
    u8 type;
    u8 len;
    u8 value[1];
}DATA_TLV_S;

/* 
 * 检查整个数据报文是否正常，CHECK校验,正常返回TLV_SUCCESS
 * */
u8 checkDatagramValid(DATA_TLV_S* firstTlvData);

/* 
 * 获得第一个TLV，传入数据报文原文
 * */
DATA_TLV_S* getFirstTlv(u8 *data);

/* 
 * 通过本TLV查询下一个TLV的数据
 * 返回空表示没有下一个了
 * */
DATA_TLV_S* getNextTlv(DATA_TLV_S* tlvData);

/* 
 * 检查当前TLV是否正常，CHECK校验通过返回TLV_SUCCESS
 * */
u8 isTlvValid(DATA_TLV_S*tlvData);

/* 
 * 计算CHECKSUM，不包含STARTTLV，包含ENDTLV
 * 计算成功返回TLV_SUCCESS
 * */
u8 computCheckSum(DATA_TLV_S* firstTlvData, u8* checkSum);

/* 
 * 获得数据报文的长度，包含头和ENDTLV
 * */
u8 getkDatagramLen(DATA_TLV_S* firstTlvData, u8*dataLen);


//返回实际写入的长度
int toString(DATA_TLV_S* tlvData, char* buffer, int bufferLen);

#endif
