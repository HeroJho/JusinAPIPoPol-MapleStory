#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"

#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "EventMgr.h"
#include "UIMgr.h"


#include "ObjMgr.h"
#include "Skill.h"
#include "BladeFury.h"
#include "KarmaFury.h"
#include "PhantomBlow.h"
#include "BladeStorm.h"
#include "DoubleJump.h"
#include "SkillMgr.h"


CPlayer::CPlayer()
	: m_eCurState(IDLE)
	, m_ePreState(END)
	, m_bDoubleJump(false)
	, m_bDrop(false)
	, m_bHit(false)
	, m_eDoubleDir(DIR_LEFT)
	, m_fDropSpeed(0.f)
	, m_fDropY(0.f)
	, m_fHitTime(0.f)
	, m_fOldHitTime(0.f)
	, m_fOldSkillTime(0.f)
	, m_fSkillTime(0.f)
	, m_pDropLine(nullptr)
	, m_pHangLine(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	CSkillMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerL.bmp", L"PlayerL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerR.bmp", L"PlayerR");
	Set_FrameKey(L"PlayerL");
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = (DWORD)1000.f;
	m_tFrame.dwTime = (DWORD)GetTickCount64();


	// 콜리젼 크기, 피봇 설정
	m_tInfo.fCCX = 50.f;
	m_tInfo.fCCY = 80.f;
	m_tColPivot.x = (LONG)0.f;
	m_tColPivot.y = (LONG)-35.f;
	// 텍스쳐 크기 설정
	m_tInfo.fTCX = 200.f;
	m_tInfo.fTCY = 200.f;


	m_fDropSpeed = 20.f;
	m_bHit = false;
	m_fOldHitTime = 0.f;
	m_fHitTime = 3000.f;

	m_fOldSkillTime = 0.f;
	m_fSkillTime = 800.f;

	Set_Stat(100, 200, 10);

	m_eCurState = IDLE;
	m_fSpeed = 3.f;
	m_fJumpPower = 10.f;

	m_pOldLine = nullptr;
	m_pDropLine = nullptr;
	m_pHangLine = nullptr;
	m_bDrop = false;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;
	m_fDropY = 0.f;

	m_bDoubleJump = false;
	m_eDoubleDir = DIR_END;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	
	switch (m_eCurState)
	{
	case CPlayer::IDLE:
		Key_Input();
		break;
	case CPlayer::WALK:
		Key_Input();
		break;
	case CPlayer::AIR:
		Key_Input();
		break;
	case CPlayer::ATTACK:
		Skill_Update();
		break;
	case CPlayer::SKILL:
		Skill_Update();
		break;
	case CPlayer::HIT:
		Key_Input();
		Hit_Update();
		break;
	case CPlayer::BENDIDLE:
	case CPlayer::BENDWALK:
		break;
	case CPlayer::HANGIDLE:
	case CPlayer::HANGWALK:
		Hang_Input();
		break;
	case CPlayer::DEAD:
		Key_Input();
		break;
	}

	Update_Rect();
	CSkillMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	switch (m_eCurState)
	{
	case CPlayer::IDLE:
		Update_Gravity();
		break;
	case CPlayer::WALK:
		Update_Gravity();
		break;
	case CPlayer::AIR:
		Update_Gravity();
		break;
	case CPlayer::ATTACK:
		Update_Gravity();
		break;
	case CPlayer::SKILL:
		Update_Gravity();
		break;
	case CPlayer::HIT:
		Update_Gravity();
		break;
	case CPlayer::BENDIDLE:
	case CPlayer::BENDWALK:
		break;
	case CPlayer::HANGIDLE:
	case CPlayer::HANGWALK:
		Update_Hang();
		break;
	case CPlayer::DEAD:
		Update_Gravity();
		break;
	}

	// 무적
	if (m_bHit && (m_fOldHitTime + m_fHitTime < GetTickCount64()))
	{
		m_bHit = false;
	}

	Motion_Change();
	Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_bHit)
	{
		// TODO : 피격 스프라이트  처리
		GdiTransparentBlt(hDC, 						
			int(m_tTRect.left + iScrollX),			
			int(m_tTRect.top - 37 + iScrollY),
			int(m_tInfo.fTCX),						
			int(m_tInfo.fTCY),
			hMemDC,									
			m_tFrame.iFrameStart * (int)m_tInfo.fTCX,
			m_tFrame.iMotion * (int)m_tInfo.fTCY,
			(int)m_tInfo.fTCX,						
			(int)m_tInfo.fTCY,
			RGB(255, 0, 255));						
	}
	else
	{
		GdiTransparentBlt(hDC, 									// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tTRect.left + iScrollX),					// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tTRect.top - 37 + iScrollY),
			int(m_tInfo.fTCX),								// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fTCY),
			hMemDC,											// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fTCY,
			(int)m_tInfo.fTCX,								// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fTCY,
			RGB(255, 0, 255));								// 제거하고자 하는 색상
	}


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
	wsprintf(lpOut, TEXT("배꼽벌렁이"));
	TextOut(hDC, m_tTRect.left + iScrollX + 65, m_tTRect.top - 37 + iScrollY + 145, lpOut, lstrlen(lpOut));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


}
void CPlayer::Release(void)
{
	
}


