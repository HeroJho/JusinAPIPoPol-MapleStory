#pragma once

#include "Include.h"

class CSlotTemp
{
public:
	CSlotTemp();
	virtual ~CSlotTemp();

public:
	void SetInfo(ITEM _sInfo) { m_sInfo = _sInfo; }
	ITEM& GetInfo() { return m_sInfo; }

private:
	ITEM m_sInfo;

};

