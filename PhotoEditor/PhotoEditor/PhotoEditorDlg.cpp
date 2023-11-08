
// PhotoEditorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PhotoEditor.h"
#include "PhotoEditorDlg.h"
#include "afxdialogex.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include "OpenImage.h"
#include <chartdir.h>
using namespace cv;
using namespace std;

int CPhotoEditorDlg::mnX = 200000000;
int CPhotoEditorDlg::draw = 0;
int CPhotoEditorDlg::inside = 0;
int CPhotoEditorDlg::initX = -1;
int CPhotoEditorDlg::initY = -1;
int CPhotoEditorDlg::endX = -1;
int CPhotoEditorDlg::endY = -1;
int CPhotoEditorDlg::iStartX = -1;
int CPhotoEditorDlg::iStartY = -1;
int CPhotoEditorDlg::iEndX = -1;
int CPhotoEditorDlg::iEndY = -1;
int CPhotoEditorDlg::mxX = -1;
int CPhotoEditorDlg::mnY = 200000000;
int CPhotoEditorDlg::mxY = -1;
int CPhotoEditorDlg::previousVal= -1;
int CPhotoEditorDlg::moveTrackbarValue = -1;
int CPhotoEditorDlg::initialTrackbarValue = 0;
int CPhotoEditorDlg::btnClick = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhotoEditorDlg dialog



CPhotoEditorDlg::CPhotoEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHOTOEDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhotoEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPhotoEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CPhotoEditorDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_OpenImage, &CPhotoEditorDlg::OnBnClickedOpenimage)
    //ON_BN_CLICKED(IDC_BUTTON1, &CPhotoEditorDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_DrawLine, &CPhotoEditorDlg::OnBnClickedDrawline)
    ON_BN_CLICKED(IDC_PatternMatching, &CPhotoEditorDlg::OnBnClickedPatternmatching)
    ON_BN_CLICKED(IDC_3DCHART, &CPhotoEditorDlg::OnBnClicked3dchart)
    ON_BN_CLICKED(IDC_CPen, &CPhotoEditorDlg::OnBnClickedCpen)
END_MESSAGE_MAP()


// CPhotoEditorDlg message handlers

