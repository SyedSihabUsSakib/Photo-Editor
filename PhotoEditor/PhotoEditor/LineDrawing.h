#pragma once


// CLineDrawing dialog

class CLineDrawing : public CDialogEx
{
	DECLARE_DYNAMIC(CLineDrawing)

public:
	CLineDrawing(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CLineDrawing();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LineDrawing };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSubmit();
	afx_msg void OnBnClicked2dchart();
	
};
