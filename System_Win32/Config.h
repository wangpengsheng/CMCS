#pragma once
#include "../public_include/common1.h"
#include <mutex>
#include <vector>


#define SYSCCONFIG CConfig::get_instance()

class _declspec(dllexport) CConfig
{
public:
	static CConfig& get_instance();
	static void destory_instance();
	virtual ~CConfig();
	
private:

	void init();
	bool load_cards(const char* xml_name);

	static std::unique_ptr<CConfig> m_pInstance;
	static std::mutex m_pInstance_lock;
	static std::mutex m_rwMutex;
	std::string m_strConfigPath;


	std::vector<CardInfo>	m_vecCardInfo;
	std::map<string,CardInfo> m_CardsMap;
	CConfig();
};

