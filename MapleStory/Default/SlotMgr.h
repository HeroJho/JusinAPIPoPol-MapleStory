#pragma once

#include "Include.h"
#include "SlotTemp.h"

class CSlotMgr
{
private:
	CSlotMgr();
	~CSlotMgr();

#pragma region Ins
public:
	static		CSlotMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSlotMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSlotMgr* m_pInstance;
#pragma endregion

public:
	CSlotTemp** GetSlotInfo() { return m_aSlotInfo; }

public:
	void SetSlotInfo(ITEM _eInfo, int _iIndex);
	void ChangeSlot(int _iLeftId, int _iRightId);

public:
	void UseA();
	void UseS();
	void UseD();
	void UseZ();
	void UseX();
	void UseC();
	void Use1();
	void Use2();
	void Use3();
	void Use4();
	void Use5();
	void Use6();

public:
	void		Initialize(void);
	int			Update(void);
	void		Release(void);


private:
	CSlotTemp* m_aSlotInfo[12];


};

