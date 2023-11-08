// OpenImage.cpp : implementation file
//

#include "pch.h"
#include "PhotoEditor.h"
#include "OpenImage.h"
#include "afxdialogex.h"


// COpenImage dialog

IMPLEMENT_DYNAMIC(COpenImage, CDialogEx)

COpenImage::COpenImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHOTOEDITOR_DIALOG, pParent)
{

}

COpenImage::~COpenImage()
{
}

void COpenImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpenImage, CDialogEx)
END_MESSAGE_MAP()


// COpenImage message handlers
