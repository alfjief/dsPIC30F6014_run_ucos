#include "includes.h"

static u16* pUart6YC;
static u8* pUart6YX;
static u8 rxd6Buf[50];
static u8 txd6Buf[50];
static UartTag uart6;
OS_STK displayStak[64];
static void sendUart6(u8 w142);

//ÿ������һ��
void uart6FaultCheck() {
	if (++uart6.faultPtr > 180) {
		uart6.faultPtr = 0;
		if (uart6.uartState == 0) {
			uart6.uartState = 1;
			//displayInit();
			//	saveFault(RecordLcdCommFail);
			//saveFaultflag = 1;
		}
		//setSpakeTimes(2);
	}
}
/*
 * �ⲿ�ж�4���������������պͷ��͹��ܡ�
 * */
void __attribute__((interrupt, no_auto_psv)) _INT4Interrupt(void) {
	u8 temp;

	IFS2bits.INT4IF = 0; /*Reset INT4 interrupt flag */
	temp = read_ST554(FCRREG, UART_6);
	temp &= 0x0f;
	while (temp > 1) {
		if (temp == 0x02) //����
				{
			if (uart6.enableSend) {
				if (uart6.txdptr > uart6.txdlen) {
					uart6.enableSend = 0;
					write_ST554(8, MCRREG, UART_6);
				} else {
					temp = 0;
					while ((temp < 16) && (uart6.txdptr <= uart6.txdlen)) {
						write_ST554(txd6Buf[uart6.txdptr], DLLREG, UART_6);
						uart6.txdptr++; //57b2
						temp++;
					}
				}
			}
		} else if ((temp == 0x04) || (temp == 0x0c)) //����
				{
			temp = read_ST554(DLLREG, UART_6);
			if (uart6.resFinish == 0) {
				if (uart6.resBegin == 0) {
					if (temp == MODUS_ADDR) { //ADDRESS
						uart6.resBegin = 1;
						uart6.resLen = 0;
						uart6.resFinish = 0;
						uart6.rxdptr = 1;
						rxd6Buf[0] = temp;
					}
				} else if (uart6.resLen == 0) {
					switch (uart6.rxdptr) {
					case 1:
						rxd6Buf[uart6.rxdptr++] = temp;
						if ((temp != 0x10) && (temp != 0x0f)) {
							uart6.rxdlen = 8;
							uart6.resLen = 1;
						}
						break;
					case 6:
						rxd6Buf[uart6.rxdptr++] = temp;
						uart6.rxdlen = temp + 9;
						uart6.resLen = 1;
						break;
					default:
						rxd6Buf[uart6.rxdptr++] = temp;
						break;
					}
				} else {
					rxd6Buf[uart6.rxdptr++] = temp;
					if (uart6.rxdptr >= uart6.rxdlen) {
						uart6.resBegin = 0;
						uart6.resLen = 0;
						uart6.resFinish = 1;
					}
				}
			}
		} else if (temp == 0x06)
			temp = read_ST554(LSRREG, UART_6);
		temp = read_ST554(IIRREG, UART_6);
		temp &= 0x0f;
	}
	temp = read_ST554(MSRREG, UART_6);
}
/*
 * ������յ��ı��ģ�Э�����������
 * */
