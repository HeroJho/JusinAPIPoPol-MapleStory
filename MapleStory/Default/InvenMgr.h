#pragma once

#include "Item.h"
#include "Item_Info.h"

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
	list<CItem_Info*>& Get_InvenList() { return m_lList; }
	list<CItem_Info*>& Get_EquipList() { return m_lEquipList; }

public:
	void Add_Item(ITEM _pItem);
	void Use_Item(int _iInvenID);
	ITEM FInd_Info(int _iInvenID);

	ITEM FInd_EquipInfo(int _iInvenID);
	void Remove_EquipInfo(int _iInvenID);

	void Add_Money(int _iMoney) { m_iMoney += _iMoney; }
	bool Des_Money(int _iMoney);

	int GetEmptyIndex();
	int GetEmptyEquipIndex();

public:
	ITEM MakeItemInfo(CItem* _pItem);
	void ChangeSlot(int _iLeftId, int _iRightId);
	void ChangeEquipSlot(int _iLeftId, int _iRightId);

private:
	list<CItem_Info*> m_lList;
	list<CItem_Info*> m_lEquipList;
	int m_iMoney;

	int m_iMaxCount;


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