/* SPDX-License-Identifier: LGPL-2.1-only */
/*
 * pcanwrite.cpp - PCANBasic Example: Simple Write
 *
 * Copyright (C) 2001-2020  PEAK System-Technik GmbH <www.peak-system.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Contact:    <linux@peak-system.com>
 * Maintainer: Stephane Grosjean <s.grosjean@peak-system.com>
 * Author:     Thomas Haber <thomas@toem.de>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "diagio.h"


unsigned long initialCRC32Value = 0xFFFFFFFF;

static const uint8_t dlc_len_table[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64 };

void signal_handler(int s)
{
    printf("Interrupted by SIG%u!\n", s);
}

int readMsg(can_iso_tp_link_t_p link,unsigned short pcan_device,TPCANMsg *Message)
{
    TPCANStatus Status;
	TPCANTimestamp ts;
    Status = CAN_Read(pcan_device, Message, &ts);

	if (Status != PCAN_ERROR_OK) {
		if (Status == PCAN_ERROR_QRCVEMPTY) {
			// nothing to read
			return Res_ERROR;
		}
		printf("CAN_Read(%xh) failure 0x%x\n", pcan_device, (int) Status);
		return Res_ERROR;
	}

	// emergency exit...
	if (Message->ID == 0xff && Message->LEN == 1 && Message->DATA[0] == 0xff)
		return Res_ERROR;
    
	// printf("  - R ID:%4x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x TS:%010u.%03u\n",
	// 		(int) Message->ID, (int) Message->LEN, (int) Message->DATA[0],
	// 		(int) Message->DATA[1], (int) Message->DATA[2],
	// 		(int) Message->DATA[3], (int) Message->DATA[4],
	// 		(int) Message->DATA[5], (int) Message->DATA[6],
	// 		(int) Message->DATA[7], ts.millis, ts.micros);
    if((Message->DATA[1] == 0x7F) && (Message->DATA[3] == 0x78))
	{
		return Res_PENDING;
	}
	struct CAN_msg msg;
	//msg = (struct CAN_msg *)malloc(sizeof(struct CAN_msg));
	msg.id.id = Message->ID;
	msg.id.isCANFD = 0;
	msg.id.isExt = 0;
	msg.id.isRemote = 0;
	msg.dlc = Message->LEN;
	memcpy(msg.data,Message->DATA,Message->LEN);
    
	iso_can_tp_L_Data_indication(link,&msg);
	// free(msg);
	// msg = NULL;
	if((Message->DATA[0] & 0xF0) == 0x30 && (Message->DATA[1] == 0x00))
	{
		return Res_WAITCF;
	}
	return Res_OK;
}

int readMsg_Vector(can_iso_tp_link_t_p link,TPCANMsg *Message)
{
    XLstatus status;
//    pthread_mutex_lock(&mutex);
    VCANMsg Vmsg;
    status = CAN_ReceiveFD(&Vmsg,link->init_info.rx_id.id);
/*    status = CAN_Receive(&Vmsg)*/;
    if(status == XL_ERR_QUEUE_IS_EMPTY)
    {
        return Res_ERROR;
    }
    Message->ID = Vmsg.ID;
    Message->LEN = Vmsg.LEN;
    memcpy(&Message->DATA[0],&Vmsg.DATA[0],Message->LEN);
    if (Message->ID == 0xff && Message->LEN == 1 && Message->DATA[0] == 0xff)
        return Res_ERROR;
    if((Message->DATA[1] == 0x7F) && (Message->DATA[3] == 0x78))
    {
        return Res_PENDING;
    }