void CPlayer::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if(_eDir == DIR_LEFT)
		m_pFrameKey = L"PlayerL";
	else
		m_pFrameKey = L"PlayerR";

	m_eCurState = _eState;
}


void CPlayer::Update_Gravity(void)
{
	// 1. 라인을 얻어온다.
	float		LinefY = 0.f;

	CLine* m_pCurLine = nullptr;

	if (m_bDrop && !m_pDropLine)
	{
		m_pCurLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY, m_bDrop);
		m_pDropLine = m_pCurLine;
		m_fDropY = LinefY;
	}
	else if (!m_pDropLine)
	{
		m_pCurLine = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &LinefY, m_bDrop);
		m_fDropY = LinefY;
	}
	if (!m_pCurLine)
		m_pCurLine = m_pDropLine;

	// 3. 공중 여부에 따라 중력 적용한다.
	if (m_bOnAir)
	{
		// m_fAirTime += 0.2f;

		m_fValY += 0.4f;

		// m_tInfo.fY -= m_fJumpPower * m_fAirTime - 1.f * m_fAirTime * m_fAirTime * 0.5f;
		m_tInfo.fY += m_fValY;

		if(m_eCurState != ATTACK && m_eCurState != SKILL)
			SetCurState(AIR, m_eDir);
	}


	if (m_bJump)
	{
		if (m_bDoubleJump)
		{
			if (m_eDoubleDir == DIR_END)
			{
				m_fValY = 0.f;
				m_eDoubleDir = m_eDir;
			}

			if(m_eDoubleDir == DIR_LEFT)
				m_tInfo.fX -= 6.f;
			else
				m_tInfo.fX += 6.f;

			m_tInfo.fY -= m_fJumpPower - 1.f;
		}
		else
		{
			m_tInfo.fY -= m_fJumpPower;
		}
	}

	// 2. 공중인지 아닌지 판단한다.
	if (m_fDropY <= m_tInfo.fY)
	{	// 바닥일 때
		m_tInfo.fY = m_fDropY;
		m_bOnAir = false;
		m_bDrop = false;
		m_pDropLine = nullptr;
		m_fValY = 0.f;
	}
	else if (m_fDropY > m_tInfo.fY)
	{	// 공중일 때
		// 이전 라인이랑 같고,           대각선일때
		if (!(m_pOldLine == m_pCurLine && m_pCurLine->Get_Diagonal()))
		{
			m_bOnAir = true;
		}
	}

	if (!m_bOnAir)
	{
		m_tInfo.fY = m_fDropY;
		m_pDropLine = nullptr;
		m_bDrop = false;
		m_bJump = false;
		m_bDoubleJump = false;
		m_eDoubleDir = DIR_END;
		m_fValY = 0.f;
	}

	m_pOldLine = m_pCurLine;
}

