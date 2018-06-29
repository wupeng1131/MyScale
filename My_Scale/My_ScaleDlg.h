
// My_ScaleDlg.h : 头文件
//

#pragma once
#include "MyOpenGL.h"
#include "afxcmn.h"
#include <iostream>
using namespace std; 
// CMy_ScaleDlg 对话框
//Joint My_O1(15,-2.5,2.5);

class CMy_ScaleDlg : public CDialogEx
{
// 构造
public:
	CMy_ScaleDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMy_ScaleDlg(void);
	MyOpenGL* m_GL;
// 对话框数据
	enum { IDD = IDD_MY_SCALE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:  
GLbyte* colorArr;
 GLbyte* judgeArr1;
 GLbyte* judgeArr2;
GLint viewPort[4];  
double location[30];
GLint location2[30];
GLint Waist_X[6];
int winWidth;  
int winHeight;  

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void glGrab();
	afx_msg void saveColorData2Img ();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	CSliderCtrl m_Slider;

	afx_msg void OnNMCustomdrawS1(NMHDR *pNMHDR, LRESULT *pResult);
	 float m_num;
	 float m_num2;
	 float m_num3;
	 float m_num4;
	 float m_num5;
	 float m_num_x,m_num_y;
	 afx_msg void OnNMCustomdrawS2(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnNMCustomdrawS3(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnNMCustomdrawS4(NMHDR *pNMHDR, LRESULT *pResult);
	 CSliderCtrl m_Slider2;
	 CSliderCtrl m_Slider3;
	 CSliderCtrl m_Slider4;
	 CSliderCtrl m_Slider5;
	 afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	 int Radio1;
	 afx_msg void OnBnClickedRadio1();
	 afx_msg void OnNMCustomdrawS5(NMHDR *pNMHDR, LRESULT *pResult);
	 
	 afx_msg void OnBnClickedCancel();
	 afx_msg void OnBnClickedButton1();
	 afx_msg void OnEnChangeEdit();
	 afx_msg void OnBnClickedButton2();
	 afx_msg void OnBnClickedButton3();
	 double m_modulus;
};
