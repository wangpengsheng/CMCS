#pragma once
#ifndef   _LOGGER_H_
#define   _LOGGER_H_

#include <fstream>
#include <mutex>

class _declspec(dllexport) logger
{
public:
	logger( );

	~logger( );

	void init(const std::string& path, const std::string& prefix);

	void set_filename(const std::string& filename);

	void set_console_show(bool show)
	{
		this->m_console_show = show;
	}

	void set_file_save(bool save)
	{
		this->m_file_save = save;
	}

	void set_mode(bool mode)
	{
		this->m_mode = mode;
	}

	void log(const char* format, ...);

	void log(const std::string& _message);

	unsigned long get_rows( )
	{
		return m_file_rows;
	}

	void set_title(const std::string& _title)
	{
		this->m_title = _title;
	}

private:
	std::mutex m_lock;

	std::string m_path;

	std::string m_file_name;

	std::string m_prefix;

	std::ofstream m_file_stream;

	bool m_console_show;

	bool m_file_save;

	std::string m_title;

	bool m_title_exist;

	bool m_mode;	//TRUE 每次都需要打开和关闭 FALSE 打开关闭一次

	unsigned long m_file_rows;

	static std::string get_current_date( );

	static std::string get_current_time( );

	static bool create_dir(const char* _path);

	void file_close( );
};

#endif
