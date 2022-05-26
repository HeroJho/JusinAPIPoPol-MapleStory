#include "stdafx.h"
#include "Pet.h"
#include "EventMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "Money.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "QuestMgr.h"

CPet::CPet()
{

}

CPet::~CPet()
{
	Release();
}

void CPet::Initialize(void)
{
	m_pTarget = nullptr;
		

	Set_FrameKey(L"PetL");
	SetCurState(IDLE, DIR_LEFT);
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 1000.f;
	m_tFrame.dwTime = GetTickCount64();

	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 25.f;
	m_tInfo.fCCY = 25.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -10.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 60.f;
	m_tInfo.fTCY = 60.f;

	Set_Stat(0, 0, 0);
	m_bCanHit = true;

	m_bJump = false;
	m_fSpeed = 0.4f;
	m_fJumpPower = 6.5f;

	m_pOldLine = nullptr;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fVelX = 0.f;
	m_fAirTime = 0.f;

	m_fStopRange = 0.f;
}

int CPet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_pTarget != nullptr)
	{
		if (m_pTarget->IsHang())
			SetCurState(HANG, m_eDir);

		// 일정 범위 떨어지면 초기화
		float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
		if (400.f < fX || -400.f > fX || 200.f < fY || -200.f > fY)
		{
			int iRX = CEventMgr::Get_Instance()->GetRandomNum_Int(-30, 30);
			m_tInfo.fX = m_pTarget->Get_Info().fX + iRX;
			m_tInfo.fY = m_pTarget->Get_Info().fY;
			SetCurState(IDLE, m_eDir);
		}
	}

	switch (m_eCurState)
	{
	case IDLE:
		Update_Idle();
		break;
	case CHASE:
		Update_Chase();
		break;
	case JUMP:
		Update_Jump();
		break;
	case HANG:
		Update_Hang();
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPet::Late_Update(void)
{
	Update_Gravity();

	if (!m_bStayPlay)
	{
		Motion_Change();
		Move_Frame();
	}
}

void CPet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 						
		int(m_tTRect.left + iScrollX),			
		int(m_tTRect.top - 22 + iScrollY),
		int(m_tInfo.fTCX),						
		int(m_tInfo.fTCY),
		hMemDC,									
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,						
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));						

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfHeight = 13;
	m_labelFontInfo.lfWidth = 7;
	m_labelFontInfo.lfCharSet = HANGEUL_CHARSET;
	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);

	SetBkMode(hDC, OPAQUE);
	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(255, 255, 255));
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("귀요미야"));
	TextOut(hDC, m_tTRect.left + iScrollX, m_tTRect.top + iScrollY + 38, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);
}

void CPet::Release(void)
{

}

void CPet::OnHit(CObj* _pOther)
{

}

void CPet::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"PetL";
	else
		m_pFrameKey = L"PetR";

	m_eDir = _eDir;
	m_eCurState = _eState;
}

void CPet::SetPlayerPos()
{
	if (m_pTarget == nullptr)
		return;

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY - 10;
	m_fVelX = 0.f;
	SetCurState(IDLE, m_eDir);
}


void CPet::Update_Idle()
{
	if (m_pTarget == nullptr)
		return;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;

	if (100.f < fX)
	{
		SetCurState(CHASE, DIR_RIGHT);
		m_fStopRange = CEventMgr::Get_Instance()->GetRandomNum_Int(50, 500);
	}
	else if (-100.f > fX)
	{
		SetCurState(CHASE, DIR_LEFT);
		m_fStopRange = CEventMgr::Get_Instance()->GetRandomNum_Int(50, 500);
	}
	


	if (1.f < m_fVelX)
		m_fVelX += -.05f;
	else if (-1.f > m_fVelX)
		m_fVelX += .05f;
	else
		m_fVelX = 0.f;

	m_tInfo.fX += m_fVelX;
}

void CPet::Update_Chase()
{
	if (m_pTarget == nullptr)
		return;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;

	if (m_fStopRange > fX && -m_fStopRange < fX)
	{
		if(0.f > fX)
			SetCurState(IDLE, DIR_LEFT);
		else if(0.f < fX)
			SetCurState(IDLE, DIR_RIGHT);

		return;
	}

	//if (m_eDir == DIR_LEFT)
	//	m_tInfo.fX -= 3.f;
	//else if (m_eDir == DIR_RIGHT)
	//	m_tInfo.fX += 3.f;

	if (m_eDir == DIR_LEFT)
	{
		if (-3.f > m_fVelX)
			m_fVelX = -3.f;
		else
			m_fVelX -= .1f;
	}
	else if (m_eDir == DIR_RIGHT)
	{
		if (3.f < m_fVelX)
			m_fVelX = 3.f;
		else
			m_fVelX += .1f;
	}

	m_tInfo.fX += m_fVelX;

}

void CPet::Update_Jump()
{
	if (!m_bJump)
		SetCurState(IDLE, m_eDir);

	if (m_eDir == DIR_LEFT)
		m_tInfo.fX -= m_fJumpPower;
	else if (m_eDir == DIR_RIGHT)
		m_tInfo.fX += m_fJumpPower;
}

void CPet::Update_Hang()
{
	if (m_pTarget == nullptr)
		return;

	if (!m_pTarget->IsHang())
	{
		//SetCurState(IDLE, m_eDir);
		m_fJumpPower = CEventMgr::Get_Instance()->GetRandomNum_Int(10, 30) * 0.1;
		if(m_pTarget->Get_Dir() == DIR_LEFT)
			SetCurState(JUMP, DIR_LEFT);
		else
			SetCurState(JUMP, DIR_RIGHT);

		m_bJump = true;
		m_fValY = 0.f;
		return;
	}
		
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;
}


void CPet::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Item")
	{
		_pOther->OnHit(this);
	}
	else if (m_pTarget == nullptr && _pOther->Get_Tag() == "Player")
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MONE4);
		CSoundMgr::Get_Instance()->PlaySound(L"DogSound.wav", SOUND_MONE4, 1);
		m_pTarget = (CPlayer*)CObjMgr::Get_Instance()->Get_Player();
	}

}

void CPet::OnePlayEnd(void)
{
	m_tFrame.iFrameStart = 2;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 1;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

void CPet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CHASE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case HANG:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount64();
			break;
		}

		m_ePreState = m_eCurState;
	}
}