//    pthread_mutex_unlock(&mutex);
    struct CAN_msg msg;
    //msg = (struct CAN_msg *)malloc(sizeof(struct CAN_msg));
    msg.id.id = Message->ID;
    msg.id.isCANFD = 0;
    msg.id.isExt = 0;
    msg.id.isRemote = 0;
    msg.dlc = Message->LEN;
    memcpy(msg.data,Message->DATA,Message->LEN);

    iso_can_tp_L_Data_indication(link,&msg);
    // free(msg);
    // msg = NULL;
    if((Message->DATA[0] & 0xF0) == 0x30 && (Message->DATA[1] == 0x00))
    {
        return Res_WAITCF;
    }
    return Res_OK;
}
//Std_ReturnType DoIP_DiagnosticMessage(uint8_t isFuntion,PduIdType connection,SduDataPtrType dataPtr,uint32 dataLength,struct sendMsg* rxMsg)
//{
//	Std_ReturnType res = E_NOT_OK;
//    if(DoIP_TcpTransmit(connection,DOIP_HDR_TYPE_DIAG_REQ,
//                    isFuntion,DOIP_ZERO,dataLength,dataPtr,FALSE) == E_OK)
//    {
//        PduInfoType PduInfoPtr;
//        PduInfoPtr.SduDataPtr = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
//		boolean enter = FALSE;
//        while (1)
//	    {
//	    	BufReq_ReturnType r;
//	    	{
//	    		if(receive(&DoIP_Con2SoConId[DOIP_ZERO],&PduInfoPtr)==1)
//	    		{
//	    			int zero = 0;
//	    			PduLengthType *len;
//	    			len = &zero;
//	    			if(DoIP_SoAdTpStartOfReception(DOIP_ZERO,&PduInfoPtr,0,len) == E_OK)
//	    			{
//	    				r = DoIP_SoAdTpCopyRxData(DOIP_ZERO,&PduInfoPtr,len);
//						if((PduInfoPtr.SduDataPtr[2] << 8 | PduInfoPtr.SduDataPtr[3]) == 0x8002)
//						{
//							enter = TRUE;

//							#pragma region printDebug
//							time_t now;
//							struct tm *local_time;
//							now = time(NULL);
//							local_time = localtime(&now);
//							printf("[%d-%02d-%02d %02d:%02d:%02d]Receive DOIP_ACK\n",
//							    local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
//							    local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
//							#pragma endregion
//							if(isFuntion != TRUE)
//							{
//								res = E_OK;
//								continue;
//							}
//							res = E_OK;
//							break;
//						}
//	    				if(enter == FALSE)
//						{
//							break;
//						}
//                        if((isFuntion != TRUE) &&(enter == TRUE))
//                        {
//                            memcpy(rxMsg->payload,lastMsgInfo.SduDataPtr,lastMsgInfo.SduLength);
//				            rxMsg->size = lastMsgInfo.SduLength;
//				            lastMsgInfo.SduLength = 0;
//				            if((PduInfoPtr.SduDataPtr[2] << 8 | PduInfoPtr.SduDataPtr[3]) == 0x8001)
//							{
//								res = E_OK;
//								break;
//							}
					            
//                        }
	    				
//	    			}
//	    		}
//	    	}
//	    }
//        free(PduInfoPtr.SduDataPtr);
//	    PduInfoPtr.SduDataPtr = NULL;
//    }
//	return res;
    
//}


