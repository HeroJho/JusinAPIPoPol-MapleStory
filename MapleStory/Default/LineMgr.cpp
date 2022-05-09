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

void CLineMgr::Scene_1()
{
	Release();

	LINE		tf{ 0.f, 930.f, 3670.f, 930.f };
	m_LineList.push_back(new CLine(tf));
}

void CLineMgr::Scene_2()
{
	Release();

	LINE		tf{ 0.f, 1570.f, 2238.f, 1570.f };
	m_LineList.push_back(new CLine(tf));
	tf.Init(385.f, 1500.f, 475.f, 1500.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1547, 1387.f, 1705.f, 1387.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init( 1752.f, 1435.f, 1846.f, 1435.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1700.f, 1500.f, 1870.f, 1500.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(373.f, 1270.f, 1859.f, 1270.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(281.f, 1150.f, 417.f, 1150.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(281.f, 1090.f, 417.f, 1090.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(465.f, 1030.f, 1770.f, 1030.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init( 1641.f, 1202.f, 1814.f, 1202.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1694.f, 1136.f, 1786.f, 1136.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(456.f, 1205.f, 549.f, 1205.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(531.f, 963.f, 625.f, 963.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(375.f, 909.f, 507.f, 909.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(375.f, 850.f, 507.f, 850.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(552.f, 787.f, 1678.f, 787.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1559.f, 960.f, 1730.f, 960.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1615.f, 896.f, 1704.f, 896.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(613.f, 724.f, 704.f, 724.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(463.f, 670.f, 597.f, 670.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1457.f, 718.f, 1630.f, 718.f);
	m_LineList.push_back(new CLine(tf));
	tf.Init(1515.f, 655.f, 1605.f, 655.f);
	m_LineList.push_back(new CLine(tf));


	// ��
	tf.Init(1768.f, 1264.f, 1768.f, 1387.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1164.f, 1264.f, 1164.f, 1473.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(419.f, 1264.f, 419.f, 1437.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(825.f, 1025.f, 825.f, 1025.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1645.f, 787.f, 1645.f, 845.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1200.f, 785.f, 1200.f, 957.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(825.f, 1025.f, 825.f, 1200.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1725.f, 1028.f, 1725.f, 1088.f);
	m_HangLineList.push_back(new CLine(tf));
	tf.Init(1199.f, 783.f, 1199.f, 960.f);
	m_HangLineList.push_back(new CLine(tf));

}
