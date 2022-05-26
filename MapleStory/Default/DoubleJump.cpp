#include "stdafx.h"
#include "DoubleJump.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"


CDoubleJump::CDoubleJump()
{
}

CDoubleJump::~CDoubleJump()
{
	Release();
}

void CDoubleJump::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_PEFFECT2);
	CSoundMgr::Get_Instance()->PlaySound(L"DoubleJump.wav", SOUND_PEFFECT2, 1);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/DoubleJump/DoubleJumpL.bmp", L"DoubleJumpL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/DoubleJump/DoubleJumpR.bmp", L"DoubleJumpR");
	Set_FrameKey(L"DoubleJumpL");
	m_bOnePlay = true;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.dwTime = GetTickCount64();


	// �ݸ��� ũ��, �Ǻ� ����
	m_tInfo.fCCX = 10.f;
	m_tInfo.fCCY = 10.f;
	m_tColPivot.x = 0.f;
	m_tColPivot.y = -30.f;
	// �ؽ��� ũ�� ����
	m_tInfo.fTCX = 250.f;
	m_tInfo.fTCY = 150.f;

	Set_Stat(0, 0, 0);
	m_fSpeed = 0.f;

	m_bCanHit = false;
	m_CanHitCount = 0;
	m_CanHitMaxCount = -1;

	m_pOldLine = nullptr;
	m_bJump = false;
	m_bOnAir = false;
	m_fValY = 0.f;
	m_fAirTime = 0.f;

	m_fOldSkillTime = GetTickCount64();
	m_fSkillTime = 100.f;
	m_fDeleteTime = 450.f;

	m_bOnePos = false;
}

int CDoubleJump::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bOnePos)
	{
		m_tInfo.fX = m_pTarget->Get_Info().fX;
		m_tInfo.fY = m_pTarget->Get_Info().fY;
		m_bOnePos = true;
		SetFrameDir(m_pTarget->Get_Dir());
	}
	

	if (m_pTarget->Get_Dir() == DIR_LEFT)
	{
		m_tColPivot.x = -40.f;
		m_tColPivot.y = -25.f;
	}
	else
	{
		m_tColPivot.x = 40.f;
		m_tColPivot.y = -25.f;
	}


	// ��Ʈ �ð�
	if (m_fOldSkillTime + m_fSkillTime < GetTickCount64() && !m_bJump)
	{
		m_bCanHit = true;
		m_bJump = true;
	}
	// �Ҹ� �ð�
	if (m_fOldSkillTime + m_fDeleteTime < GetTickCount64())
	{
		m_bDead = true;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CDoubleJump::Late_Update(void)
{
	if (!m_bStayPlay)
		Move_Frame();
}

void CDoubleJump::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	int left = 0;
	if (m_eDir == DIR_LEFT)
	{
		left = m_tTRect.left + iScrollX + 100;
	}
	else
	{
		left = m_tTRect.left + iScrollX - 100;
	}

	GdiTransparentBlt(hDC, 									// ���� ����, ���������� �׸��� �׸� DC
		left,					// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tTRect.top - 20 + iScrollY),
		int(m_tInfo.fTCX),								// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fTCY),
		hMemDC,											// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fTCX,		// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fTCY,
		(int)m_tInfo.fTCX,								// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fTCY,
		RGB(255, 0, 255));								// �����ϰ��� �ϴ� ����
}

void CDoubleJump::Release(void)
{
}

void CDoubleJump::OnCollision(CObj* _pOther)
{
	/*if (m_CanHitCount > m_CanHitMaxCount)
		return;
	if (!_pOther->Get_CanHit())
		return;

	++m_CanHitCount;

	if (_pOther->Get_Tag() == "Monster")
	{
		_pOther->OnHit(this);
	}*/
}


void CDoubleJump::SetFrameDir(DIRECTION _eDir)
{
	if (_eDir == DIR_LEFT)
		m_pFrameKey = L"DoubleJumpL";
	else
		m_pFrameKey = L"DoubleJumpR";

	m_eDir = _eDir;
}

void CDoubleJump::Motion_Change(void)
{

}