unsigned int sendAndReceiveMessage(uint8_t deviceType ,can_iso_tp_link_t_p link, struct sendMsg* sendmsg,struct sendMsg* rxMsg)
{
    //TPCANMsg *readMessage;
	if(deviceType == CAN)
	{
    	unsigned int res = Res_ERROR;
        uint8_t isFunction = sendmsg->isFunction;
        int sendRes = iso_can_tp_N_USData_request(link,isFunction,sendmsg->payload,sendmsg->size);
		if(sendRes == 0)
		{
			struct CAN_msg* confirmMsg;
		    confirmMsg = (struct CAN_msg *)malloc(sizeof(struct CAN_msg));
		    confirmMsg->id.id = link->tx_record.last_msg.id.id;
    	    confirmMsg->id.isCANFD = link->tx_record.last_msg.id.isCANFD;
		    confirmMsg->id.isExt = link->tx_record.last_msg.id.isExt;
		    confirmMsg->id.isRemote = link->tx_record.last_msg.id.isRemote;
		    confirmMsg->dlc = link->tx_record.last_msg.dlc;
            memcpy(confirmMsg->data,link->tx_record.last_msg.data,dlc_len_table[(confirmMsg->dlc)& 0xf] );

			iso_can_tp_L_Data_confirm(link,confirmMsg,0);
			free(confirmMsg);
			confirmMsg = NULL;

		} 
		else
		{
			return res;
        }
		struct timeval tv;
    	gettimeofday(&tv,NULL);
		unsigned int initTime = tv.tv_sec*1000 + tv.tv_usec/1000;
		unsigned int endTime = initTime;
        int64_t timeout = 2000;
		do
		{
            uint8_t res = Res_OK;
            TPCANMsg readMessage;

            if(tool == 0)
            {
               res = readMsg(link,0x51,&readMessage);
            }
            else if(tool ==1)
            {
                res = readMsg_Vector(link,&readMessage);
            }
    	    //readMessage = (TPCANMsg *)malloc(sizeof(TPCANMsg));

    	    if( res == Res_OK)
			{
				timeout = 150;
				gettimeofday(&tv,NULL);
		        initTime = tv.tv_sec*1000 + tv.tv_usec/1000;
				if(((readMessage.DATA[0] & 0xF0) == 0x00) || (link->rx_record.status == rx_idle))
				{
					rxMsg->isFunction = 0;
					rxMsg->size = link->rx_record.rx_len;
					memcpy(rxMsg->payload,link->init_info.rx_buff,rxMsg->size);
					return Res_OK;			
				}
			}
			else if(res == Res_PENDING)
			{
				gettimeofday(&tv,NULL);
		        initTime = tv.tv_sec*1000 + tv.tv_usec/1000;
    	        timeout = 5100;
			}
			else if (res == Res_WAITCF)
			{
				if(readMessage.DATA[0] == 0x32)
				{
					//free(readMessage);
					return Res_ERROR;
                }
                initTime = tv.tv_sec*1000 + tv.tv_usec/1000;
			}

			//free(readMessage);
			gettimeofday(&tv,NULL);
		    endTime = tv.tv_sec*1000 + tv.tv_usec/1000;
		}while((endTime - initTime) < timeout);
		return Res_TIMEOUT;
	}
	else if(deviceType == Ethernet)
	{
//		PduInfoType PduInfoPtr;
//    	PduInfoPtr.SduDataPtr = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
//		//returnPduInfoPtr = (PduInfoType *)malloc(sizeof(PduInfoType));
//		if(DoIP_Con2SoConState[DOIP_ZERO] == SOAD_SOCON_ONLINE)
//		{
//			uint8 sendData[1024];
//			memcpy(sendData,sendmsg->payload,sendmsg->size);
			
//			if(DoIP_DiagnosticMessage(DOIP_ZERO,DOIP_ZERO,sendData,sendmsg->size,rxMsg) == DOIP_E_OK)
//			{
//			}
//			else
//			{
//				return Res_ERROR;
//			}
//			// DoIP_TcpTransmit(DOIP_ZERO,DOIP_HDR_TYPE_DIAG_REQ,
//            //         DOIP_ZERO,DOIP_ZERO,DOIP_TWO,sendmsg->payload,FALSE) ;
//		}
		
	}

}

unsigned int sendFuntionalMessage(uint8_t deviceType ,can_iso_tp_link_t_p link,struct sendMsg* sendmsg)
{
	if(deviceType == CAN)
	{
		uint8_t isFunction = sendmsg->isFunction;
		uint32_t size = sendmsg->size;
//		uint8_t *payload  = (uint8_t *)malloc(sizeof(uint8_t));
//		memcpy(payload,sendmsg->payload,size);
		uint8_t res =  Res_ERROR;
        if(iso_can_tp_N_USData_request(link,isFunction,sendmsg->payload,size) == 0)
		{
			struct CAN_msg* confirmMsg;
		    confirmMsg = (struct CAN_msg *)malloc(sizeof(struct CAN_msg));
		    confirmMsg->id.id = link->tx_record.last_msg.id.id;
    	    confirmMsg->id.isCANFD = link->tx_record.last_msg.id.isCANFD;
		    confirmMsg->id.isExt = link->tx_record.last_msg.id.isExt;
		    confirmMsg->id.isRemote = link->tx_record.last_msg.id.isRemote;
		    confirmMsg->dlc = link->tx_record.last_msg.dlc;
		    memcpy(confirmMsg->data,link->tx_record.last_msg.data,confirmMsg->dlc);

			iso_can_tp_L_Data_confirm(link,confirmMsg,0);
			free(confirmMsg);
			res = Res_OK;
		} 
//    	free(payload);
//		payload = NULL;
		return res;
	}
	else if(deviceType == Ethernet)
	{
//		PduInfoType PduInfoPtr;
//    	PduInfoPtr.SduDataPtr = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
//		PduInfoType returnPduInfoPtr;
//		returnPduInfoPtr.SduDataPtr = (uint8_t *)malloc(sizeof(uint8_t)*1024);
//		returnPduInfoPtr.SduLength = 0;
//		memset(returnPduInfoPtr.SduDataPtr,0x00,1024);
//		//returnPduInfoPtr = (PduInfoType *)malloc(sizeof(PduInfoType));
//		if(DoIP_Con2SoConState[DOIP_ZERO] == SOAD_SOCON_ONLINE)
//		{
//			uint8 sendData[1024];
//			memcpy(sendData,sendmsg->payload,sendmsg->size);
			
//			if(DoIP_DiagnosticMessage(DOIP_ONE,DOIP_ZERO,sendData,sendmsg->size,NULL) == DOIP_E_OK)
//			{
//    			return Res_OK;
//			}
//			else
//			{
//				return Res_ERROR;
//			}
//		}
		
	}
}

