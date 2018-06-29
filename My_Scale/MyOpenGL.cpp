#include "stdafx.h"
#include "data.h"
#include "read_data.h"
#include "picture.h"
#include "parameter.h"
using namespace cv; 

extern int n1,n2,n3,n4,n5,n6,n7,n8,n9;
extern float scale;
extern float scale2;
extern float scale3;
extern float scale4;
extern float scale5;
GLfloat O6x;
GLfloat O6y;
int PaintFlag=1; 
 int t_dx,t_dy;
 static GLfloat pos[4] =  {5.0, 5.0, 10.0, 0.0};
	static GLfloat red[4] =  {0.8, 0.1, 0.0, 1.0};
	static GLfloat green[4] =  {0.0, 0.8, 0.2, 1.0};
	static GLfloat blue[4] =  {0.2, 0.2, 1.0, 1.0};
	static GLfloat white_light[4]={1.0,1.0,1.0,1.0};
	static GLfloat  lmodel_ambient[]={0.1,0.1,0.1,1.0};

//将像素坐标存放在一个一维数组中	
int jian[4]={0};
int kua[4]={0};
int zhou[4]={0};
int wan[4]={0};
int xi[4]={0};
int foot[4]={0};
int xiongwei[2]={0};
int center=0;
int B_kua_y=0;
int B_jian_y=0;
MyOpenGL::MyOpenGL(void):My_O6(21,-33,5),My_O7(30.5,-53,5),My_O4(6.5,-99,7),My_O5(5,-137,6)
	,My_T0(-10,-98.5,7),My_T1(-7,-136.5,5),My_O1(15,-2.5,2.5),My_O2(15,-6,3.5),My_O3(11.5,-55,5)
	,My_p1(0,0,0),My_p2(0,0,0)
{
	step=0.0;
	s=0.1;
	prePt .SetPoint (-1,-1);
	nowPt .SetPoint (-1,-1);	  
}


MyOpenGL::~MyOpenGL(void)
{
	wglMakeCurrent (NULL,NULL);
	wglDeleteContext (hglrc);
	::ReleaseDC (m_hWnd ,hdc);
	
}
    BEGIN_MESSAGE_MAP(MyOpenGL, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE ()
    END_MESSAGE_MAP()

int MyOpenGL::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
        if (CWnd::OnCreate(lpCreateStruct) == -1)  
        return -1; 
		if(MySetPixelFormat(::GetDC(m_hWnd))==FALSE)  
        return 0;  
		//获得绘图描述表
		hdc=::GetDC (m_hWnd );
		//创建渲染描述表
		hglrc =wglCreateContext (hdc);
		wglMakeCurrent (hdc,hglrc);//B171114012
			 img = cvLoadImage("D://p//A180517005.jpg", 1);//读入彩色图wp:3.jieguo9,hong g7.jieguo10,chen g5.jieguo7
			 CvSize size=cvSize (REAL_WIDTH,REAL_HEIGHT);
			 cvSetImageROI (img,cvRect (BEGIN_X,BEGIN_Y,size.width ,size.height ));
			 IplImage  *pDest= cvCreateImage(size,img->depth,img->nChannels);
			 cvCopy(img,pDest); //复制图像
             cvResetImageROI(pDest);//源图像用完后，清空ROI
			 // cv::Mat edge1=img;
			 /*Mat  src1=cvarrToMat(pDest);
			 Mat  edge1,gray1;
			 edge1.create(src1.size (),src1.type ());//创建同类型大小的矩阵
             cvtColor (src1,gray1,CV_BGR2GRAY);//转化为灰度图
             blur (gray1,edge1,Size (3,3));//3X3降噪
             Canny(edge1,edge1,150,100,3);//获取边缘
			 IplImage pDest_1(edge1 );*/
             LoadTexture(pDest, &texture ); 


			 img1 = cvLoadImage("D://p//B180517005.jpg", 1);//读入彩色图//jieguo9..wp2
			 CvSize size1=cvSize (REAL_WIDTH,REAL_HEIGHT);
			 cvSetImageROI (img1,cvRect (BEGIN_X,BEGIN_Y,size1.width ,size1.height ));
			 IplImage  *pDest1= cvCreateImage(size1,img1->depth,img1->nChannels);
			 cvCopy(img1,pDest1); //复制图像
             cvResetImageROI(pDest1);//源图像用完后，清空ROI
             LoadTexture(pDest1, &texture1 );
		return 0;
}

