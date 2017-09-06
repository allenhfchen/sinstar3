#pragma once
#include "../include/sinstar-i.h"

#include "ui/InputWnd.h"
#include "ui/StatusWnd.h"

#include "InputState.h"

class CSinstar3Impl:
	public ISinstar,
	public IInputListener,
	public SOUI::SObject,
	public SOUI::CSimpleWnd
{
public:
	CSinstar3Impl(ITextService *pTxtSvr);
	virtual ~CSinstar3Impl(void);

	virtual void OnIMESelect(BOOL bSelect);
	virtual void OnCompositionStarted();
	virtual void OnCompositionChanged();
	virtual void OnCompositionTerminated();
	virtual void OnSetCaretPosition(POINT pt,int nHei);
	virtual void OnSetFocusSegmentPosition(POINT pt,int nHei);
	virtual void ProcessKeyStoke(LPVOID lpImeContext,UINT vkCode,LPARAM lParam,BOOL bKeyDown,BOOL *pbEaten);
	virtual void TranslateKey(LPVOID lpImeContext,UINT vkCode,UINT uScanCode,BOOL bKeyDown,BOOL *pbEaten);
	virtual void OnSetFocus(BOOL bFocus);
	virtual int  GetCompositionSegments();
	virtual int  GetCompositionSegmentEnd(int iSeg);
	virtual int	 GetCompositionSegmentAttr(int iSeg);
	virtual BOOL OnHotkey(LPVOID lpImeContext,REFGUID guidHotKey);
	virtual void OnOpenStatusChanged(BOOL bOpen);
	virtual void OnConversionModeChanged(EInputMethod uMode);
	virtual void CheckDefIME();
	virtual void ShowHelp();
	virtual EInputMethod GetDefInputMode();
	virtual BOOL ShowCompWnd();
	virtual LRESULT OnWildMessage(WPARAM wParam,LPARAM lParam);

public:
	virtual void OnFinalRelease();
	virtual HRESULT OnQueryInterface(REFIID riid, void **ppvObject);

	virtual int GetID() const {	return SENDER_SINSTSR3;}
protected:
	virtual HWND GetHwnd() const;
	virtual void OnInputStart();
	virtual void OnInputEnd(const SStringT & strInput);
	virtual BOOL GoNextCandidatePage();
	virtual BOOL GoPrevCandidatePage();
	virtual short SelectCandidate(UINT vKey,const BYTE * lpbKeyState);

public:
	LRESULT OnSvrNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BEGIN_MSG_MAP_EX(CSinstar3Impl)
		MESSAGE_HANDLER_EX(ISComm_GetCommMsgID(),OnSvrNotify)
		CHAIN_MSG_MAP(SOUI::CSimpleWnd)
	END_MSG_MAP()



private:
	ITextService	*m_pTxtSvr;
	CInputWnd		*m_pInputWnd;
	CStatusWnd		*m_pStatusWnd;

	CInputState		m_inputState;

	void			*m_pCurImeContext;

};



