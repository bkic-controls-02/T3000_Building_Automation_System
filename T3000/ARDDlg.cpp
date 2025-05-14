// ARDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T3000.h"
#include "ARDDlg.h"
#include "afxdialogex.h"

#include "timer.h"
 
#include "../SQLiteDriver/CppSQLite3.h"
// CARDDlg dialog
int Remote_Get_PanelName(unsigned char nmodbusid, unsigned char npid_type, CString& ret_name);
IMPLEMENT_DYNAMIC(CARDDlg, CDialogEx)

CARDDlg::CARDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CARDDlg::IDD, pParent)
    , m_Serial_Number(0)
    , m_type_id(_T(""))
{

}

BOOL CARDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetSerialComPortNumber1(m_szComm);
	for (UINT i = 0; i < m_szComm.size(); i++)
	{
		m_add_device_com_port.AddString(m_szComm[i]);
	}
	m_add_device_com_port.SetCurSel(0);
    

	m_add_device_baudrate.InsertString(0,_T("9600"));
	m_add_device_baudrate.InsertString(1,_T("19200"));
	m_add_device_baudrate.InsertString(2,_T("38400"));
	m_add_device_baudrate.InsertString(3,_T("57600"));
    m_add_device_baudrate.InsertString(4,_T("76800"));
	m_add_device_baudrate.InsertString(5,_T("115200"));
	m_add_device_baudrate.SetCurSel(1);
	m_add_device_modbus_id.SetWindowText(_T("255"));

	CString	g_configfile_path = g_strExePth + _T("") MY_CONFIG;
	CString strIP;
	int IPPort;
	GetPrivateProfileString(_T("MBPOLL_Setting"), _T("IP Address"), _T("127.0.0.1"), strIP.GetBuffer(MAX_PATH), MAX_PATH, g_configfile_path);
	IPPort = GetPrivateProfileInt(_T("MBPOLL_Setting"), _T("IP Port"), 6001, g_configfile_path);

	m_ipaddress.SetWindowText(strIP);
	strIP.Format(_T("%d"), IPPort);
	m_porteditor.SetWindowText(strIP);
    m_minipanel_comport.SetCurSel(0);
	((CButton *)GetDlgItem(IDC_RADIO_NET_DEVICE))->SetCheck(TRUE);//ѡ��
	
    OnCbnDropdownComboProductName();
	((CEdit*)GetDlgItem(IDC_EDIT_TYPE_ID))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_SERIAL_NUMBER))->SetReadOnly(TRUE);
	strIP.Format(_T("%d"), GetNewSerialNumber());
	GetDlgItem(IDC_EDIT_SERIAL_NUMBER)->SetWindowText(strIP);




	//if (offline_mode)
	//{
	//	GetDlgItem(IDOK)->SetWindowTextW(L"Add");

	//	GetDlgItem(IDC_RADIO_NET_DEVICE)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_PORT)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_COMBO_ADD_DEVICE_COMPORT)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_COMBO_ADD_DEVICE_BAUDRATE)->EnableWindow(FALSE);

	//}
	//else
	//{
		GetDlgItem(IDOK)->SetWindowTextW(L"Connect");
		GetDlgItem(IDC_RADIO_NET_DEVICE)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS1)->EnableWindow(TRUE);
		GetDlgItem(IDC_PORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_ADD_DEVICE_COMPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_ADD_DEVICE_BAUDRATE)->EnableWindow(TRUE);
	//}
    Enable_Net_UI(true);
	return TRUE; 
}

void CARDDlg::Enable_Net_UI(bool enable_net)
{
	m_is_net_device = enable_net;
	if(enable_net)
	{
		m_ipaddress.EnableWindow(1);
		m_porteditor.EnableWindow(1);
        m_minipanel_comport.EnableWindow(1);
		m_add_device_com_port.EnableWindow(0);
		m_add_device_baudrate.EnableWindow(0);
		//m_add_device_modbus_id.EnableWindow(0);
	}
	else
	{
		m_ipaddress.EnableWindow(0);
		m_porteditor.EnableWindow(0);
        m_minipanel_comport.EnableWindow(0);
		m_add_device_com_port.EnableWindow(1);
		m_add_device_baudrate.EnableWindow(1);
		//m_add_device_modbus_id.EnableWindow(1);
	}
}

CARDDlg::~CARDDlg()
{
}

void CARDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddress);
	DDX_Control(pDX, IDC_PORT, m_porteditor);
	DDX_Control(pDX, IDC_COMBO_ADD_DEVICE_COMPORT, m_add_device_com_port);
	DDX_Control(pDX, IDC_COMBO_ADD_DEVICE_BAUDRATE, m_add_device_baudrate);
	DDX_Control(pDX, IDC_EDIT_ADD_DEVICE_MODBUS_ID, m_add_device_modbus_id);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NUMBER, m_Serial_Number);
	DDX_Text(pDX, IDC_EDIT_TYPE_ID, m_type_id);
	DDX_Control(pDX, IDC_COMBO_PRODUCT_NAME, m_combox_productname);
	DDX_Control(pDX, IDC_COMBO1, m_minipanel_comport);
	//  DDX_Control(pDX, IDC_CHECK_ONLINE_OFFLINE, m_offlineButton);
}


BEGIN_MESSAGE_MAP(CARDDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CARDDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_NET_DEVICE, &CARDDlg::OnBnClickedRadioNetDevice)
	ON_BN_CLICKED(IDC_RADIO2, &CARDDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON_LOCAL_MSTP_DEVICE, &CARDDlg::OnBnClickedButtonLocalMstpDevice)
    ON_CBN_DROPDOWN(IDC_COMBO_PRODUCT_NAME, &CARDDlg::OnCbnDropdownComboProductName)
    ON_CBN_SELCHANGE(IDC_COMBO_PRODUCT_NAME, &CARDDlg::OnCbnSelchangeComboProductName)
//	ON_BN_CLICKED(IDC_CHECK_ONLINE_OFFLINE, &CARDDlg::OnBnClickedCheckOnlineOffline)
END_MESSAGE_MAP()


// CARDDlg message handlers


