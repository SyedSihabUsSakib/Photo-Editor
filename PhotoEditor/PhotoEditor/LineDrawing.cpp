// LineDrawing.cpp : implementation file
//
#include "pch.h"
#include "PhotoEditor.h"
#include "LineDrawing.h"
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
#include <memblock.h>
#include <./chartdir.h>
using namespace std;
using namespace cv;

// CLineDrawing dialog

IMPLEMENT_DYNAMIC(CLineDrawing, CDialogEx)

CLineDrawing::CLineDrawing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LINEDRAWING1, pParent)
{

}

CLineDrawing::~CLineDrawing()
{
}

void CLineDrawing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLineDrawing, CDialogEx)
	ON_BN_CLICKED(IDC_SUBMIT, &CLineDrawing::OnBnClickedSubmit)
    ON_BN_CLICKED(IDC_2DCHART, &CLineDrawing::OnBnClicked2dchart)
    
END_MESSAGE_MAP()


// CLineDrawing message handlers


void CLineDrawing::OnBnClickedSubmit()
{
	// TODO: Add your control notification handler code here
	CString strValue;
	GetDlgItemText(IDC_EDIT1, strValue); // Replace IDC_EDIT_CONTROL with the actual ID of your edit control
	int nValue = _ttoi(strValue);
	//TRACE("the value is --> %d", nValue);
    ofstream outputFile("pixelValues.csv");
    if (!outputFile.is_open())
    {
        cerr << "Could not open the output file" << endl;
        //return -1;
    }
    vector<int> rowPixels;
    Mat img = cv::imread("D:/Image Processing/W2P1TOP.bmp");
    cout << "I am gray Cols--->>" << img.cols << endl;
    for (int col = 0; col < img.cols; col++)
    {
        uchar pixelValue = img.at<uchar>(nValue, col);
        outputFile << static_cast<int>(pixelValue);
        rowPixels.push_back(static_cast<int>(img.at<uchar>(nValue, col)));
        if (col < img.cols - 1)
        {
            outputFile << ",";
        }
        //img.at<cv::Vec3b>(nValue, col) = cv::Vec3b(0, 0, 0);

    }
    for (int col = 0; col < img.cols; col++)
    {
        img.at<cv::Vec3b>(nValue, col) = cv::Vec3b(0, 0, 0);

    }
    outputFile.close();
    imshow("Extract Row nValue", img);
}


void CLineDrawing::OnBnClicked2dchart()
{
    //// TODO: Add your control notification handler code here

    CString strValue;

    GetDlgItemText(IDC_EDIT1, strValue); // Replace IDC_EDIT_CONTROL with the actual ID of your edit control
    int nValue = _ttoi(strValue);
    vector<double> data;
    Mat img = cv::imread("D:/Image Processing/W2P1TOP.bmp");
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    for (int col = 0; col < img.cols; col++)
    {
        //uchar pixelValue = img.at<uchar>(nValue, col);

        ////outputFile << static_cast<int>(pixelValue);
        //data.push_back(static_cast<double>(pixelValue));
        img.at<cv::Vec3b>(nValue, col) = cv::Vec3b(0, 0, 0);
    }
    cout << "I am gray Cols--->>" << img.cols << endl;
    const char* labels[1280];
    for (int col = 0; col < gray.cols; col++)
    {
        uchar pixelValue = gray.at<uchar>(nValue, col);
        
        data.push_back(static_cast<double>(pixelValue));
        int value = static_cast<int>(pixelValue);
        string str = to_string(col+1);
        str += '\0';
        const int sz = str.size();
        char* ptr = (char*)malloc((sz) * sizeof(char));
      /*  char s[3];
        for (int i = 0; i < 3; i++)
        {
            s[i] = str[i];
        }

        labels[col] = s;*/
        if (ptr != NULL)
        {
            for (int i = 0; i < sz; i++)
            {
                ptr[i] = str[i];
            }
            //ptr[sz] = '\0';
            labels[col] = ptr;
        //free(ptr);
        }
        else TRACE("----->>>>>>>>NO memory found");

    }

    imshow("Extract Row nValue", img);
    const int data_size = data.size();

    // The labels for the line chart
    
    const int labels_size = (int)(sizeof(labels) / sizeof(*labels));

    // Create a XYChart object of size 250 x 250 pixels
    XYChart* c = new XYChart(1500, 800);
    
    
    // Set the plotarea at (30, 20) and of size 200 x 200 pixels
    c->setPlotArea(30, 30, 1450, 700);
    // Add a line chart layer using the given data
 
    c->addLineLayer(DoubleArray(data.data(), data_size));
    
    // Set the labels on the x axis.

    c->xAxis()->setLabels(StringArray(labels, labels_size));

    // Display 1 out of 3 labels on the x-axis.
    c->xAxis()->setLabelStep(50);
    // Output the chart
    c->makeChart("simpleline.png");
    //free up resources
    Mat img1 = imread("simpleline.png");
    //free(ptr);
    imshow("2D Chart", img1);
    delete c;
   /* for (int i = 0; i < 1280; i++)
    {
        free(labels[i]);
    }*/


}

