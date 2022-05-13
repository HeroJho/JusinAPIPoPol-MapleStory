#pragma once

typedef	struct tagInfo
{
	// 바닥 좌표
	float	fX;
	float	fY;
	// 출력 크기
	float   fTCX;
	float   fTCY;

	// 콜리젼 좌표
	float	fCX;
	float	fCY;
	// 콜리젼 크기
	float	fCCX;
	float	fCCY;

}INFO;

typedef struct tagStat
{
	int		iHp;
	int		iMaxHp;

	int		iMp;
	int		iMaxMp;

	int		iAt;

	int		iLevel;
	int		iExp;
	int		iMaxExp;

}STAT;

typedef	struct	tagLinePoint 
{
	float		fX;
	float		fY;

	tagLinePoint(){	ZeroMemory(this, sizeof(tagLinePoint));	}
	tagLinePoint(float _fX, float _fY) : fX(_fX) , fY(_fY){	}

}LINEPOINT;

typedef	struct	tagLineInfo 
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLineInfo()	{	ZeroMemory(this, sizeof(tagLineInfo));	}
	tagLineInfo(LINEPOINT& tLeft, LINEPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight)	{	}
	tagLineInfo(float fXL, float fYL, float fXR, float fYR) : tLPoint(fXL, fYL), tRPoint(fXR, fYR) { }
	
	void Init(float fXL, float fYL, float fXR, float fYR)
	{ 
		tLPoint.fX = fXL;
		tLPoint.fY = fYL;
		tRPoint.fX = fXR;
		tRPoint.fY = fYR;
	}
}LINE;

typedef struct tagFrame
{
	int		iFrameStart;		// 원하는 지점부터 스프라이트 이미지 구동 시작
	int		iFrameEnd;			// 스프라이트가 끝나는 지점을 지정
	int		iMotion;			// 모션 인덱스

	DWORD	dwSpeed;			// 스프라이트가 돌아가는 속도
	DWORD	dwTime;				// 스프라이트 위치가 변경되는 시간 

}FRAME;

typedef struct itemInfo
{
	ITEMID eID;
	int iCount;
	string sTag;
	int InvenID;

}ITEM;

typedef struct skillInfo
{
	SKILLID eID;
	int iAt;
	int iMonCount;
	float m_fCoolDown;
	float m_fOldCoolDown;
	bool  m_bCanUse;

	void Init(SKILLID _eID, int _iAt, int _iMonCount, float _fCoolDown)
	{
		eID = _eID;
		iAt = _iAt;
		iMonCount = _iMonCount;
		m_fCoolDown = _fCoolDown;
		m_bCanUse = true;
	}
	void Change(int _iAt, int _iMonCount, float _fCoolDown)
	{
		iAt = _iAt;
		iMonCount = _iMonCount;
		m_fCoolDown = _fCoolDown;
		m_bCanUse = true;
	}

}SKILL;