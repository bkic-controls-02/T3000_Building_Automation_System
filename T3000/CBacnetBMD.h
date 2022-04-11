#pragma once
#define TYPE_BM_POINT_LIST  255
#define TYPE_BM_GROUP       0
#define TYPE_BM_NODES       1
#define TYPE_BM_INPUT       2
#define TYPE_BM_OUTPUT      3
#define TYPE_BM_VARIABLE    4
class CBacnetBMD
{
public:
	CBacnetBMD(void);
	~CBacnetBMD(void);
	CString m_csName;  //�ڵ�����;
	int m_index;  //�ڵ�����;
	int m_child_count;  //�ӽڵ�ĸ���;
	int m_input_count;  //����ĸ���;
	int m_output_count; //����ĸ���;
	int m_variable_count; //�����ĸ���;
	int m_node_type;   //�ڵ����� ��group ����device ����IO  ���� input
	HTREEITEM hParent;
	HTREEITEM h_treeitem;
	CBacnetBMD* pfather;
	CBacnetBMD* pchild[255];
	void UpdateCount();
	int m_floor;  //ָʾBuild view �� ��������һ ��¥
	int m_room;   //ָʾBuild view �� ��������һ ������
};