void CPlayer::Update_Hang(void)
{
	float fLineY = 0.f;
	m_pHangLine = CLineMgr::Get_Instance()->Collision_HangLine(m_tInfo.fX, m_tInfo.fY, &fLineY);

	if (!m_pHangLine)
	{
		SetCurState(IDLE, m_eDir);
		return;
	}

	m_tInfo.fX = m_pHangLine->Get_Info().tLPoint.fX;
	
	m_pDropLine = nullptr;
	m_bDrop = false;
	m_bJump = false;
	m_bDoubleJump = false;
	m_eDoubleDir = DIR_END;
	m_fValY = 2.f;
	if(m_eCurState != HANGWALK)
		SetCurState(HANGIDLE, m_eDir);
}

void CPlayer::Hit_Update(void)
{
	if (m_eDir == DIR_LEFT)
		m_tInfo.fX += m_fDropSpeed;
	else
		m_tInfo.fX -= m_fDropSpeed;

}

void CPlayer::Skill_Update(void)
{
	//if (m_fOldSkillTime + m_fSkillTime < GetTickCount64())
	//{
	//	SetCurState(IDLE, m_eDir);
	//}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		//m_eDir = DIR_LEFT;
		//SetCurState(WALK, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		//m_eDir = DIR_RIGHT;
		//SetCurState(WALK, m_eDir);
	}

	m_bOnePlay = true;
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;

	// GetKeyState
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eDir = DIR_LEFT;
		SetCurState(WALK, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eDir = DIR_RIGHT;
		SetCurState(WALK, m_eDir);
	}
	else
	{
		if (m_eCurState != HANGIDLE && m_eCurState != HANGWALK)
			SetCurState(IDLE, m_eDir);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_bJump && !m_bDoubleJump)
		{
			CObj* pSkill = CAbstractFactory<CDoubleJump>::Create(m_tInfo.fCX, m_tInfo.fCY, "Skill");
			pSkill->Set_Target(this);

			CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);


			m_bDoubleJump = true;
			m_bOnAir = true;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_bDrop = true;
			m_bOnAir = true;
		}
		else
		{
			m_fJumpPower = 9.2f;
			m_bJump = true;
			m_bOnAir = true;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP) || CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		SetCurState(HANGIDLE, m_eDir);
	}


	// TODO: 스킬 매니저
	if (m_eCurState == SKILL || m_eCurState == ATTACK)
		return;


	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		SetCurState(ATTACK, m_eDir);

		CObj* pSkill = CAbstractFactory<CSkill>::Create(m_tInfo.fCX, m_tInfo.fCY, "Skill");
		pSkill->Set_Target(this);

		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		if(CSkillMgr::Get_Instance()->UseSkill(SK_SKILL1))
			SetCurState(SKILL, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		if (CSkillMgr::Get_Instance()->UseSkill(SK_SKILL2))
			SetCurState(SKILL, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		if (CSkillMgr::Get_Instance()->UseSkill(SK_SKILL4))
			SetCurState(SKILL, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		if (CSkillMgr::Get_Instance()->UseSkill(SK_SKILL3))
			SetCurState(SKILL, m_eDir);
	}

}

void CPlayer::Hang_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		SetCurState(HANGWALK, m_eDir);
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		SetCurState(HANGWALK, m_eDir);
	}
	else
		SetCurState(HANGIDLE, m_eDir);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		SetCurState(IDLE, m_eDir);
		m_bJump = true;
		m_bOnAir = true;
	}
}