void MyOpenGL::ChangeTexture( CString &strFilePath )
{
	int len = strFilePath.GetLength();
	char T1[20]="0";
	char T2[20]="0";
	for (int i = 0; i< len; i++)
	{
		T1[i] = strFilePath.GetAt(i);
		T2[i] = strFilePath.GetAt(i);
	}
	T1[5]='A';//正面图和侧面图
	T2[5]='B';
	T1[2]='/';
	T2[2]='/';
	T1[4]='/';
	T2[4]='/';
  hdc=::GetDC (m_hWnd );
		//创建渲染描述表
		hglrc =wglCreateContext (hdc);
		wglMakeCurrent (hdc,hglrc);//B171114012
			 img = cvLoadImage(T1, 1);//读入彩色图wp:3.jieguo9,hong g7.jieguo10,chen g5.jieguo7
			 CvSize size=cvSize (REAL_WIDTH,REAL_HEIGHT);
			 cvSetImageROI (img,cvRect (BEGIN_X,BEGIN_Y,size.width ,size.height ));
			 IplImage  *pDest= cvCreateImage(size,img->depth,img->nChannels);
			 cvCopy(img,pDest); //复制图像
             cvResetImageROI(pDest);//源图像用完后，清空ROI
             LoadTexture(pDest, &texture ); 

			 img1 = cvLoadImage(T2, 1);//读入彩色图//jieguo9..wp2
			 CvSize size1=cvSize (REAL_WIDTH,REAL_HEIGHT);
			 cvSetImageROI (img1,cvRect (BEGIN_X,BEGIN_Y,size1.width ,size1.height ));
			 IplImage  *pDest1= cvCreateImage(size1,img1->depth,img1->nChannels);
			 cvCopy(img1,pDest1); //复制图像
             cvResetImageROI(pDest1);//源图像用完后，清空ROI
             LoadTexture(pDest1, &texture1 );
			 
}
void MyOpenGL::OnPaint ()
{    
	PAINTSTRUCT ps;
	glClearColor( 0.0, 0.6, 0.0,1.0 );//改变背景色
	//glClearColor( 0.0, 1.0, 0.0,1.0 );//改变背景色
	glPushMatrix ();
	gluOrtho2D (0,2,0,2);
	glClear (GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );	 
	glDisable(GL_DEPTH_TEST); 	  	

	BeginPaint(&ps);	
   
	Rendercene ();
	EndPaint(&ps);
    glColor3f(255,255,255); 
	glPopMatrix ();
	//glFlush ();
	SwapBuffers (hdc);
	 
}

int MyOpenGL::MySetPixelFormat(HDC hDC)  
{  
    PIXELFORMATDESCRIPTOR pixelDesc;  
  
    pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);  
    pixelDesc.nVersion = 1;  
  
    pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |   
        PFD_SUPPORT_OPENGL |  
        PFD_DOUBLEBUFFER |  
        PFD_TYPE_RGBA;  
  
    pixelDesc.iPixelType = PFD_TYPE_RGBA;  
    pixelDesc.cColorBits = 32;  
    pixelDesc.cRedBits = 0;  
    pixelDesc.cRedShift = 0;  
    pixelDesc.cGreenBits = 0;  
    pixelDesc.cGreenShift = 0;  
    pixelDesc.cBlueBits = 0;  
    pixelDesc.cBlueShift = 0;  
    pixelDesc.cAlphaBits = 0;  
    pixelDesc.cAlphaShift = 0;  
    pixelDesc.cAccumBits = 0;  
    pixelDesc.cAccumRedBits = 0;  
    pixelDesc.cAccumGreenBits = 0;  
    pixelDesc.cAccumBlueBits = 0;  
    pixelDesc.cAccumAlphaBits = 0;  
    pixelDesc.cDepthBits = 0;  
    pixelDesc.cStencilBits = 1;  
    pixelDesc.cAuxBuffers = 0;  
    pixelDesc.iLayerType = PFD_MAIN_PLANE;  
    pixelDesc.bReserved = 0;  
    pixelDesc.dwLayerMask = 0;    
    pixelDesc.dwVisibleMask = 0;  
    pixelDesc.dwDamageMask = 0;  
  
    int iPixelFormat;   
  
    // 为设备描述表得到最匹配的像素格式   
    if((iPixelFormat = ChoosePixelFormat(hDC, &pixelDesc)) == 0)  
    {  
        MessageBox(_T("ChoosePixelFormat Failed"), NULL, MB_OK);  
        return FALSE;  
    }  
  
    // 设置最匹配的像素格式为当前的像素格式   
    if(SetPixelFormat(hDC, iPixelFormat, &pixelDesc) == FALSE)  
    {  
        MessageBox (_T("SetPixelFormat Failed"), NULL, MB_OK);  
        return FALSE;  
    }  
    return TRUE;  
}  