void CARDDlg::OnBnClickedOk()
{
    
   CString ip;
   CString strport;
   BOOL is_open = false;   
   int temp_communication_type = GetLastCommunicationType();
   int temp_comport = 0;
   int temp_baudrate = 19200;
   int read_modbus_id = 255;
   CString temp_cs_port;
   CString temp_baud;
   CString temp_id;
   CString StrProtocol;
   int nComport = 0;
   UpdateData(TRUE);
   unsigned char modbus_mstp_rtu_id = 0;
   int nbaudrate = 115200;
   unsigned short port = 502;

   //int product_type_id = _wtoi(m_type_id);
   //if (product_type_id < 220 && product_type_id != 210)
   //{
   //    AfxMessageBox(_T(" In order to identify your product,Please Enter a number not less than 220!")) ;
   //    return;
   //}
   m_add_device_modbus_id.GetWindowTextW(temp_id);
   read_modbus_id = _wtoi(temp_id); 
   if (read_modbus_id <0||read_modbus_id>255)
   {
       AfxMessageBox(_T("Modbus ID should be more than 1 and less than 255")) ;
       return;
   }
   

   if(temp_communication_type == 0)
   {
	   temp_comport = GetLastOpenedComport();
	   temp_baudrate = GetLastSuccessBaudrate();
	   g_protocol = MODBUS_RS485;
   }

   if (!offline_mode)
   {
	   if (m_is_net_device)
	   {
		   m_ipaddress.GetWindowText(ip);
		   m_porteditor.GetWindowText(strport);
		   if (ip.IsEmpty() || strport.IsEmpty())
		   {
			   AfxMessageBox(_T("ip or port can not be empty!"));
			   return;
		   }
		   port = _wtoi(strport);
		   SetCommunicationType(1);
		   is_open = Open_Socket_Retry(ip, port);
		   StrProtocol = _T("1");
	   }
	   else
	   {
		   SetCommunicationType(0);
		   close_com();

		   m_add_device_com_port.GetWindowTextW(temp_cs_port);
		   m_add_device_baudrate.GetWindowTextW(temp_baud);

		   nComport = _wtoi(temp_cs_port.Mid(3));
		   nbaudrate = _wtoi(temp_baud);
		   if (nComport > 0)
		   {
			   BOOL  bret = open_com(nComport);
			   Change_BaudRate(nbaudrate);
			   if (bret)
				   is_open = true;
			   else
				   is_open = false;
		   }
		   else
		   {
			   is_open = false;
		   }
		   /*}*/
		   StrProtocol = _T("0");


	   }
   }
   else
   {
	   ip =L"192.168.0.3";
	   strport=L"502";
	   temp_cs_port=L"COM3";
	   temp_baud = L"19200";
	   StrProtocol = _T("0");
   }
   MODE_SUPPORT_PTRANSFER = 0; //��ʱ�ر�;
   if (is_open && (offline_mode == false))
   {




       unsigned short test_array[1000];
       int ntest_ret = 0;

       memset(test_array, 0, 2000);

       ntest_ret = Read_Multi(read_modbus_id, &test_array[0], 0, 100, 6);
       if (ntest_ret >= 0)
       {
           _Bac_Scan_results_Info  temp_info = { 0 };
           temp_info.serialnumber = test_array[0] + test_array[1] * 256 + test_array[2] * 256 * 256 + test_array[3] * 256 * 256 * 256;
           temp_info.product_type = test_array[7];
           temp_info.modbus_addr = test_array[6];
           temp_info.panel_number = 0; //�����ݶ�0  
           temp_info.software_version = 0;
           temp_info.hardware_version = 0;
           temp_info.device_id = 0;
           if (m_is_net_device)
           {
			   //CIPAddressCtrl
			   m_ipaddress.GetAddress(temp_info.ipaddress[0], temp_info.ipaddress[1], temp_info.ipaddress[2], temp_info.ipaddress[3]);
			   temp_info.panel_number = test_array[36];
			   temp_info.device_id = GetDeviceInstance(temp_info.product_type);
               //temp_info.ipaddress[0] = test_array[47];
               //temp_info.ipaddress[1] = test_array[48];
               //temp_info.ipaddress[2] = test_array[49];
               //temp_info.ipaddress[3] = test_array[50];
				   if(ShowBacnetView(test_array[7]) )
					   temp_info.m_protocol = PROTOCOL_BACNET_IP;
				   else
						temp_info.m_protocol = MODBUS_TCPIP;
           }
           else
           {
               temp_info.m_protocol = MODBUS_RS485;
           }
		   CString temp_view_name;
		   Remote_Get_PanelName(read_modbus_id, temp_info.product_type, temp_view_name);
		   temp_view_name.Trim();


           CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
           CppSQLite3DB SqliteDBBuilding;
           CppSQLite3Table table;
           CppSQLite3Query q;
           SqliteDBBuilding.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);

           CString temp_serial_number;
           CString temp_baud;
           CString str_temp;
           CString temp_pname;
           CString temp_modbusid;

           CString temp_protocol;
           CString temp_product_id_string;
           CString temp_port_string;
           CString temp_object_instance;
           CString temp_panel_number;
		   CString temp_ip;
		   temp_ip.Format(_T("%d.%d.%d.%d"), temp_info.ipaddress[0], temp_info.ipaddress[1], temp_info.ipaddress[2], temp_info.ipaddress[3]);
           int count;
           temp_serial_number.Format(_T("%u"), temp_info.serialnumber);
           //str_temp.Format(_T("select * from ALL_NODE where Serial_ID = '%i'"), temp_info.serialnumber);
		   str_temp.Format(_T("Delete from ALL_NODE Where Serial_ID = '%u' "), temp_info.serialnumber);
           temp_baud.Format(_T("%u"), nbaudrate);
           q = SqliteDBBuilding.execQuery((UTF8MBSTR)str_temp);
           table = SqliteDBBuilding.getTable((UTF8MBSTR)str_temp);
           count = table.numRows();

		   temp_pname = GetProductName(temp_info.product_type);
		   temp_modbusid.Format(_T("%u"), temp_info.modbus_addr);
		   if (temp_view_name.IsEmpty())
		   {
			   temp_view_name = temp_pname + _T(":") + temp_serial_number + _T("-") + temp_modbusid;
		   }

           temp_protocol.Format(_T("%d"), temp_info.m_protocol);
           temp_product_id_string.Format(_T("%d"), temp_info.product_type);
           if (m_is_net_device)
           {
               temp_port_string.Format(_T("%d"), port);
           }
           else
               temp_port_string.Format(_T("%d"), nComport);

           temp_object_instance.Format(_T("%u"), temp_info.device_id);
           temp_panel_number.Format(_T("%u"), temp_info.panel_number);

           //if (count >= 1)
           //{
			   CString strSql;
			   strSql.Format(_T("Delete from ALL_NODE Where Serial_ID = '%u' "), temp_info.serialnumber);
			   SqliteDBBuilding.execDML((UTF8MBSTR)strSql);
               //str_temp.Format(_T("update ALL_NODE set Bautrate ='%s',Com_Port ='%s',Product_ID ='%s', Protocol ='%s',Product_name = '%s',Online_Status = 1,Object_Instance = '%s',Panal_Number = ' %s' where Serial_ID = '%s'"), temp_baud, temp_port_string, temp_product_id_string, temp_protocol,
               //    temp_view_name, temp_object_instance, temp_panel_number, temp_serial_number);
          // }
           //else
           //{
			   if (m_is_net_device)
			   {
				   str_temp.Format(_T("insert into ALL_NODE (MainBuilding_Name,Building_Name,NetworkCard_Address,Serial_ID,Floor_name,Room_name,Product_name,Product_class_ID,Product_ID,Screen_Name,Bautrate,Background_imgID,Hardware_Ver,Software_Ver,Com_Port,EPsize,Protocol,Online_Status,Custom,Parent_SerialNum,Panal_Number,Object_Instance)   values('"
					   + pFrame->m_strCurMainBuildingName + "','" + pFrame->m_strCurSubBuldingName + "','""','" + temp_serial_number + "','floor1','room1','" + temp_view_name + "','" + temp_product_id_string + "','" + temp_modbusid + "','""','" + temp_ip + "','Modbus TCP / BacnetIP','" + temp_object_instance + "','" + temp_panel_number + "','" + temp_port_string + "','0','" + temp_protocol + "','1','0','0', '" + temp_panel_number + "','" + temp_object_instance + "')"));
			   }
			   else
			   {
				   str_temp.Format(_T("insert into ALL_NODE (MainBuilding_Name,Building_Name,NetworkCard_Address,Serial_ID,Floor_name,Room_name,Product_name,Product_class_ID,Product_ID,Screen_Name,Bautrate,Background_imgID,Hardware_Ver,Software_Ver,Com_Port,EPsize,Protocol,Online_Status,Custom,Parent_SerialNum,Panal_Number,Object_Instance)   values('"
					   + pFrame->m_strCurMainBuildingName + "','" + pFrame->m_strCurSubBuldingName + "','""','" + temp_serial_number + "','floor1','room1','" + temp_view_name + "','" + temp_product_id_string + "','" + temp_modbusid + "','""','" + temp_baud + "','Default_Building_PIC.bmp','" + temp_object_instance + "','" + temp_panel_number + "','" + temp_port_string + "','0','" + temp_protocol + "','1','0','0', '" + temp_panel_number + "','" + temp_object_instance + "')"));
			   }
           //}
           SqliteDBBuilding.execDML((UTF8MBSTR)str_temp);
           SqliteDBBuilding.closedb();
           MessageBox(_T("This operation succeeds.The addition is completed successfully."));
           return;
       }
	   else
	   {
	   AfxMessageBox(_T("Read data timeout!"));
		 }

   }
   else
   {
       AfxMessageBox(_T("Can not Connect"));
   }


}


