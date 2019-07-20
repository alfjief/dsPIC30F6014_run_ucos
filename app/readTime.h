/*
 * adcHandle.h
 *
 *  Created on: 2011-12-24
 *      Author: ZhangQiangSheng
 */

#ifndef READTIME_H_
#define READTIME_H_


#define I2CTIMEOUT 300
//FM31256�Ĵ�������
#define FM31_FLAGS_CONTROL 0
#define FM31_CAL_CONTROL 1
#define FM31_SECONDS 2
#define FM31_MINUTES 3
#define FM31_HOURS 4
#define FM31_DAY_WEEK 5
#define FM31_DATE_MONTH 6
#define FM31_MONTHS 7
#define FM31_YEARS 8
#define FM31_WRT_FLAGS 9
#define FM31_WATCHDOG_CONTROL 0xa
#define DIS_6INT __asm__ volatile("disi #0x3FFF") /* disable interrupts */
#define EN_6INT __asm__ volatile("disi #0x0000") /* enable interrupts */

typedef struct {
	u8 second;
	u8 minute;
	u8 hour;
	u8 date;
	u8 month;
	u8 yearsL;
	u8 yearsH;
} TimeBCD, *pTimeBCD;

typedef struct {
	u8 second2;
	u8 second;
	u8 minute;
	u8 hour;
	u8 date;
	u8 month;
	u8 yearsL;
} TimeBIN, *pTimeBIN;

// ��FM31256�ж�ȡʱ�䵽�ڴ�
void i2cReadTime(pTimeBIN pt);
//����ʱ�䣺0-���óɹ�������Ϊʧ�ܡ�
u8 i2cSetTime(pTimeBIN pt);
/*
 * д���ݵ�FM31256�Ĵ洢��
 * memAddr���洢����ʼ��ַ
 * pData��������ʼ��ַ
 * len�����ݳ���
 * */
void i2cWriteMemory(u16 memAddr, u8* pData, u8 len);
/*
 * �����ݵ�FM31256�Ĵ洢��,������������ǱȽ��ȶ���
 * memAddr���洢����ʼ��ַ
 * pData��������ʼ��ַ
 * len�����ݳ���
 * */
void i2cReadMemory(u16 memAddr, u8* pData, u8 len);
//��λ���Ź�
void I2cWdtReset();
//FM31256�Ĵ������ú���
void i2cTimeInit();
/*
 * �������EEPROM�е����ݡ�
 * memAddr-��ʼ��ַ��len-���ȡ�
 * */
void i2cClearMemory(u16 memAddr, u8 len);

void i2cReadTimeToU16(u16* ptime);

#endif /* ADCHANDLE_H_ */