void iso_to_poll()
//void iso_to_poll(void *args)
{
	struct timeval tv;
    gettimeofday(&tv,NULL);
	unsigned int usr_ms = tv.tv_sec*1000 + tv.tv_usec/1000;
	iso_can_tp_poll(&link_iso,usr_ms);

}

unsigned int checkResultUDS(uint8_t *Resp,uint8_t RespSize,struct sendMsg *rxmsg)
{
	uint8_t res = Res_ERROR;

	time_t now;
    now = time(NULL);
    struct tm *local_time = localtime(&now);
    


    char qtPrintf[30];

    unsigned char data[1024];

	if((rxmsg->payload == NULL) || (rxmsg->size == 0))
	{
//        sprintf(qtPrintf,"[%d-%02d-%02d %02d:%02d:%02d]Error:No Response:",local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
//                local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
//        call_myclass_func(pclass, qtPrintf,data,0);
//		printf("[%d-%02d-%02d %02d:%02d:%02d]Error:No Response\n",
//            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
//            local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
		return res;
	}
	if(memcmp(Resp,rxmsg->payload,RespSize) == 0)
	{
        sprintf(qtPrintf,"[%d-%02d-%02d %02d:%02d:%02d]Response:",local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
                local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
//   		printf("[%d-%02d-%02d %02d:%02d:%02d]Response:",
//            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
//            local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
		res = Res_OK;
	}
    else
	{  
        sprintf(qtPrintf,"[%d-%02d-%02d %02d:%02d:%02d]Error:",local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
                local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
//		printf("[%d-%02d-%02d %02d:%02d:%02d]Error:",
//            local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday,
//            local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
	}		
    for(int i = 0;i < rxmsg->size;i++)
    {
        data[i] = rxmsg->payload[i];
    }
//    call_myclass_func(pclass, qtPrintf,data,rxmsg->size);
//    for(int i = 0;i < rxmsg->size;i++)
//	{
//		printf("%02x ",rxmsg->payload[i]);
//	}
//    printf("\n");
	//free(local_time);
	return res;
}

void SecurityAccessAlgorithm(uint8_t level,uint8_t *seed,uint8_t *key)
{
	uint32_t SEED = ((seed[0] << 24) | (seed[1] << 16) | (seed[2] << 8) | seed[3]);
	uint32_t temp1,temp2,temp3,temp4,PIN,KEYK;
    if(level == 0x09)
        PIN = LEVEL_09;
	else if(level == 0x03)
        PIN = LEVEL_01;
	temp1 = (SEED >> 3) ^ (PIN << 3);
    temp2 = (SEED << 2) ^ (PIN >> 2);
    temp3 = temp1 ^ temp2;
    temp4 = (temp3 >> 1) ^ (PIN << 1);
    KEYK = temp3 ^ temp4;
	key[0] = (KEYK & 0xFF000000) >> 24;
	key[1] = (KEYK & 0x00FF0000) >> 16;
	key[2] = (KEYK & 0x0000FF00) >> 8;
	key[3] = (KEYK & 0x000000FF);
}

uint8_t SecurityAccess_27(can_iso_tp_link_t_p link,uint8_t securityLevel)
{
	uint8_t* sendData = NULL;
	struct sendMsg securityRequest;
	securityRequest.isFunction=0;
	securityRequest.size = 2;

	sendData = (uint8_t *)malloc(sizeof(uint8_t));
    sendData[0] = 0x27;
	sendData[1] = securityLevel;
	memcpy(securityRequest.payload,sendData,2);
	struct sendMsg* rxmsg ;
	rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
	uint8_t res = Res_ERROR;
    if(sendAndReceiveMessage(CAN,link,&securityRequest,rxmsg) ==  Res_OK)
    {
		sendData[0] += 0x40; 
		if(checkResultUDS(sendData,2,rxmsg) == Res_OK)
		{
			uint8_t seed[4];
    	    memcpy(seed,&rxmsg->payload[2],4);

			uint8_t key[4];
    	    SecurityAccessAlgorithm(securityLevel,seed,key);

   			sendData[0] = 0x27;
   			sendData[1] = securityLevel + 1;
   			securityRequest.size = 6;
   			memcpy(securityRequest.payload,sendData,2);
   			memcpy(&securityRequest.payload[2],key,4); 
   			if(sendAndReceiveMessage(CAN,link,&securityRequest,rxmsg) == Res_OK)
			{
				sendData[0] += 0x40; 
				if(checkResultUDS(sendData,2,rxmsg) == Res_OK)
				{
					res = Res_OK;
				}
			}
		}
	}
	free(sendData);
	free(rxmsg);
    return res;
}

uint8_t EraseFlash_31(can_iso_tp_link_t_p link,uint32_t memoryaddr,uint32_t memorysize)
{
	uint8_t earseFlash[4] = {0x31,0x01,0xFF,0x00};
	uint8_t res = Res_ERROR;
	//uint8_t earseFlash[5] = {0x31,0x01,0xFF,0x00,0x44};
	// uint8_t memoryAddr[4];
	// memoryAddr[0] = (memoryaddr & 0xFF000000) >> 24;
	// memoryAddr[1] = (memoryaddr & 0x00FF0000) >> 16;
	// memoryAddr[2] = (memoryaddr & 0x0000FF00) >> 8;
	// memoryAddr[3] = (memoryaddr & 0x000000FF);

	// uint8_t memorySize[4];
    // memorySize[0] = (memorysize & 0xFF000000) >> 24;
	// memorySize[1] = (memorysize & 0x00FF0000) >> 16;
	// memorySize[2] = (memorysize & 0x0000FF00) >> 8;
	// memorySize[3] = (memorysize & 0x000000FF);


	struct sendMsg eraseFlashRequest;
	eraseFlashRequest.isFunction=0;
	eraseFlashRequest.size = 4;

	memcpy(eraseFlashRequest.payload,earseFlash,5);
    // struct sendMsg eraseFlashRequest;
	// eraseFlashRequest.isFunction=0;
	// eraseFlashRequest.size = 13;

	// memcpy(eraseFlashRequest.payload,earseFlash,5);
	// memcpy(eraseFlashRequest.payload +5,memoryAddr,4);
	// memcpy(eraseFlashRequest.payload +9,memorySize,4);

	struct sendMsg *rxmsg;
	rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
	//rxmsg->payload = (uint8_t *)malloc(sizeof(uint8_t));

	if(sendAndReceiveMessage(link->devicetype,link,&eraseFlashRequest,rxmsg) == Res_OK)
	{
		earseFlash[0] += 0x40;

    	if(checkResultUDS(earseFlash,4,rxmsg) == Res_OK)
		{
			res = Res_OK;
		}
	}
	return res;
}

uint8_t downloadProcess_36(can_iso_tp_link_t_p link,const char* filename,uint32_t sendblock)
{
	FILE *pf = fopen(filename,"rb");
	if(pf == NULL)
	{
		printf("Error: unable to open file %s\n",filename);
        return Res_ERROR;
	}
	uint8_t readData[MAX_BUFF_LEN];
	int BlockCount = 0x01;
	readData[0] = 0x36;
	
	struct sendMsg *rxmsg;
	rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
	size_t ret;
	do
	{
		readData[1] = BlockCount;
		ret = fread(&readData[2],sizeof(uint8_t),sendblock,pf);
		struct sendMsg downloadData;
	    downloadData.isFunction=0;
	    downloadData.size = ret + 2;
		if(ret == 0)
		{
			fclose(pf);
			return Res_OK;
		}
	    memcpy(downloadData.payload,readData,downloadData.size);
	    

		crc32_Caculate(&downloadData.payload[2],downloadData.size -2,&initialCRC32Value);
        if(sendAndReceiveMessage(CAN,link,&downloadData,rxmsg) != Res_OK)
		    return Res_ERROR;

		uint8_t downloadResp[2]; 
		downloadResp[0] = 0x76;
		downloadResp[1] = BlockCount;

        if(checkResultUDS(downloadResp,2,rxmsg) != Res_OK)
	    {
	    	return Res_ERROR;
	    }

	    BlockCount++;
	    if(BlockCount > 0xFF)
	    	BlockCount = 0x00;
	    if (ret < sendblock)
	    {
			for(int i = 0;i< ret+2;i++)
			{
				printf("%02x ",downloadData.payload[i]);
			}
	    	break;
	    }
	} while (1);
	
	fclose(pf);
	// free(readData);
	// readData = NULL;
}

uint32_t crc32_Caculate(uint8_t* ReqBuffer,uint16_t ReqBufferLen,uint32_t* crcValue)
{
	for(int i = 0;i < ReqBufferLen;i++)
	{
		*crcValue = crc_table[(*crcValue  ^ ReqBuffer[i]) & 0xff] ^ (*crcValue  >> 8);
		//*crcValue = ((*crcValue >> 8) & 0x00FFFFFF) ^ crc_table[(*crcValue ^ ReqBuffer[i])&0xFF];
	}
	return *crcValue;
}

uint8_t verifyIntegrity_31(can_iso_tp_link_t_p link) 
{
	uint8_t res =  Res_ERROR;
    uint8_t verifyintegrity[8] = {0x31,0x01,0x02,0x02};
	initialCRC32Value = (unsigned int)~initialCRC32Value;
	verifyintegrity[4] = (initialCRC32Value & 0xFF000000) >> 24;
	verifyintegrity[5] = (initialCRC32Value & 0x00FF0000) >> 16;
	verifyintegrity[6] = (initialCRC32Value & 0x0000FF00) >> 8;
	verifyintegrity[7] = (initialCRC32Value & 0x000000FF);

	struct sendMsg verifyintegrityRequest;
	verifyintegrityRequest.isFunction=0;
	verifyintegrityRequest.size = 8;

	memcpy(verifyintegrityRequest.payload ,verifyintegrity,verifyintegrityRequest.size);

	struct sendMsg *rxmsg;
	rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));

    if(sendAndReceiveMessage(CAN,link,&verifyintegrityRequest,rxmsg) == Res_OK)
	{
		verifyintegrity[0] += 0x40;

    	if(checkResultUDS(verifyintegrity,4,rxmsg) == Res_OK && rxmsg->payload[4] == 0x00)
		{
			res = Res_OK;
		}
	}
	return res;
}

