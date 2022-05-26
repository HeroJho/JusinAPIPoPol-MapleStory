#include "stdafx.h"
#include "InvenMgr.h"
#include "Item_UI.h"


CInvenMgr* CInvenMgr::m_pInstance = nullptr;
CInvenMgr::CInvenMgr()
	: m_iMaxCount(24)
	, m_iMoney(0)
{
}

CInvenMgr::~CInvenMgr()
{
	Release();
}

void CInvenMgr::Initialize(void)
{

}

void CInvenMgr::Release(void)
{
	for (auto& sInfo : m_lList)
		Safe_Delete(sInfo);
	m_lList.clear();

	for (auto& sInfo : m_lEquipList)
		Safe_Delete(sInfo);
	m_lEquipList.clear();
}

void CInvenMgr::Add_Item(ITEM _pItem)
{
	// 소비템이면 합친다
	if (_pItem.eID == IT_CONSUM)
	{
		bool bAdd = false;
		for (auto& sInfo : m_lList)
		{
			if (_pItem.sTag == sInfo->GetInfo().sTag)
			{
				sInfo->GetInfo().iCount += 1;
				bAdd = true;
				break;
			}
		}
		if (!bAdd && m_iMaxCount > m_lList.size())
		{
			_pItem.InvenID = GetEmptyIndex();

			CItem_Info* pItemUI = new CItem_Info;
			pItemUI->SetInfo(_pItem);

			m_lList.push_back(pItemUI);
		}
	}
	else if (_pItem.eID == IT_EQUIT)
	{
		if (m_iMaxCount > m_lEquipList.size())
		{
			_pItem.InvenID = GetEmptyEquipIndex();

			CItem_Info* pItemUI = new CItem_Info;
			pItemUI->SetInfo(_pItem);

			m_lEquipList.push_back(pItemUI);
		}
	}

}

void CInvenMgr::Use_Item(int _iInvenID)
{
	for (auto iter = m_lList.begin(); iter != m_lList.end(); ++iter)
	{
		if (_iInvenID == (*iter)->GetInfo().InvenID)
		{
			(*iter)->GetInfo().iCount -= 1;
			(*iter)->Use_Item();
			if (0 >= (*iter)->GetInfo().iCount)
			{
				Safe_Delete(*iter);
				m_lList.erase(iter);
			}

			break;
		}
	}
}

ITEM CInvenMgr::FInd_Info(int _iInvenID)
{
	for (auto iter = m_lList.begin(); iter != m_lList.end(); ++iter)
	{
		if (_iInvenID == (*iter)->GetInfo().InvenID)
		{
			return (*iter)->GetInfo();
		}
	}

	ITEM i;
	i.InvenID = 100;

	return i;
}

ITEM CInvenMgr::FInd_EquipInfo(int _iInvenID)
{
	for (auto iter = m_lEquipList.begin(); iter != m_lEquipList.end(); ++iter)
	{
		if (_iInvenID == (*iter)->GetInfo().InvenID)
		{
			return (*iter)->GetInfo();
		}
	}

	ITEM i;
	i.InvenID = 100;

	return i;
}

void CInvenMgr::Remove_EquipInfo(int _iInvenID)
{
	for (auto iter = m_lEquipList.begin(); iter != m_lEquipList.end(); ++iter)
	{
		if (_iInvenID == (*iter)->GetInfo().InvenID)
		{
			Safe_Delete(*iter);
			m_lEquipList.erase(iter);
			return;
		}
	}
}

bool CInvenMgr::Des_Money(int _iMoney)
{
	if (m_iMoney < _iMoney)
		return false;

	m_iMoney -= _iMoney;

	return true;
}

int CInvenMgr::GetEmptyIndex()
{
	if (m_lList.empty())
		return 0;

	for (int i = 0; i < 24; ++i)
	{
		int iCount = 0;
		for (auto& sInfo : m_lList)
		{
			if (sInfo->GetInfo().InvenID == i)
				break;
			else if (sInfo->GetInfo().InvenID != i)
			{
				++iCount;
			}
		}

		if (iCount == m_lList.size())
			return i;
	}

	return 100;
}

int CInvenMgr::GetEmptyEquipIndex()
{
	if (m_lEquipList.empty())
		return 0;

	for (int i = 0; i < 24; ++i)
	{
		int iCount = 0;
		for (auto& sInfo : m_lEquipList)
		{
			if (sInfo->GetInfo().InvenID == i)
				break;
			else if (sInfo->GetInfo().InvenID != i)
			{
				++iCount;
			}
		}

		if (iCount == m_lEquipList.size())
			return i;
	}

	return 100;
}

ITEM  CInvenMgr::MakeItemInfo(CItem* _pItem)
{
	ITEM sInfo{};
	sInfo.eID = _pItem->Get_ItemId();
	sInfo.sTag = _pItem->Get_ItemTag();
	sInfo.iCount = 1;

	return sInfo;
}

void CInvenMgr::ChangeSlot(int _iLeftId, int _iRightId)
{

	for (auto iter = m_lList.begin(); iter != m_lList.end(); ++iter)
	{
		if (_iLeftId == (*iter)->GetInfo().InvenID)
		{
			for (auto iter = m_lList.begin(); iter != m_lList.end(); ++iter)
			{
				if (_iRightId == (*iter)->GetInfo().InvenID)
				{
					(*iter)->GetInfo().InvenID = _iLeftId;
					break;
				}
			}

			(*iter)->GetInfo().InvenID = _iRightId;
			break;
		}

	}
}

void CInvenMgr::ChangeEquipSlot(int _iLeftId, int _iRightId)
{

	for (auto iter = m_lEquipList.begin(); iter != m_lEquipList.end(); ++iter)
	{
		if (_iLeftId == (*iter)->GetInfo().InvenID)
		{
			for (auto iter = m_lEquipList.begin(); iter != m_lEquipList.end(); ++iter)
			{
				if (_iRightId == (*iter)->GetInfo().InvenID)
				{
					(*iter)->GetInfo().InvenID = _iLeftId;
					break;
				}
			}

			(*iter)->GetInfo().InvenID = _iRightId;
			break;
		}

	}
}
