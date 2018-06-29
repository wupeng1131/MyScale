
// My_ScaleDlg.cpp : 实现文件
//
/*
*Copyright wupeng
*Author wupeng
*2018.5.24
*/
#include "stdafx.h"
#include "My_Scale.h"
#include "My_ScaleDlg.h"
#include "afxdialogex.h"
#include "windows.h" 
//#include "stdafx.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "fit.h"
#include <direct.h>
#include <io.h>
#include <time.h>
#include <queue>
#include <conio.h>
#include <fstream>
#include "grab.h"
#include "parameter.h"
//#include "picture.h"
using namespace std; 
using namespace cv; 
#define O2X (15+m_GL->My_O2.dx)*scale2*3.72*0.57915
#define O2Y (-6+m_GL->My_O2.dy)*scale*3.72*0.57915
#define O6X (21+m_GL->My_O6.dx)*scale2*3.72*0.57915
#define O6Y (-33+m_GL->My_O6.dy)*scale*3.72*0.57915
#define O7X (30.5+m_GL->My_O7.dx)*scale2*3.72*0.57915
#define O7Y (-53+m_GL->My_O7.dy)*scale*3.72*0.57915

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 float scale;
 float scale2;
 float scale3;
 float scale4;
 float scale5;
 char order[9]={0};
 int time_flag=0;
 char p1[22]="D://p//C000000000.bmp";
 int total=0;
 time_t timep1;//定义时间
 int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0;
struct tm  *pt1;//系统定义的结构
  int chest_Y=0;
 //int  cut1=321,cut2=670;
 double my_error[3];
 
	////////////////////
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy_ScaleDlg 对话框



CMy_ScaleDlg::CMy_ScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy_ScaleDlg::IDD, pParent)
	, m_num(1.0),m_num2(1.0),m_num3(1.0),m_num4(1.0),m_num5(1.0),m_num_x (1.0),m_num_y (1.0)
	, Radio1(-1)
	, m_modulus(MODULUS)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_GL=NULL;
	
	for(int i=0;i<30;i++)
	{
	  location[i]=-1;
	  location2[i]=-1;
	}
}

CMy_ScaleDlg ::~CMy_ScaleDlg()
{
  if(m_GL)
  {
    delete m_GL;
	m_GL=NULL;
  }
}
void CMy_ScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_S1, m_Slider);
	DDX_Control(pDX, IDC_S2, m_Slider2);
	DDX_Control(pDX, IDC_S3, m_Slider3);
	DDX_Control(pDX, IDC_S4, m_Slider4);
	DDX_Control(pDX, IDC_S5, m_Slider5);

	//DDX_Text(pDX, IDC_EDIT_X, m_num_x);
	//DDX_Text(pDX, IDC_EDIT_Y, m_num_y);
	DDV_MinMaxFloat(pDX, m_num, 0.1, 2);
	DDV_MinMaxFloat(pDX, m_num2, 0.1, 2);
	DDV_MinMaxFloat(pDX, m_num3, 0.1, 2);
	DDV_MinMaxFloat(pDX, m_num4, 0.1, 2);
	DDV_MinMaxFloat(pDX, m_num5, 0.1, 2);
	//DDV_MinMaxFloat(pDX, m_num_x, 0.1, 2);
	//DDV_MinMaxFloat(pDX, m_num_y, 0.1, 2);
	DDX_Radio(pDX, IDC_RADIO1, Radio1);

	DDX_Text(pDX, IDC_EDIT1, m_modulus);
}

