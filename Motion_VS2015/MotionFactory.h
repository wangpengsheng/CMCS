#pragma once
#include "Motion_common.h"

#define MOTION_FACTORY CMotionFactory::get_instance()

class CMotionFactory
{
public:
	
	static CMotionFactory &get_instance()
	{
		if (m_instance == nullptr)
		{
			std::lock_guard<mutex> lock(m_instance_lock);
			if (m_instance == nullptr)
			{
				m_instance.reset(new CMotionFactory());
			}
		}
		return *m_instance;
	}
	
	virtual ~CMotionFactory();

private:
	static std::mutex m_instance_lock;
	static std::unique_ptr<CMotionFactory> m_instance;
	CMotionFactory();
};

