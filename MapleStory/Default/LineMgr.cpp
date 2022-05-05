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
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), CDeleteObj());
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& _fX, float& _fY, float* pY)
{
	// 직선의 방정식
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_LineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	float fMinY = 0.f;
	for (auto& iter : m_LineList)
	{
		// 1. 해당 라인의 x축 범위 안에 있다.
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
		{
			// 2. L- P에서 음수 제외, 차가 제일 작은 라인을 선택한다.

			float	x1 = iter->Get_Info().tLPoint.fX;
			float	x2 = iter->Get_Info().tRPoint.fX;

			float	y1 = iter->Get_Info().tLPoint.fY;
			float	y2 = iter->Get_Info().tRPoint.fY;

			float fTempY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
			
			// 음수면 제외 (선이 플레이어 위에 있다)
			fTempY = fTempY - _fY;
			if (0.f > fTempY)
				continue;

			// 제일 작은지 비교
			if (fTempY < fMinY)
			{
				fMinY = fTempY;
				pTarget = iter;
			}
			else if (!pTarget)
			{
				fMinY = fTempY;
				pTarget = iter;
			}
		}
		
	}
	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_Info().tLPoint.fX;
	float	x2 = pTarget->Get_Info().tRPoint.fX;

	float	y1 = pTarget->Get_Info().tLPoint.fY;
	float	y2 = pTarget->Get_Info().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;

	return true;
}

void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// 파일 경로와 이름 명시
		GENERIC_READ,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		OPEN_EXISTING,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		m_LineList.push_back(new CLine(tInfo));
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), _T("성공"), MB_OK);
}

void CLineMgr::Test_Line()
{
	LINE		tInfo{ 0.f, 500.f, 800.f, 500.f };
	m_LineList.push_back(new CLine(tInfo));

	LINE		tInfo1{ 400.f, 400.f, 500.f, 400.f };
	m_LineList.push_back(new CLine(tInfo1));
}
