#include "stdafx.h"
#include "InvenMgr.h"
#include "Item_UI.h"


CInvenMgr* CInvenMgr::m_pInstance = nullptr;
CInvenMgr::CInvenMgr()
	: m_iMaxCount(24)
	, m_iMoney(0)
	, m_iInvenID(0)
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
	{
		Safe_Delete(sInfo);
	}
	m_lList.clear();
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
			_pItem.InvenID = m_iInvenID++;

			CItem_UI* pItemUI = new CItem_UI;
			pItemUI->SetInfo(_pItem);

			m_lList.push_back(pItemUI);
		}
	}
	else
	{
		if (m_iMaxCount > m_lList.size())
		{
			_pItem.InvenID = m_iInvenID++;
			
			CItem_UI* pItemUI = new CItem_UI;
			pItemUI->SetInfo(_pItem);

			m_lList.push_back(pItemUI);
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

bool CInvenMgr::Des_Money(int _iMoney)
{
	if (m_iMoney < _iMoney)
		return false;

	m_iMoney -= _iMoney;

	return true;
}

ITEM  CInvenMgr::MakeItemInfo(CItem* _pItem)
{
	ITEM sInfo{};
	sInfo.eID = _pItem->Get_ItemId();
	sInfo.sTag = _pItem->Get_ItemTag();
	sInfo.iCount = 1;

	return sInfo;
}
