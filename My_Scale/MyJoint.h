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
	void DrawJoint(void);//绘制节点
	void LinkJoint(void);//连接节点
	void JointToJoint(MyJoint &);
	void JointToPoint(float a[]);
	float dx,dy;//移动位置的偏移量
	float Ox,Oy;//关节点的初始位置
	float width;//椭圆节点的宽度
	CPoint prePt,nowPt;//记录鼠标移动的轨迹	
	HDC hdc;
	HGLRC  hglrc;
	
	
};