void MyOpenGL::OnMouseMove (UINT nFlags,CPoint point)
{
	
	if(nFlags & MK_LBUTTON ==TRUE )
	{
	  OnPaint ();
	  nowPt .x=point.x;
	  nowPt .y=point.y;
	 
	  if(prePt .x!=-1 && prePt.y!=-1 && nowPt.x!=-1&&nowPt.y!=-1)
	  {
	        double tDx = nowPt.x - prePt.x;
            double tDy = nowPt.y - prePt.y;
            
			 if(tDx > 0.) {
                if(n1) My_O6 .dx +=0.35;
				if(n2) My_O7 .dx +=0.35;
				if(n3) {My_O4 .dx +=0.35;}
				if(n4) {My_O5 .dx +=0.35;}
				if(n5) {My_O1 .dx +=0.35;}
				if(n6) {My_O2 .dx +=0.35;}
				if(n7) {My_O3 .dx +=0.35;}
				if(n8) {My_p1.dx  +=0.001;}
				if(n9) {My_p2.dx  +=0.001;}
            } 
			 else if(tDx < 0.) {
              if(n1) My_O6 .dx -=0.35;
			  if(n2) My_O7 .dx -=0.35;
			  if(n3) {My_O4 .dx -=0.35;}
			  if(n4) {My_O5 .dx -=0.35;}
			  if(n5) {My_O1 .dx -=0.35;}
			  if(n6) {My_O2 .dx -=0.35;}
			  if(n7) {My_O3 .dx -=0.35;}
			  if(n8) {My_p1.dx  -=0.001;}
			  if(n9) {My_p2.dx  -=0.001;}
            }
            if(tDy > 0.) {
                
			 if(n1)	My_O6 .dy -=0.35;
			 if(n2)	My_O7 .dy -=0.35;
			 if(n3)	{My_O4 .dy -=0.35;My_T0 .dy -=0.35;}
			 if(n4)	{My_O5 .dy -=0.35;My_T1 .dy -=0.35;}
			 if(n5) {My_O1 .dy -=0.35;}
			 if(n6) {My_O2 .dy -=0.35;}
			 //if(n7) {My_O3 .dy -=0.35;}
			 if(n8) {My_p1.dy  -=0.001;}
			 if(n9) {My_p2.dy  -=0.001;}
            } 
			else if(tDy < 0.) {
             if(n1)   My_O6 .dy +=0.35;
			 if(n2)   My_O7 .dy +=0.35;
			 if(n3)   {My_O4 .dy +=0.35;My_T0 .dy +=0.35;}
			 if(n4)   {My_O5 .dy +=0.35;My_T1 .dy +=0.35;}
			 if(n5) {My_O1 .dy +=0.35;}
			 if(n6) {My_O2 .dy +=0.35;}
			 if(n8) {My_p1.dy  +=0.001;}
			 if(n9) {My_p2.dy  +=0.001;}
            }
	  }
	  prePt.x = nowPt.x;
      prePt.y = nowPt.y;
	}
	else t_dx=t_dy=PaintFlag=0;
}

