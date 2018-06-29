#include "stdafx.h"
#include "DrawFlag.h"


DrawFlag::DrawFlag(void)
{
}


DrawFlag::~DrawFlag(void)
{
	wglMakeCurrent (NULL,NULL);
	wglDeleteContext (hglrc);
	::ReleaseDC (m_hWnd ,hdc);
}

void DrawFlag::draw(int x,int y)
{
 
		hdc=::GetDC (m_hWnd );
		//创建渲染描述表
		hglrc =wglCreateContext (hdc);
		wglMakeCurrent (hdc,hglrc);//B171114012
		PAINTSTRUCT ps;
		//glClearColor( 0.0, 0.6, 0.0,1.0 );//改变背景色
	//glClearColor( 0.0, 1.0, 0.0,1.0 );//改变背景色
	glPushMatrix ();
	gluOrtho2D (0,2,0,2);
	//glClear (GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );	 
	glDisable(GL_DEPTH_TEST); 	
		//BeginPaint(&ps);	 
	    Rendercene(x,y);
//	   EndPaint(&ps);
	   glPopMatrix ();
	//glFlush ();
	SwapBuffers (hdc);
}
void DrawFlag::Rendercene(int x,int y)
{
  glColor3f(255,0,0); 
  glBegin(GL_POLYGON );
  glVertex2f (0,0);
  glVertex2f (1.0,1.0);
  glVertex2f (1.5,1.0);
  glVertex2f (1.0,1.5);
  glEnd();
}
