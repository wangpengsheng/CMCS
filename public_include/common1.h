#pragma once
#include "stdafx.h"
#include <vector>
#include <bitset>
#include <string>
#include <mutex>
#include <future>
#include <iostream>
#include <map>
//������˶����

using namespace std;

#define CFGDIR(X) "D:/Auto_Sloder_Welding/config/"##X

#define INVALID_AXIS		-1		//��Ч��
#define MOTOR_MAX_NAME		36		//����
#define MOTOR_MAX_AXIS		6       //�������᣿
#define COOL_CNT			2		//ÿ�ſ�ֻ����2������ϵ
#define CRD_AXIS_CNT		4		//ÿ������ϵ���4����
#define SAME_PULSE_OFFSET	5		//�����ٸ�������Ϊλ��û�б仯
#define MAX_AXISCNT			8


//�������������ź��Ƿ�ȡ��
#define DMC_CFG			"dmc_cfg"
#define POSITIVE_SENCE	"positive_sence"        //����λ
#define NEGATIVE_SENCE	"negative_sence"        //����λ
#define ALARM_SENCE		"alarm_sence"           //�����ź�
#define HOME_SENCE		"home_sence"            //ԭ���ź�
#define GPI_SENCE		"gpi_sence"             //ͨ������
#define GPIEXT_SENCE	"gpiext_sence"          //��չ��ͨ������
#define ENABLE_SENCE	"enable_sence"          //�ŷ�ʹ��
#define CLEAR_SENCE		"clear_sence"           //�������
#define GPO_SENCE		"gpo_sence"             //ͨ�����
#define GPOEXT_SENCE	"gpoext_sence"          //��չ��ͨ�����


//�������
enum EM_ERR_CODE
{
    RETURN_OK = 0,                  //��������
};

//class Semaphore {
//public:
//    Semaphore (int count_ = 0)
//    : count(count_) 
//    {
//    }
//    
//    inline void notify( int tid ) {
//        std::unique_lock<std::mutex> lock(mtx);
//        count++;
//        cout << "thread " << tid <<  " notify" << endl;
//        //notify the waiting thread
//        cv.notify_one();
//    }
//    inline void wait( int tid ) {
//        std::unique_lock<std::mutex> lock(mtx);
//        while(count == 0) {
//            cout << "thread " << tid << " wait" << endl;
//            //wait on the mutex until notify is called
//            cv.wait(lock);
//            cout << "thread " << tid << " run" << endl;
//        }
//        count--;
//    }
//private:
//    std::mutex mtx;
//    std::condition_variable cv;
//    int count;
//};

//io����
enum EM_IO_TYPE
{
	EM_IO_START = 0,		//��ʼio
	EM_IO_RESET,			//��λio
	EM_IO_ESTOP,			//��ͣ
	EM_IO_PAUSE,			//��ͣ
	EM_IO_STOP,				//ֹͣ����IO
	EM_IO_USUALLY,			//����IO
	EM_IO_BRAKE,			//ɲ��IO
	EM_IO_OTHER,			//����
};

//����Ϣ
struct STM_CARD  
{
	unsigned short cardIndex;   //������
	unsigned short axisCnt;     //�����
	unsigned short ioCnt;       //��ioλ��
	unsigned short extCnt;      //��չģ�����
	unsigned short cntType;     //���ӿ����ӷ�ʽ
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
	EM_AXIS_ALARM = 1,			//��������
	EM_AXIS_LIMIT_P = 5,		//��λ����
	EM_AXIS_LIMIT_L = 6,		//��λ����
	EM_AXIS_ESTOP = 8,			//��ͣio
	EM_AXIS_ENABLE = 9,			//ʹ�ܱ�־
	EM_AXIS_MOVING = 10,		//�滮���˶���־
};
//����ID��ÿ����ֻ����2��
enum EM_CRDID
{
	EM_CRD_FST = 1,
	EM_CRD_SEC,
};

//������
enum EM_AXIS_TYPE
{
	EM_AXIS_SERVO = 0,      //�ŷ�
	EM_AXIS_STEPPER,        //�������
	EM_AXIS_DDMOTOR,        //DD���
	EM_AXIS_FLOW,           //��ˮ��Ƥ��������Ҫ��ԭ
};
//IO�ź�����
enum EM_GPIO_TYPE
{
	EM_GPO = 0,     //ͨ�����  ���
	EM_GPI,         //ͨ������
	EM_LIMIT_POS,   //����λ
	EM_LIMIT_NEG,   //����λ
	EM_ALARM,       //�����ź�
	EM_HOME,        //ԭ���ź�
	EM_ENABLE,      //�ŷ�ʹ��  ���
	EM_CLEAR,       //�������  ���
	EM_ADC,         //ģ����
	EM_RDY,		    //read�ź�
	EM_INP		    //inp �ᵽλ�ź�
};
//����λ��ʽ
enum EM_LIMIT_TYPE
{
	EM_AXIS_LIMITN = 0,     //�ظ���λ
	EM_AXIS_LIMITP,         //������λ
	EM_AXIS_NOLIMIT,        //����λ
};

