/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "string.h"
#include "diskio.h"
#include "stm32f4xx.h"
#include "stm324xg_eval_sdio_sd.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/*-----------------------------------------------------------------------*/

#define FS_PRINTF_EN	0		/* 1��ʾ��ӡ������Ϣ */

#if FS_PRINTF_EN == 1
	#define fs_printf(...)	printf(__VA_ARGS__)
#else
	#define fs_printf(...)
#endif	


#define SECTOR_SIZE		512U

uint32_t Mass_Block_Size,Mass_Block_Count;

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
/**
  * @brief  Configures SDIO IRQ channel.
  * @param  None
  * @retval None
  */

static void nvic_configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_InitStructure.NVIC_IRQChannel = SD_SDIO_DMA_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&NVIC_InitStructure);  
}

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	SD_CardInfo mSDCardInfo;
	uint32_t DeviceSizeMul = 0, NumberOfBlocks = 0;	
	uint16_t Status;
	
	nvic_configuration();
	
	Status = SD_Init();
	if (Status != SD_OK)	
	{
		goto retfail;
	}

	SD_GetCardInfo(&mSDCardInfo);
	SD_SelectDeselect((uint32_t) (mSDCardInfo.RCA << 16));
	DeviceSizeMul = (mSDCardInfo.SD_csd.DeviceSizeMul + 2);
	
	if (mSDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
	{
		Mass_Block_Count = (mSDCardInfo.SD_csd.DeviceSize + 1) * 1024;
	}
	else
	{
		NumberOfBlocks  = ((1 << (mSDCardInfo.SD_csd.RdBlockLen)) / 512);
		Mass_Block_Count = ((mSDCardInfo.SD_csd.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks/2));
	}
	
	Status = SD_SelectDeselect((uint32_t) (mSDCardInfo.RCA << 16)); 
	Status = SD_EnableWideBusOperation(SDIO_BusWide_4b); 
	if (Status != SD_OK)
	{
		goto retfail;
	}
	

	Mass_Block_Size  = 512;
			
	return RES_OK;
retfail:	
	return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	SD_Error Status = SD_OK;

	if (count == 1) 
	{
		Status = SD_ReadBlock(buff, sector << 9 , SECTOR_SIZE);
	} 
	else 
	{
		Status = SD_ReadMultiBlocks(buff, sector << 9 , SECTOR_SIZE, count);
	}
		
	/* Check if the Transfer is finished */
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
	
	if (Status == SD_OK) 
	{
		return RES_OK;
	} 
	else
	{
		return RES_ERROR;
	}
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
/* The FatFs module will issue multiple sector transfer request
/  (count > 1) to the disk I/O layer. The disk function should process
/  the multiple sector transfer properly Do. not translate it into
/  multiple single sector transfers to the media, or the data read/write
/  performance may be drasticaly decreased. */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	SD_Error Status = SD_OK;
	
#if 1
	while (count--)
	{
		Status = SD_WriteBlock((uint8_t *)buff, sector << 9 ,SECTOR_SIZE);
		
		/* Check if the Transfer is finished */
    Status = SD_WaitWriteOperation();
		
    while(SD_GetStatus() != SD_TRANSFER_OK);
		if (Status != SD_OK)
		{
			break;
		}
	}
#else		/* SD_WriteMultiBlocks() ż����ִ�г��� */	
	if (count == 1) 
	{
		Status = SD_WriteBlock((uint8_t *)buff, sector << 9 ,SECTOR_SIZE);
	} 
	else 
	{
		Status = SD_WriteMultiBlocks((uint8_t *)buff, sector << 9 ,SECTOR_SIZE, count);	
	}
	
	/* Check if the Transfer is finished */
	Status = SD_WaitWriteOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
#endif	

	if (Status == SD_OK) 
	{
		return RES_OK;
	} 
	else
	{
		return RES_ERROR;
	}
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}

