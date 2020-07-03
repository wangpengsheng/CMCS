#include <iostream>
#include "MotionFactory.h"
#include "Motion_common.h"
#include "pugixml.hpp"

int main(int argc, char* argv[])
{
	auto motion_factory = MOTION_FACTORY;
	const auto axi_config = CFGDIR("config/axisconfig.xml");
	cout << axi_config << endl;
	pugi::xml_document xdoc;
	pugi::xml_parse_result result = xdoc.load_file(axi_config);
	if(!result)
	{
		AfxMessageBox(_T("加载卡参数文件失败"));
		return 0;
	}
	
	pugi::xml_node rootNode = xdoc.document_element();
	if(rootNode.empty())
		return 0;
	cout << rootNode.name() << endl;
	return 0;
}
