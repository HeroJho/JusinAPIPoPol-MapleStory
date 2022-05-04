#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 5.f;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	/*float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	
	float		fRadian = acosf(fWidth / fDiagonal);	// acos값으로 나올 수 있는 각도의 범위는 0~180도 사이 값에 해당한다.

	/ *if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		fRadian = (2 * PI) - fRadian;* /	

	// 라디안 값을 디그리로 치환
	m_fAngle = (fRadian * 180.f) / PI;

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;
	
	m_tInfo.fX += m_fSpeed * cosf((m_fAngle) * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle)* PI / 180.f);*/

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	/*if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
		m_fSpeed *= -1.f;*/
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	
}
