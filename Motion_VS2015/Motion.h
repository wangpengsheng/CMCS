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

	//*******************************************初始化*****************************/
	int InitBoard();		//初始化运动控制卡
	int InitAllCard();		//根据配置文件初始化所有卡
	void Deinit();			//关闭运动卡
	//*******************************************复位*******************************/
	int Reset();														//card--reset
	int Axis_Reset(unsigned short cardIndex, unsigned short axisIndex); //axis-reset
	//*******************************************HOME*******************************/
	int Axis_Home(unsigned short cardIndex, unsigned short axisIndex); //单轴回原-不等待
	int Axis_WaiteHome(unsigned short cardIndex, unsigned short axisIndex); //等待回原结束
	int Axis_WaiteHome(unsigned short cardIndex, unsigned short axisIndex, int waitTime); //等待回原结束，等待时间到达，停止轴运动
	int Axis_WaitHome(unsigned short cardIndex, unsigned short axisIndex, double curPos, double len);//等待回原结束，轴移动超过len距离，停止轴
	int Axis_Home_Finished(unsigned short cardIndex, unsigned short axisIndex); //单轴回原是否成功//不等待
	//*******************************************轴状态******************************/
	int Axis_Is_Moving(unsigned short cardIndex, unsigned short axisIndex); //1运动中 0就绪
	//*******************************************轴运动******************************/
	int Move_Pos(unsigned short cardIndex, unsigned short axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0);
	int Move_Offset(unsigned short cardIndex, unsigned short axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0, int basePos = 0);
	int Move_Jog(unsigned short cardIndex, unsigned short axisIndex, int dir, double vel = 0, double acc = 0, double dec = 0); //dir 0 负方向 1 正方向
	int Axis_Stop(unsigned short cardIndex, unsigned short axisIndex, int stopType);
	int Set_Current_Pos(unsigned short cardIndex, unsigned short axisIndex, double pos); //设置该轴位置
	int Get_Current_Pos(unsigned short cardIndex, unsigned short axisIndex, double& val); //获取当前位置
	int Get_Panning_Pos(unsigned short cardIndex, unsigned short axisIndex, double& val); //获取规划位置
	//*******************************************轴运动 -- 插补*******************************/
	int CreateCrd(unsigned short* pCardIndex, unsigned short* pAxisIndex, unsigned short axisCnt);
	int AddArcPos(int crdID, double* ppos1, double* ppos2, double* ppos3, TSpeed* pspeed);
	int CrdStatus(int crdID, short* pRun, long* pSegment);
	int ClearCrdData(int crdID);
	int GetAxisType(unsigned short cardIndex, unsigned short axisIndex); //获取轴类型
	/*********************************************IO读写****************************************************************/
	//专用IO读写（位读取）
	int ReadInBit_Alarm(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡报警信号
	int ReadInBit_LimitN(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡负限位
	int ReadInBit_LimitP(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡正限位
	int ReadInBit_Origin(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡原点信号
	int ReadInBit_Ready(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡就绪信号
	int ReadInBit_Inplace(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡到位信号
	int ReadInBit_Enable(unsigned short cardIndex, unsigned short axisInx, short& val); //读取卡使能信号
	int writeOutBit_Enable(unsigned short cardIndex, unsigned short axisInx, const short val); //设置是卡能信号

	int ReadIn_Ext(unsigned short extIndex, long long& val);		//读取扩展卡输入
	int ReadOut_Ext(unsigned short extIndex, long long& val);		//读取扩展卡输出
	int WriteOut_Ext(unsigned short extIndex, const long long val); //设置扩展卡输出

	//普通IO位读写
	int ReadInBit(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val, int cardType);
	int ReadOutBit(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val, int cardType);
	int writeOutBit(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, const short val, int cardType);

	int ReadInBit_Self(unsigned short cardIndex, unsigned short IOIndex, short& val);		 //读取自身普通输入位
	int ReadOutBit_Self(unsigned short cardIndex, unsigned short IOIndex, short& val);		 //读取自身普通输出位
	int WriteOutBit_Self(unsigned short cardIndex, unsigned short IOIndex, const short val); //设置自身普通输出位

	int ReadInBit_Ext(unsigned short extIndex, unsigned short IOIndex, short& val);			//读取0640扩展输入位
	int ReadOutBit_Ext(unsigned short extIndex, unsigned short IOIndex, short& val);		//读取0640扩展输出位
	int WriteOutBit_Ext(unsigned short extIndex, unsigned short IOIndex, const short val);  //设置0640扩展输出位

	int ReadInBit_Can(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val);//读取Can扩展输入位
	int ReadOutBit_Can(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, short& val);//读取Can扩展输出位
	int WriteOutBit_Can(unsigned short cardIndex, unsigned short cardNode, unsigned short IOIndex, const short val);//设置Can扩展输出位

	//插补相关函数
	int motion_check_done(unsigned short cardIndex, unsigned short axisIndex);
	//	int motion_conti_stop_list(unsigned short cardIndex, quint16 crd, quint16 mode);
	//	int motion_conti_open_list(quint16 cardIndex, quint16 crd, quint16 axisNum, quint16* axisList);

private:
	Motion();
	static std::unique_ptr<Motion> instance;
};

