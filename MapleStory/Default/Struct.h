#pragma once

typedef	struct tagInfo
{
	// �ٴ� ��ǥ
	float	fX;
	float	fY;
	// ��� ũ��
	float   fTCX;
	float   fTCY;

	// �ݸ��� ��ǥ
	float	fCX;
	float	fCY;
	// �ݸ��� ũ��
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
	int		iFrameStart;		// ���ϴ� �������� ��������Ʈ �̹��� ���� ����
	int		iFrameEnd;			// ��������Ʈ�� ������ ������ ����
	int		iMotion;			// ��� �ε���

	DWORD	dwSpeed;			// ��������Ʈ�� ���ư��� �ӵ�
	DWORD	dwTime;				// ��������Ʈ ��ġ�� ����Ǵ� �ð� 

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