void MyOpenGL ::Rendercene ()
{   glEnable(GL_TEXTURE_2D); 
/*下面是关于背景的操作*/
	glPushMatrix();  //左背景
    glTranslatef(POSITION1_X+My_p1.dx , POSITION1_Y+My_p1.dy, 0);   //通过测试知道，（0,0）的坐标是图片中心
    Background();                   //背景方块  
    glPopMatrix();
	glPushMatrix(); //右背景
    glTranslatef(POSITION2_X+My_p2.dx, POSITION2_Y +My_p2.dy, 0); 
    Background1();  
    glPopMatrix();
	glDisable (GL_TEXTURE_2D);
/*下面是计算各个部位点的具体像素尺寸,这里注意，图片的原点在图片的中央*/
	//position1_x和position2_x分别如何求解？这里的base_point 是左上方的点
	//read_mydata();
	int base_point[2]={(POSITION1_X+My_p1.dx)*335-PICTURE_WIDTH/2, (POSITION1_Y+My_p1.dy)*335+PICTURE_HEIGHT/2};
	jian[0]=base_point[0]+PICTURE_WIDTH *O_jian[0];//肩
	jian[1]=base_point[1]-PICTURE_HEIGHT*O_jian[1];
	jian[2]=base_point[0]+PICTURE_WIDTH *O_jian[2];
	jian[3]=base_point[1]-PICTURE_HEIGHT*O_jian[3];
	kua[0]= base_point[0]+PICTURE_WIDTH *O_kua[0];//胯
	kua[1]= base_point[1]-PICTURE_HEIGHT*O_kua[1];
	kua[2]= base_point[0]+PICTURE_WIDTH *O_kua[2];
	kua[3]= base_point[1]-PICTURE_HEIGHT*O_kua[3];
	zhou[0]=base_point[0]+PICTURE_WIDTH *O_zhou[0];//肘关节
	zhou[1]=base_point[1]-PICTURE_HEIGHT*O_zhou[1];
	zhou[2]=base_point[0]+PICTURE_WIDTH *O_zhou[2];
	zhou[3]=base_point[1]-PICTURE_HEIGHT*O_zhou[3];
	wan[0]=base_point[0]+PICTURE_WIDTH *O_wan[0];//手腕
	wan[1]=base_point[1]-PICTURE_HEIGHT*O_wan[1];
	wan[2]=base_point[0]+PICTURE_WIDTH *O_wan[2];
	wan[3]=base_point[1]-PICTURE_HEIGHT*O_wan[3];
	xi[0]=base_point[0]+PICTURE_WIDTH *O_xi[0];//膝盖
	xi[1]=base_point[1]-PICTURE_HEIGHT*O_xi[1];
	xi[2]=base_point[0]+PICTURE_WIDTH *O_xi[2];
	xi[3]=base_point[1]-PICTURE_HEIGHT*O_xi[3];
	foot[0]=base_point[0]+PICTURE_WIDTH *O_foot[0];//脚腕
	foot[1]=base_point[1]-PICTURE_HEIGHT*O_foot[1];
	foot[2]=base_point[0]+PICTURE_WIDTH *O_foot[2];
	foot[3]=base_point[1]-PICTURE_HEIGHT*O_foot[3];
	center=CENTER;
	B_kua_y=(kua[1]+kua[3])/2;
	B_jian_y=(jian[1]+jian[3])/2;
/*下面是绘制骨架图*/
	/*
	glColor3f(255,0,0); 
	glPushMatrix ();
	glTranslatef (0.5f,1.5f,0.0f);
	glScalef(1, scale , 1 );	
	glPushMatrix ();
	glScalef(scale2 , 1 , 1 );
    line(A0 ,A1);
	line(A1,A2);
	//line(A2,A3);
	//line(A4,A5);
	
	drawArc1 (M1);
	line(A6,A7);
	//line(A7,A8);
	line(A1,A18);
	//line(A8,A18);
	//line(w1,w2);
	//circle(O1);	
	My_O1.DrawJoint ();
	My_O1.JointToPoint(A2);
	line(C7,C8);
	line(C9,C10);
	My_O2.JointToPoint (A5);//这里有点小失误。这里才是正确的位置
	My_O3 .JointToPoint (A7);
	glPopMatrix ();
	/////////////////////////手臂部分
	glPushMatrix ();
	glTranslatef (0,(1-scale3)*O2[1]/90,0.0f);
	glScalef(scale2, scale3 , 1 );
	My_O6 .DrawJoint ();
	My_O7 .DrawJoint ();
	
	
	My_O6.JointToJoint (My_O7);
	
	//circle(O2);
	My_O2 .DrawJoint ();
	My_O2 .JointToJoint(My_O6);
	
	glPopMatrix ();
	////////////////////腿的部分
	
	glPushMatrix ();
	glTranslatef (0,(1-scale4)*O3[1]/90,0.0f);
	glScalef(scale2, scale4 , 1 );
	
	m_A19 [0]=My_O5 .Ox+My_O5.dx;
	m_A19 [1]=My_O5 .Oy+My_O5.dy-4;
	
	My_O5 .JointToPoint (m_A19);
	//circle(O3);
	My_O3.DrawJoint  ();
	
	My_O3 .JointToPoint (A18);
	My_O3 .JointToJoint (My_O4);
	My_O4.DrawJoint  ();
	My_O5.DrawJoint  ();
	
	My_O5.JointToJoint (My_O4);
	glPopMatrix ();
	
///////////////////////////////////
	//反面
	
  glScaled (-1.0,1.0,1.0);
  glPushMatrix ();
	glScalef(scale2 , 1 , 1 );
 line(A0 ,A1);
	line(A1,A2);
	//line(A2,A3);
	//line(A4,A5);
	drawArc1 (M1);
	line(A6,A7);
	//line(A7,A8);
	line(A1,A18);
	//line(A8,A18);
	//circle(O1);
	My_O1.DrawJoint ();
	My_O1.JointToPoint(A2);
	line(C7,C8);
	line(C9,C10);
	My_O2.JointToPoint (A5);
	My_O3 .JointToPoint (A7);
	glPopMatrix ();
	/////////////////////////手臂部分
	glPushMatrix ();
	glTranslatef (0,(1-scale3)*O2[1]/90,0.0f);
	glScalef(scale2, scale3 , 1 );////////////////////反面
	//My_O6 .JointToPoint(O2);
	My_O6.JointToJoint (My_O7);
	//circle(O2);	
	My_O6 .DrawJoint ();
	My_O7 .DrawJoint ();
	My_O2 .DrawJoint ();
	My_O2 .JointToJoint(My_O6);
	
	glPopMatrix ();
	////////////////////腿的部分
	
	glPushMatrix ();
	glTranslatef (0,(1-scale4)*O3[1]/90,0.0f);
	glScalef(scale2, scale4 , 1 );		
	My_O5 .JointToPoint (m_A19);
	//circle(O3);	
	My_O4.DrawJoint  ();
	My_O5.DrawJoint  ();
	//My_O4 .JointToPoint(A9);
	My_O5.JointToJoint (My_O4);
	My_O3.DrawJoint  ();
	
	My_O3 .JointToPoint (A18);
	My_O3 .JointToJoint (My_O4);
	glPopMatrix ();	
	 glScaled (-1.0,1.0,1.0);
	glTranslatef (1.0,0,0);
	glScaled (scale5,1.0,1.0);
	//glScalef(1, scale2 , 1 );
	/////画第二部分的图
	line(B0,B1);
	line(B1,B2);
	line(B2,B3);
	line(B4,B5);
	line(B5,B6);
	line(B6,B7);
	line(B7,B8);
	line(B8,B9);
	
	line(B8,B20);
	line(B20,B19);
	line(B19,B18);
	line(B18,B17);
	line(B17,B16);
	line(B16,B15);
	line(B15,B2);
	line(B3,B4);
	line(D1,D2);
	line(D3,D4);
	drawArc (R1);
	drawArc (R2);
	drawArc (R3);
	/////////////////////腿的部分
	glPushMatrix ();
	glTranslatef (0,(1-scale4)*B8[1]/90,0.0f);
	glScalef(1, scale4 , 1 );
	
	m_B21[0]=My_T1.Ox+My_T1.dx;
	m_B21[1]=My_T1.Oy+My_T1.dy-1.5;
	m_B13[0]=m_B21[0]-8;
	m_B13[1]=m_B21[1]-3;
	m_B14[0]=m_B21[0]+4;
	m_B14[1]=m_B21[1]-6;
	line(m_B13,m_B21);
	line(m_B14,m_B21);
	My_T0.DrawJoint  ();
	My_T1.DrawJoint  ();
	My_T0.JointToPoint(B8);
	My_T0 .JointToJoint(My_T1);
	glPopMatrix ();
	/////////////////////////////
	glPopMatrix ();
	
	*/
}


  