void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_ePreState = m_eCurState;

		// 스킬 상태이면 애니메이션 안 바뀜
		if (m_bOnePlay)
			return;

		//m_bOnePlay = false;
		//m_bStayPlay = false;

		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = (DWORD)800.f;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = (DWORD)100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case AIR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = (DWORD)100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case ATTACK:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = (DWORD)120;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case SKILL:
			m_bOnePlay = true;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = (DWORD)120;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = (DWORD)200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case BENDIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = (DWORD)100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case HANGIDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = (DWORD)100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case BENDWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = (DWORD)100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case HANGWALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = (DWORD)100;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = (DWORD)200;
			m_tFrame.dwTime = (DWORD)GetTickCount64();
			break;
		}
	}
}


void CPlayer::OnHit(CObj* _pOther)
{
	if (m_bHit)
		return;

	m_tStat.iHp -= _pOther->Get_Stat().iAt;
	CUIMgr::Get_Instance()->ChangePlayerHp(m_tStat.iHp, m_tStat.iMaxHp);
	if (m_tStat.iHp <= 0.f)
	{
		m_tStat.iHp = 0.f;
	}

	SetCurState(HIT, m_eDir);

	m_bHit = true;
	m_fOldHitTime = (float)GetTickCount64();

	m_fJumpPower = 5.f;
	m_bJump = true;
	m_bOnAir = true;
}

bool CPlayer::DecreaseMp(int _iValue)
{
	if (m_tStat.iMp < _iValue)
		return false;

	m_tStat.iMp -= _iValue;

	CUIMgr::Get_Instance()->ChangePlayerMp(m_tStat.iMp, m_tStat.iMaxMp);

	return true;
}

void CPlayer::AddExp(int _iValue)
{
	m_tStat.iExp += _iValue;
	CUIMgr::Get_Instance()->ChangePlayerExp(m_tStat.iExp, m_tStat.iMaxExp);

	if (m_tStat.iExp > m_tStat.iMaxExp)
	{
		int temp = m_tStat.iExp - m_tStat.iMaxExp;
		LevelUp();
		m_tStat.iExp = 0;
		m_tStat.iExp += temp;
		CUIMgr::Get_Instance()->ChangePlayerExp(m_tStat.iExp, m_tStat.iMaxExp);
	}
}

void CPlayer::LevelUp()
{
	++m_tStat.iLevel;
	m_tStat.iMaxExp = m_tStat.iLevel * 200;
}

void CPlayer::IncreaseHp(int _iValue)
{
	m_tStat.iHp += _iValue;
	if (m_tStat.iMaxHp < m_tStat.iHp)
		m_tStat.iHp = m_tStat.iMaxHp;

	CUIMgr::Get_Instance()->ChangePlayerHp(m_tStat.iHp, m_tStat.iMaxHp);
}

void CPlayer::IncreaseMp(int _iValue)
{
	m_tStat.iMp += _iValue;
	if (m_tStat.iMaxMp < m_tStat.iMp)
		m_tStat.iMp = m_tStat.iMaxMp;

	CUIMgr::Get_Instance()->ChangePlayerMp(m_tStat.iMp, m_tStat.iMaxMp);
}

void CPlayer::OnePlayEnd(void)
{
	m_bOnePlay = false;
	m_bStayPlay = false;
	SetCurState(IDLE, m_eDir);
}

void CPlayer::OnCollision(CObj* _pOther)
{
	if (_pOther->Get_Tag() == "Monster")
	{
		// OnHit(_pOther);
	}
	else if (_pOther->Get_Tag() == "Item")
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			_pOther->OnHit(this);
		}
	}



	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		if (_pOther->Get_Tag() == "Portal_1To2")
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_2);
		else if (_pOther->Get_Tag() == "Portal_2To1")
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_1);
		else if (_pOther->Get_Tag() == "Portal_1ToBoss")
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_BOSS);
		else if (_pOther->Get_Tag() == "Portal_BossTo1")
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_1);
		else if (_pOther->Get_Tag() == "Portal_4To1")
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_1);
		else if (_pOther->Get_Tag() == "Portal_1To4")
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_4);
	}

}