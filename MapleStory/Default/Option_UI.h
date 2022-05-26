#pragma once
#include "Obj.h"
#include "SoundButton.h"
class COption_UI :
    public CObj
{
public:
	COption_UI();
	virtual ~COption_UI();

public:
	CSoundButton** GetSoundButton() { return m_pSoundButton; }
	void Open() { m_bIsOpen = true; };
	void Close() { m_bIsOpen = false; };

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual     void	ColRender(HDC hDC) override;

private:
	bool m_bIsOpen;
	CSoundButton* m_pSoundButton[11];
};

 