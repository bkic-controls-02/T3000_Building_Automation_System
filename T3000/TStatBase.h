#pragma once



class Mainnet_info
{
//////////////////////////////////////////////////////////////////////////
// �����豸������ϵ����
public:
	Mainnet_info();
	~Mainnet_info();
	DWORD m_dwSerialID;	// ���豸�����������к�
	int m_ProductType;		// ���豸�������Ĳ�Ʒ���ͣ�NC��CM5�ȵ�
	int	 m_nModbusID;		// ���豸���������豸��ַ
	
	CString GetMainnetInfo();
};

class CTStatBase
{
public:
	CTStatBase(void);
	~CTStatBase(void);

	// ��÷���ֵ�ͷ�����Ϣ�ֿ�
	virtual int ReadOneReg(int nRegAddr, OUT int& nVal) = 0;
	virtual int ReadOneReg(int nRegAddr) = 0;
	virtual int WriteOneReg(int nRegAddr, IN int& nVali) = 0;

	virtual int ReadMultiReg(int nRegAddrStart, int nRegAddrEnd, OUT int* nVal) = 0;
	virtual int WriteMultiReg(int nRegAddrStart, int nRegAddrEnd, OUT int* nVal) = 0;

	// дID����д�Ĵ�����YES
	virtual int WriteDevID(int nID)const=0;	
	virtual int ReadDevID(int& nID)=0;

	// Ҳ����ͨ����д�Ĵ�����ʵ��
	virtual BOOL IsOnLine() = 0;	
	
	//---------------------------------------------------------------------------

	virtual int GetDevID()const;	
	virtual void SetDevID(int nID);

	int GetProductType()const;		// ֱ�ӷ��ر�����ͨ��ֻ�е�һ��ȡֵʱ����Ҫ���Ĵ�������ô��������ר�ŵĶ�����
	void SetProductType(int nProductType); // ���ͳ���ʱ���Ѿ�ȷ�����ٸ��ġ�
	
	float GetHardwareVersion()const; // ͬ��
	void SetHardwareVersion(float fHardwareVersion); // ͬ��

	float GetSoftwareVersion()const; // ������Ը��£���ˡ������Ӿ����������
	void SetSoftwareVersion(float fSoftwareVersion); 

	void SetBuildingName(const CString& strBuildingName); 
	CString GetBuildingName()const;

	void SetFloorName(const CString& strFloorName); 
	CString GetFloorName()const;
	
	void SetRoomName(const CString& strRoomName); 
	CString GetRoomName()const;

	void SetSerialID(unsigned int dwSerialID); 
	unsigned int  GetSerialID()const;

	CString GetSubnetName() const;
	void SetSubnetName(const CString& strSubnetName);
	
	CString GetProductCusName() const;
	void SetProductCusName(const CString& strProductCusName);
	
	
	Mainnet_info	m_mainnet_info;
public:
	unsigned int	m_dwSerialID;				// ÿ����Ʒ�����к�ID������ʱ�趨
	int			m_nDevID;					// �豸ID�����豸��������ʱ��ID��������ݱ�����Ĵ���ͬ��
	BOOL		m_bOnLine;					// ����״̬��TRUE�����ߣ�FALSE������
	int			m_nProductType;			//	��Ʒ�ͺţ��ɴ��ж�5A��5B�������ȵȣ������Ƿ���NC
	float		m_fHardware_version;	//  Ӳ���汾��
	float		m_fSoftware_version;	//  ����汾��
	bool		m_cus_name;				//1 �����пͻ��Լ�������;
	CString m_product_cus_name; //�ͻ��Զ��������;
	CString	m_strBuildingName;		// ��������
	CString	m_strFloorName;			// ����¥��
	CString	m_strRoomName;		// ��������
	CString   m_strSubnetName;       // ������

};
