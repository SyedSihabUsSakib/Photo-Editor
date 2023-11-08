// CPen.cpp : implementation file
//

#include "pch.h"
#include "PhotoEditor.h"
#include "CPen.h"
#include "afxdialogex.h"


// CCPen dialog

IMPLEMENT_DYNAMIC(CCPen, CDialogEx)

CCPen::CCPen(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CPEN, pParent)
{

}

CCPen::~CCPen()
{
}

void CCPen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMGCONTROL, m_ImgControl);
}


BEGIN_MESSAGE_MAP(CCPen, CDialogEx)
	ON_BN_CLICKED(IDC_LIMAGE, &CCPen::OnBnClickedLimage)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCPen message handlers


void CCPen::OnBnClickedLimage()
{
	// TODO: Add your control notification handler code here
	CImage image;
	image.Load(_T("D:/Image Processing/W2P1TOP.bmp"));

	// Get the Picture Control's device context
	CClientDC dc(&m_ImgControl);

	// Draw the loaded image on the Picture Control
	image.BitBlt(dc.m_hDC, 0, 0, image.GetWidth(), image.GetHeight(), 0, 0);
	//TRACE("inside the load image --->>>");
}

void CCPen::OnLButtonDown(UINT nFlags, CPoint point)
{
	//TRACE("clicked the left button __->>>come on");
	if (!isDrawing)
	{
		startPoint = point;
		endPoint = point;
		isDrawing = true;
	}
}
void CCPen::OnLButtonUp(UINT nFlags, CPoint point)
{
	//TRACE("clicked the left button Upppppp__->>>come on %d",isDrawing);
	if (isDrawing)
	{
		endPoint = point;
		RedrawWindow();
		isDrawing = false;

		// Draw the rectangle or take any action here
		/*CClientDC dc(this);
		CRect rect(startPoint, endPoint);
		dc.Rectangle(&rect);*/
	}
}
void CCPen::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isDrawing)
	{
		endPoint = point;
		//RedrawWindow(); // Redraw the window to display the rectangle while dragging.
		
	}
}
void CCPen::OnPaint()
{
	CPaintDC dc(this);

	// Draw your image here (replace this with loading and displaying your image)
	// Example: dc.BitBlt(...);
	CImage image;
	image.Load(_T("D:/Image Processing/W2P1TOP.bmp"));

	// Get the Picture Control's device context
	CClientDC dcc(&m_ImgControl);

	// Draw the loaded image on the Picture Control
	image.BitBlt(dcc.m_hDC, 0, 0, image.GetWidth(), image.GetHeight(), 0, 0);
	if (isDrawing)
	{
		CBrush transparentBrush; // Create a transparent brush
		transparentBrush.CreateStockObject(NULL_BRUSH); // Make it a null brush

		CBrush* pOldBrush = dc.SelectObject(&transparentBrush); // Select the null brush

		CRect rect(startPoint, endPoint);
		dc.Rectangle(&rect);

		dc.SelectObject(pOldBrush); // Restore the original brush

	}

	CDialog::OnPaint(); // Call the base class implementation
}

// trying again


