#include "StdAfx.h"
#include <io.h>
#include <direct.h>
#include <cstdarg>
#include <sstream>
#include "logger.h"

std::string logger::get_current_date( )
{
	SYSTEMTIME _time;
	GetLocalTime(&_time);
	char buffer[16] = {0};
	sprintf_s(buffer, "%02d-%02d-%02d", _time.wYear, _time.wMonth, _time.wDay);
	return buffer;
}

std::string logger::get_current_time( )
{
	SYSTEMTIME _time;
	GetLocalTime(&_time);
	char buffer[16] = {0};
	sprintf_s(buffer, " %02d:%02d:%02d.%03d", _time.wHour, _time.wMinute, _time.wSecond, _time.wMilliseconds); //空格必须加
	return buffer;
}

bool logger::create_dir(const char* _path)
{
	char buffer[256] = {0};
	const int n_len = strlen(_path);
	strncpy_s(buffer, _path, n_len + 1);
	for(auto i = 0;i < n_len;++i)
	{
		if(buffer[i] == '/' || buffer[i] == '\\')
		{
			char buffer_path[256] = {0};
			strncpy_s(buffer_path, buffer, i);
			if(_access(buffer_path, 0) != 0)
			{
				if(_mkdir(buffer_path) != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void logger::init(const std::string& path, const std::string& prefix)
{
	std::string rpath;
	rpath = path;

	const auto value_1 = path[path.length() - 1];
	if(value_1 != '/' && value_1 != '\\')
	{
		rpath.append("/");
	}
	create_dir(rpath.c_str());
	rpath.append(prefix);
	rpath.append(get_current_date());
	rpath.append(".csv");
	set_filename(rpath);
}

void logger::set_filename(const std::string& _filename)
{
	m_file_name = _filename;
	if(_access(m_file_name.c_str(), 0))
		m_title_exist = false;
	m_file_stream.open(m_file_name.c_str(), std::ios_base::out | std::ios_base::app);
}

void logger::log(const char* format, ...)
{
	std::string msg;
	{				//加块防止死锁-不能删除
		std::unique_lock<std::mutex> lock(m_lock);
		va_list parg;
		static char buffer[4096] = { 0 };
		va_start(parg, format);
		vsnprintf_s(buffer, 4096 - 2, format, parg);
		va_end(parg);
		msg = buffer;
	}
	log(msg);
}

void logger::log(const std::string& _message)
{
	std::unique_lock<std::mutex> lock(m_lock);
	std::stringstream stream;
	if(!m_title_exist)
	{
		stream << m_title << std::endl;
		m_title_exist = true;
	}
	stream << get_current_time().c_str() << "," << _message.c_str() << "\n";
	if(m_console_show)
	{
		fprintf_s(stdout, "%s", static_cast<const char*>(stream.str().c_str()));
	}
	//if((m_file_save && m_file_stream.is_open()))
	//{
	//	m_file_stream << stream.str();
	//	++m_file_rows;
	//	m_file_stream.flush(); // 即使在异常中也可以写入到文件，性能有所损失,但可接受
	//}
	if(m_file_save)
	{
		if(m_mode)
		{
			m_file_stream.open(m_file_name.c_str(),std::ios_base::out | std::ios_base::app);
		}
		if(m_file_stream.is_open())
		{
			m_file_stream << stream.str();
			++m_file_rows;
			m_file_stream.flush();
		}
		if(m_mode)
		{
			m_file_stream.close();
		}
	}
}

logger::logger( ): m_console_show(false), m_file_save(true), m_title(" "), m_title_exist(true), m_file_rows(0),m_mode(false)
{
}

logger::~logger( )
{
	file_close();
}

void logger::file_close( )
{
	if(m_file_stream.is_open())
	{
		m_file_stream.flush();
		m_file_stream.close();
	}
}
