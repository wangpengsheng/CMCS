#pragma once
#include "stdafx.h"
#include <vector>
#include <bitset>
#include <string>
#include <mutex>
#include <future>
#include <iostream>
//电机及运动相关

using namespace std;

#define CFGDIR(X) "D:/Auto_Sloder_Welding/"##X

#define INVALID_AXIS		-1		//无效轴
#define MOTOR_MAX_NAME		36		//名称
#define MOTOR_MAX_AXIS		6       //最大多少轴？
#define COOL_CNT			2		//每张卡只能有2个坐标系
#define CRD_AXIS_CNT		4		//每个坐标系最多4个轴
#define SAME_PULSE_OFFSET	5		//差距多少个脉冲认为位置没有变化
#define MAX_AXISCNT			8


//以下自由配置信号是否取反
#define DMC_CFG			"dmc_cfg"
#define POSITIVE_SENCE	"positive_sence"        //正限位
#define NEGATIVE_SENCE	"negative_sence"        //负限位
#define ALARM_SENCE		"alarm_sence"           //报警信号
#define HOME_SENCE		"home_sence"            //原点信号
#define GPI_SENCE		"gpi_sence"             //通用输入
#define GPIEXT_SENCE	"gpiext_sence"          //扩展卡通用输入
#define ENABLE_SENCE	"enable_sence"          //伺服使能
#define CLEAR_SENCE		"clear_sence"           //清除报警
#define GPO_SENCE		"gpo_sence"             //通用输出
#define GPOEXT_SENCE	"gpoext_sence"          //扩展卡通用输出


//错误代码
enum EM_ERR_CODE
{
	ERR_INPUT_PARAM = -1000,        //入参为空或者不合法

	//comm err
	ERR_TIMEOUT,                    //等待超时
	ERR_NO_CONNECT,                 //未连接
	ERR_NOINIT_COMM,                //未初始化comm库
	ERR_NO_REG,                     //未注册
	ERR_REPEAT_REG,                 //重复注册
	ERR_DATA_OVERLIMIT,             //数据溢出
	ERR_INVALID_ID,                 //此ID不存在，或者不合法
	ERR_NO_NAME,                    //该名称不存在
	ERR_NAME_EXIST,                 //该名称已经存在
	ERR_CFG_ACTION,                 //配置文件读取/写入错误
	ERR_CFG_DATA,                   //配置文件错误

	//NetWork
	ERR_NOINIT,						//未初始化
	ERR_INVALID_IP,                 //无效IP
	ERR_INVALID_PORT,               //无效端口
	ERR_INVALID_SOCKET,             //无效句柄
	ERR_CONN_CLOSE,					//连接断开
	ERR_LISTEN,						//socket监听失败
	ERR_ACCEPT,						//接受连接失败
	ERR_CONNECT,					//连接服务端失败
	ERR_RECV_MSG,                   //接收消息出错
	ERR_SEND_MSG,                   //发送消息出错
	ERR_GET_SKTINFO,                //获取socket信息(ip,port)
	ERR_SEND_CHECK,                 //发送校验失败

	//user
	ERR_NOINIT_USER,                //未初始化user库
	ERR_NO_LOGIN,                   //未登录
	ERR_NO_LIMIT,                   //无权限
	ERR_INVALID_PWD,                //密码无效
	ERR_LIMIT_OVER,                 //权限设置只有32位，超限了

	//cntl
	ERR_NOINIT_CNTL,                //未初始化串口库
	ERR_OPEN_COM,                   //打开串口失败
	ERR_INVALID_COM,                //无效的串口句柄
	ERR_COM_WRITE,                  //设置/写入串口错误

	//motor err
	ERR_MOTOR_API,                  //控制卡接口命令返回错误
	ERR_NO_CARD,                    //控制卡不存在，或者无卡
	ERR_CARD_EXIST,                 //控制卡已经存在
	ERR_LOAD_CFG,                   //加载配置文件失败
	ERR_INIT_MOTOR,                 //初始化控制卡失败
	ERR_INVALID_AXIS,               //无效轴
	ERR_INVALID_CARD,               //无效卡
	ERR_INVALID_EXT,                //无效的IO模块(卡自带或扩展模块)
	ERR_NOINIT_MOTOR,               //未初始化控制卡
	ERR_AXIS_HOME,                  //轴回原失败
	ERR_SET_HOMEPOS,                //设置原点位置失败
	ERR_AXIS_MOVING,                //轴正在运动中
	ERR_GET_CURPOS,                 //获取当前位置失败
	ERR_CARD_RESET,                 //卡复位失败
	ERR_AXIS_RESET,                 //轴复位失败
	ERR_AXIS_TRAP,                  //轴点位运动失败
	ERR_AXIS_CAPTURE,               //硬件捕获模式失败
	ERR_AXIS_GEAR,                  //跟随模式运动失败
	ERR_SET_CRD,                    //建立坐标系失败
	ERR_CRD_OVERLIMIT,              //坐标系超过2个
	ERR_GET_CRD,                    //获取坐标系失败
	ERR_ARC_MOVE,                   //圆弧插补不合法，数据错误
	ERR_CRD_MOVE,                   //坐标系运动失败
	ERR_IO_TYPE,                    //io类型错误
	ERR_WRITE_IO,                   //写入io失败

