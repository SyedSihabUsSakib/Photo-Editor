
// PhotoEditorDlg.h : header file
//

#pragma once
#include "LineDrawing.h"
#include "CPen.h"

// CPhotoEditorDlg dialog
class CPhotoEditorDlg : public CDialogEx
{
// Construction
public:
	CPhotoEditorDlg(CWnd* pParent = nullptr);	// standard constructor
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	static int draw, inside;
	static int initX, initY, endX, endY, iStartX, iStartY, iEndX, iEndY;
	static int mnX, mnY, mxX, mxY;
	static int moveTrackbarValue;
	static int initialTrackbarValue;
	static int btnClick;
	static int previousVal;
	static void onTrackbarChange(int value, void* userData);
	static void onEvent(int event, int x, int y, int flags, void* userdata);
	int resultWidth,resultHeight;
	double minValue, maxValue;
	afx_msg void OnBnClickedOpenimage();
	afx_msg void OnBnClickedDrawline();
	afx_msg void OnBnClickedPatternmatching();
public:
	CLineDrawing m_Second;
	afx_msg void OnBnClicked3dchart();
	afx_msg void OnBnClickedCpen();

public:
	CCPen m_Pen;
};
