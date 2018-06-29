#include "stdafx.h"
#include "MyJoint.h"
#define X (nowPt.x-167.5)*0.268656
#define Y (67-nowPt.y)*0.268656
extern float scale;
extern void line(float a[2],float b[2]);

MyJoint ::MyJoint (float m_Ox,float m_Oy,float m_width):Ox(m_Ox),Oy(m_Oy),width(m_width)
{
  dx=0;dy=0;
  prePt .SetPoint (-1,-1);
  nowPt .SetPoint (-1,-1);
}
MyJoint::~MyJoint(void)
{}
    


void MyJoint::DrawJoint(void)
{
   GLfloat  cos_num,sin_num;
    
  glBegin (GL_POINTS);
  for (int i=0;i<100;i++)
  {
     cos_num =cos(i*2*pi/100.0);
	 sin_num =sin(i*2*pi/100.0);
	 glVertex2f ((Ox+dx)/90.0+(cos_num/180.0*width ),(Oy+dy)/90.0+(sin_num/180.0*width/2));
  }
  glEnd();
  
}

void MyJoint::JointToJoint (MyJoint &a)
{
	float O_1[2]={Ox+dx,Oy+dy};
	float O_2[2]={a.Ox +a.dx ,a.Oy +a.dy};
	line(O_1,O_2);
}
void MyJoint ::JointToPoint (float a[2])
{
  float O_1[2]={Ox+dx,Oy+dy};
  line(O_1,a);
}








