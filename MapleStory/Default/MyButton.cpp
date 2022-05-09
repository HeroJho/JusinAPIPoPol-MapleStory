#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCCX = 150.f;
	m_tInfo.fCCY = 150.f;
}

int CMyButton::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{

}

void CMyButton::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)m_tInfo.fCCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����

}

void CMyButton::Release(void)
{

}
