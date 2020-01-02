/*
 * cmd_interface.h
 *
 *  Created on: 2018-11-22
 *      Author: Administrator
 */

#ifndef CMD_INTERFACE_H_
#define CMD_INTERFACE_H_

#include "tl_common.h"

/****************************************************************************************************************************
 * Address allocation:
 * 		0x840004    0x840005    0x840006    0x840007    0x840008    0x840009
 * 		ParaAddr_L  ParaAddr_H  fifo_size   fifo_cnt    wptr        rptr
 * 		0x84000a    0x84000b    0x84000c    0x84000d    0x84000e    0x84000f
 * 		ResAddr_L   ResAddr_H   fifo_size   fifo_cnt    wptr        rptr
 * Note:
 * -1.this block of address is very safe,and it would not be interrupted because of unreasonable definition
 * by programmer or automatic allocation mechanism in processing of program. It is why we use this part of address!
 *
 * -2.a block of continuous address is created in ram,which is divided into two parts :one part is used to receive command
 * from the upper monitor,another part is used to send result waited to read by the upper monitor
 *
 * -3.In order to advance the speed of the whole system,we consider to use 5 layers of fifo	to upload or download data,
 * every layer of fifo has 16 bytes.
 *
****************************************************************************************************************************/
#define    IO_BASE_ADDR    	0x808000

#define    INFO_BUF_RPTR    		(IO_BASE_ADDR + 4)
#define    INFO_BUF_WPTR    		(IO_BASE_ADDR + 5)
#define    INFO_BUF_SIZE    		(IO_BASE_ADDR + 6)
#define    INFO_BUF_MASK     		(IO_BASE_ADDR + 7)
#define    INFO_BUF_STATUS  		(IO_BASE_ADDR + 8)
#define    INFO_BUF_STATUS_CHECK  	(IO_BASE_ADDR + 9)
//#define    INFO_BUF_QR_ADDR  	(IO_BASE_ADDR + 0xa)
#define    INFO_BUF_ADDR  			(IO_BASE_ADDR + 0xc)
#define    INFO_BUF_CHECKSUM  		(IO_BASE_ADDR + 0xe)

#define BigLittleSwap32(A)        ((((unsigned int)(A) & 0xff000000) >> 24) | \
								   (((unsigned int)(A) & 0x00ff0000) >> 8) | \
								   (((unsigned int)(A) & 0x0000ff00) << 8) | \
								   (((unsigned int)(A) & 0x000000ff) << 24))

#define BigLittleSwap16(A)        ((((unsigned short)(A) & 0xff00) >> 8) | \
								   (((unsigned short)(A) & 0x00ff) << 8))

#define    InfoBuffSize    150
#define    InfoBuffCnt     8
unsigned char infoBuff[InfoBuffCnt][InfoBuffSize];

typedef enum{
	PROTOCAL_THREAD = 0,
	PROTOCAL_ZIGBEE,
	PROTOCAL_BLE,
	PROTOCAL_BLUETOOTH,
	PROTOCAL_HOMEKIT,
	PROTOCAL_6LOWPAN,
	PROTOCAL_JUSTFORTEST,
}InforProtocalType;

typedef enum{
	PAYLOAD_STRING = 0,
	PAYLOAD_BYTES,
}InforPayloadType;

typedef struct{
	unsigned int timeStamp;
	unsigned int timeStampSwm;
	unsigned short checkSum;
	unsigned char protocalType;
	unsigned char payloadType;
	unsigned short payloadLen;
	unsigned int messageCnt;
	unsigned char buff[127];
}Info_Context_Typdef;

/**
 * @brief      	This function is used to write result waiting to be read by the upper monitor
 * @param[in]  	*pSrcBuf	-save the result to the specified location waiting to be read
 * @param[in]  	len			-set the length of result waiting to read
 * @return     	none
 */
extern unsigned int infoBuf_Write(unsigned char *pPayloadBuf, unsigned char pPayloadLen);

/**
 * @brief      	This function is used to initiate the buffer of command
 * @param[in]  	BufAddr 	- set the address of buffer of command from the upper monitor
 * @param[in]  	BufSize		- set the size of address of buffer of command from the upper monitor
 * @param[in]	BufCnt		- set layers of fifo
 * @return     	none
 */
extern void infoBuf_Init(unsigned short bufAddr, unsigned char bufSize, unsigned char bufCnt);

extern void infoBuf_filled(void* infoData);
#endif /* CMD_INTERFACE_H_ */
