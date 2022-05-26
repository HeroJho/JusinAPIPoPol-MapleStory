#include "stdafx.h"
#include "CutMgr.h"

#include "ObjMgr.h"
#include "UIMgr.h"
#include "ScrollMgr.h"

#include "Player.h"
#include "AbstractFactory.h"
#include "BlockBox.h"
#include "EventMgr.h"
#include "Chang.h"
#include "Portal.h"

CCutMgr* CCutMgr::m_pInstance = nullptr;
CCutMgr::CCutMgr()
	: m_bCut_1(false)
	, m_bCut_2(false)
	, m_bCut_3(false)
	, m_bCut_4(false)
	, m_fDomiTime(0.f)
	, m_fOldDomiTime(0.f)
	, m_bDomi(false)
	, m_fWriteTime(0.f)
	, m_fOldWriteTime(0.f)
	, m_bWrite(false)
	, m_fNextMapTime(0.f)
    , m_fOldNextMapTime(0.f)
	, m_pNpc(nullptr)
	, m_fNpcMarkTime(0.f)
	, m_fOldNpcMarkTime(0.f)
	, m_bMark(false)
{
}

CCutMgr::~CCutMgr()
{
	Release();
}



int CCutMgr::Update(void)
{
	if (m_bCut_1)
		UpdateCut_1();
	if (m_bCut_2)
		UpdateCut_2();
	if (m_bCut_3)
		UpdateCut_3();
	if (m_bCut_4)
		UpdateCut_4();

	return 0;
}

void CCutMgr::Late_Update(void)
{

}
void CCutMgr::Render(HDC hDC)
{

}


void CCutMgr::StartCut_1()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

	m_bCut_1 = true;
	// 플레이어 멈추기
	((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->SetHold();
	// 회상 스크린
	CUIMgr::Get_Instance()->ScreenStart();
	// 2초 뒤 흔들림
	CScrollMgr::Get_Instance()->StartShake(6.f, 4.f, 1000.f, 2000.f);

	// 카메라 고정
	CObj* Block = CAbstractFactory<CBlockBox>::Create(1000.f, 600.f, "Block");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, Block);
	CScrollMgr::Get_Instance()->Set_Target(Block);

	// 도미 이펙트
	m_fDomiTime = 5000.f;
	m_fOldDomiTime = GetTickCount64();
	m_bDomi = false;

	m_fWriteTime = 9000.f;
	m_fOldWriteTime = GetTickCount64();
	m_bWrite = false;

	m_fNextMapTime = 18000.f;
	m_fOldNextMapTime = GetTickCount64();

	m_fNpcMarkTime = 2000.f;
	m_fOldNpcMarkTime = GetTickCount64();

	m_bMark = false;
}
void CCutMgr::UpdateCut_1()
{
	if (!m_bDomi && m_fOldDomiTime + m_fDomiTime < GetTickCount64())
	{
		CUIMgr::Get_Instance()->DomiClose();
		m_bDomi = true;
	}

	if (!m_bWrite && m_fOldWriteTime + m_fWriteTime < GetTickCount64())
	{
		CUIMgr::Get_Instance()->StartWriteDarkedMage();
		m_bWrite = true;
	}

	if (!m_bMark && m_fOldNpcMarkTime + m_fNpcMarkTime < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(L"Shake.wav", SOUND_PEFFECT3, 1);
		m_pNpc->SetMark();
		m_bMark = true;
	}
	
	if (m_fOldNextMapTime + m_fNextMapTime < GetTickCount64())
	{
		//CUIMgr::Get_Instance()->DomiReset();
		CUIMgr::Get_Instance()->ScreenReset();
		CUIMgr::Get_Instance()->WriteDarkedMageReset();
		CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_3);
		((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->ResetHold();
		m_bCut_1 = false;
	}
}


void CCutMgr::StartCut_2()
{
	m_bCut_2 = true;
	// 플레이어 멈추기
	//((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->SetHold();

	// 회상 스크린
	CUIMgr::Get_Instance()->ScreenStart();

	// 2초 뒤 흔들림
	CScrollMgr::Get_Instance()->StartShake(6.f, 4.f, 1000.f, 5000.f);


	m_fDomiTime = 2000.f;
	m_fOldDomiTime = GetTickCount64();
	m_bDomi = false;

	m_fWriteTime = 5000.f;
	m_fOldWriteTime = GetTickCount64();
	m_bWrite = false;

	m_fNextMapTime = 11000.f;
	m_fOldNextMapTime = GetTickCount64();
}
void CCutMgr::UpdateCut_2()
{
	if (!m_bDomi && m_fOldDomiTime + m_fDomiTime < GetTickCount64())
	{
		// 카메라 고정
		CObj* Block = CAbstractFactory<CBlockBox>::Create(201.f, 561.f, "Block");
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, Block);
		CScrollMgr::Get_Instance()->Set_Target(Block);
		m_bDomi = true;
	}


	if (!m_bWrite && m_fOldWriteTime + m_fWriteTime < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_NPC);
		CSoundMgr::Get_Instance()->PlaySound(L"DarkTalk_2.wav", SOUND_NPC, 1);
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(L"Shake.wav", SOUND_PEFFECT3, 1);

		//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CChang>::Create(201.f, 400.f, "Monster"));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(206.f, 636.f, "Portal_4To5"));
		// 포탈 생성
		m_bWrite = true;
	}


	if (m_fOldNextMapTime + m_fNextMapTime < GetTickCount64())
	{
		CUIMgr::Get_Instance()->ScreenReset();
		//CUIMgr::Get_Instance()->WriteDarkedMageReset();
		//((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->ResetHold();
		CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
		m_bCut_2 = false;
	}
}

