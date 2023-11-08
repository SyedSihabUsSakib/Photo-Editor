#pragma once


// COpenImage dialog

class COpenImage : public CDialogEx
{
	DECLARE_DYNAMIC(COpenImage)

public:
	COpenImage(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COpenImage();
	/*static void onTrackbarChange(int value, void* userData);
	static void onEvent(int event, int x, int y, int flags, void* userdata);*/
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOEDITOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	/*public:
	bool draw = false, inside = false;
	int initX = -1, initY = -1, endX = -1, endY = -1, iStartX = -1, iStartY = -1, iEndX = -1, iEndY = -1;
	int mnX, mnY, mxX, mxY;
	int moveTrackbarValue = -1;
	int initialTrackbarValue = 1, previousVal = 1;*/
	
};