unsigned int downloadRequest_34(can_iso_tp_link_t_p link,uint32_t memoryaddr,uint32_t memorysize)
{
	uint8_t downloadreq[3] = {0x34,0x00,0x44};
	unsigned int blocksize = 0;
	uint8_t memoryAddr[4];
	memoryAddr[0] = (memoryaddr & 0xFF000000) >> 24;
	memoryAddr[1] = (memoryaddr & 0x00FF0000) >> 16;
	memoryAddr[2] = (memoryaddr & 0x0000FF00) >> 8;
	memoryAddr[3] = (memoryaddr & 0x000000FF);

	uint8_t memorySize[4];
    memorySize[0] = (memorysize & 0xFF000000) >> 24;
	memorySize[1] = (memorysize & 0x00FF0000) >> 16;
	memorySize[2] = (memorysize & 0x0000FF00) >> 8;
	memorySize[3] = (memorysize & 0x000000FF);

    struct sendMsg downloadRequest;
	downloadRequest.isFunction=0;
	downloadRequest.size = 11;
	//eraseFlashRequest.payload = (uint8_t *)malloc(sizeof(uint8_t));

	memcpy(downloadRequest.payload,downloadreq,3);
	memcpy(downloadRequest.payload +3,memoryAddr,4);
	memcpy(downloadRequest.payload +7,memorySize,4);

	struct sendMsg *rxmsg;
	rxmsg = (struct sendMsg*)malloc(sizeof(struct sendMsg));
	//rxmsg->payload = (uint8_t *)malloc(sizeof(uint8_t));

	sendAndReceiveMessage(link->devicetype,link,&downloadRequest,rxmsg);

	downloadreq[0] += 0x40;

    if(checkResultUDS(downloadreq,1,rxmsg) == 1)
	{
		if(rxmsg->size == 6)
		{
			blocksize = ((rxmsg->payload[2] << 24) |(rxmsg->payload[3] << 16) | (rxmsg->payload[4] << 8) | rxmsg->payload[5]);
		}
        else if(rxmsg->size == 4)
		{
			blocksize = ((rxmsg->payload[2] << 8) |(rxmsg->payload[3]));
		} 
		return blocksize;
	}
	else
	{
		return 0; 
	}
}

