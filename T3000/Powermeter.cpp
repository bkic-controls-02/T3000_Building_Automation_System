// Powermeter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "T3000.h"
#include "Powermeter.h"
#include "afxdialogex.h"


// CPowermeter �Ի���

IMPLEMENT_DYNAMIC(CPowermeter, CFormView)

CPowermeter::CPowermeter(CWnd* pParent /*=NULL*/)
	: CFormView(CPowermeter::IDD)
{

}

CPowermeter::~CPowermeter()
{
}

void CPowermeter::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPowermeter, CFormView)
END_MESSAGE_MAP()


// CPowermeter ��Ϣ�������

void CPowermeter::Fresh()
{

}

void CPowermeter::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
}