void CARDDlg::OnBnClickedRadioNetDevice()
{
	
	Enable_Net_UI(1);
}


void CARDDlg::OnBnClickedRadio2()
{
	
	Enable_Net_UI(0);
}


void CARDDlg::OnBnClickedButtonLocalMstpDevice()
{
	
	CppSQLite3DB SqliteDBBuilding;
	CppSQLite3Table table;
	CppSQLite3Query q;
	SqliteDBBuilding.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);


	MessageBox(_T("Scan device may take a few minutes , Please wait!!"));
	vector<CString>				m_szComs;
	GetSerialComPortNumber1(m_szComs);
	int com_port_count =  m_szComs.size();
	for (int z=1;z<com_port_count;z++)
	{
		CString temp_cstring;
		temp_cstring = m_szComs.at(z).Right(m_szComs.at(z).GetLength() - 3);
		int com_port =  _wtoi(temp_cstring);
		Initial_bac(com_port);




		for (int x=0;x<25;x++)
		{
			//CString strInfo;strInfo.Format(_T("Scan Com%d,protocol Bacnet MSTP.Send global command time left(%d)"),temp_port,14-i);
			//pScan->ShowBacnetComScanInfo(strInfo);
			Send_WhoIs_Global(-1,-1);
			Sleep(1000);
		}




		for (int j=0;j<5;j++)
		{
			int ready_to_read_count =	m_bac_handle_Iam_data.size();

			CString strInfo;
			strInfo.Format(_T("Scan  Bacnet mstp.Found %d BACNET device"),ready_to_read_count);
			if((int)m_bac_scan_result_data.size()>= ready_to_read_count)
				break;
			TRACE(_T("gloab scan = %d\r\n"),ready_to_read_count);
			for (int i=0;i<ready_to_read_count;i++)
			{
				int	resend_count = 0;
				do 
				{
					resend_count ++;
					if(resend_count>50)
						break;
					g_invoke_id = GetPrivateData(
						m_bac_handle_Iam_data.at(i).device_id,
						GETSERIALNUMBERINFO,
						0,
						0,
						sizeof(Str_Serial_info));		

					Sleep(SEND_COMMAND_DELAY_TIME);
				} while (g_invoke_id<0);
				//	Sleep(1000);
			}
		}




		int ret_scan_count =	m_bac_scan_result_data.size(); 
		if(ret_scan_count == 0 )
		{
			MessageBox(_T("No bacnet mstp device found."));
			return;
		}
		CString bac_strInfo;
		bac_strInfo.Format(_T("Scan  Bacnetip.Found %d recognizable Bacnet device"),ret_scan_count);
		//pScan->ShowBacnetComScanInfo(bac_strInfo);
		TRACE(_T("serial scan = %d\r\n"),ret_scan_count);

		CString strMainBuildName,strSubBuildingName;
		CMainFrame* pFrame=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
		strMainBuildName= pFrame->m_strCurMainBuildingName;
		strSubBuildingName= pFrame->m_strCurSubBuldingName;
		int product_count = pFrame->m_product.size();

		for (int scan_count = 0; scan_count < ret_scan_count ; scan_count ++)
		{
			bool exist_in_db = false;
			int m_product_count = 0;
			for (int a=0;a<product_count;a++)
			{
				if(m_bac_scan_result_data.at(scan_count).serialnumber == pFrame->m_product.at(a).serial_number)
				{
					m_product_count = a;
					exist_in_db = true;
					break;
				}
			}
			CString modbusid;
			CString str_ip_address;
			CString str_n_port;
			CString str_serialid;
			CString product_class_id;
			CString str_product_name;
			CString strSql;
// 			m_pCon.CreateInstance(_T("ADODB.Connection"));
// 			m_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);

			modbusid.Format(_T("%d"),m_bac_scan_result_data.at(scan_count).modbus_addr);


			str_ip_address.Format(_T("%u.%u.%u.%u"),(unsigned char)m_bac_scan_result_data.at(scan_count).ipaddress[0],
													(unsigned char)m_bac_scan_result_data.at(scan_count).ipaddress[1],
													(unsigned char)m_bac_scan_result_data.at(scan_count).ipaddress[2],
													(unsigned char)m_bac_scan_result_data.at(scan_count).ipaddress[3])  ;
			str_n_port.Format(_T("%d"),m_bac_scan_result_data.at(scan_count).modbus_port);
			str_serialid.Format(_T("%u"),m_bac_scan_result_data.at(scan_count).serialnumber);
			product_class_id.Format(_T("%d"),m_bac_scan_result_data.at(scan_count).product_type);
			str_product_name = GetProductName(m_bac_scan_result_data.at(scan_count).product_type);
			str_product_name = str_product_name + _T(":") + str_serialid + _T("-") + modbusid + _T("-") + str_ip_address;

			if(exist_in_db)
			{
				if((str_ip_address.CompareNoCase(pFrame->m_product.at(m_product_count).BuildingInfo.strIp) != 0) ||
					(m_bac_scan_result_data.at(scan_count).modbus_port != pFrame->m_product.at(m_product_count).ncomport) ||
					(m_bac_scan_result_data.at(scan_count).modbus_addr != pFrame->m_product.at(m_product_count).product_id) ||
					(m_bac_scan_result_data.at(scan_count).device_id != ((int)pFrame->m_product.at(m_product_count).hardware_version )))
				{
					CString instance_value;
					instance_value.Format(_T("%u"),m_bac_scan_result_data.at(scan_count).device_id);
					try
					{
						 
						strSql.Format(_T("update ALL_NODE set Bautrate ='%s' where Serial_ID = '%s'"),str_ip_address,str_serialid);
						 
						strSql.Format(_T("update ALL_NODE set Com_Port ='%s' where Serial_ID = '%s'"),str_n_port,str_serialid);
						SqliteDBBuilding.execDML((UTF8MBSTR)strSql);
						strSql.Format(_T("update ALL_NODE set Product_ID ='%s' where Serial_ID = '%s'"),modbusid,str_serialid);
						SqliteDBBuilding.execDML((UTF8MBSTR)strSql);
						strSql.Format(_T("update ALL_NODE set Hardware_Ver ='%s' where Serial_ID = '%s'"),instance_value,str_serialid);
						SqliteDBBuilding.execDML((UTF8MBSTR)strSql);
					}
					catch(_com_error *e)
					{
						AfxMessageBox(e->ErrorMessage());
					}
					 
					SqliteDBBuilding.closedb();

					pFrame->m_product.at(m_product_count).ncomport = m_bac_scan_result_data.at(scan_count).modbus_port;
					pFrame->m_product.at(m_product_count).BuildingInfo.strIp = str_ip_address;
					pFrame->m_product.at(m_product_count).product_id = m_bac_scan_result_data.at(scan_count).modbus_addr;
				}

			}
			else
			{

			}

		}

	}
}