BEGIN_MESSAGE_MAP(CMy_ScaleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy_ScaleDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_S1, &CMy_ScaleDlg::OnNMCustomdrawS1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_S2, &CMy_ScaleDlg::OnNMCustomdrawS2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_S3, &CMy_ScaleDlg::OnNMCustomdrawS3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_S4, &CMy_ScaleDlg::OnNMCustomdrawS4)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO1, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO4, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO5, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO6, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO7, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO8, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO9, &CMy_ScaleDlg::OnBnClickedRadio1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_S5, &CMy_ScaleDlg::OnNMCustomdrawS5)
	ON_BN_CLICKED(IDCANCEL, &CMy_ScaleDlg::OnBnClickedCancel)


	ON_BN_CLICKED(IDC_BUTTON2, &CMy_ScaleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy_ScaleDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy_ScaleDlg 消息处理程序

BOOL CMy_ScaleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect(0,0,670,670);
	m_GL=new MyOpenGL;//用New的方式创建
	//MyOpenGL m_GL;
	m_GL->Create( NULL,   //缺省的窗口
		NULL,   //无窗口名称
		WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,
		// 定义窗口风格
		rect,   // 窗口的大小
		this,   // 指定当前对话框为其父窗口指针
		0);   
	//在这里对滑块进行设定
	m_Slider.SetRange (10,200,TRUE);
	m_Slider .SetPageSize (5);
	m_Slider .SetPos (10);
	m_Slider2.SetRange (10,200,TRUE);
	m_Slider2 .SetPageSize (5);
	m_Slider2 .SetPos (10);
	m_Slider3.SetRange (10,200,TRUE);
	m_Slider3 .SetPageSize (5);
	m_Slider3.SetPos (100);
	m_Slider4.SetRange (10,200,TRUE);
	m_Slider4 .SetPageSize (5);
	m_Slider4 .SetPos (100);
	m_Slider5.SetRange (10,200,TRUE);
	m_Slider5 .SetPageSize (5);
	m_Slider5 .SetPos (10);
	///////////////////////////
	//Joint My_O1(15,-2.5,2.5);

      

	////////////////////////下面是文件操作
	if ( _access("D://p",0) )
		  {
			  _mkdir("D://p");
			  MessageBox (_T("The file \"p\"has been created successfully!"));
			 
		  }//在这里创建名为w的文件夹
	
	fstream _order;
	_order.open("D://p//order",ios::in);
	if(!_order)
	{
	  ofstream orderfile("D://p//order");
	   if(!orderfile){//检查是否打开成功
        cout << "Failed to create file...\n";
        exit(0);
    }
	    orderfile <<"000000000";//向文件写数据
        orderfile .close();//关闭文件*/
	}
	else
	{
	   _order.read(order,9);
	   time_flag=(order[0]-48)*100000+(order[1]-48)*10000+(order[2]-48)*1000+(order[3]-48)*100+(order[4]-48)*10+order[5]-48;
	}//在这里设置记录截图次数的文件order
	///////////////////////////
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy_ScaleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy_ScaleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy_ScaleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
typedef GLbyte* bytePt;


void CMy_ScaleDlg ::saveColorData2Img ()
{
  Mat show=Mat(winHeight ,winWidth ,CV_8UC3 ,Scalar ::all(0));
  for (int i = 0; i< winHeight; i++)  
    {  
        for (int j = 0; j< winWidth; j++)  
        {  
            show.at<Vec3b>(winHeight-i-1, j) = Vec3b(colorArr[(i*winWidth+j)*4+2], colorArr[(i*winWidth+j)*4+1], colorArr[(i*winWidth+j)*4]);  
        }  
    } 
  //////////////////////////////////////////////////////
  fstream _order;
	_order.open("D://p//order",ios::in);		
    _order.read(order,9);
	time_flag=(order[0]-48)*100000+(order[1]-48)*10000+(order[2]-48)*1000+(order[3]-48)*100+(order[4]-48)*10+order[5]-48;
	  total=(order[6]-48)*100+(order[7]-48)*10+order[8]-48;
	
	                   time(&timep1);
			           pt1=gmtime(&timep1);
				       p1[8]=(pt1->tm_year-100)/10+48;
				       p1[9]=(pt1->tm_year-100)%10+48;
				       p1[10]=(1+pt1->tm_mon)/10+48;
				       p1[11]=(1+pt1->tm_mon)%10+48;
				       p1[12]=pt1->tm_mday/10+48;
				       p1[13]=pt1->tm_mday%10+48;				      				      
				////////////////////////////////////////////////////
					   
					  					   
if(time_flag >(pt1->tm_year-100)*10000+(1+pt1->tm_mon)*100+pt1->tm_mday)
					   {
					     //MessageBox (_T("系统日期出现错误！"));
						 exit(1);//说明时间倒流，出错
					   }
else if(time_flag ==(pt1->tm_year-100)*10000+(1+pt1->tm_mon)*100+pt1->tm_mday)
                      {
						   total++;//在同一天拍照，total值依次增加
						    if(total==1000) 
			                   {
			                     total=0;
			                   }
						 
						  
                      }
else
                      {
						  total=0;//在后面的日期拍照，则total变为0						  
                      }
                          p1[14]=total/100+48;
				          p1[15]=(total/10)%10+48;
				          p1[16]=total%10+48;
	
						   ofstream in ;
	                      in.open("D://p//order",ios::binary);//保存order数据
	                      in.write (p1+8,9);
	                      in.close();
   ////////////////////////////////////////////////////////
   IplImage ipl_img1(show);
   //cvSaveImage ("D://PPPPP.bmp",&ipl_img1 ,0);
     cvSaveImage(p1, &ipl_img1,0);
	 CString b0;
	 b0.Format (_T("图片抓取成功"));
	 	
	 MessageBox(b0);
	  
}
void CMy_ScaleDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	glGrab ();
	saveColorData2Img ();
	/* CString str;
	   str.Format (_T("身高%1.fcm,胸围%1.fcm,肩宽%1.2fcm,\r\n臂长%1.fcm,腿长%1.fcm,中腰围%1.fcm,\r\n腰围%1.fcm,臀围%1.fcm,领围%1.fcm,胸宽%1.fcm,前身%1.fcm,立档%1.fcm"),my_height*MODULUS,xiong_wei *MODULUS,//(92*scale2*2/3+70.7*scale5)*MODULUS*2,
		//(35+2*m_GL ->My_O1 .dx)*scale2*3.72*0.57915,
		//(location[my_max(location)]-location[0]+1)*MODULUS,//0.57915,
		jian_kuan*MODULUS,
		bi_chang*MODULUS,//sqrt((O6X -O2X)*(O6X -O2X)+(O6Y -O2Y)*(O6Y -O2Y) )+sqrt((O7X -O6X)*(O7X -O6X)+(O7Y -O6Y)*(O7Y -O6Y) ),
		tui_chang*MODULUS,
		zhong_yao*MODULUS,
		yao*MODULUS,
		tun*MODULUS,
		linwei*MODULUS,
		xiongkuan*MODULUS,
		qianshen*MODULUS,
		lidang*MODULUS
		//((Waist_X[1]-Waist_X[0])*2/3+(Waist_X[3]-Waist_X[2]))*MODULUS*2
		);
	 SetDlgItemText (IDC_POSITION,str);
	 */
	 CString str0,str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11;
	 str0.Format(_T("%1.fcm"),my_height*m_modulus);
	 SetDlgItemText (IDC_E0,str0);
	 str1.Format(_T("%1.fcm"),linwei*m_modulus);
	 SetDlgItemText (IDC_E1,str1);
	 str2.Format(_T("%1.2fcm"),jian_kuan*m_modulus);
	 SetDlgItemText (IDC_E2,str2);
	 str3.Format(_T("%1.fcm"),xiongkuan*m_modulus);
	 SetDlgItemText (IDC_E3,str3);
	 str4.Format(_T("%1.fcm"),xiong_wei *m_modulus);
	 SetDlgItemText (IDC_E4,str4);
	 str5.Format(_T("%1.fcm"),zhong_yao*m_modulus);
	 SetDlgItemText (IDC_E5,str5);
	 str6.Format(_T("%1.fcm"),yao*m_modulus);
	 SetDlgItemText (IDC_E6,str6);
	 str7.Format(_T("%1.fcm"),tun*m_modulus);
	 SetDlgItemText (IDC_E7,str7);
	 str8.Format(_T("%1.fcm"),bi_chang*m_modulus);
	 SetDlgItemText (IDC_E8,str8);
	 str9.Format(_T("%1.fcm"),tui_chang*m_modulus);
	 SetDlgItemText (IDC_E9,str9);
	 str10.Format(_T("%1.fcm"),qianshen*m_modulus);
	 SetDlgItemText (IDC_E10,str10);
	 str11.Format(_T("%1.fcm"),lidang*m_modulus);
	 SetDlgItemText (IDC_E11,str11);
	 //MessageBox (_T("The file \"p\"has been created successfully!"));
					    
				          
}

