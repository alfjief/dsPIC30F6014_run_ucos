/*
 * uart2.c
 *
 *  Created on: 2011-12-24
 *      Author: ZhangQiangSheng
 *      ��ͨѶ��ͨ�ų���
 */

#include "includes.h"

#define STO_LEN	13
const u8 sto[STO_LEN] = { 0xFE, 0xFE, 0xFE, 0xFE, 0x68, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x05 };
static u8 rxd2Buf[100];
static u8 txd2Buf[100];
static UartTag uart2;

/*
 * ��ͨѶ��ͨ�ų����ʼ��
 * */
void uart2Init() {
	//UARTX �����ʼĴ���
	U2BRG = 0x33;
	//U2RXIP<2:0>��  UART2 �������ж����ȼ�λ
	IPC6bits.U2RXIP = 0b010;
	//U2TXIP<2:0>��  UART2�������ж����ȼ�λ
	IPC6bits.U2TXIP = 0b001;
	//UARTX ģʽ�Ĵ���
	U2MODE = 0x8800;
	//UARTX ״̬�Ϳ��ƼĴ���
	U2STA = 0x8400;
	//UART1 �������жϱ�־״̬λ
	IFS1bits.U2RXIF = 0;
	//UART1�������жϱ�־״̬λ
	IFS1bits.U2TXIF = 0;
	//UART1�������ж�����λ
	IEC1bits.U2RXIE = 1;
	//UART1�������ж�����λ
	IEC1bits.U2TXIE = 1;
	uart2.resBegin = 0;
	uart2.resLen = 0;
	uart2.resFinish = 0;
	uart2.enableSend = 0;
	uart2.faultPtr = 0;
	uart2.pRxdBuf = (u8 *) &rxd2Buf;
	uart2.pTxdBuf = (u8 *) &txd2Buf;
}
void startSend(u8 len) {
	u8 bcc = 0, i;
	for (i = 4; i < len; i++) {
		bcc += txd2Buf[i];
	}
	txd2Buf[len++] = bcc; //У��
	txd2Buf[len++] = 0x16; //������
	uart2.txdptr = 1;
	uart2.txdlen = len;
	uart2.enableSend = 1;
	U2TXREG = 0xFE;
}
void payReadCard() {
	u8 len = STO_LEN;
	memCpy(&txd2Buf, &sto, STO_LEN);
	txd2Buf[len++] = 4;
	txd2Buf[len++] = DI0 + ADD_VALUE;
	txd2Buf[len++] = DI1 + ADD_VALUE;
	txd2Buf[len++] = CMD_READ_CARD + ADD_VALUE;
	txd2Buf[len++] = DI3 + ADD_VALUE;
	startSend(len);
}
void payVerityPwd(u32 pwd) {
	u8 len = STO_LEN;
	memCpy(&txd2Buf, &sto, STO_LEN);
	txd2Buf[len++] = 7;
	txd2Buf[len++] = DI0 + ADD_VALUE;
	txd2Buf[len++] = DI1 + ADD_VALUE;
	txd2Buf[len++] = CMD_VERIFY_PWD + ADD_VALUE;
	txd2Buf[len++] = DI3 + ADD_VALUE;
	txd2Buf[len++] = (u8) pwd + ADD_VALUE;
	txd2Buf[len++] = (u8) (pwd >> 8) + ADD_VALUE;
	txd2Buf[len++] = (u8) (pwd >> 16) + ADD_VALUE;
	startSend(len);
}
/* 30aa
 * �����ͨѶ����յ�������
 * */
void u2rxDataHandle() {
	unsigned char i, sum, len;
	unsigned char di0, di1, di2, di3;
	if (uart2.resFinish != 0) {
		uart2.faultPtr = 0;
		uart2.uartState = 0;
		len = rxd2Buf[9] + 10; //������ʼ����������ȣ���10����
		while (len--) {
			sum += rxd2Buf[i++];
		}
		if (rxd2Buf[i] == sum) {
			sum = rxd2Buf[8];
			len = rxd2Buf[9];
			di0 = rxd2Buf[10] - 0x33;
			di1 = rxd2Buf[11] - 0x33;
			di2 = rxd2Buf[12] - 0x33;
			di3 = rxd2Buf[13] - 0x33;
			switch (di2) {
			case CMD_READ_CARD: //1�����װ���Ͷ���,��������
				if (rxd2Buf[26] == 0x33) {

				} else if (rxd2Buf[26] == 0xcc) {

				} else if (rxd2Buf[26] == 0x34) {

				} else {

				}
				break;
			case CMD_VERIFY_PWD: //2�����װ��������ȷ��,��������

				break;
			case CMD_SET_CHARGE_MODE: //3�����װ���ͳ�緽ʽѡ��,��������

				break;
			}
		}
		uart2.resFinish = 0;
	}
}

/*
 * ��ͨѶ��ͨ�ų���
 * */
void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt() {
	unsigned int i;
	IFS1bits.U2TXIF = 0;
	if (uart2.enableSend) {
		if (uart2.txdptr > uart2.txdlen) {
			uart2.enableSend = 0;
		} else {
			for (i = 0; (i < 4) && (uart2.txdptr <= uart2.txdlen); i++) {
				U2TXREG = txd2Buf[uart2.txdptr];
				uart2.txdptr++;
			}
		}
	}
}

/*
 *
 * */
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt() {
	IFS1bits.U2RXIF = 0;
	unsigned char temp;
	temp = U2RXREG;
	if (U2STAbits.OERR == 1) { //OERR��  ���ջ������������״̬λ��ֻ�� /���㣩
		U2STAbits.OERR = 0; //�����������е����ݶ�ʧ
		uart2.resBegin = 0;
	} else if (U2STAbits.PERR == 1) { //bit 3 PERR����żУ�����״̬λ��ֻ����
		U2STAbits.PERR = 0;
		uart2.resBegin = 0;
	} else if (U2STAbits.FERR == 1) { //bit 2 FERR��֡����״̬λ��ֻ����
		U2STAbits.FERR = 0;
		uart2.resBegin = 0;
	} else {
		if (uart2.resFinish == 0) {
			if (uart2.resBegin == 0) {
				if (temp == 0x68) { //֡��ʼ��
					uart2.resBegin = 1;
					uart2.resLen = 0;
					uart2.resFinish = 0;
					uart2.rxdptr = 1;
					rxd2Buf[0] = temp;
				}
			} else if (uart2.resLen == 0) {
				switch (uart2.rxdptr) {
				case 7:
					if (temp == 0x68) { //�ڶ���֡��ʼ��
						rxd2Buf[uart2.rxdptr++] = temp;
					} else {
						uart2.resBegin = 0;
					}
					break;
				case 9:
					rxd2Buf[uart2.rxdptr++] = temp;
					uart2.rxdlen = temp + 12;
					uart2.resLen = 1;
					break;
				default:
					rxd2Buf[uart2.rxdptr++] = temp;
					break;
				}
			} else {
				rxd2Buf[uart2.rxdptr++] = temp;
				if (uart2.rxdptr >= uart2.rxdlen) {
					uart2.resBegin = 0;
					uart2.resLen = 0;
					uart2.resFinish = 1;
				}
			}
		}
	}
}

