
//////////////////////////////////////////////////////////////////////////
//  
// �������Ĳ�ͬ��һ������
// 1�����������⻬����������Խ�����ڵ����������顣
// 2���������������˻��飨LButtonDown�����û���ͳ�Ϊ���㻬�顣
// 3�����������������ʱ�����㻬���ܹ��ƶ����ǽ��㻬�鲻����
// 4��ע�⣬��������yֵ����Ϊ����������slide�̶����ϵ�������ˣ���Ҫʱ��ע�������ת��
//
//
//
//

#pragma once
#include "thumboperator.h"


class CFSBThumb;
class CMultiThumbOpt :
	public CThumbOperator
{
public:
	CMultiThumbOpt(void);
	virtual ~CMultiThumbOpt(void);

	virtual COLORREF GetThumbColor();
	virtual void SetThumbColor(COLORREF clr);
	virtual int GetThumbWidth();
	virtual void SetThumbWidth(int nWidth);
	virtual void SetThumbShape(FSB_THUMBSHAPE tbShape);
	virtual void Draw(CDC* pDC);
	virtual BOOL InitThumb(BOOL bHorizontal, int nThumbWidth, CRect& rcChannel);
	virtual void MovePage(const CPoint& pt);
	virtual void MoveNextStep();
	virtual void MovePreStep();
	virtual void OnLButtonDown(const CPoint& point);
	virtual void OnMouseMove(const CPoint& point);
	virtual void OnLButtonUp(const CPoint& point);
	virtual void SetTicsArray(vector<int>& szTics);
	// ���᷵�ص�ǰ��Ծ
	virtual int GetThumbNum();
	virtual int GetThumbPosition();	
	virtual int GetAllThumbPosition(vector<int>& szThumbPos);	
	virtual void SetThumbPosition(int nIndex, int nPosition);	

	virtual void CalcThumbPosition();
	//////////////////////////////////////////////////////////////////////////
	// non virtual function
	// ����Thumb�ĸ���
	void SetThumbNum(int nThumbNum);
    
protected:

	// ���һ��Thumb�����ƶ����ı߽�ֵ(�̶ȵ�λ)�����������ڵ�����Thumb�Ŀ̶�λ�ã�Position�����������غϣ�
	// param1: nInded , thumb ������������thumb�����е�λ�ã����ݹ涨�����е�thumb������Խ���������ڵ�thumb��
	// param2: nMin, �±߽磬thumb�����ƶ�������С�Ŀ̶�λ��
	// param3: nMax,�ϱ߽磬thumb�����ƶ��������Ŀ̶�λ��
	//
	void GetThumbRange(int nIndex, int& nMin, int& nMax);
	int GetFocusThumb(const CPoint& point);
	void MoveToPosition(int nIndex, int nPosition);
	int SearchThumbPosition(const CPoint& pt);
	void ReCalcChannelRect();
    
protected:
	
	vector<int>*					m_szTicMarks;  // λ�������ض�Ӧ������

	vector<CFSBThumb*>				m_szThumb;

	int								m_nFocusThumb;
   /* int m_nMinPos;
    int m_nMidPos;
    int m_nMaxPos;*/
};