//��ԭ��ʽ
enum EM_HOME_TYPE
{
	EM_HOME_NORMAL = 0,     //������ԭ
	EM_HOME_SPECIAL1,       //Ӳ������ ���ⷽʽ1
	EM_HOME_SPECIAL2,       //index+home ���ⷽʽ2
	EM_HOME_SELF,           //�Զ����ԭ
};

//�ٶȽṹ
typedef struct _TSpeed
{
	double vel;
	double acc;
	double dec;
} TSpeed;

/*******************************�岹***************************************/

struct TMovept
{//�岹����
	int     dir;			//1 ˳ʱ�뷽�� -1 ��ʱ�뷽�� 0ֱ�߲岹
	long    pos[6];			//1��λ�� Բ���岹�յ�X
	//long    pos2;			//2��λ�� Բ���岹�е�Y
	//long    pos3;			//3��λ�� Բ���岹Բ��X
	//long    pos4;			//4��λ�� Բ���岹Բ��Y
	//long    pos5;			//5��λ�� Բ���岹 ��1����
	//long    pos6;			//6��λ�� Բ���岹 ��2����
	double  vel;			//�ٶ�
	double  acc;			//�Ӽ��ٶ�
};


//struct TCool
//{//����ϵ����
//	Semaphore				samStop;				//ֹͣ�ź���
//	Semaphore				samExit;				//�˳��ź���
//	//QFuture<int>			threadHandle;			//
//	std::future<int>		threadHandle;
//	unsigned short			cardID;					//����
//	unsigned short			crdID;					//����ϵid
//	unsigned short			bLock;					//�Ƿ��Ѿ���������ϵ
//	unsigned short			axisCnt;				//������
//	unsigned short			axis[CRD_AXIS_CNT];		//����������
//	unsigned short			isMoving;				//�Ƿ����˶��У�1�˶��� 0�����˶���
//	unsigned short			curMoveIndex;			//��ǰ����ɲ岹��
//	std::vector<TMovept*>	vecpt;					//�岹�λ�����
//};

struct Coord
{
	unsigned short  cardIndex;      //������
	unsigned short  index;          //����ϵ[0,1]
};

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

//IO����
//typedef struct _IOInfo
//{
//	string name;
//	int		cardType;		//0=�˶����ƿ�����1=IOC0640,3=Can����
//	int		cardIndex;		//����
//	int		cardNode;		//Can�ڵ㣬�˶����ƿ�����Ľڵ��
//	int		ioIndex;		//io����
//	int		sense;			//1=�ߵ�ƽ��Ч��0-�͵�ƽ��Ч
//	int		group;			//����
//
//	_IOInfo()
//	{
//		name = "";
//		cardType = 0;
//		cardIndex = 0;
//		cardNode = 0;
//		ioIndex = 0;
//		sense = 1;
//		group = 0;
//	}
//
//	_IOInfo& operator=(const _IOInfo& other)
//	{
//		name = other.name;
//		cardType = other.cardType;
//		cardIndex = other.cardIndex;
//		cardNode = other.cardNode;
//		ioIndex = other.ioIndex;
//		sense = other.sense;
//		group = other.group;
//		return *this;
//	}
//
//}IOInfo, *IOInfoPtr;





