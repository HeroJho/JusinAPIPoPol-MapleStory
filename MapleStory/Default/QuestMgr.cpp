#include "stdafx.h"
#include "QuestMgr.h"
#include "EventMgr.h"
#include "UIMgr.h"
#include "CutMgr.h"

CQuestMgr* CQuestMgr::m_pInstance = nullptr;
CQuestMgr::CQuestMgr()
{
}


CQuestMgr::~CQuestMgr()
{
	Release();
}

void CQuestMgr::Initialize(void)
{
	m_b5 = false;
	m_b6 = false;


	m_eCurState = Stay1;

	m_iBlueNail = 0;
	m_iMaxBlueNail = 10;
	m_iRedNail = 0;
	m_iMaxRedNail = 10;
	m_iGreen = 0;
	m_iMaxGreen = 10;

	m_iDelNail = 0;
	m_iMaxDelNail = 9;
	m_iDelPig = 0;
	m_iMaxDelPig = 9;

	m_iNightC = 0;
	m_iMaxNightC = 30;
	m_iNightE = 0;
	m_iMaxNightE = 30;
}

void CQuestMgr::Update(void)
{
	/*if(m_eCurState == Stay2)*/

}

void CQuestMgr::Release(void)
{
	
}

void CQuestMgr::HuntingMonster(MONSTERID _eID)
{
	if (m_eCurState == Q1)
	{
		switch (_eID)
		{
		case MON_BLUESNAIL:
			++m_iBlueNail;
			if (m_iBlueNail > m_iMaxBlueNail)
				m_iBlueNail = m_iMaxBlueNail;
			break;
		case MON_REDSNAIL:
			++m_iRedNail;
			if (m_iRedNail > m_iMaxRedNail)
				m_iRedNail = m_iMaxRedNail;
			break;
		case MON_GREENMUSH:
			++m_iGreen;
			if (m_iGreen > m_iMaxGreen)
				m_iGreen = m_iMaxGreen;
			break;
		}
	}
	else if (m_eCurState == Q2)
	{
		switch (_eID)
		{
		case MON_DELSNAIL:
			++m_iDelNail;
			if (m_iDelNail > m_iMaxDelNail)
				m_iDelNail = m_iMaxDelNail;
			break;
		case MON_DELPIG:
			++m_iDelPig;
			if (m_iDelPig > m_iMaxDelPig)
				m_iDelPig = m_iMaxDelPig;
			break;
		}
	}
	else if (m_eCurState == Q3)
	{
		switch (_eID)
		{
		case MON_NIGHTC:
			++m_iNightC;
			if (m_iNightC > m_iMaxNightC)
				m_iNightC = m_iMaxNightC;
			break;
		case MON_NIGHTE:
			++m_iNightE;
			if (m_iNightE > m_iMaxNightE)
				m_iNightE = m_iMaxNightE;
			break;
		}
	}



	// Äù½ºÆ® ¿Ï·á
	if (m_eCurState == Q1 && m_iBlueNail == m_iMaxBlueNail && m_iRedNail == m_iMaxRedNail && m_iGreen == m_iMaxGreen)
	{
		m_eCurState = CQ1;
	}
	else if (m_eCurState == Q2 && m_iDelNail == m_iMaxDelNail && m_iDelPig == m_iMaxDelPig)
	{
		m_eCurState = CQ2;
	}
	else if (m_eCurState == Q3 && m_iNightC == m_iMaxNightC && !m_b5)
	{
		CCutMgr::Get_Instance()->StartCut_3();
		m_b5 = true;
	}
	else if (m_eCurState == Q3 && m_iNightE == m_iMaxNightE && !m_b6)
	{
		CCutMgr::Get_Instance()->StartCut_4();
		m_b6 = true;
	}
}

void CQuestMgr::AcceptQuest()
{
	if (m_eCurState == Stay1)
	{	
		CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"QuestAlert.wav", SOUND_ITEM, 1);

		m_eCurState = Q1;
	}
	else if (m_eCurState == CQ1)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"QuestClear.wav", SOUND_ITEM, 1);

		m_eCurState = Stay2; 
		CCutMgr::Get_Instance()->StartCut_1();
	}
	else if (m_eCurState == Stay2)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"QuestAlert.wav", SOUND_ITEM, 1);

		m_eCurState = Q2;
	}
	else if (m_eCurState == CQ2)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"QuestClear.wav", SOUND_ITEM, 1);

		m_eCurState = Stay3;
		CCutMgr::Get_Instance()->StartCut_2();
	}
	else if (m_eCurState == Stay3)
	{
		m_eCurState = Q3;
	}
}