BOOL CPhotoEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    m_Second.Create(IDD_LINEDRAWING1, this);
    m_Pen.Create(IDD_CPEN, this);
    //CPhotoEditorDlg imgObj;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhotoEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPhotoEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// draw the icon
        dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPhotoEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPhotoEditorDlg::onEvent(int event, int x, int y, int flags, void* userdata)
{
    
    //Mat* originalImage = static_cast<cv::Mat*>(userdata);
    //CPhotoEditorDlg* imgObj = static_cast<CPhotoEditorDlg*>(userdata);
    Mat originalImage = cv::imread("D:/Image Processing/MotherImage.bmp");
    //TRACE("previous values--->>\n initx and inity values--> % d % d--->> drawing value is -->>%d \n", initX, initY, draw);
    if (event == EVENT_LBUTTONDOWN)
    {
       /* cout << x << " " << y << endl;
        TRACE("%d %d\n", x, y);*/
       
        if ((x >= mnX && x <= mxX && y >= mnY && y <= mxY))
        {
            inside = 1;
            iStartX = x - mnX;
            iStartY = y - mnY;
            endX = mxX - x;
            endY = mxY - y;
            draw = 0;
        }
        else {
            inside = 0;
            initX = x;
            initY = y;
            draw = 1;
            endX = -1;
            endY = -1;
            TRACE("initx and inity values--> % d % d--->> drawing value is -->>%d \n", initX, initY, draw);
        }
    }
    else if (event == EVENT_MOUSEMOVE)
    {
        //cout << "draw-->" << draw << endl;
        //cout << "inside event_mouseMove --> " << x << " " << y << endl;
        //initX = x;
        //TRACE("%d initx value %d\n", draw, initX);

        if (draw)
        {
            //Mat copyImg = originalImage.clone();
            //TRACE("inside the drawing*******");
            Mat copyImg = originalImage.clone();

            endX = x;
            endY = y;
            mnX = min(initX, endX);
            mnX = max(0, mnX);
            mnY = min(initY, endY);
            mnY = max(mnY, 0);
            mxX = max(initX, endX);
            mxX = min(mxX, copyImg.cols - 1);
            mxY = max(initY, endY);
            mxY = min(mxY, copyImg.rows - 1);
           
            rectangle(copyImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255,1), 1);
            imshow("Painter", copyImg);
        }
        else if (inside)
        {
            //Mat copyImg = originalImage.clone();
            Mat copyImg = originalImage.clone();
            mnX = x - iStartX;
            mnY = y - iStartY;
            mxX = x + endX;
            mxY = y + endY;
            mnX = max(0, mnX);
            mnY = max(mnY, 0);
            mxX = min(mxX, copyImg.cols - 1);
            mxY = min(mxY, copyImg.rows - 1);

            rectangle(copyImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 1);
            imshow("Painter", copyImg);
        }
    }
    else if (event == EVENT_LBUTTONUP) {
        if (draw)
        {
            draw = false;
            //Mat copyImg = originalImage.clone();
            Mat copyImg = originalImage.clone();
            TRACE("btnUp --> draw--> %d \n", endX);
            if(endX!=-1)rectangle(copyImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 2);
            imshow("Painter", copyImg);
            TRACE("Inside--> %d\n", mxX);
            if (btnClick)
            {
                destroyWindow("Tracker");
                btnClick = 0;
            }
            if (endX != -1)
            {
                int val = mxX-mnX;
                //TRACE("%d\n", mxX);
                //int val = mxX;
                //TRACE("%d\n", mxX);

                Mat trackImg = cv::imread("D:/Image Processing/MotherImage.bmp");
                namedWindow("Tracker");
                previousVal = mxX-mnX;
                //previousVal = mxX;
                createTrackbar("Size", "Tracker", &val, max(trackImg.rows, trackImg.cols)-mnX, onTrackbarChange, &trackImg);
                btnClick = 1;
            }
            
        }
        else if (inside)
        {
            inside = false;
            //Mat copyImg = originalImage.clone();
            Mat copyImg = originalImage.clone();
            rectangle(copyImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 2);
            imshow("Painter", copyImg);
            if (btnClick)
            {
                destroyWindow("Tracker");
                btnClick = 0;
            }
            int val = mxX-mnX;
            TRACE("%d\n", mxX);
            //int val = mxX;
            TRACE("%d\n", mxX);

            Mat trackImg = cv::imread("D:/Image Processing/MotherImage.bmp");
            namedWindow("Tracker");
            previousVal = mxX-mnX;
            //previousVal = mxX;
            createTrackbar("Size", "Tracker", &val, max(trackImg.rows, trackImg.cols)-mnX, onTrackbarChange, &trackImg);
            btnClick = 1;
        }
        //Adding Trackbar to Control Dynamic Region Selection
        //Mat copyImg = originalImage.clone();
        // int tmpMn = mnX;
        // int tmpMx = mxX;
        // //int val = mxX - mnX;
        // int val = 0;

        /*namedWindow("Tracker");
        createTrackbar("Size", "Tracker", &val, 500, onTrackbarChange,&copyImg);
        btnClick = 1;*/
        
    }
    else if (event == EVENT_LBUTTONDBLCLK)
    {

        ofstream outputFile("ROI.csv");
        /*int mnX = min(initX, endX);
        int mxX = max(initX, endX);
        int mnY = min(initY, endY);
        int mxY = max(initY, endY);*/
        //Mat copyImg = originalImage.clone();
        Mat copyImg = originalImage.clone();

        for (int row = mnY; row <= mxY; row++)
        {
            copyImg.at<Vec3b>(row, mnX + 1) = Vec3b(0, 0, 0);
            for (int col = mnX; col <= mxX; col++)
            {
                //cout << row << " " << col << " uchar---> ";
                uchar pixelValue = copyImg.at<uchar>(row, col);
                /*cout << pixelValue << " int value--=> ";
                cout << static_cast<int>(pixelValue) << endl;*/
                outputFile << static_cast<int>(pixelValue);
                //rowPixels.push_back(static_cast<int>(gray.at<uchar>(507, col)));
                if (col < mxX)
                {
                    outputFile << ",";
                }
            }
            outputFile << endl;

        }
        //imshow("strucked Line", copyImg);
        outputFile.close();
        /*cout << "mn and Max values" << endl;
        cout << mnX << " " << mnY << endl;
        cout << mxX << " " << mxY << endl;
        cout << copyImg.rows << " " << copyImg.cols << endl;*/
        int width = mxX - mnX + 1;
        int height = mxY - mnY + 1;
        //Mat org = originalImage.clone();
        Mat org = originalImage.clone();
        Mat croppedImg = org(Rect(mnX, mnY, width, height));
        imshow("Cropped ROI", croppedImg);
        cv::imwrite("D:/Image Processing/cropped_image.jpg", croppedImg);
       /* namedWindow("Tracker");
        createTrackbar("Size", "Tracker", &initialTrackbarValue, 200, onTrackbarChange, &copyImg);
        btnClick = 1;*/
        endX = -1;
    }
}