	//control err
	ERR_NOINIT_CONTROL,             //未初始化control库
	ERR_MOVE_OVERLIMIT,             //运动超限
	ERR_OCCUPY_IO,                  //IO被占用
	ERR_OCCUPY_AXIS,                //轴被占用
	ERR_STATION_NOREADY,            //工站未就绪
	ERR_ROBOT_EXEC,                 //robot指令返回失败
	ERR_ROBOT_CONNECT,              //机器人通讯错误

	//ops error
	ERR_PROC_NOREADY,               //流程未就绪
	ERR_VISION_CONN,                //视觉连接错误
	ERR_VISION_GR,                  //视觉处理失败
	ERR_SYS_NOREADY,                //系统未就绪

	//公共错误
	ERR_ERROR,

    ERR_EM_MAX,                     //最大值,不是错误码
    RETURN_OK = 0,                  //正常返回
};

class Semaphore {
public:
    Semaphore (int count_ = 0)
    : count(count_) 
    {
    }
    
    inline void notify( int tid ) {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cout << "thread " << tid <<  " notify" << endl;
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait( int tid ) {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0) {
            cout << "thread " << tid << " wait" << endl;
            //wait on the mutex until notify is called
            cv.wait(lock);
            cout << "thread " << tid << " run" << endl;
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

enum EM_IO_TYPE
{//io类型
	EM_IO_START = 0,		//开始io
	EM_IO_RESET,			//复位io
	EM_IO_ESTOP,			//急停
	EM_IO_PAUSE,			//暂停
	EM_IO_STOP,				//停止操作IO
	EM_IO_USUALLY,			//常用IO
	EM_IO_BRAKE,			//刹车IO
	EM_IO_OTHER,			//其它
};


struct STM_CARD  //卡信息
{
	unsigned short cardIndex;   //卡索引
	unsigned short axisCnt;     //轴个数
	unsigned short ioCnt;       //主io位数
	unsigned short extCnt;      //扩展模块个数
	unsigned short cntType;     //连接卡连接方式
	STM_CARD()
	{
		cardIndex = 0;
		axisCnt = 0;
		ioCnt = 0;
		extCnt = 0;
		cntType = 0;
	}
};

enum EM_AXIS_STATUS_TYPE
{
	EM_AXIS_ALARM = 1,		//驱动报警
	EM_AXIS_LIMIT_P = 5,		//限位触发
	EM_AXIS_LIMIT_L = 6,		//
	EM_AXIS_ESTOP = 8,		//急停io
	EM_AXIS_ENABLE = 9,		//使能标志
	EM_AXIS_MOVING = 10,		//规划器运动标志

};

enum EM_CRDID
{//坐标ID，每个卡只能有2个
	EM_CRD_FST = 1,
	EM_CRD_SEC,
};


enum EM_AXIS_TYPE
{//轴类型
	EM_AXIS_SERVO = 0,      //伺服
	EM_AXIS_STEPPER,        //步进电机
	EM_AXIS_DDMOTOR,        //DD马达
	EM_AXIS_FLOW,           //流水线皮带，不需要回原
};

enum EM_GPIO_TYPE
{//IO信号类型
	EM_GPO = 0,     //通用输出  输出
	EM_GPI,         //通用输入
	EM_LIMIT_POS,   //正限位
	EM_LIMIT_NEG,   //负限位
	EM_ALARM,       //报警信号
	EM_HOME,        //原点信号
	EM_ENABLE,      //伺服使能  输出
	EM_CLEAR,       //清除报警  输出
	EM_ADC,         //模拟量
	EM_RDY,		    //read信号
	EM_INP		    //inp 轴到位信号
};

enum EM_LIMIT_TYPE
{//回限位方式
	EM_AXIS_LIMITN = 0,     //回负限位
	EM_AXIS_LIMITP,         //回正限位
	EM_AXIS_NOLIMIT,        //无限位
};


enum EM_HOME_TYPE
{//回原方式
	EM_HOME_NORMAL = 0,     //正常回原
	EM_HOME_SPECIAL1,       //硬件捕获 特殊方式1
	EM_HOME_SPECIAL2,       //index+home 特殊方式2
	EM_HOME_SELF,           //自定义回原
};


typedef struct _TSpeed
{//速度结构
	double vel;
	double acc;
	double dec;
} TSpeed;

/*******************************插补***************************************/

struct TMovept
{//插补参数
	int     dir;			//1 顺时针方向 -1 逆时针方向 0直线插补
	long    pos[6];			//1轴位置 圆弧插补终点X
	//long    pos2;			//2轴位置 圆弧插补中点Y
	//long    pos3;			//3轴位置 圆弧插补圆心X
	//long    pos4;			//4轴位置 圆弧插补圆心Y
	//long    pos5;			//5轴位置 圆弧插补 轴1索引
	//long    pos6;			//6轴位置 圆弧插补 轴2索引
	double  vel;			//速度
	double  acc;			//加减速度
};


struct TCool
{//坐标系数据
	Semaphore				samStop;				//停止信号量
	Semaphore				samExit;				//退出信号量
	//QFuture<int>			threadHandle;			//
	std::future<int>		threadHandle;
	unsigned short			cardID;					//卡号
	unsigned short			crdID;					//坐标系id
	unsigned short			bLock;					//是否已经锁定坐标系
	unsigned short			axisCnt;				//轴数量
	unsigned short			axis[CRD_AXIS_CNT];		//轴索引数组
	unsigned short			isMoving;				//是否在运动中，1运动中 0不在运动中
	unsigned short			curMoveIndex;			//当前已完成插补段
	std::vector<TMovept*>	vecpt;					//插补段缓冲区
};

struct Coord
{
	unsigned short  cardIndex;      //卡索引
	unsigned short  index;          //坐标系[0,1]
};

/************************************************************************/
typedef struct _AxisPos
{
	std::string	axisName;
	double	axisPos;
	_AxisPos& operator=(const _AxisPos & other)
	{
		axisName = other.axisName;
		axisPos = other.axisPos;
		return *this;
	}
}AxisPos;

typedef enum
{
	Y_LEFT = 0,
	Y_RIGHT = 1,
	Y_NONE
}PointType;

typedef struct _StationPoint
{
	string		name;
	string		desc;
	double		X;
	double		Y;
	double		Z;
	double		U;
	double		V;

	_StationPoint()
		:name(""), desc(""), X(0.0), Y(0.0), Z(0.0), U(0.0), V(0.0)
	{

	}

}StationPoint;

typedef struct _IOInfo
{
	string name;
	int		cardType;		//0=运动控制卡本身，1=IOC0640,3=Can总线
	int		cardIndex;		//卡号
	int		cardNode;		//Can节点，运动控制卡下面的节点号
	int		ioIndex;		//io索引
	int		sense;			//1=高电平有效，0-低电平有效
	int		group;			//分组

	_IOInfo()
	{
		name = "";
		cardType = 0;
		cardIndex = 0;
		cardNode = 0;
		ioIndex = 0;
		sense = 1;
		group = 0;
	}

	_IOInfo& operator=(const _IOInfo& other)
	{
		name = other.name;
		cardType = other.cardType;
		cardIndex = other.cardIndex;
		cardNode = other.cardNode;
		ioIndex = other.ioIndex;
		sense = other.sense;
		group = other.group;
		return *this;
	}

}IOInfo, *IOInfoPtr;


typedef struct _AxisParam
{//轴参数
	int			cardIndex;				    //卡索引
	int			axisIndex;				    //轴索引
	string		axisName;				    //轴名称
	int			motorType;				    //参考 EM_AXIS_TYPE 0-伺服, 1步进, 2 dd马达
	int			homeSense;					//原点限位有效电平
	int			limitMode;					//限位方式
	int			limitSense;					//正限位有效电平
	int			almMode;					//报警启用/禁止模式
	int			almSense;					//报警有效电平

	double		stepvalue;					//1mm对应多少脉冲
	double		limitN;						//负软限位脉冲
	double		limitP;						//正软限位脉冲
	double		vel;						//默认工作速度  这里所有速度都是 脉冲/毫秒
	double		accTime;					//加速时间
	double		decTime;					//减速时间

	int			homeDir;					//回限位方式，EM_LIMIT_TYPE 0 负限位 1 回正限位 2 无限位
	int			homeType;				    //回原方式 参考 EM_HOME_TYPE 0 正常 1 硬件捕获 2 index 3 自定义 dd马达类型时表示 回原操作IO 8:null,8:card,8:ioindex,8:extmodle
	double		homeVel;					//回原速度 速度加速度 都需要 / 1000
	double		homeAccTime;				//加速时间
	double		homeDecTime;				//减速时间
	double		sreachhomePos;				//回原搜索的距离 脉冲
	double		inHomeOffset;				//原点偏移量 回原前，若处于原点位置，则偏移
	double		afterhomeOffset;			//回原后偏移量

	//回零时，轴向限位移动的速度
	double      homeVelToLimit;
	double      homeAccToLimit;
	double      homeDecToLimit;

	bool		enable;



	_AxisParam()
	{
		cardIndex = 0;
		axisIndex = 0;
		axisName = "";
		motorType = 0;
		homeSense = 0;
		limitMode = 0;
		limitSense = 0;
		almMode = 0;
		almSense = 0;

		stepvalue = 0;
		limitN = 0;
		limitP = 0;
		vel = 0;
		accTime = 0;
		decTime = 0;

		homeDir = 0;
		homeType = 0;
		homeVel = 0;
		homeAccTime = 0;
		homeDecTime = 0;
		sreachhomePos = 0;
		inHomeOffset = 0;
		afterhomeOffset = 0;
		homeVelToLimit = 0;
		homeAccToLimit = 0;
		homeDecToLimit = 0;
		enable = true;

	}

	_AxisParam& operator = (const _AxisParam& other)
	{
		cardIndex = other.cardIndex;
		axisIndex = other.axisIndex;
		axisName = other.axisName;
		motorType = other.motorType;
		homeSense = other.homeSense;
		limitMode = other.limitMode;
		limitSense = other.limitSense;
		almMode = other.almMode;
		almSense = other.almSense;

		stepvalue = other.stepvalue;
		limitN = other.limitN;
		limitP = other.limitP;
		vel = other.vel;
		accTime = other.accTime;
		decTime = other.decTime;

		homeDir = other.homeDir;
		homeType = other.homeType;
		homeVel = other.homeVel;
		homeAccTime = other.homeAccTime;
		homeDecTime = other.homeDecTime;
		sreachhomePos = other.sreachhomePos;
		inHomeOffset = other.inHomeOffset;
		afterhomeOffset = other.afterhomeOffset;
		homeVelToLimit = other.homeVelToLimit;
		homeAccToLimit = other.homeAccToLimit;
		homeDecToLimit = other.homeDecToLimit;
		enable = other.enable;

		return *this;
	}

} AxisParam, *AxisParamPtr;


class AxisPrivate
{
public:
	bool bInit;				//是否初始化
	bool bExitFlag;			//退出标志
	bool bHighHome;			//是否可以高速回原
	int  iHomeResult;		//回原结果
	string strConfiPath;
	AxisParam para;			//轴参数

	AxisPrivate()
		:bInit(false), bExitFlag(false), bHighHome(false), iHomeResult(-1)
	{

	}
};

class Axis;
class CardPrivate
{
	friend class Card;
	friend class Card_Smc606;


	EM_ERR_CODE		errorCode;
	unsigned short	cardID;			//卡ID
	unsigned short	axisCnt;			//轴数量

	mutex			mutex;			//临界区
	TCool			stCool[COOL_CNT];	//坐标系
	Axis**		pAxis;			//轴数组类指针

	CardPrivate()
	{
		errorCode = ERR_ERROR;
		cardID = 0;
		axisCnt = 0;
		pAxis = nullptr;
	}
};



typedef struct _ExtIOCard
{
	int		extID;		//扩展卡号
	int		address;	//地址
	bool		bInit;

	_ExtIOCard()
	{
		extID = 0;
		address = 0x00000;
		bInit = false;
	}

	_ExtIOCard& operator = (const _ExtIOCard& other)
	{
		extID = other.extID;
		address = other.address;
		bInit = other.bInit;

		return *this;
	}
}ExtIOCard, *ExtIOCardPtr;

class Card;

typedef struct _CardInfo
{
	std::vector<AxisParam>	vecAxisParam;
	bool                    bInit;

	_CardInfo()
	{
		bInit = false;
	}

	_CardInfo& operator = (const _CardInfo& other)
	{
		vecAxisParam = other.vecAxisParam;
		bInit = other.bInit;
		return *this;
	}

}CardInfo, *CardInfoPtr;



