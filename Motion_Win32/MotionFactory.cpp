#include "stdafx.h"
#include "MotionFactory.h"
#include <iostream>


std::unique_ptr<CMotionFactory> CMotionFactory::m_instance = nullptr;
std::mutex CMotionFactory::m_instance_lock;

CMotionFactory& CMotionFactory::get_instance()
{
	if (m_instance == nullptr)
	{
		std::lock_guard<std::mutex> lock(m_instance_lock);
		if (m_instance == nullptr)
		{
			m_instance.reset(new CMotionFactory());
		}
	}
	return *m_instance;
}

CMotionFactory::~CMotionFactory()
{
	if (m_instance != nullptr)
	{
		m_instance = nullptr;
		cout << "Factory uninstall ..." << endl;
	}
}

bool CMotionFactory::LoadCardInfo()
{

	return true;
}

CMotionFactory::CMotionFactory()
{
	cout << "Factory install ..." << endl;
}