void CPhotoEditorDlg::onTrackbarChange(int value, void* userData)
{
    /*Mat* img = static_cast<Mat*>(userData);
    Mat trackImg = img->clone();*/
    Mat trackImg = cv::imread("D:/Image Processing/MotherImage.bmp");
    moveTrackbarValue = value;
    //TRACE("current val --> %d\n", moveTrackbarValue);
    //TRACE("prev val --> %d\n", previousVal);
    if (value < previousVal) {
        mxX -= (previousVal-value);
        mxY -= (previousVal-value);
        //mxY -= previousVal;
        mxX = max(mxX, mnX);
        mxY = max(mxY, mnY);
    }
    else if (value > previousVal)
    {
        mxX += (value-previousVal);
        mxY += (value-previousVal);
        //mxY += value;
        mxX = min(mxX, trackImg.cols - 1);
        mxY = min(mxY, trackImg.rows - 1);
    }

    rectangle(trackImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 2);
    imshow("Painter", trackImg);
    previousVal = value;
}

void CPhotoEditorDlg::OnBnClickedOpenimage()
{
    // TODO: Add your control notification handler code here
    // TODO: Add your control notification handler code here
     CPhotoEditorDlg::mnX = 200000000;
     CPhotoEditorDlg::draw = 0;
     CPhotoEditorDlg::inside = 0;
     CPhotoEditorDlg::initX = -1;
     CPhotoEditorDlg::initY = -1;
     CPhotoEditorDlg::endX = -1;
     CPhotoEditorDlg::endY = -1;
     CPhotoEditorDlg::iStartX = -1;
     CPhotoEditorDlg::iStartY = -1;
     CPhotoEditorDlg::iEndX = -1;
     CPhotoEditorDlg::iEndY = -1;
     CPhotoEditorDlg::mxX = -1;
     CPhotoEditorDlg::mnY = 200000000;
     CPhotoEditorDlg::mxY = -1;

    CPhotoEditorDlg imgObj;
    cv::Mat img = cv::imread("D:/Image Processing/MotherImage.bmp");
    //Dynamic region selection
    Mat regImg = img.clone();
    namedWindow("Painter");
    imshow("Painter", regImg);
    setMouseCallback("Painter", onEvent, &regImg);
    //initialTrackbarValue = mxX - mnX;
    /*namedWindow("Tracker");
    createTrackbar("Size", "Tracker", &initialTrackbarValue, 200, onTrackbarChange, &regImg);
    btnClick = 1;*/
}



