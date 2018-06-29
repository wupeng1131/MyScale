#pragma once
#include "afxwin.h"
#include <glut.h>
#include <freeglut.h>
#include <freeglut_ext.h>
#include <freeglut_std.h>
class DrawFlag :
	public CWnd
{
public:
	DrawFlag(void);
	~DrawFlag(void);
	int MySetPixelFormat(HDC hDC);
	void Rendercene(int x,int y);
	//void begin();
	void draw(int x,int y);
	HDC hdc;
	HGLRC  hglrc;
	
	

public:
	 
};

