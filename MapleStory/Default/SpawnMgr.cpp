#include "stdafx.h"
#include "SpawnMgr.h"

#include "ObjMgr.h"
#include "EventMgr.h"

CSpawnMgr* CSpawnMgr::m_pInstance = nullptr;

CSpawnMgr::CSpawnMgr()
{

}

CSpawnMgr::~CSpawnMgr()
{
	Release();
}

void CSpawnMgr::Initialize(void)
{
	m_iMaxMonsterCount = 0;
	m_iMonsterCount = 0;
	m_iLineCount = 0;

	m_fGenTime = 15000.f;
	m_fOldGenTime = 0.f;
}

void CSpawnMgr::Update(void)
{
	// 15√ ∏∂¥Ÿ ¡®
	if (m_fOldGenTime + m_fGenTime < GetTickCount64())
	{

		while (m_iMonsterCount < m_iMaxMonsterCount)
		{
			int iLine = CEventMgr::Get_Instance()->GetRandomNum_Int(0, m_iLineCount - 1);
			int iCount = 0;

			for (auto& iter : m_lRects)
			{
				if (iCount == iLine)
				{
					int iRanX = CEventMgr::Get_Instance()->GetRandomNum_Int(iter.rect.left, iter.rect.right);
					int iRanY = iter.rect.bottom;

					CObjMgr::Get_Instance()->MakeMonster(iter.Id, iRanX, iRanY);
					++m_iMonsterCount;
					break;
				}
				++iCount;
			}
		}

		m_fOldGenTime = GetTickCount64();
	}

}

void CSpawnMgr::Release(void)
{
	m_lRects.clear();
}

void CSpawnMgr::Scene_2()
{
	Release();

	m_iMaxMonsterCount = 60;
	m_iLineCount = 9;

	SpawnInfo s;
	// 1
	s.Init(MON_BLUESNAIL, 20 + 50, 2218 - 50, 1570);
	m_lRects.push_back(s);
	// s.Init(MON_REDSNAIL, 20 + 30, 2218 - 30, 1570);
	// m_lRects.push_back(s);
	// s.Init(MON_BLUESNAIL, 20 + 30, 2218 - 30, 1570);
	// m_lRects.push_back(s);
	s.Init(MON_REDSNAIL, 20 + 50, 2218 - 50, 1570);
	m_lRects.push_back(s);
	
	// 2
	//s.Init(MON_BLUESNAIL, 393 + 30, 1839 - 30, 1270);
	//m_lRects.push_back(s);
	s.Init(MON_BLUESNAIL, 393 + 50, 1839 - 50, 1270);
	m_lRects.push_back(s);

	// 3
	//s.Init(MON_REDSNAIL, 485 + 30, 1750 - 30, 1030);
	//m_lRects.push_back(s);
	s.Init(MON_GREENMUSH, 485 + 50, 1750 - 50, 1030);
	m_lRects.push_back(s);

	// 4
	s.Init(MON_GREENMUSH, 572 + 50, 1658 - 50, 787);
	m_lRects.push_back(s);


	// TEST
	
	// 1
	s.Init(MON_DELSNAIL, 20 + 50, 2218 - 50, 1570);
	m_lRects.push_back(s);
	// s.Init(MON_REDSNAIL, 20 + 30, 2218 - 30, 1570);
	// m_lRects.push_back(s);
	// s.Init(MON_BLUESNAIL, 20 + 30, 2218 - 30, 1570);
	// m_lRects.push_back(s);
	s.Init(MON_DELPIG, 20 + 50, 2218 - 50, 1570);
	m_lRects.push_back(s);

	// 2
	//s.Init(MON_BLUESNAIL, 393 + 30, 1839 - 30, 1270);
	//m_lRects.push_back(s);
	s.Init(MON_NIGHTC, 393 + 50, 1839 - 50, 1270);
	m_lRects.push_back(s);

	// 3
	//s.Init(MON_REDSNAIL, 485 + 30, 1750 - 30, 1030);
	//m_lRects.push_back(s);
	s.Init(MON_NIGHTE, 485 + 50, 1750 - 50, 1030);
	m_lRects.push_back(s);

	// 4
	s.Init(MON_NIGHTE, 572 + 50, 1658 - 50, 787);
	m_lRects.push_back(s);



}