unsigned int connectDevice(uint8_t device)
{
   if(device == CAN)
   {
		TPCANMsg Message;
		TPCANStatus Status;
		unsigned int pcan_device = 0x51;
		Status = CAN_Initialize(pcan_device, PCAN_BAUD_500K, 0, 0, 0);
		if(Status != PCAN_ERROR_OK)
		{
			return Res_ERROR;
		}
        Status = CAN_SetValue(pcan_device,PCAN_TRACE_LOCATION,"./log/",sizeof(char));
		if(Status != PCAN_ERROR_OK)
		{
			return Res_ERROR;
		}
		unsigned short size = 100;
		Status = CAN_SetValue(pcan_device,PCAN_TRACE_SIZE,&size,sizeof(unsigned short));
		if(Status != PCAN_ERROR_OK)
		{
			return Res_ERROR;
		}
		unsigned long configuration =  TRACE_FILE_DATE | TRACE_FILE_TIME | TRACE_FILE_SEGMENTED;

		Status = CAN_SetValue(pcan_device, PCAN_TRACE_CONFIGURE, &configuration, sizeof(unsigned long));
		if(Status != PCAN_ERROR_OK)
		{
			return Res_ERROR;
		}
        uint8_t traceStatus = PCAN_PARAMETER_ON;

		Status = CAN_SetValue(pcan_device,PCAN_TRACE_STATUS,&traceStatus,sizeof(traceStatus));
		if(Status != PCAN_ERROR_OK)
		{
			return Res_ERROR;
		}
		return Res_OK;
   }
   else if(device == Ethernet)
   {
//		DoIP_Init(NULL);
		return Res_OK;
   }
}

