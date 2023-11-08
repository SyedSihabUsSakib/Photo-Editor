#pragma once


// CPatternMatching dialog

class CPatternMatching : public CDialogEx
{
	DECLARE_DYNAMIC(CPatternMatching)

public:
	CPatternMatching(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPatternMatching();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOEDITOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPatternMatching();
};
