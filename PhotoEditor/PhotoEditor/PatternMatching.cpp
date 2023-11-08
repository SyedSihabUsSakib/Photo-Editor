// PatternMatching.cpp : implementation file
//

#include "pch.h"
#include "PhotoEditor.h"
#include "PatternMatching.h"
#include "afxdialogex.h"
#include "framework.h"
#include "PhotoEditorDlg.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "OpenImage.h"
using namespace cv;
using namespace std;

// CPatternMatching dialog

IMPLEMENT_DYNAMIC(CPatternMatching, CDialogEx)

CPatternMatching::CPatternMatching(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHOTOEDITOR_DIALOG, pParent)
{

}

CPatternMatching::~CPatternMatching()
{
}

void CPatternMatching::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatternMatching, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPatternMatching::OnBnClickedButtonPatternMatching)
END_MESSAGE_MAP()


// CPatternMatching message handlers


void CPatternMatching::OnBnClickedButtonPatternMatching()
{
	// TODO: Add your control notification handler code here

    
}