void displayCommentHandle(void) {
	u16 temp, crcbuf, num;
	u8 i, j, len, yxtemp, writetemp, settemp;

	while (1) {

		if (uart6.resFinish) {
//		delay_ms(20); //�ٶȿ���в���װ��ͨ����
			uart6.faultPtr = 0;
			uart6.uartState = 0;

			if ((rxd6Buf[1] == 0x10) || (rxd6Buf[1] == 0x0f)) {
				len = rxd6Buf[6] + 7;
				crcbuf = crc16(&rxd6Buf[0], len);
				temp = ((u16) rxd6Buf[len] & 0x00ff) | ((u16) rxd6Buf[len + 1] << 8);
			} else {
				crcbuf = crc16(&rxd6Buf[0], 6);
				temp = ((u16) rxd6Buf[6] & 0x00ff) | ((u16) rxd6Buf[7] << 8);
			}
			if (temp == crcbuf) {
				if ((rxd6Buf[1] == 1) || (rxd6Buf[1] == 2)) //��ң��
						{
					temp = ((u16) rxd6Buf[3] & 0x00ff) | ((u16) rxd6Buf[2] << 8);
					temp = temp % 10000;
					num = ((u16) rxd6Buf[5] & 0x00ff) | ((u16) rxd6Buf[4] << 8);
					len = num / 8;
					if (num % 8)
						len++;
					txd6Buf[0] = MODUS_ADDR; //ADDRESS;
					txd6Buf[1] = rxd6Buf[1];
					txd6Buf[2] = len;
					num = (u16) len;
					len = 3;
					i = temp % 8;
					j = temp / 8;
					while (num--) {
						temp = (u16) pUart6YX[j] | ((u16) pUart6YX[j + 1] << 8);
						j++;
						txd6Buf[len++] = temp >> i;
					}
					sendUart6(len);
				} else if ((rxd6Buf[1] == 3) || (rxd6Buf[1] == 4)) //��ң�� 8+1+16+16=41
						{
					temp = ((u16) rxd6Buf[3] & 0x00ff) | ((u16) rxd6Buf[2] << 8);
					temp = temp % 10000;
					num = (u16) rxd6Buf[5];
					len = 0;
					txd6Buf[len++] = MODUS_ADDR; //ADDRESS;
					txd6Buf[len++] = rxd6Buf[1];
					txd6Buf[len++] = rxd6Buf[5] << 1;

					while (num--) {
						if (temp <= YCBUF_LEN) {
							txd6Buf[len++] = pUart6YC[temp] >> 8;
							txd6Buf[len++] = pUart6YC[temp];
							temp++;
						} else {
							crcbuf = (temp - 100) * 2;
							txd6Buf[len++] = pUart6YX[crcbuf + 1];
							txd6Buf[len++] = pUart6YX[crcbuf];
							temp++;
						}
					}
					sendUart6(len);
				} else if (rxd6Buf[1] == 5) //ң�� 01 05 BITnH BITnL FF 00 CRCL CRCH
						{
					temp = ((u16) rxd6Buf[3] & 0x00ff) | ((u16) rxd6Buf[2] << 8);
					temp = temp % 10000;
					if (temp < 120) {
						i = temp % 8;
						j = temp / 8;
						yxtemp = pUart6YX[j];
						num = ((u16) rxd6Buf[5] & 0x00ff) | ((u16) rxd6Buf[4] << 8);
						if (num == 0xff00) //��:1
								{
							len = 0x01;
							len = len << i;
							pUart6YX[j] = yxtemp | len;
						} else if (num == 0x0000) //��:0
								{
							len = 0x01;
							len = (len << i) ^ 0xff;
							pUart6YX[j] = yxtemp & len;
						}
					}
					len = 0;
					txd6Buf[len++] = MODUS_ADDR; //ADDRESS;
					txd6Buf[len++] = 0x05;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					sendUart6(len);
				} else if (rxd6Buf[1] == 6) //д�����Ĵ��� 01 06 RnH RnL DATAH DATAL CRCL CRCH
						{
					temp = ((u16) rxd6Buf[3] & 0x00ff) | ((u16) rxd6Buf[2] << 8);
					temp = temp % 10000;
					if (temp <= YCBUF_LEN) {
						num = ((u16) rxd6Buf[5] & 0x00ff) | ((u16) rxd6Buf[4] << 8);
						pUart6YC[temp] = num;
//					if (temp >= 70 && temp < 100)
//?????????						saveYcbuf();
//					else
						if ((temp > 52) && (temp < 60)) {
							//set_time();
						}
					} else if (temp < 110) {
						temp -= 100;
						temp <<= 1;
						pUart6YX[temp++] = rxd6Buf[5];
						pUart6YX[temp] = rxd6Buf[4];
					}
					len = 0;
					txd6Buf[len++] = MODUS_ADDR; //ADDRESS;
					txd6Buf[len++] = 0x06;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					sendUart6(len);
				} else if (rxd6Buf[1] == 0x0f) //����дң��λ
						{
					temp = ((u16) rxd6Buf[3] & 0x00ff) | ((u16) rxd6Buf[2] << 8);
					temp = temp % 10000;
					num = ((u16) rxd6Buf[5] & 0x00ff) | ((u16) rxd6Buf[4] << 8);
					len = 7;
					for (crcbuf = 0; crcbuf < num; crcbuf++) {
						if ((crcbuf % 8) == 0)
							writetemp = rxd6Buf[len++];
						i = temp % 8;
						j = temp / 8;
						yxtemp = pUart6YX[j];

						if (writetemp & 0x01) //��:1
								{
							settemp = 0x01;
							settemp = settemp << i;
							if (j < 20)
								pUart6YX[j] = yxtemp | settemp;
						} else //��:0
						{
							settemp = 0x01;
							settemp = (settemp << i) ^ 0xff;
							if (j < 20)
								pUart6YX[j] = yxtemp & settemp;
						}
						temp++;
						writetemp = writetemp >> 1;
					}
					len = 0;
					txd6Buf[len++] = MODUS_ADDR; //ADDRESS;
					txd6Buf[len++] = 0x0f;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					sendUart6(len);
				} else if (rxd6Buf[1] == 0x10) //����д�Ĵ���
						{
					temp = ((u16) rxd6Buf[3] & 0x00ff) | ((u16) rxd6Buf[2] << 8);
					temp = temp % 10000;
					num = ((u16) rxd6Buf[5] & 0x00ff) | ((u16) rxd6Buf[4] << 8);
					len = rxd6Buf[6];
					i = 7;
					while (num--) {
						if (temp <= YCBUF_LEN)
							pUart6YC[temp] = ((u16) rxd6Buf[i + 1] & 0x00ff) | ((u16) rxd6Buf[i] << 8);

						else if (temp < 110) {
							crcbuf = temp - 100;
							crcbuf <<= 1;
							pUart6YX[crcbuf++] = rxd6Buf[i + 1];
							pUart6YX[crcbuf] = rxd6Buf[i];
						}
						temp++;
						i += 2;
					}
//				if ((temp > 70) && (temp < 100))
//					saveYcbuf();
//				if ((temp > 54) && (temp <= 60)) {
//					set_time();
//				}
					len = 0;
					txd6Buf[len++] = MODUS_ADDR; //ADDRESS;
					txd6Buf[len++] = 0x10;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					txd6Buf[len] = rxd6Buf[len];
					len++;
					sendUart6(len);
				}
			}
			uart6.resFinish = 0;
		}
		//displayButtunCheck();

		OSTimeDly(OS_TIME_100ms );
	}
}