//�����
typedef struct _AxisParam
{
	int			cardIndex;				    //������
	int			axisIndex;				    //������
	int			motorType;				    //�ο� EM_AXIS_TYPE 0-�ŷ�, 1����, 2 dd���
	string		axisName;				    //������
	string      axisDes;					//������
	
	double		vel;						//Ĭ�Ϲ����ٶ�  
	double		acc;						//����
	double		dec;						//����
	double		homeVel;					//��ԭ�ٶ� �ٶȼ��ٶ� ����Ҫ / 1000
	double		homeAcc;					//����
	double		homeDec;					//����
	double      homeVelToLimit;				//����ʱ��������λ�ƶ����ٶ�
	double      homeAccToLimit;				//����ʱ��������λ�ƶ��ļ��ٶ�
	double      homeDecToLimit;				//����ʱ��������λ�ƶ��ļ��ٶ�

	double		limitN;						//������λ����
	double		limitP;						//������λ����
	int			homeDir;					//����λ��ʽ��EM_LIMIT_TYPE 0 ����λ 1 ������λ 2 ����λ
	int			homeType;				    //��ԭ��ʽ �ο� EM_HOME_TYPE 0 ���� 1 Ӳ������ 2 index 3 �Զ��� dd�������ʱ��ʾ ��ԭ����IO 8:null,8:card,8:ioindex,8:extmodle
	double		searchHomePos;				//��ԭ�����ľ��� ����
	double		inHomePosOffset;			//ԭ��ƫ���� ��ԭǰ��������ԭ��λ�ã���ƫ��
	double		afterHomePosOffset;			//��ԭ��ƫ����
	int			pulseInMode;				//��������
	int			MMPerround;					//���ֱ� MMGearRatio
	int			PulseOneMM;					//1mm��Ӧ��������
	int			pulseperround;				//һȦ��������
	int			limitPinLogic;				//��λ��Ч��ƽ
	bool		enableSLimit;				//�Ƿ���������λ
	bool		enableAlm;					//��������/��ֹģʽ
	int			almPinLogic;				//���������źŵ���Ч��ƽ����
	int			pulseOutMode;				//����������ͣ�0:��AB�� 1:AB��1�� 2:AB��2�� 3:AB��4��)
	int			homePinLogic;				//����ԭ���źŵ���Ч��ƽ����

	bool		enable;
	_AxisParam()
	{
		cardIndex = 0;
		axisIndex = 0;
		motorType = 0;
		axisName = "";
		axisDes = "";

		vel = 0;
		acc = 0;
		dec = 0;
		homeVel = 0;
		homeAcc = 0;
		homeDec = 0;		
		homeVelToLimit = 0;
		homeAccToLimit = 0;
		homeDecToLimit = 0;

		limitN = 0;
		limitP = 0;
		homeDir = 0;
		homeType = 0;
		searchHomePos = 0;
		inHomePosOffset = 0;
		afterHomePosOffset = 0;
		pulseInMode = 0;
		MMPerround = 0;
		PulseOneMM = 0;
		pulseperround = 0;
		limitPinLogic = 0;
		enableSLimit = false;
		enableAlm = false;
		almPinLogic = 0;
		pulseOutMode = 0;
		homePinLogic = 0;

		enable = false;
	}

	_AxisParam& operator = (const _AxisParam& other)
	{
		cardIndex = other.cardIndex;
		axisIndex = other.axisIndex;
		motorType = other.motorType;
		axisName = other.axisName;
		axisDes = other.axisDes;

		vel = other.vel;
		acc = other.acc;
		dec = other.dec;
		homeVel = other.homeVel;
		homeAcc = other.homeAcc;
		homeDec = other.homeDec;
		homeVelToLimit = other.homeVelToLimit;
		homeAccToLimit = other.homeAccToLimit;
		homeDecToLimit = other.homeDecToLimit;

		limitN = other.limitN;
		limitP = other.limitP;
		homeDir = other.homeDir;
		homeType = other.homeType;	
		searchHomePos = other.searchHomePos;
		inHomePosOffset = other.inHomePosOffset;
		afterHomePosOffset = other.afterHomePosOffset;
		pulseInMode = other.pulseInMode;
		MMPerround = other.MMPerround;
		PulseOneMM = other.PulseOneMM;
		pulseperround = other.pulseperround;
		limitPinLogic = other.limitPinLogic;
		enableSLimit = other.enableSLimit;
		enableAlm = other.enableAlm;
		almPinLogic = other.almPinLogic;
		pulseOutMode = other.pulseOutMode;
		homePinLogic = other.homePinLogic;

		enable = other.enable;

		return *this;
	}

} AxisParam, *AxisParamPtr;

typedef struct _ExtIOCard
{
	int		extID;		//��չ����
	int		address;	//��ַ
	bool	bInit;		//�Ƿ��ʼ��

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

typedef struct _CardInfo
{
	std::string cardName;
	int cardIndex;
	std::vector<AxisParam>	vecAxisParam;
	bool bInit;

	_CardInfo()
	{
		bInit = false;
	}

	_CardInfo& operator = (const _CardInfo& other)
	{
		cardName = other.cardName;
		cardIndex = other.cardIndex;
		vecAxisParam = other.vecAxisParam;
		bInit = other.bInit;
		return *this;
	}

}CardInfo, *CardInfoPtr;

enum CardType
{
	MOTION,
	IO,
	CAN_IO,
	RS232,
	NONE
};


typedef struct newCardInfo
{
	CardType card_type;
	std::string card_name;
	int card_id;
	int card_port;
	string card_version;
}NewCardInfo;


struct VisionPara
{
	unsigned short light1;

	unsigned short light2;

	unsigned short light3;

	unsigned short light4;

	unsigned int exposure;

	VisionPara( )
		: light1(0), light2(0), light3(0), light4(0), exposure(0)
	{
	}
};


struct VisionConfig
{
	string cameraID;

	double pixEqui;

	std::map<string, VisionPara> mapVision;

	VisionConfig( )
	{
		cameraID = "";
		pixEqui = 0.0;
	}
};

