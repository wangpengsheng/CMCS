#pragma once
#include "common1.h"

#ifndef USHORT
#define USHORT
typedef unsigned short ushort;
#endif

class IOBase
{
public:
	IOBase(): m_bExtendCard(false), m_max_io(32), m_connected(false)
	{
	};
	virtual ~IOBase()
	{
		cout << "eixt ICard interface" << endl;
	}

	//³ÉÔ±
public:
	bool m_bExtendCard;
	string m_card_version;
	ushort m_max_io;
	bool m_connected;

	//virtual
	virtual	bool Connect() = 0;

	virtual	bool Disconnect() = 0;

	virtual	void Update() = 0;

	virtual	void Stop() = 0;

	virtual	void LoadConfig(string configFile) = 0;

	
public:

};


