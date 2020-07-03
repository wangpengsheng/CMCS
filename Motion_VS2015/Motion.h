#pragma once
#include <memory>
#include <iostream>
#include "Motion_common.h"

class Axis;
class MotionImp;

#define MOTION_INSTANCE Motion::getInstance()

class Motion
{
public:
	static Motion &getInstance()
	{
		if (instance == nullptr)
		{
			instance.reset(new Motion());
		}
		return *instance;
	}
	~Motion();

	//*******************************************��ʼ��*****************************/
	int InitBoard();		//��ʼ���˶����ƿ�
	int InitAllCard();		//���������ļ���ʼ�����п�
	void Deinit();			//�ر��˶���
	//*******************************************��λ*******************************/
	int Reset();														//card--reset
	int Axis_Reset(unsigned short cardIndex, unsigned short axisIndex); //axis-reset
	//*******************************************HOME*******************************/
	int Axis_Home(unsigned short cardIndex, unsigned short axisIndex); //�����ԭ-���ȴ�
	int Axis_WaiteHome(unsigned short cardIndex, unsigned short axisIndex); //�ȴ���ԭ����
	int Axis_WaiteHome(unsigned short cardIndex, unsigned short axisIndex, int waitTime); //�ȴ���ԭ�������ȴ�ʱ�䵽�ֹͣ���˶�
	int Axis_WaitHome(unsigned short cardIndex, unsigned short axisIndex, double curPos, double len);//�ȴ���ԭ���������ƶ�����len���룬ֹͣ��
	int Axis_Home_Finished(unsigned short cardIndex, unsigned short axisIndex); //�����ԭ�Ƿ�ɹ�//���ȴ�
	//*******************************************��״̬******************************/
	int Axis_Is_Moving(unsigned short cardIndex, unsigned short axisIndex); //1�˶��� 0����
	//*******************************************���˶�******************************/
	int Move_Pos(unsigned short cardIndex, unsigned short axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0);
	int Move_Offset(unsigned short cardIndex, unsigned short axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0, int basePos = 0);
	int Move_Jog(unsigned short cardIndex, unsigned short axisIndex, int dir, double vel = 0, double acc = 0, double dec = 0); //dir 0 ������ 1 ������
	int Axis_Stop(unsigned short cardIndex, unsigned short axisIndex, int stopType);
	int Set_Current_Pos(unsigned short cardIndex, unsigned short axisIndex, double pos); //���ø���λ��
	int Get_Current_Pos(unsigned short cardIndex, unsigned short axisIndex, double& val); //��ȡ��ǰλ��
	int Get_Panning_Pos(unsigned short cardIndex, unsigned short axisIndex, double& val); //��ȡ�滮λ��
	//*******************************************���˶� -- �岹*******************************/
	int CreateCrd(unsigned short* pCardIndex, unsigned short* pAxisIndex, unsigned short axisCnt);
	int AddArcPos(int crdID, double* ppos1, double* ppos2, double* ppos3, TSpeed* pspeed);
	int CrdStatus(int crdID, short* pRun, long* pSegment);
	int ClearCrdData(int crdID);
	int GetAxisType(unsigned short cardIndex, unsigned short axisIndex); //��ȡ������
	/*********************************************IO��д****************************************************************/
	//ר��IO��д��λ��ȡ��
	int ReadInBit_Alarm(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ�������ź�
	int ReadInBit_LimitN(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ������λ
	int ReadInBit_LimitP(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ������λ
	int ReadInBit_Origin(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ��ԭ���ź�
	int ReadInBit_Ready(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ�������ź�
	int ReadInBit_Inplace(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ����λ�ź�
	int ReadInBit_Enable(unsigned short cardIndex, unsigned short axisInx, short& val); //��ȡ��ʹ���ź�
	int writeOutBit_Enable(unsigned short cardIndex, unsigned short axisInx, const short val); //�����ǿ����ź�

	int ReadIn_Ext(unsigned short extIndex, long long& val);		//��ȡ��չ������
	int ReadOut_Ext(unsigned short extIndex, long long& val);		//��ȡ��չ�����
	int WriteOut_Ext(unsigned short extIndex, const long long val); //������չ�����

	//��ͨIOλ��д
	int ReadInBit(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val, int cardType);
	int ReadOutBit(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val, int cardType);
	int writeOutBit(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, const short val, int cardType);

	int ReadInBit_Self(unsigned short cardIndex, unsigned short IOIndex, short& val);		 //��ȡ������ͨ����λ
	int ReadOutBit_Self(unsigned short cardIndex, unsigned short IOIndex, short& val);		 //��ȡ������ͨ���λ
	int WriteOutBit_Self(unsigned short cardIndex, unsigned short IOIndex, const short val); //����������ͨ���λ

	int ReadInBit_Ext(unsigned short extIndex, unsigned short IOIndex, short& val);			//��ȡ0640��չ����λ
	int ReadOutBit_Ext(unsigned short extIndex, unsigned short IOIndex, short& val);		//��ȡ0640��չ���λ
	int WriteOutBit_Ext(unsigned short extIndex, unsigned short IOIndex, const short val);  //����0640��չ���λ

	int ReadInBit_Can(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val);//��ȡCan��չ����λ
	int ReadOutBit_Can(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val);//��ȡCan��չ���λ
	int WriteOutBit_Can(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, const short val);//����Can��չ���λ

	//�岹��غ���
	int motion_check_done(unsigned short cardIndex, unsigned short axisIndex);
	//	int motion_conti_stop_list(unsigned short cardIndex, quint16 crd, quint16 mode);
	//	int motion_conti_open_list(quint16 cardIndex, quint16 crd, quint16 axisNum, quint16* axisList);

private:
	Motion();
	static std::unique_ptr<Motion> instance;
};