void CCutMgr::StartCut_3()
{
	m_bCut_3 = true;
	// 플레이어 멈추기
	//((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->SetHold();

	// 회상 스크린
	CUIMgr::Get_Instance()->ScreenStart();

	// 2초 뒤 흔들림
	CScrollMgr::Get_Instance()->StartShake(6.f, 4.f, 1000.f, 5000.f);


	m_fDomiTime = 2000.f;
	m_fOldDomiTime = GetTickCount64();
	m_bDomi = false;

	m_fWriteTime = 5000.f;
	m_fOldWriteTime = GetTickCount64();
	m_bWrite = false;

	m_fNextMapTime = 8000.f;
	m_fOldNextMapTime = GetTickCount64();
}
void CCutMgr::UpdateCut_3()
{
	if (!m_bDomi && m_fOldDomiTime + m_fDomiTime < GetTickCount64())
	{
		// 카메라 고정
		CObj* Block = CAbstractFactory<CBlockBox>::Create(1353.f, 487.f, "Block");
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, Block);
		CScrollMgr::Get_Instance()->Set_Target(Block);
		m_bDomi = true;
	}


	if (!m_bWrite && m_fOldWriteTime + m_fWriteTime < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(L"Shake.wav", SOUND_PEFFECT3, 1);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(1353.f, 487.f, "Portal_5To6"));
		// 포탈 생성
		m_bWrite = true;
	}


	if (m_fOldNextMapTime + m_fNextMapTime < GetTickCount64())
	{
		CUIMgr::Get_Instance()->ScreenReset();
		CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
		m_bCut_3 = false;
	}
}

void CCutMgr::StartCut_4()
{
	m_bCut_4 = true;
	// 플레이어 멈추기
	//((CPlayer*)CObjMgr::Get_Instance()->Get_Player())->SetHold();

	// 회상 스크린
	CUIMgr::Get_Instance()->ScreenStart();

	// 2초 뒤 흔들림
	CScrollMgr::Get_Instance()->StartShake(6.f, 4.f, 1000.f, 5000.f);


	m_fDomiTime = 2000.f;
	m_fOldDomiTime = GetTickCount64();
	m_bDomi = false;

	m_fWriteTime = 5000.f;
	m_fOldWriteTime = GetTickCount64();
	m_bWrite = false;

	m_fNextMapTime = 8000.f;
	m_fOldNextMapTime = GetTickCount64();
}
void CCutMgr::UpdateCut_4()
{
	if (!m_bDomi && m_fOldDomiTime + m_fDomiTime < GetTickCount64())
	{
		// 카메라 고정
		CObj* Block = CAbstractFactory<CBlockBox>::Create(1228.f, 663.f, "Block");
		CObjMgr::Get_Instance()->Add_Object(OBJ_BLOCK, Block);
		CScrollMgr::Get_Instance()->Set_Target(Block);
		m_bDomi = true;
	}

	if (!m_bWrite && m_fOldWriteTime + m_fWriteTime < GetTickCount64())
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
		CSoundMgr::Get_Instance()->PlaySound(L"Shake.wav", SOUND_PEFFECT3, 1);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MAP, CAbstractFactory<CPortal>::Create(1228.f, 663.f, "Portal_6To7"));
		// 포탈 생성
		m_bWrite = true;
	}


	if (m_fOldNextMapTime + m_fNextMapTime < GetTickCount64())
	{
		CUIMgr::Get_Instance()->ScreenReset();
		CScrollMgr::Get_Instance()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
		m_bCut_4 = false;
	}
}


void CCutMgr::Release(void)
{

}
