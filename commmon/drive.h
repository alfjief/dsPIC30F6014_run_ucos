/*
 * drive.h
 *
 *  Created on: 2014-8-15
 *      Author: Administrator
 */

void taskDriveTest();

//------------------Ӳ�����------------------------//
#define	LED2			LATDbits.LATD14  //
#define	LED3			LATDbits.LATD15  //
#define	LED4			LATFbits.LATF7   //
#define	LED5			LATFbits.LATF6
#define	LED6			LATDbits.LATD11  //
//#define	portActrl		LATCbits.LATC14 //relay1�����ཻ��
#define	portActrl		LATCbits.LATC3  //A�ڿ���,relay6
#define	portAReadyLamp	LATCbits.LATC4  //A�����ֵ�,relay7
#define	portALamp		LATDbits.LATD13 //A�ڳ��ָʾ��,relay3
#define	portBctrl		LATAbits.LATA6  //B�ڿ���,relay4
#define	portBReadyLamp	LATAbits.LATA7  //B�����ֵ�,relay5
#define	portBLamp		LATDbits.LATD12 //B�ڳ��ָʾ��,relay2
#define	relay1			LATCbits.LATC14 //relay1
#define	speaker			LATGbits.LATG6 //������
//
#define 	ST16C_RESET		LATCbits.LATC13		//st16c55d�ĸ�λ
