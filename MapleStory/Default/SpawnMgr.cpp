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

	m_fGenTime = 6000.f;
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

	m_iMaxMonsterCount = 30;
	m_iLineCount = 9;

	SpawnInfo s;
	// 1
	s.Init(MON_BLUESNAIL, 20 + 200, 2218 - 200, 1570);
	m_lRects.push_back(s);
	s.Init(MON_REDSNAIL, 20 + 200, 2218 - 200, 1570);
	m_lRects.push_back(s);
	s.Init(MON_BLUESNAIL, 20 + 200, 2218 - 200, 1570);
	m_lRects.push_back(s);
	s.Init(MON_REDSNAIL, 20 + 200, 2218 - 200, 1570);
	m_lRects.push_back(s);
	
	// 2
	s.Init(MON_BLUESNAIL, 393 + 200, 1839 - 200, 1270);
	m_lRects.push_back(s);
	s.Init(MON_BLUESNAIL, 393 + 200, 1839 - 200, 1270);
	m_lRects.push_back(s);

	// 3
	s.Init(MON_REDSNAIL, 485 + 200, 1750 - 200, 1030);
	m_lRects.push_back(s);
	s.Init(MON_GREENMUSH, 485 + 200, 1750 - 200, 1030);
	m_lRects.push_back(s);

	// 4
	s.Init(MON_GREENMUSH, 572 + 200, 1658 - 200, 787);
	m_lRects.push_back(s);

}

void CSpawnMgr::Scene_4()
{
	Release();

	m_iMaxMonsterCount = 20;
	m_iLineCount = 9;

	// 1
	SpawnInfo s;
	s.Init(MON_DELSNAIL, 31 + 200, 605 - 200, 366);
	m_lRects.push_back(s);

	s.Init(MON_DELPIG, 663 + 200, 1413 - 200, 418);
	m_lRects.push_back(s);

	s.Init(MON_DELPIG, 1644 + 200, 2321 - 200, 237);
	m_lRects.push_back(s);

	s.Init(MON_DELSNAIL, 1825 + 200, 2406 - 200, 594);
	m_lRects.push_back(s);

	s.Init(MON_DELSNAIL, 935 + 200,  2785 - 200, 992);
	m_lRects.push_back(s);
	s.Init(MON_DELPIG, 935 + 200, 2785 - 200, 992);
	m_lRects.push_back(s);

	s.Init(MON_DELSNAIL, 480 + 200, 1414 - 200, 776);
	m_lRects.push_back(s);

	s.Init(MON_DELPIG, 1 + 200, 454 - 200, 814);
	m_lRects.push_back(s);
}

void CSpawnMgr::Scene_5()
{
	Release();

	m_iMaxMonsterCount = 25;
	m_iLineCount = 6;

	// 1
	SpawnInfo s;
	s.Init(MON_NIGHTC, 0 + 100, 1420 - 100, 1025);
	m_lRects.push_back(s);
	s.Init(MON_NIGHTC, 0 + 100, 1420 - 100, 1025);
	m_lRects.push_back(s);

	s.Init(MON_NIGHTC, 867 + 100, 1421 - 100, 725);
	m_lRects.push_back(s);

	s.Init(MON_NIGHTC, 135 + 100, 729 - 100, 724);
	m_lRects.push_back(s);

	s.Init(MON_NIGHTC, 864 + 100, 1419 - 100, 486);
	m_lRects.push_back(s);

	s.Init(MON_NIGHTC, 134 + 100, 821 - 100, 425);
	m_lRects.push_back(s);
}

void CSpawnMgr::Scene_6()
{
	Release();

	m_iMaxMonsterCount = 15;
	m_iLineCount = 3;

	// 1
	SpawnInfo s;
	s.Init(MON_NIGHTE, 0 + 100, 1419 - 100, 650);
	m_lRects.push_back(s);
	s.Init(MON_NIGHTE, 261 + 100, 1196 - 100, 290);
	m_lRects.push_back(s);
	s.Init(MON_NIGHTE, 261 + 100, 1196 - 100, 290);
	m_lRects.push_back(s);
}

