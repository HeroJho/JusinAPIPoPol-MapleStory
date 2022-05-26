#pragma once

#include "Include.h"

class CItem_Info
{
public:
	CItem_Info();
	virtual ~CItem_Info();

public:
	void SetInfo(ITEM _sInfo) { m_sInfo = _sInfo; };
	ITEM& GetInfo() { return m_sInfo; }
	void Use_Item();


private:
	ITEM m_sInfo;

};