void CARDDlg::OnCbnDropdownComboProductName()
{
    CString StrSql;
    _variant_t temp_variant;
    Custom_Product_Node product_node;
    m_Custom_Product.clear();
    m_combox_productname.ResetContent();
	CppSQLite3DB SqliteDBT3000;
	SqliteDBT3000.open((UTF8MBSTR)g_strDatabasefilepath);
	CppSQLite3Query q;
    StrSql.Format(_T("Select * From ProductsTypeRegisterTables Where ProductType >=220"));
    q=SqliteDBT3000.execQuery((UTF8MBSTR)StrSql);
    while(!q.eof()){
       
         product_node.Product_Type = q.getIntField("ProductType");
		 product_node.Product_Name = q.getValuebyName(L"ProductName");
            m_Custom_Product.push_back(product_node);
            q.nextRow();
    }
    SqliteDBT3000.closedb();
	
    for(int i=0;i<(int)m_Custom_Product.size();i++){
        m_combox_productname.AddString(m_Custom_Product.at(i).Product_Name);
    }
	m_combox_productname.AddString(L"Add New");
}
int CARDDlg::GetNewProductID()
{
	CppSQLite3DB SqliteDBT3000;
	SqliteDBT3000.open((UTF8MBSTR)g_strDatabasefilepath);
	CppSQLite3Query q;
	CString StrSql;

	int NewID = -1;
	for (int id = 220;  id<256;id++)
	{
		StrSql.Format(_T("Select * From ProductsTypeRegisterTables Where ProductType = %d"),id);
		q = SqliteDBT3000.execQuery((UTF8MBSTR)StrSql);
		if (q.eof())
		{
			NewID = id;
			break;
		}
	}
	SqliteDBT3000.closedb();
	return NewID;
}
int CARDDlg::GetNewSerialNumber()
{	
	int NewSerialNumber = -1;

	time_t t;
	srand((unsigned)time(&t));

	CppSQLite3DB SqliteBuildingDB;
	SqliteBuildingDB.open((UTF8MBSTR)g_strCurBuildingDatabasefilePath);
	CppSQLite3Query q;
	CString StrSql;

 

	int trytime = 3000;
	while (trytime > 0)
	{
		int tempid = rand();
		StrSql.Format(_T("Select * From ALL_NODE Where Serial_ID = '%d' "), tempid);
		q = SqliteBuildingDB.execQuery((UTF8MBSTR)StrSql);
		if (q.eof())
		{
			NewSerialNumber = tempid;
			break;
		}
		--trytime;
	}
	SqliteBuildingDB.closedb();
	return NewSerialNumber;
}

