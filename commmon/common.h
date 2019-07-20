/*
 * common.h
 *
 *  Created on: 2014-8-13
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_

//-------------------�汾----------------------------//
#define VERSION_YEARS 3014		//��λv3.0����λ14��
#define MONTHS_DATA 804		//��λ1�£���λ8��

typedef unsigned char u8;
typedef unsigned char bool;
typedef unsigned int u16;
typedef unsigned long u32;
#define NULL                     (0)
#ifndef true
#define true          (1)
#endif
#ifndef false
#define false         (0)
#endif

typedef struct {
	u16 userID0_3; //�û�����0-3λ17f0,//���ұߵ�λ
	u16 userID4_7; //�û�����4-7λ
	u16 userID8_11; //�û�����8-11λ
	u16 userID12_15; //�û�����12-15λ
	u16 yuYueIdA; //5
	u16 yuYueIdB; //6
	u32 cardBalance; //����ʣ������7
	u16 pageNum; //��ѹ�����ɸ澯����9,1800
	u16 buttonNum; //��λ���Ѿ����������ص�����10 ��״̬1802
	u16 hmiPageNum; //Ŀǰ���״̬��־λ����11,1804
	u16 inputMoney; //�������������Ҫ���Ľ������12,1806
	u16 chargeMode; //������λ���ĳ��ģʽѡ��13,1808
	u16 chargeTime; //ԤԼ���ʱ��14,180a
	u16 userIdA0_3; //A���û����ŵ�15,180c
	u16 userIdA4_7; //A���û���180e
	u16 userIdA8_11; //A���û���1810
	u16 userIdA12_15; //A���û���1812
	u32 balanceA; //A������1814
	u16 inputMoneyA; //����������1818
	u16 chargeModeA; //���ģʽ181a
	u16 chargeTimeHoursA; //û��ʹ��
	u16 chargeTimeMinuA; //A�ڳ�������24,181e��ԤԼʣ��ʱ��
	u16 chargeElecA; //A���ѳ�����25,1820
	u32 chargeMoneyA; //A���ѳ����26,1822
	u16 cardMoneyA; //A�ڿ�����28,1824
	u32 startElecA; //����ʱ����
	u16 stateA; //31
	//1-5-����쳣�������豸����ͨѶ�쳣(����ʧ��)
	//2-�����豸������ģ��ͨѶ�쳣
	//6-ͨѶ���쳣
	//7-��������
	//40-ֹͣ��磨��������ֹͣ��
	//41-ֹͣ��磨ѡ������������ֹͣ��
	//60-����ʱ�뿪ʼ��翨�Ų�ͬ
	//61-    ��  ��
	//62-�޷��ҵ��õ��¼
	//63-�ۿ�ʧ��
	//65-�˿����ڳ��
	u16 alarmType; //32   //����쳣
	u32 passwordCom; //������λ��������ֵ33,1830
	u16 userIdB0_3; //B���û����ŵ�35,1834
	u16 userIdB4_7; //B���û�����1836
	u16 userIdB8_11; //B���û�����1838
	u16 userIdB12_15; //B���û�����183a
	u32 balanceB; //183c�����
	u16 inputMoneyB; //�û�����������
	u16 chargeModeB; //���ģʽ
	u16 chargeTimeHoursB; //û��ʹ��
	u16 chargeTimeMinuB; //B���ѳ�������44,1846,ԤԼʣ��ʱ��
	u16 chargeElecB; //B���ѳ�����45,1848
	u16 chargeMoneyB; //B���ѳ����46,184a
	u32 cardMoneyB; //B�ڿ�����λ47,184c
	u32 rtElecA; //49ʵʱ����
	u16 stateB; //51
	////////////100///////////////////
	u16 lcdTimePtr;		//52
	u16 u1858;
	u16 realTime[7];		//54
//	u16 secondsmmmm; //��54
//	u16 seconds; //ʱ����55
//	u16 minutes; //ʱ�ӷ�56
//	u16 hours; //ʱ��ʱ57
//	u16 dates; //ʱ����58
//	u16 months; //ʱ����59
//	u16 yearsL; //ʱ����60

	//������ѹ�������
	u16 voltageArms; //A��ʵʱ����ѹ61,1868
	//������ѹ�������
	u16 voltageBrms; //B��ʵʱ����ѹ62,186a
	//������ѹ�������
	u16 voltageCrms; //C���ѹ63,186c
	u16 currentArms; //A��ʵʱ������64,186e
	u16 adc4; //1870
	u16 adc5; //1872
	u16 currentBrms; //B��ʵʱ������67,1874
	u16 adc7; //1876
	u16 adc8; //1878
	u16 record_ov_value; //��¼�½������澯ֵ70����ѹֵ,187a

	//д��EEPROM��ʼ��ַ������60�ֽ�
	u16 ov_vlaue; //��ѹ��׼,187c
	u16 uv_vlaue; //Ƿѹ��׼,187e
	u16 oi_vlaue; //������׼,0x1f4=500,1880
	u16 pwmDuty; //74ռ�ձ�
	u16 u1884; //0x3a98; //15000
	u16 u1886; //0x2710; //10000
	u16 u1888; //0x1388; //5000

	u16 ammeCount; //����ַ����78,188a
	u16 ammeAdd5A; //����ַ��5λ,188c
	u16 ammeAdd4A; //����ַ��4λ,188e
	u16 ammeAdd3A; //����ַ��3λ,1890
	u16 ammeAdd2A; //����ַ��2λ,1892
	u16 ammeAdd1A; //����ַ��1λ,1894
	u16 ammeAdd0A; //����ַ��0λ,1896
	u16 ammeAdd5B; //����ַ��5λ,1898
	u16 ammeAdd4B; //����ַ��4λ,189a
	u16 ammeAdd3B; //����ַ��3λ,189c
	u16 ammeAdd2B; //����ַ��2λ,189e
	u16 ammeAdd1B; //����ַ��1λ,18a0
	u16 ammeAdd0B; //����ַ��0λ90,18a2

	u16 coef_voltageA; //A���ѹϵ����18a4
	u16 coef_voltageB; //B���ѹϵ����
	u16 coef_voltageC; //C���ѹϵ����
	u16 coef_currentA; //A�����ϵ����
	u16 coef_adc4; //
	u16 coef_adc5; //
	u16 coef_currentB; //B�����ϵ����
	u16 coef_adc7; //18b2
	u16 coef_adc8; //18b4

	u16 sumCheck_18b6; //99У��
	//д��EEPROM��β��ַ������3C

	//���ϼ�¼
	u16 readFlag;		//1-��ȡ���ϼ�¼��־
	u16 readChargeFlag;	//1-��ȡ����¼��־
	u16 recordNum; //��¼��
	u16 ttt[20]; //����

	u16 years_v; //124���������汾
	u16 data_v;
	u16 years2_v; //ͨѶ�����汾
	u16 data2_v;
	u16 priceH;
	u16 priceL; //���
	//
	u16 wsPwm; //130�������źŰ��ϴ�
	u16 woshouVolt; //���ְ�У׼��ѹ131
	u16 wsVoltA; //�������źŰ��ϴ�
	u16 wsVoltB; //�������źŰ��ϴ�
	u32 congealMoney; //134������
	u16 deviceID; //136,վ�ڳ��׮���
	u16 id_num1; //137,��ά��ID��λ
	u16 id_num2; //138
	u16 id_num3;
	u16 id_num4; //140,10λID��ʼ��ַ
	u16 id_num5; //141
	u16 id_num6;
	u16 id_num7;
	u16 id_num8; //144ID��λ

	u16 e1; //145//��ʾ������������Ļ��,������ֽڱ���
	u16 hmiPageNum2; //146
	u16 e3; //
	u16 e4; //
	u16 e5; //
	u16 e6; //150

	u16 AmeterVoltA; //A��A���ѹ151
	u16 AmeterVoltB; //A��B���ѹ
	u16 AmeterVoltC; //A��C���ѹ
	u16 AmeterCurrA; //A��A�����154
	u16 AmeterCurrB; //A��B�����
	u16 AmeterCurrC; //A��C�����
	u16 BmeterVoltA; //B��A���ѹ157
	u16 BmeterVoltB; //B��B���ѹ
	u16 BmeterVoltC; //B��C���ѹ
	u16 BmeterCurrA; //B��A�����160
	u16 BmeterCurrB; //B��B�����
	u16 BmeterCurrC; //B��C�����162
	u16 tta[8]; //163-169����

	u8 record[240]; //171

} YCBUF, *pYCBUF;

typedef struct {
	//196c
	unsigned opFlag0 :1; //RG7,A�����ź�PP
	unsigned opFlag1 :1; //RG8,�Ӵ���A����
	unsigned opFlag2 :1; //RG9,B�����ź�PP
	unsigned opFlag3 :1; //RB2,�Ӵ���B����
	unsigned opFlag4 :1; //RB3
	unsigned opFlag5 :1; //RB4
	unsigned opFlag6 :1; //RB5
	unsigned opFlag7 :1; //RB6

	//196d,AB�ڳ�����
	unsigned u196d_0 :1; //196d-0
	unsigned readyLampA :1; //A�����ֵ�,196d-1
	unsigned chargeACtrl :1; //A�ڿ���,196d-2
	unsigned readyLampB :1; //B�����ֵ�,196d-3
	unsigned chargeBCtrl :1; //B�ڿ���,196d-4
	unsigned chargeLampA :1; //A�ڳ��ָʾ��,196d-5
	unsigned chargeLampB :1; //B�ڳ��ָʾ��.196d-6
	unsigned u196d_7 :1; //196d-7

	//�������������1Ԫ������1����ת�������������
	unsigned icCardMoneOk_196e_0 :1; //��һ�ζ����ɹ�
	unsigned u196ebit1 :1;
	unsigned u196ebit2 :1;
	unsigned u196ebit3 :1;
	unsigned u196ebit4 :1;
	unsigned u196ebit5 :1;
	unsigned u196ebit6 :1;
	unsigned u196ebit7 :1; //ǰ�γ��δ����

	//196f
	unsigned inCard :1; //������λ��Ҫ׼������������25
	unsigned sendPassword :1; //�����������λ��ͬʱ�ø�λ
	/* �ڵ����Ļȷ����ťʱ����ʾ������Ѹ�λ����Ϊ1��
	 * ���Ƴ����19a0��1�����Ͷ�������������ݣ�
	 * ����������һ������ʱ���Ѹ�λ���㡣
	 * */
	unsigned firstCard :1; //�״β忨��ʾ27
	unsigned writeCard :1; //����д��ʧ��
	unsigned otherCard :1; //��������翨�Ų�ͬ
	unsigned selectPortA :1; //ѡ��A�ں󷢸���λ���ı�־
	unsigned selectPortB :1; //ѡ��B�ں󷢸���λ���ı�־
	//�ȸ���ҳ������λOver
	unsigned outCard :1; //�˿�����32,196f-7

	//1970,�澯
	unsigned voltageAlarmA :1; //�����ǷѹΪ1//����A��ѹ�쳣�澯33
	unsigned voltageAlarmB :1; //�����ǷѹΪ1//����B��ѹ�쳣�澯
	unsigned enableA :1; //A��ڿ�ѡ��ť35
	unsigned enableB :1; //B��ڿ�ѡ36
	unsigned u1970bit4 :1; //
	unsigned u1970bit5 :1; //
	unsigned currAlarmA :1; //A�ڹ���
	unsigned currAlarmB :1; //B�ڹ���

	//1971,1-���У�0-�����ɣ�δ����
	unsigned settlFinishA :1; //1-A�ڽ���д��δ�ܳɹ�,1971-0
	//1-���У�0-���
	unsigned settlFinishB :1; //1-B�ڽ���д��δ�ܳɹ���1971-1
	unsigned stopA :1; //��������ֹA�ڳ��43,1971-2
	unsigned stopB :1; //��������ֹB�ڳ��,1971-3
	unsigned portErrA :1; //A��ڹ���,1971-4
	unsigned portErrB :1; //B��ڹ���46,1971-5
	unsigned settlementA :1; //����A��ڽ��,1971-6
	unsigned settlementB :1; //����B��ڽ��48,1971-7

	//�澯1972
	unsigned u1972bit0 :1; //49�����ǷѹΪ1
	unsigned u1972bit1 :1;
	unsigned u1972bit2 :1;
	unsigned u1972bit3 :1;
	unsigned u1972bit4 :1; //�����ǷѹΪ1
	unsigned u1972bit5 :1;
	unsigned u1972bit6 :1;
	unsigned u1972bit7 :1; //56
	//ԤԼ���1973
	unsigned yueA :1; //A���Ѿ�ԤԼ,57
	unsigned yueAstart :1; //ԤԼ�û���ʼ���
	unsigned yueB :1; //B���Ѿ�ԤԼ,59
	unsigned yueBstart :1; //ԤԼ�û���ʼ���
	unsigned u1973bit4 :1;
	unsigned u1973bit5 :1;
	unsigned u1973bit6 :1;
	unsigned u1973bit7 :1; //64

	//��ʱ���
	unsigned u1974bit0 :1; //65
	unsigned u1974bit1 :1; //ʱ���ʽ����û�õ�
	unsigned showStopPasswordA :1; //67��ʾֹͣ��������
	unsigned showStopPasswordB :1; //68��ʾֹͣ��������
	unsigned stopPasswordVerify :1; //69ֹͣ���ʱ������֤
	unsigned receivingPassword :1; //0-���ڽ������룬1-�Ѿ����յ�����
	unsigned chargingTxtA :1; //0-����У�1-��ͣ71
	unsigned chargingTxtB :1; //0-����У�1-��ͣ
	//
	unsigned verifyTimePassword :1; //73�·���֤��������
	unsigned isCard :1; //74�Ƿ��п�
	unsigned isTiming :1; //75�Ƿ�ʱ
	unsigned verifyPasswordOK :1; //�����Ƿ���ȷ
	unsigned hideChargeButton :1; //77AB�ڶ���ʱ��磬���س�簴ť��
	unsigned pwmOnA :1; //���ְ��ϴ�ռ�ձ��Ƿ��Ѿ�����
	unsigned pwmOnB :1; //���ְ��ϴ�ռ�ձ��Ƿ��Ѿ�����
	unsigned woshouban_set :1; //80��ʾ���������ְ�У׼����

} YXBUF, *pYXBUF; //��20��

typedef struct {
	unsigned resBegin :1; //���յ���ʼ��
	unsigned resLen :1; //���յ������򳤶���
	unsigned resFinish :1; //�������
	unsigned enableSend :1; //ʹ�ܷ���
	unsigned aa1 :1; //����
	unsigned aa2 :1;
	unsigned aa3 :1;
	unsigned aa4 :1;
	u8 rxdptr;
	u16 rxdlen;
	u8 txdptr;
	u8 txdlen;
	u8* pRxdBuf;
	u8* pTxdBuf;
	u8 uartState; //ͨ��״̬
	u16 faultPtr; //�쳣����
} UartTag, *pUartTag;


void memCpy(u8* pDst, u8* pSrc, u16 len);
u8 memComp(u8* pDst, u8* pSrc, u16 len);
void copyU16ToU8(u8*pdst, u16*psrc, u8 len);
void copyU8ToU16(u16*pdst, u8*psrc, u8 len);
void clrMem(u8*psrc, u16 len);


#endif /* COMMON_H_ */
