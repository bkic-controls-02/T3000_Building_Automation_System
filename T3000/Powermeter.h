#pragma once


// CPowermeter �Ի���

class CPowermeter : public CFormView
{
	DECLARE_DYNAMIC(CPowermeter)

public:
	CPowermeter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPowermeter();


    enum { IDD = IDD_DIALOG_POWER_METER};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()

public:
    void Fresh();
};