/*05F7E
 * �����CRCУ��ֵ������������������н�β,
 * ʹ��16c554d����ʾ�����ͨ��
 * w142-���ݽ�β
 * */
static void sendUart6(u8 w142) {
	u16 w14; //16λ
	w14 = crc16(txd6Buf, w142); //
	txd6Buf[w142++] = w14; //������ֽ�
	txd6Buf[w142++] = (w14 & 0xFF00) >> 8; //������ֽ�
	uart6.txdptr = 1;
	uart6.txdlen = w142;
	uart6.enableSend = 1;

//��ֹ�ж�
	IEC1bits.INT1IE = 0;
	IEC1bits.INT2IE = 0;
	IEC2bits.INT3IE = 0;
	IEC2bits.INT4IE = 0;

	write_ST554(0xA, MCRREG, UART_6); //����RTS=0׼�����ͣ�CD=0,
	write_ST554(MODUS_ADDR, DLLREG, UART_6); //

//ʹ���ж�
	IEC1bits.INT1IE = 1;
	IEC1bits.INT2IE = 1;
	IEC2bits.INT3IE = 1;
	IEC2bits.INT4IE = 1;
}

/*
 * CRCУ��
 * w0=w146����ҪУ�����ݵĵ�ַ,u163f
 * w1=w148����ҪУ�����ݵĳ���
 */
u16 crc16(u8 * w146, u8 w148) {
	u16 w14;
	u8 w144;
	w14 = 0xFFFF;
	while (w148--) {
		w14 = w14 ^ *w146++; //w146����Ϊ8λ
		for (w144 = 0; w144 < 8; w144++) {
			if ((w14 & 1) == 0) { //0x002ea8,���LSB�Ƿ�Ϊ1
				w14 = w14 >> 1;
			} else { //0x002ea8
				w14 = w14 >> 1;
				w14 = w14 ^ 0xa001; //10100000,00000001
			}
		}
	}
	return w14;
}
/*
 * w2��Ҫд�������
 * w1��ACE�Ĵ�����ַA0-A2��16C554��
 * w0��ͨ��ѡ��CS��0-A;1-B;2-C;3-D
 * */