uint8_t DoIP_ReceiveRoutingActive()
{
//	PduInfoType PduInfoPtr;
//    PduInfoPtr.SduDataPtr= (uint8_t *)malloc(sizeof(uint8) * 1024);
//    while (1)
//	{
//		//PduInfoPtr->SduDataPtr = (uint8 *)malloc(0xFFFFFF);
//		BufReq_ReturnType r;
//		if(DoIP_Con2SoConState[DOIP_ZERO] == SOAD_SOCON_ONLINE)
//		{
//			if(receive(&DoIP_Con2SoConId[DOIP_ZERO],&PduInfoPtr)==1)
//			{
//				int zero = 0;
//				PduLengthType *len;
//				len = &zero;
//				if(DoIP_SoAdTpStartOfReception(DOIP_ZERO,&PduInfoPtr,0,len) == E_OK)
//				{
//					r = DoIP_SoAdTpCopyRxData(DOIP_ZERO,&PduInfoPtr,len);
//					break;
//				}
//			}
//		}
//		/* code */
//	}
//	free(PduInfoPtr.SduDataPtr);
//	PduInfoPtr.SduDataPtr = NULL;

//	if(DoIP_TcpCon2ActivMgt[DOIP_ZERO].activState == DOIP_ROUT_ACTIV_STATE_ACTIVATED)
//	{
//        return Res_OK;
//	}
//	else
//	{
//		return Res_ERROR;
//	}
}
