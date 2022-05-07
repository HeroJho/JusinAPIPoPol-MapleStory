#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	Test_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);

	for (auto& iter : m_HangLineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();

	for_each(m_HangLineList.begin(), m_HangLineList.end(), CDeleteObj());
	m_HangLineList.clear();
}

CLine* CLineMgr::Collision_Line(float& _fX, float& _fY, float* pY, bool _bGetSecond)
{
	// ������ ������
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;
	CLine*		pSecondTarget = nullptr;

	float fMinY = 0.f;
	for (auto& iter : m_LineList)
	{
		// 1. �ش� ������ x�� ���� �ȿ� �ִ�.
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			// 2. L- P���� ���� ����, ���� ���� ���� ������ �����Ѵ�.
			float	x1 = iter->Get_Info().tLPoint.fX;
			float	x2 = iter->Get_Info().tRPoint.fX;

			float	y1 = iter->Get_Info().tLPoint.fY;
			float	y2 = iter->Get_Info().tRPoint.fY;

			float fTempY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
			
			// ������ ���� (���� �÷��̾� ���� �ִ�)
			fTempY = fTempY - _fY;
			if (-3.f > fTempY)
				continue;

			// ���� ������ ��
			if (fTempY < fMinY)
			{
				fMinY = fTempY;
				pSecondTarget = pTarget;
				pTarget = iter;
			}
			else if (!pTarget)
			{
				fMinY = fTempY;
				pTarget = iter;
			}
		}
		
	}

	if (!pSecondTarget)
		pSecondTarget = pTarget;

	if (_bGetSecond)
	{
		float	x1 = pSecondTarget->Get_Info().tLPoint.fX;
		float	x2 = pSecondTarget->Get_Info().tRPoint.fX;

		float	y1 = pSecondTarget->Get_Info().tLPoint.fY;
		float	y2 = pSecondTarget->Get_Info().tRPoint.fY;
		*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	}
	else
	{
		float	x1 = pTarget->Get_Info().tLPoint.fX;
		float	x2 = pTarget->Get_Info().tRPoint.fX;

		float	y1 = pTarget->Get_Info().tLPoint.fY;
		float	y2 = pTarget->Get_Info().tRPoint.fY;
		*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	}

	return _bGetSecond ? pSecondTarget : pTarget;
}

CLine* CLineMgr::Collision_HangLine(float& _fX, float& _fY, float* pY)
{
	// ������ ������
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_HangLineList.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_HangLineList)
	{
		// 1. �ش� ������ x��, y�� ���� �ȿ� �ִ�. >> ���� Ż �� �ִ�
		if (_fX >= iter->Get_Info().tLPoint.fX - 20.f &&
			_fX <= iter->Get_Info().tRPoint.fX + 20.f &&
			_fY >= iter->Get_Info().tLPoint.fY - 5.f &&
			_fY <= iter->Get_Info().tRPoint.fY)
		{
			pTarget = iter;
		}

	}

	if (pTarget)
	{
		float	x1 = pTarget->Get_Info().tLPoint.fX;
		float	x2 = pTarget->Get_Info().tRPoint.fX;

		float	y1 = pTarget->Get_Info().tLPoint.fY;
		float	y2 = pTarget->Get_Info().tRPoint.fY;
		*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	}

	return pTarget;
}


void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

void CLineMgr::Test_Line()
{
	LINE		tf{ 0.f, 1000.f, 5830.f, 1000.f };
	m_LineList.push_back(new CLine(tf));


	LINE		tInfo{ 0.f, 500.f, 800.f, 500.f };
	m_LineList.push_back(new CLine(tInfo));
	LINE		tInfo1{ 300.f, 400.f, 500.f, 400.f };
	m_LineList.push_back(new CLine(tInfo1));
	LINE		tInfo3{ 500.f, 400.f, 600.f, 300.f };
	m_LineList.push_back(new CLine(tInfo3, true));
	LINE		tInfo2{ 100.f, 350.f, 400.f, 350.f };
	m_LineList.push_back(new CLine(tInfo2));
	LINE		tInfo4{ 500.f, 200.f, 600.f, 200.f };
	m_LineList.push_back(new CLine(tInfo4));

	LINE		tInfo5{ 150.f, 350.f, 150.f, 450.f };
	m_HangLineList.push_back(new CLine(tInfo5));

	LINE		tInfo6{ 100.f, 50.f, 400.f, 50.f };
	m_LineList.push_back(new CLine(tInfo6));
	LINE		tInfo7{ 200.f, 50.f, 200.f, 300.f };
	m_HangLineList.push_back(new CLine(tInfo7));
}
