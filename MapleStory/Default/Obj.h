#pragma once

#include "Include.h"

#include "LineMgr.h"
#include "Line.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION eDir) { m_eDir = eDir; }
	void		Set_Dead()				{ m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void		Set_Tag(string _sTag) { m_sTag = _sTag; }
	void		Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	void		Set_Stat(int _iMaxHp, int _iAt);

	bool		Get_Dead() { return m_bDead; }

	float Get_ColPosX() { return m_tInfo.fCX; }
	float Get_ColPosY() { return m_tInfo.fCY; }

	const string Get_Tag() { return m_sTag; }

	const STAT&		Get_STAT(void) const { return m_tStat; }
	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }


public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

	void	ColRender(HDC hDC);

	virtual		void	OnCollision(CObj* _pOther) {};

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);
	void		Update_Gravity(void);

protected:
	INFO		m_tInfo;
	STAT		m_tStat;
	RECT		m_tRect;
	RECT		m_tTRect;		// �ؽ��� ��Ʈ
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fAngle;

	DIRECTION	m_eDir;
	bool		m_bDead;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	POINT       m_tColPivot;
	string		m_sTag;

protected:
	bool					m_bJump;
	bool					m_bOnAir;		// ���� ���� Ȯ��
	float					m_fJumpPower;	// ���� ��
	float					m_fAirTime;	// ���� �� ���� �ð�
	float					m_fValY;

	CLine*					m_pOldLine;
};

