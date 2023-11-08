#pragma once
#include <vector>

// CCPen dialog

class CCPen : public CDialogEx
{
	DECLARE_DYNAMIC(CCPen)

public:
	CCPen(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCPen();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ImgControl;
	CRect m_Rectangle;
	CPoint startPoint;
	CPoint endPoint;
	bool isDrawing = false;
	afx_msg void OnBnClickedLimage();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
//public:
//	std::vector<CPoint> croppedPoints; // Store cropping points
//	CPoint startPoint; // Starting point for cropping
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);
//	virtual BOOL OnInitDialog();
//
//	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	DECLARE_MESSAGE_MAP()

};
