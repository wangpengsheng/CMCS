#include "MotionFactory.h"


std::unique_ptr<CMotionFactory> CMotionFactory::m_instance = nullptr;
std::mutex CMotionFactory::m_instance_lock;
CMotionFactory::~CMotionFactory()
{
	if (m_instance != nullptr)
	{
		m_instance = nullptr;
		cout << "Factory uninstall ..." << endl;
	}
}

CMotionFactory::CMotionFactory()
{
	cout << "Factory install ..." << endl;
}