void CARDDlg::OnCbnSelchangeComboProductName()
{
     	int sel = m_combox_productname.GetCurSel();
	    if (sel == m_combox_productname.GetCount() -1)//���һ��New
	    {
			GetDlgItem(IDC_PRODUCTNAME_EDITOR)->ShowWindow(TRUE);
			 CString TypeID;
			 int NewID = GetNewProductID();
			 if (NewID != -1)
			 {
				 TypeID.Format(_T("%d"), NewID);
				 GetDlgItem(IDC_EDIT_TYPE_ID)->SetWindowText(TypeID);
			 }
			 else
			 {
				 AfxMessageBox(L"Can't get a useful product id for you");
			 }
			

			//

	    } 
	    else
	    {
			GetDlgItem(IDC_PRODUCTNAME_EDITOR)->ShowWindow(FALSE);
			CString TypeID;
			TypeID.Format(_T("%d"), m_Custom_Product.at(sel).Product_Type);
			GetDlgItem(IDC_EDIT_TYPE_ID)->SetWindowText(TypeID);
	    }
		
       
		
}


void CARDDlg::OnEnKillfocusEditTypeId()
{
     CString TypeID;
     GetDlgItem(IDC_EDIT_TYPE_ID)->GetWindowText(TypeID);
     if (TypeID.IsEmpty())
     {
          return;
     }
     
     CString ProductName , New_Product_Name;
     GetDlgItem(IDC_COMBO_PRODUCT_NAME)->GetWindowText(ProductName);

	 GetDlgItem(IDC_PRODUCTNAME_EDITOR)->GetWindowTextW(New_Product_Name);
	 if (ProductName.CompareNoCase(L"Add New") == 0 && New_Product_Name.IsEmpty())
	 {
		 MessageBox(L"Please input a product name!");
		 GetDlgItem(IDC_PRODUCTNAME_EDITOR)->SetFocus();
		 return;
	 }
	 else if (ProductName.CompareNoCase(L"Add New") == 0)
	 {
		 ProductName = New_Product_Name;
	 }


     int ProductID;
     ProductID = _wtoi(TypeID);
     BOOL Check_Input = FALSE;
     for (int i = 0; i<(int) m_Custom_Product.size();i++)
     {
         if (m_Custom_Product.at(i).Product_Type == ProductID)
         {     Check_Input = TRUE ;
             if (ProductName.CompareNoCase(m_Custom_Product.at(i).Product_Name)!=0)
             {
                 CString strtips;
                 strtips.Format(_T("Product Type :%d have occupied,The Product is %s!"),m_Custom_Product.at(i).Product_Type,m_Custom_Product.at(i).Product_Name);
                 AfxMessageBox(strtips);
                 return;
             }
             break;

         }
         if (ProductName.CompareNoCase(m_Custom_Product.at(i).Product_Name)==0)
         {        Check_Input = TRUE ;
             if (m_Custom_Product.at(i).Product_Type != ProductID)
             {
                 CString strtips;
                 strtips.Format(_T("The Product is %s already in system, Product Type :%d!"),m_Custom_Product.at(i).Product_Type,m_Custom_Product.at(i).Product_Name);
                 AfxMessageBox(strtips);
                 return;
             }
             break;
         }
     }
     if (!Check_Input)
     {
         CString StrSql;
         _variant_t temp_variant;
         Custom_Product_Node product_node;
         m_Custom_Product.clear();
		 CppSQLite3DB SqliteDBT3000;
		 SqliteDBT3000.open((UTF8MBSTR)g_strDatabasefilepath);
        
         StrSql.Format(_T("Insert into ProductsTypeRegisterTables(ProductType,ProductName) Values(%d,'%s')"),ProductID,ProductName);
         SqliteDBT3000.execDML((UTF8MBSTR)StrSql);
          SqliteDBT3000.closedb();
     }
}


//void CARDDlg::OnEnKillfocusEditAddDeviceModbusId()
//{
//    
//}
// void CARDDlg::OnCbnSelchangeComboAddDeviceComport()
// {
//      CString strComName;
// 	 m_add_device_com_port.GetWindowTextW(strComName);
// 	 if (strComName.CompareNoCase(L"OfflineDevice")==0)
// 	 {
// 	     GetDlgItem(IDOK)->SetWindowTextW(L"Add");
// 	 }
// }


//void CARDDlg::OnBnClickedCheckOnlineOffline()
//{
//    int checked = m_offlineButton.GetCheck();
//	if (checked)
//	{
//	    GetDlgItem(IDOK)->SetWindowTextW(L"Add");
//
//		IDC_RADIO_NET_DEVICE
//		IDC_IPADDRESS1
//
//	} 
//	else
//	{
//		GetDlgItem(IDOK)->SetWindowTextW(L"Connect");
//	}
//}
