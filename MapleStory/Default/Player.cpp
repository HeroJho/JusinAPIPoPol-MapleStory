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
#include "SlotMgr.h"
#include "LevelUp.h"
#include "SoundMgr.h"
#include "Fall.h"
#include "SceneMgr.h"
#include "Damge.h"


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
	, m_bHold(false)
	, m_bHitAnim(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::ResetDead()
{
	IncreaseHp(CStatMgr::Get_Instance()->Get_PlayerMaxHP());
	IncreaseMp(CStatMgr::Get_Instance()->Get_PlayerMaxMP());
	
	SetCurState(HIT, m_eDir);

	m_bHit = true;
	m_fOldHitTime = (float)GetTickCount64();
	m_fOldHitAnimTime = GetTickCount64();
}

void CPlayer::Initialize(void)
{
	CSkillMgr::Get_Instance()->Initialize();


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
	
	Set_Stat(5, 200, 10);

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

	m_fHitAnimTime = 100.f;
	m_fOldHitAnimTime = 0.f;
	m_fRotAngle = 0.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	// 연산을 진행
	if (m_eCurState == DEAD)
	{
		Update_Rect();
		return OBJ_NOEVENT;
	}

		

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
	if (m_eCurState == DEAD)
	{
		Update_Gravity();
		return;
	}


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


	if (m_eCurState == DEAD)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerDead");

		m_fRotAngle += 2.f;

		int fX = 20 * cosf((m_fRotAngle)*PI / 180.f);
		int fY = 20 * sinf((m_fRotAngle)*PI / 180.f);

		GdiTransparentBlt(hDC,
			int(m_tTRect.left + iScrollX) + 65 + fX,
			int(m_tTRect.top - 37 + iScrollY) + 20 + fY,
			60,
			80,
			hMemDC,
			0,
			0,
			60,
			80,
			RGB(255, 0, 255));
		return;
	}


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (m_bHit)
	{
		if (m_fOldHitAnimTime + m_fHitAnimTime < GetTickCount64())
		{
			if (m_bHitAnim)
				m_bHitAnim = false;
			else
				m_bHitAnim = true;

			m_fOldHitAnimTime = GetTickCount64();
		}

		if (m_bHitAnim)
		{
			if(m_eDir == DIR_LEFT)
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerPainL");
			else
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerPainR");

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
				RGB(165, 0, 165));
		}
		else
		{
			if (m_eDir == DIR_LEFT)
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerPainPL");
			else
				hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerPainPR");

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

	}
	else
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

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

	if (CSceneMgr::Get_Instance()->Get_CurSceneId() != SC_ENDING)
	{
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

}
void CPlayer::Release(void)
{

}


void CPlayer::SetCurState(STATE _eState, DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
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

		if (m_eCurState != ATTACK && m_eCurState != SKILL && m_eCurState != DEAD)
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

			if (m_eDoubleDir == DIR_LEFT)
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
		m_pHangLine = nullptr;
		m_fValY = 0.f;
	}
	else if (m_fDropY > m_tInfo.fY)
	{	// 공중일 때
		// 이전 라인이랑 같고,           대각선일때
		if (!(m_pOldLine == m_pCurLine && m_pCurLine->Get_Diagonal()))
		{
			m_bOnAir = true;
			m_pHangLine = nullptr;
		}
	}

	if (!m_bOnAir)
	{
		m_tInfo.fY = m_fDropY;
		m_pDropLine = nullptr;
		m_pHangLine = nullptr;
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
		m_pHangLine = nullptr;
		return;
	}

	m_tInfo.fX = m_pHangLine->Get_Info().tLPoint.fX;

	m_pDropLine = nullptr;
	m_bDrop = false;
	m_bJump = false;
	m_bDoubleJump = false;
	m_eDoubleDir = DIR_END;
	m_fValY = 2.f;
	if (m_eCurState != HANGWALK)
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
	if (m_bHold)
		return;

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
			if (!m_bDrop)
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
				CSoundMgr::Get_Instance()->PlaySound(L"Jump.wav", SOUND_PEFFECT3, 1);
			}

			m_bDrop = true;
			m_bOnAir = true;
		}
		else if(!m_bJump)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Jump.wav", SOUND_PEFFECT3, 1);

			m_fJumpPower = 9.2f;
			m_bJump = true;
			m_bOnAir = true;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_UP) || CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
	{
		SetCurState(HANGIDLE, m_eDir);
	}

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		CSlotMgr::Get_Instance()->UseA();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		CSlotMgr::Get_Instance()->UseS();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		CSlotMgr::Get_Instance()->UseD();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		CSlotMgr::Get_Instance()->UseZ();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		CSlotMgr::Get_Instance()->UseX();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		CSlotMgr::Get_Instance()->UseC();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSlotMgr::Get_Instance()->Use1();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSlotMgr::Get_Instance()->Use2();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSlotMgr::Get_Instance()->Use3();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		CSlotMgr::Get_Instance()->Use4();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		CSlotMgr::Get_Instance()->Use5();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('6'))
	{
		CSlotMgr::Get_Instance()->Use6();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		CObj* pSkill = CAbstractFactory<CSkill>::Create(m_tInfo.fX, m_tInfo.fY, "Skill");
		pSkill->Set_Target(this);
		((CSkill*)pSkill)->Set_SkillInfo(CStatMgr::Get_Instance()->Get_PlayerAT(), 1);
		CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);
		SetStateAttack();

		CSkillMgr::Get_Instance()->CreateVect();
		CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Attack.wav", SOUND_PEFFECT, 1);
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
	if (m_eCurState == DEAD)
		return;

	if (m_bHit)
		return;

	m_tStat.iHp -= _pOther->Get_Stat().iAt;
	CUIMgr::Get_Instance()->ChangePlayerHp(m_tStat.iHp, CStatMgr::Get_Instance()->Get_PlayerMaxHP());

	CDamge* pDamage = (CDamge*)CAbstractFactory<CDamge>::Create(m_tInfo.fX, m_tInfo.fY - 60.f);
	pDamage->Init(_pOther->Get_Stat().iAt * _pOther->Get_Stat().iAt, _pOther->Get_Stat().iAt * _pOther->Get_Stat().iAt * 10, 9);
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILLE, pDamage);


	// CUIMgr::Get_Instance()->MakeDamge(5, 1.f, _pOther->Get_Stat().iAt * 34, _pOther->Get_Stat().iAt * 64, m_tInfo.fX, m_tInfo.fY, 120.f, 35.f);
	if (m_tStat.iHp <= 0.f)
	{
		m_tStat.iHp = 0.f;
		m_bDoubleJump = false;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFall>::Create(m_tInfo.fX, m_tInfo.fY - 250.f));
		SetCurState(DEAD, m_eDir);
		CUIMgr::Get_Instance()->OpenDead();
		return;
	}

	SetCurState(HIT, m_eDir);

	m_bHit = true;
	m_fOldHitTime = (float)GetTickCount64();
	m_fOldHitAnimTime = GetTickCount64();

	m_fJumpPower = 5.f;
	m_bJump = true;
	m_bOnAir = true;
}