void CMy_ScaleDlg::OnNMCustomdrawS1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
		UpdateData (TRUE );
		m_num=m_Slider .GetPos()/100.0;
		scale=m_num;			  
	    m_GL->OnPaint ();
	  
		UpdateData (FALSE);
	*pResult = 0;
}


void CMy_ScaleDlg::OnNMCustomdrawS2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
		UpdateData (TRUE );
		m_num2=m_Slider2 .GetPos()/100.0;
		scale2=m_num2;
		 m_GL->OnPaint ();
		
		UpdateData (FALSE);
	*pResult = 0;
}

void CMy_ScaleDlg::OnNMCustomdrawS3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
		UpdateData (TRUE );
		m_num3=m_Slider3 .GetPos()/100.0;
		scale3=m_num3;
		 m_GL->OnPaint ();
		UpdateData (FALSE);
	*pResult = 0;
}


void CMy_ScaleDlg::OnNMCustomdrawS4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
		UpdateData (TRUE );
		m_num4=m_Slider4 .GetPos()/100.0;
		scale4=m_num4;
		 m_GL->OnPaint ();
		UpdateData (FALSE);
	*pResult = 0;
}


void CMy_ScaleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMy_ScaleDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData (TRUE);
	switch(Radio1 )
	{
	case 0:
		  n1=1;n2=0;n3=0;n4=0;n5=0;n6=0;n7=0;n8=0;n9=0;
		break;
	case 1:
		  n1=0;n2=1;n3=0;n4=0;n5=0;n6=0;n7=0;n8=0;n9=0;
		break;
	case 2:
		  n1=0;n2=0;n3=1;n4=0;n5=0;n6=0;n7=0;n8=0;n9=0;
		break;
	case 3:
		  n1=0;n2=0;n3=0;n4=1;n5=0;n6=0;n7=0;n8=0;n9=0;
		break;
	case 4:
		  n1=0;n2=0;n3=0;n4=0;n5=1;n6=0;n7=0;n8=0;n9=0;
		break;
	case 5:
		  n1=0;n2=0;n3=0;n4=0;n5=0;n6=1;n7=0;n8=0;n9=0;
		break;
	case 6:
		  n1=0;n2=0;n3=0;n4=0;n5=0;n6=0;n7=1;n8=0;n9=0;
		break;
	case 7:
		  n1=0;n2=0;n3=0;n4=0;n5=0;n6=0;n7=0;n8=1;n9=0;
		break;
	case 8:
		  n1=0;n2=0;n3=0;n4=0;n5=0;n6=0;n7=0;n8=0;n9=1;
		break;
	}
}


