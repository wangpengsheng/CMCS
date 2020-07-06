#pragma once
#include <mutex>

#define MOTION_FACTORY CMotionFactory::get_instance()
using namespace std;
class _declspec(dllexport) CMotionFactory
{
public:
	static CMotionFactory& get_instance();
	virtual ~CMotionFactory();
	bool LoadCardInfo();
private:
	static std::mutex m_instance_lock;
	static std::unique_ptr<CMotionFactory> m_instance;
	CMotionFactory();
};

