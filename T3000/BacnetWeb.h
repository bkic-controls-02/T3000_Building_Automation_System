#pragma once
#include "CWebBrowser2.h"

// CBacnetWeb �Ի���

class CBacnetWeb : public CDialogEx
{
	DECLARE_DYNAMIC(CBacnetWeb)

public:
	CBacnetWeb(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBacnetWeb();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WEB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    CWebBrowser2 m_browser;
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
