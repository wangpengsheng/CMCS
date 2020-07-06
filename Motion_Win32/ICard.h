#pragma once
#include "common1.h"

#ifndef USHORT
#define USHORT
typedef unsigned short ushort;
#endif

class ICard
{
public:
	ICard();
	ICard(NewCardInfo card_info){};
	virtual ~ICard();


	//≥…‘±
public:
	NewCardInfo m_config;
	bool m_bExtendCard;
	string m_card_version;
	ushort m_max_io;
	bool m_connected;

	//virtual

public:

};

