#pragma once

#include "Item.h"
#include "Item_UI.h"

class CInvenMgr
{
private:
	CInvenMgr();
	~CInvenMgr();

public:
	void		Initialize(void);
	void		Release(void);

public:
	int Get_Money() { return m_iMoney; }
	list<CItem_UI*>& Get_InvenList() { return m_lList; }

public:
	void Add_Item(ITEM _pItem);
	void Use_Item(int _iInvenID);
	
	void Add_Money(int _iMoney) { m_iMoney += _iMoney; }
	bool Des_Money(int _iMoney);

public:
	ITEM MakeItemInfo(CItem* _pItem);

private:
	list<CItem_UI*> m_lList;
	int m_iMoney;

	int m_iMaxCount;
	int m_iInvenID;

#pragma region Ins
public:
	static		CInvenMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CInvenMgr;
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
	static CInvenMgr* m_pInstance;
#pragma endregion
};

