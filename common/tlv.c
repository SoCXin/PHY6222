#include "tlv.h"

/* 
 * 获得数据报文的长度，包含头和ENDTLV
 * */
u8 getkDatagramLen(DATA_TLV_S* firstTlvData, u8*dataLen)
{
    DATA_TLV_S* tlvData = firstTlvData;
    u16 length = 0;
    
    if ((NULL == tlvData) || (NULL == dataLen))
    {
        return TLV_ERROR;
    }
    
    while(NULL != tlvData)
    {
        if (TLV_SUCCESS != isTlvValid(tlvData))
        {
            return TLV_ERROR;
        }
        
        length += 1; //TYPE域
        if (TLV_DATA_TYPE_END == tlvData->type)
        {
            break;
        }
        
        length += 1;//长度域
        length += tlvData->len; 
        
        //长度不能越限
        if (length > TVL_DATA_MAX_LEN)
        {
            return TLV_ERROR;
        }
        
        tlvData = getNextTlv(tlvData);
    }
    
    *dataLen = (u8)length;
    
    return TLV_SUCCESS;
}

/* 
 * 检查整个数据报文是否正常，CHECK校验,正常返回TLV_SUCCESS
 * */
u8 checkDatagramValid(DATA_TLV_S* firstTlvData)
{
    u8 dataCheckSum = 0;
    u8 calcCheckSum = 0;
    
    if (NULL == firstTlvData)
    {
        return TLV_ERROR;
    }
    
    //第一个是checksum
    if (firstTlvData->type != TLV_DATA_TYPE_CHECKSUM)
    {
        return TLV_ERROR;
    }
    
    //checksum的长度域
    if (firstTlvData->len != TLV_CHECKSUM_VALUE_LEN)
    {
        return TLV_ERROR;
    }
    
    dataCheckSum = *(firstTlvData->value);
    
    //计算到的checksum和报文里的对比
    if (TLV_SUCCESS != computCheckSum(firstTlvData,&calcCheckSum))
    {
        return TLV_ERROR;
    }
    
    return (calcCheckSum == dataCheckSum) ? TLV_SUCCESS : TLV_ERROR;
}

/* 
 * 检查当前TLV是否正常，CHECK校验通过返回TLV_SUCCESS
 * */
u8 isTlvValid(DATA_TLV_S*tlvData)
{
    if (NULL == tlvData)
    {
        return TLV_ERROR;
    }
    
    if (TLV_DATA_TYPE_END == tlvData->type)
    {
        return TLV_SUCCESS;
    }
    
    //数据长度不能越限
    if ((0 == tlvData->len) || (tlvData->len > (TVL_DATA_MAX_LEN-2-3))) //-本数据的TYPELEN和STARTTLV的长度
    {
        return TLV_ERROR;
    }
    
    return TLV_SUCCESS;
}

/* 
 * 计算CHECKSUM，不包含STARTTLV，包含ENDTLV
 * 计算成功返回TLV_SUCCESS
 * */
u8 computCheckSum(DATA_TLV_S* firstTlvData, u8* checkSum)
{
    DATA_TLV_S* tlvData = firstTlvData;
    u8 i;

    if (NULL == checkSum)
    {
        return TLV_ERROR;
    }
    
		*checkSum = 0;
    //从START后的第一个数据TLV开始
    while (NULL != (tlvData = getNextTlv(tlvData)))
    {
        if (tlvData - firstTlvData > TVL_DATA_MAX_LEN)
        {
           return TLV_ERROR; 
        }
        
        if (TLV_DATA_TYPE_END == tlvData->type)
        {
            break;
        }
        
        if (!isTlvValid(tlvData))
        {
            return TLV_ERROR;
        }
        
        //数据校验用异或的方式
        *checkSum ^= tlvData->type;
        *checkSum ^= tlvData->len;
        
        for (i =0; i < tlvData->len; ++i)
        {
            *checkSum ^= tlvData->value[i];
        }
    }
    
    return TLV_SUCCESS;
}

/* 
 * 获得第一个TLV，传入数据报文原文
 * */
DATA_TLV_S* getFirstTlv(u8 *data)
{
    if (NULL == data)
    {
        return NULL;
    }
    
    return (DATA_TLV_S*)data;
}

/* 
 * 通过本TLV查询下一个TLV的数据
 * 返回空表示没有下一个了
 * */
DATA_TLV_S* getNextTlv(DATA_TLV_S* tlvData)
{
    u8 *data = NULL;

    if (TLV_SUCCESS != isTlvValid(tlvData))
    {
        return NULL;
    }
    
    if (TLV_DATA_TYPE_END == tlvData->type)
    {
        return NULL;
    }
    
    data = (u8*)tlvData;

    //定位到VALUE域
    data += 2;
    
    //定位到数据结尾
    data += tlvData->len;

    return (DATA_TLV_S*)data;
}

//返回实际写入的长度
int toString(DATA_TLV_S* tlvData, char* buffer, int bufferLen)
{
    int dataLen = 0;
    int i;

    if (NULL == tlvData || NULL == buffer || 0 == bufferLen)
    {
        return 0;
    }
		
		if (tlvData->type == TLV_DATA_TYPE_END)
		{
		    return 0;
		}

    dataLen = snprintf(buffer,bufferLen,"T:%02dL:%02d:V:",tlvData->type,tlvData->len);

    for (i = 0; (i < tlvData->len) && (dataLen < bufferLen); ++i)
    {
        dataLen += snprintf(buffer + dataLen, bufferLen - dataLen, "%02X", tlvData->value[i]);
    }
		
		//加回车符
		if ((i > 0) && (dataLen < bufferLen))
		{
		    dataLen += snprintf(buffer + dataLen, bufferLen - dataLen, "\n");
		}

    return dataLen;
}


