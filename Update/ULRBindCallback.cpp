#include "ULRBindCallback.h"
void CUrlDownloadToFileCallbackTestDlg::DownloadButton()//���ذ�ť,Ҳ����Ϊ�߳�
{
CBindCallback cbc;
cbc.m_pdlg = this;

(this->GetDlgItem(IDC_START))->EnableWindow(FALSE);//�������ذ�ť

//��url��������������ֹ��IE�����ж�ȡ��url������������Ӱ�����صġ�
//�����Ҫ�ӻ�������ȡ��ô�Ͱ������ע�͵�
CString szRand;
szRand.Format(_T("?skq=%d"),GetTickCount());
szUrl += szRand;

if(S_OK == URLDownloadToFile(NULL,szURL,szPath,0,&cbc))//szURL,szPathΪȫ�ֱ���
MessageBox("finished");

}

