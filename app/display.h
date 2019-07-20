/* ==========================================================================*/
/* - - - - - - - - - - - - -  U A R T . H  - - - - - - - - - - - - - - - - */
/* ==========================================================================*/
/* ==========================================================================*/
/*	Created   07-1-2010   GUANPH                                      */
/*	Modified                                                  */

#ifndef UART6_H
#define UART6_H

#define MODUS_ADDR 1
#define YCBUF_LEN  300

#define UART_3 0 //������
#define UART_4 1 //������
#define UART_5 2 //������
#define UART_6 3 //������
#define RHRREG 0	//���ܻ�����(DLAB=0)
#define THRREG 0	//���ͻ�����(DLAB=0)
#define DLLREG 0	//���������� (LSB)(DLAB=1)
#define DLMREG 1	//���������� (MSB)(DLAB=1)
#define IERREG 1	//�ж�ʹ�ܼĴ���
#define IIRREG 2	//�ж�ʶ��Ĵ���(ֻ��)
#define FCRREG 2	//FIFO���ƼĴ���(д)
#define LCRREG 3	//�߿ؼĴ���
#define MCRREG 4	//���ƽ�������ƼĴ���
#define LSRREG 5	//��״̬�Ĵ���
#define MSRREG 6	//���ƽ����״̬�Ĵ���
#define SPRREG 7	//�ݴ�(Scratch)�Ĵ���(SCR)



void displayInit(void* yc, void* yx);
void displayCommentHandle(void);
u32 displayReadPassword();
void displayWriteValue(u16 name, u8* value, u8 len);
//
void write_ST554(u8 w2, u8 w1, u8 w0);
u8 read_ST554(u8 w1, u8 w0);
u16 crc16(u8 * w146, u8 w148);

#endif
