#pragma once
#include "MyJoint.h"


class MyOpenGL :
	public CWnd
{
public:
	MyOpenGL(void);
	~MyOpenGL(void);
	//��Ա����
	int MySetPixelFormat(HDC hDC);
	void Rendercene();
	void ChangeTexture( CString &strFilePath );//�����ı��������������ͼƬ��λ��
	//void draw();
	HDC hdc;
	HGLRC  hglrc;
	CPoint prePt,nowPt;/////////////////////////
	GLfloat step,s;
	MyJoint My_O6,My_O7,My_O4,My_O5,My_T0,My_T1,My_O1,My_O2,My_O3,My_p1,My_p2;
	
	DECLARE_MESSAGE_MAP ()

public:
	  afx_msg void OnPaint();
	  afx_msg int  OnCreate(LPCREATESTRUCT  lpCreateStruct);
	  afx_msg void OnMouseMove (UINT nFlags,CPoint point);
	//MyJoint My_O2,My_O1;
	  //Joint * m_Joint;
};