void CPlayer::OnHit(int _iValue)
{
	if (m_eCurState == DEAD)
		return;

	m_tStat.iHp -= _iValue;
	CUIMgr::Get_Instance()->ChangePlayerHp(m_tStat.iHp, CStatMgr::Get_Instance()->Get_PlayerMaxHP());
	CUIMgr::Get_Instance()->MakeDamge(5, 1.f, _iValue * 34, _iValue * 64, m_tInfo.fX, m_tInfo.fY, 120.f, 35.f);
	if (m_tStat.iHp <= 0.f)
	{
		m_tStat.iHp = 0.f;
		m_bDoubleJump = false;
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CFall>::Create(m_tInfo.fX, m_tInfo.fY - 250.f));
		SetCurState(DEAD, m_eDir);
		CUIMgr::Get_Instance()->OpenDead();
		return;
	}

	SetCurState(HIT, m_eDir);

	m_bHit = true;
	m_fOldHitTime = (float)GetTickCount64();
	m_fOldHitAnimTime = GetTickCount64();

	m_fJumpPower = 5.f;
	m_bJump = true;
	m_bOnAir = true;
}

bool CPlayer::DecreaseMp(int _iValue)
{
	if (m_tStat.iMp < _iValue)
		return false;

	m_tStat.iMp -= _iValue;

	CUIMgr::Get_Instance()->ChangePlayerMp(m_tStat.iMp, CStatMgr::Get_Instance()->Get_PlayerMaxMP());

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

	CStatMgr::Get_Instance()->AddStatPoint(10);
	CStatMgr::Get_Instance()->AddSkillPoint(5);

	IncreaseHp(CStatMgr::Get_Instance()->Get_PlayerMaxHP());
	IncreaseMp(CStatMgr::Get_Instance()->Get_PlayerMaxMP());


	CObj* pSkill = CAbstractFactory<CLevelUp>::Create(m_tInfo.fX, m_tInfo.fY, "Skill");
	pSkill->Set_Target(this);
	((CSkill*)pSkill)->Set_SkillInfo(500, 45);
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, pSkill);
}

void CPlayer::IncreaseHp(int _iValue)
{
	m_tStat.iHp += _iValue;
	if (CStatMgr::Get_Instance()->Get_PlayerMaxHP() < m_tStat.iHp)
		m_tStat.iHp = CStatMgr::Get_Instance()->Get_PlayerMaxHP();

	CUIMgr::Get_Instance()->ChangePlayerHp(m_tStat.iHp, CStatMgr::Get_Instance()->Get_PlayerMaxHP());
}

void CPlayer::IncreaseMp(int _iValue)
{
	m_tStat.iMp += _iValue;
	if (CStatMgr::Get_Instance()->Get_PlayerMaxMP() < m_tStat.iMp)
		m_tStat.iMp = CStatMgr::Get_Instance()->Get_PlayerMaxMP();

	CUIMgr::Get_Instance()->ChangePlayerMp(m_tStat.iMp, CStatMgr::Get_Instance()->Get_PlayerMaxMP());
}

void CPlayer::OnePlayEnd(void)
{
	m_bOnePlay = false;
	m_bStayPlay = false;
	SetCurState(IDLE, m_eDir);
}

void CPlayer::OnCollision(CObj* _pOther)
{
	if (m_eCurState == DEAD)
		return;

	if (_pOther->Get_Tag() == "Monster")
	{
		// OnHit(_pOther);
	}
	else if (_pOther->Get_Tag() == "Item")
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		{
			_pOther->OnHit(this);
		}
	}



	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		if (_pOther->Get_Tag() == "Portal_1To2")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_2);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_2To1")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_1);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_4To3")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_3);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_3To4")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_4);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_4To5")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_5);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_5To3")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_3);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_5To6")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_6);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_6To5")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_5);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_6To7")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_7);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_7To6")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_6);
			CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
		else if (_pOther->Get_Tag() == "Portal_7ToBoss")
		{
			CEventMgr::Get_Instance()->AddSceneChangeEvent(SC_STAGE_COO);
			//CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT3);
			//CSoundMgr::Get_Instance()->PlaySound(L"Portal.wav", SOUND_PEFFECT3, 1);
		}
	}

}