void CPhotoEditorDlg::OnBnClickedPatternmatching()
{
    // TODO: Add your control notification handler code here
    cv::Mat sourceImage = cv::imread("D:/Image Processing/motherImage.bmp", cv::IMREAD_COLOR);
    cv::Mat templateImage = cv::imread("D:/Image Processing/cropped_image.jpg", cv::IMREAD_COLOR);

    if (sourceImage.empty() || templateImage.empty()) {
        std::cerr << "Could not open or find the images" << std::endl;
    }

    // Create a result image to store the match result
    resultWidth = sourceImage.cols - templateImage.cols + 1;
    resultHeight = sourceImage.rows - templateImage.rows + 1;
    cv::Mat resultImage(resultHeight, resultWidth, CV_32FC1); // CV_32FC1 is for floating-point results

    // Perform template matching
    cv::matchTemplate(sourceImage, templateImage, resultImage, cv::TM_CCOEFF_NORMED);

    // Find the location of the best match (maximum value)

    cv::Point minLocation, maxLocation;
    cv::minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation);

    // Draw a rectangle around the best match
    cv::Rect bestMatchRect(maxLocation, cv::Size(templateImage.cols, templateImage.rows));
    int templateDistance = sqrt(pow(sourceImage.cols/2-(maxLocation.x + templateImage.cols/2),2)+pow(sourceImage.rows/2- (maxLocation.y + templateImage.rows/2),2));
    TRACE("The Distance Between the center of the source image and the Matched Image is %d\n", templateDistance);
    cv::rectangle(sourceImage, bestMatchRect, cv::Scalar(0, 0, 255), 2); // Red rectangle

    // Display the result
    cv::imshow("Template Matching Result", sourceImage);
    cv::waitKey(0);
}

void CPhotoEditorDlg::OnBnClickedDrawline()
{
    // TODO: Add your control notification handler code here
    m_Second.ShowWindow(SW_SHOW);
}

void CPhotoEditorDlg::OnBnClicked3dchart()
{
    // TODO: Add your control notification handler code here
    Mat img = cv::imread("D:/Image Processing/cropped_image.jpg");
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // TODO: Add your control notification handler code here
    // The x and y coordinates of the grid
    vector<double> dataX, dataY;
    //double dataX[] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //const int dataX_size = (int)(sizeof(dataX) / sizeof(*dataX));
    //double dataY[] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //const int dataY_size = (int)(sizeof(dataY) / sizeof(*dataY));
    for (int i = 0; i < gray.rows; i++)
    {
        dataY.push_back(i);
    }
    for (int i = 0; i < gray.cols; i++)
    {
        dataX.push_back(i);
    }

    // The values at the grid points. In this example, we will compute the values using the formula
    // z = x * sin(y) + y * sin(x).
    vector<double>dataZ(dataX.size() * dataY.size());
    for (int yIndex = 0; yIndex < dataY.size(); ++yIndex) {
        double y = dataY[yIndex];
        for (int xIndex = 0; xIndex < dataX.size(); ++xIndex) {
            double x = dataX[xIndex];
            uchar pixelValue = gray.at<uchar>(yIndex, xIndex);

            //data.push_back();
            dataZ[yIndex * dataX.size() + xIndex] = static_cast<double>(pixelValue);
        }
    }

    // Create a SurfaceChart object of size 720 x 600 pixels
    SurfaceChart* c = new SurfaceChart(720, 600);

    // Add a title to the chart using 20 points Times New Roman Italic font
    c->addTitle("3D View of Cropped Image   ", "Times New Roman Italic", 20);

    // Set the center of the plot region at (350, 280), and set width x depth x height to 360 x 360
    // x 270 pixels
    c->setPlotRegion(350, 280, 360, 360, 270);
    // Set the data to use to plot the chart
    c->setData(DoubleArray(dataX.data(), dataX.size()), DoubleArray(dataY.data(), dataY.size()), DoubleArray(dataZ.data(),
        dataZ.size()));

    // Spline interpolate data to a 80 x 80 grid for a smooth surface
    c->setInterpolation(80, 80);

    // Add a color axis (the legend) in which the left center is anchored at (645, 270). Set the
    // length to 200 pixels and the labels on the right side.
    c->setColorAxis(645, 270, Chart::Left, 200, Chart::Right);

    // Set the x, y and z axis titles using 10 points Arial Bold font
    c->xAxis()->setTitle("X (nm)", "Arial Bold", 10);
    c->yAxis()->setTitle("Y (nm)", "Arial Bold", 10);
    c->zAxis()->setTitle("Pixel Intensity", "Arial Bold", 10);

    // Output the chart
    c->makeChart("surface.jpg");
    Mat image = imread("surface.jpg");
    imshow("3D Chart", image);
    //free up resources
    delete c;


}


void CPhotoEditorDlg::OnBnClickedCpen()
{
    // TODO: Add your control notification handler code here
    m_Pen.ShowWindow(SW_SHOW);
}
