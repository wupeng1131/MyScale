#pragma once
#include "afxwin.h"
#include <glut.h>
#include <freeglut.h>
#include <freeglut_ext.h>
#include <freeglut_std.h>
#include <math.h>
#define  pi 3.1415926

class MyJoint 
{
public:
	
	MyJoint(float m_Ox,float m_Oy,float m_width);
	~MyJoint(void);
	void DrawJoint(void);//���ƽڵ�
	void LinkJoint(void);//���ӽڵ�
	void JointToJoint(MyJoint &);
	void JointToPoint(float a[]);
	float dx,dy;//�ƶ�λ�õ�ƫ����
	float Ox,Oy;//�ؽڵ�ĳ�ʼλ��
	float width;//��Բ�ڵ�Ŀ��
	CPoint prePt,nowPt;//��¼����ƶ��Ĺ켣	
	HDC hdc;
	HGLRC  hglrc;
	
	
};

