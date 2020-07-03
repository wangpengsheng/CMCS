#include "stdafx.h"
#include "Config.h"
#include <pugixml.hpp>
#include "../public_include/common1.h"

std::unique_ptr<CConfig> CConfig::m_pInstance = nullptr;
std::mutex CConfig::m_pInstance_lock;
std::mutex CConfig::m_rwMutex;
CConfig::CConfig()
{
	init();
}

void CConfig::init()
{
	m_strConfigPath = CFGDIR("axisconfig2.xml");
	load_cards(m_strConfigPath.c_str());
}

bool CConfig::load_cards(const char* xml_name)
{
	pugi::xml_document doc;
	const auto result = doc.load_file(xml_name);
	if(!result) return false;
	
	const auto rootNode = doc.document_element();
	if(rootNode.empty()) return false;

	m_vecCardInfo.clear();
	for(auto node = rootNode.first_child();node;node = node.next_sibling())
	{
		CardInfo card_info;
		card_info.cardName = node.attribute("name").value();
		card_info.cardIndex = node.attribute("cardIndex").as_int();
		for (auto node_child = node.child("axis");node_child;node_child=node_child.next_sibling())
		{
			AxisParam axis_param;
			axis_param.axisIndex = node_child.attribute("index").as_int();
			axis_param.motorType = node_child.attribute("motorType").as_int();
			axis_param.axisName = node_child.attribute("axisName").value();
			axis_param.axisDes = node_child.attribute("axisDes").value();

			axis_param.vel = node_child.attribute("vel").as_double();
			axis_param.acc = node_child.attribute("acc").as_double();
			axis_param.dec = node_child.attribute("dec").as_double();
			axis_param.homeVel = node_child.attribute("homeVel").as_double();
			axis_param.homeAcc = node_child.attribute("homeAcc").as_double();
			axis_param.homeDec = node_child.attribute("homeDec").as_double();
			axis_param.homeVelToLimit = node_child.attribute("homeVelToLimit").as_double();
			axis_param.homeAccToLimit = node_child.attribute("homeAccToLimit").as_double();
			axis_param.homeDecToLimit = node_child.attribute("homeDecToLimit").as_double();

			axis_param.limitN = node_child.attribute("NL").as_double();
			axis_param.limitP = node_child.attribute("PL").as_double();
			axis_param.homeDir = node_child.attribute("homeDir").as_int();
			axis_param.homeType = node_child.attribute("homeType").as_int();
			axis_param.searchHomePos = node_child.attribute("searchHomePos").as_double();
			axis_param.inHomePosOffset = node_child.attribute("inHomePosOffset").as_double();
			axis_param.afterHomePosOffset = node_child.attribute("afterHomePosOffset").as_double();
			axis_param.pulseInMode = node_child.attribute("pulseInMode").as_int();
			axis_param.MMPerround = node_child.attribute("MMGearRatio").as_int();
			axis_param.PulseOneMM = node_child.attribute("PulseOneMM").as_int();
			axis_param.pulseperround = node_child.attribute("pulseOneRound").as_int();
			axis_param.limitPinLogic = node_child.attribute("limitPinLogic").as_int();
			axis_param.enableSLimit = node_child.attribute("enableSLimit").as_bool();
			axis_param.enableAlm = node_child.attribute("enableAlm").as_bool();
			axis_param.almPinLogic = node_child.attribute("almPinLogic").as_int();
			axis_param.pulseOutMode = node_child.attribute("pulseOutMode").as_int();
			axis_param.homePinLogic = node_child.attribute("homePinLogic").as_int();

			card_info.vecAxisParam.push_back(axis_param);
		}
		card_info.bInit = false;
		m_vecCardInfo.push_back(card_info);
	}
	return true;
}


CConfig& CConfig::get_instance()
{
	if (m_pInstance == nullptr)
	{
		std::lock_guard<mutex> lock(m_pInstance_lock);
		if (m_pInstance == nullptr)
		{
			m_pInstance.reset(new CConfig);
		}
	}
	return *m_pInstance;
}

void CConfig::destory_instance()
{
	if (m_pInstance != nullptr)
	{
		m_pInstance = nullptr;
	}
}

CConfig::~CConfig()
{
}