void write_ST554(u8 w2, u8 w1, u8 w0) {
	TRISD &= 0xFF00; //ȫ����Ϊ���
	LATD &= 0xF8FF;
	LATD |= ((u16) w1) << 8; //���õ�ַ2,A0-A2
	u16 temp;
	temp = LATD & 0xFF00;
	temp |= w2;
	if (w0 == 0) {
		LATGbits.LATG12 = 0; //ʹ��Aͨ��-CSA
	} else if (w0 == 1) {
		LATGbits.LATG13 = 0; //ʹ��Bͨ��-CSB
	} else if (w0 == 2) {
		LATGbits.LATG14 = 0; //ʹ��Cͨ��-CSC
	} else {
		LATGbits.LATG15 = 0; //ʹ��Dͨ��-CSD
	}
	LATCbits.LATC1 = 0; //ʹ��д����-IOW
	asm("nop");
	LATD = temp;
	asm("nop");
	LATCbits.LATC1 = 1; //-IOW
	asm("nop");
	if (w0 == 0) {
		LATGbits.LATG12 = 1; //ʹ��Aͨ��-CSA
	} else if (w0 == 1) {
		LATGbits.LATG13 = 1; //ʹ��Bͨ��-CSB
	} else if (w0 == 2) {
		LATGbits.LATG14 = 1; //ʹ��Cͨ��-CSC
	} else {
		LATGbits.LATG15 = 1; //ʹ��Dͨ��-CSD
	}
}
/*
 * w1��ACE�Ĵ�����ַA0-A2��
 * w0��ͨ��ѡ��CS��0-A;1-B;2-C;3-D
 * */
u8 read_ST554(u8 w1, u8 w0) {
	u16 w14;
	TRISD |= 0x00FF; //ȫ����Ϊ����
	LATD &= 0xF8FF;
	LATD |= ((u16) w1) << 8; //���õ�ַ2,A0-A2
//ʹ��ͨ��
	if (w0 == 0) {
		LATGbits.LATG12 = 0; //ʹ��Aͨ��-CSA
	} else if (w0 == 1) {
		LATGbits.LATG13 = 0; //ʹ��Bͨ��-CSB
	} else if (w0 == 2) {
		LATGbits.LATG14 = 0; //ʹ��Cͨ��-CSC
	} else {
		LATGbits.LATG15 = 0; //ʹ��Dͨ��-CSD
	}
	asm("nop");
	LATCbits.LATC2 = 0; //ʹ�ܶ�����-IOR
	asm("nop");
	w14 = PORTD;
	LATCbits.LATC2 = 1; //-IOR
	asm("nop");
	if (w0 == 0) {
		LATGbits.LATG12 = 1; //ʹ��Aͨ��-CSA
	} else if (w0 == 1) {
		LATGbits.LATG13 = 1; //ʹ��Bͨ��-CSB
	} else if (w0 == 2) {
		LATGbits.LATG14 = 1; //ʹ��Cͨ��-CSC
	} else {
		LATGbits.LATG15 = 1; //ʹ��Dͨ��-CSD
	}
	return (u8) w14;
}
/*
 * �ⲿ�ж�4��ʼ�����ú���
 * */
void displayInit(void* yc, void* yx) {
	IEC2bits.INT4IE = 0; /*Disenable INT4 Interrupt Service Routine */

	write_ST554(0x80, LCRREG, 3); //�߿��ƼĴ���
	write_ST554(0xc, DLLREG, 3); //�������ռĴ���/д�����ͼĴ���
	write_ST554(0, DLMREG, 3); //�ж�ʹ�ܼĴ���
	write_ST554(3, LCRREG, 3); //�߿��ƼĴ���
//��������ʹ��,����ż,ֹͣλ����1,���ͻ���յ��ֳ���8
//FIFO�жϴ�����8
	write_ST554(0x87, FCRREG, 3); //�����жϱ�ʶ�Ĵ���/д��FIFO���ƼĴ���
//ʹ��TXRDY��ISR���ȼ�3���жϡ�ʹ��RXRDY��ISR���ȼ�2���жϡ�
	write_ST554(3, IERREG, 3); //�ж�ʹ�ܼĴ���
	write_ST554(8, MCRREG, 3); //ģʽ���ƼĴ���

	read_ST554(RHRREG, 3);
	read_ST554(LSRREG, 3);
	read_ST554(IIRREG, 3);
	read_ST554(RHRREG, 3);
	read_ST554(LSRREG, 3);
	read_ST554(IIRREG, 3);

	INTCON2 &= 0xffef; /*Setup INT4 pins to interupt on rising edge */

	IPC9bits.INT4IP = 4;
	IFS2bits.INT4IF = 0; /*Reset INT4 interrupt flag */
	IEC2bits.INT4IE = 1; /*Enable INT4 Interrupt Service Routine */
	uart6.resBegin = 0;
	uart6.resLen = 0;
	uart6.resFinish = 0;
	uart6.enableSend = 0;
	uart6.faultPtr = 0;
	uart6.pRxdBuf = (u8 *) &rxd6Buf;
	uart6.pTxdBuf = (u8 *) &txd6Buf;
	pUart6YC = (u16*) yc;
	pUart6YX = (u8*) yx;

	OSTaskCreate(displayCommentHandle, (void *) 1, &displayStak[0], 1);

}