void CMy_ScaleDlg::OnNMCustomdrawS5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
		UpdateData (TRUE );
		m_num5=m_Slider5 .GetPos()/100.0;
		scale5=m_num5;
		 m_GL->OnPaint ();
		UpdateData (FALSE);
	*pResult = 0;
}


void CMy_ScaleDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CDialogEx::OnCancel();
}




int LoadTexture1(IplImage *image,GLuint *text)
{
  if(image==NULL ) return -1;
  glGenTextures (1,text);
  glBindTexture (GL_TEXTURE_2D ,*text);
  glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_MAG_FILTER ,GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D ,GL_TEXTURE_MIN_FILTER ,GL_LINEAR);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
  0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image->imageData);
	 return 0;
}

void CMy_ScaleDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	 // TODO: Add your control notification handler code here   
    // 设置过滤器   
    TCHAR szFilter[] = _T("图片文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);   
    CString strFilePath;   
   
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();   
       // SetDlgItemText(IDC_OPEN_EDIT, strFilePath);   
		m_GL->ChangeTexture(strFilePath);
		m_GL->OnPaint ();
	//UpdateData (FALSE);
	//char *filepath=(LPSTR)(LPCSTR)strFilePath.GetBuffer(0);
	//UpdateWindow();
		Invalidate();
}
    }   

void CMy_ScaleDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	CString mesg;
	mesg.Format (_T("系数为%f"),m_modulus);
	MessageBox(mesg);
    }   

