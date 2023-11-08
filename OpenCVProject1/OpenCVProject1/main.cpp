#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace cv;
using namespace std;

bool draw = false, inside = false;
int initX = -1, initY = -1, endX = -1, endY = -1, iStartX = -1, iStartY = -1, iEndX = -1, iEndY = -1;
int mnX, mnY, mxX, mxY;
int moveTrackbarValue = -1;
int initialTrackbarValue = 1, previousVal = 1;
void onTrackbarChange(int value, void* userData)
{
    Mat* img = static_cast<Mat*>(userData);
    Mat trackImg = img->clone();
    moveTrackbarValue = value;
    if (value < previousVal) {
        mxX -= value;
        mxY -= value;
        mxX = max(mxX, mnX);
        mxY = max(mxY, mnY);
    }
    else if (value > previousVal)
    {
        mxX += value;
        mxY += value;
        mxX = min(mxX, trackImg.cols - 1);
        mxY = min(mxY, trackImg.rows - 1);
    }
    
    rectangle(trackImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 2);
    imshow("Painter", trackImg);
    previousVal = value;
}
void onEvent(int event, int x, int y, int flags, void* userdata)
{
    Mat* originalImage = static_cast<cv::Mat*>(userdata);
    if (event == EVENT_LBUTTONDOWN)
    {
        cout << x << " " << y << endl;
        if (initX != -1&& (x >= mnX && x <= mxX && y >= mnY && y <= mxY))
        {
            inside = true;
            iStartX = x-mnX;
            iStartY = y - mnY;
            iEndX = mxX - x;
            iEndY = mxY - y;
        }
        else {
            inside = false;
            initX = x;
            initY = y;
            draw = true;
        }
    }
    else if (event == EVENT_MOUSEMOVE)
    {
        //cout << "draw-->" << draw << endl;
        //cout << "inside event_mouseMove --> " << x << " " << y << endl;
        if (draw)
        {
            Mat copyImg = originalImage->clone();
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
            
            rectangle(copyImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 1);
            imshow("Painter", copyImg);
        }
        else if (inside)
        {
            Mat copyImg = originalImage->clone();
            mnX = x - iStartX;
            mnY = y - iStartY;
            mxX = x + iEndX;
            mxY = y + iEndY;
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
            Mat copyImg = originalImage->clone();
            rectangle(copyImg, Point(mnX, mnY), Point(mxX, mxY), Scalar(255, 255, 255), 2);
            imshow("Painter", copyImg);
        }
        else if (inside)
        {
            inside = false;
            Mat copyImg = originalImage->clone();
            rectangle(copyImg, Point(mnX,mnY), Point(mxX, mxY), Scalar(255, 255, 255), 2);
            imshow("Painter", copyImg);
        }
    }
    else if (event == EVENT_LBUTTONDBLCLK)
    {
       
            ofstream outputFile("ROI.csv");
            /*int mnX = min(initX, endX);
            int mxX = max(initX, endX);
            int mnY = min(initY, endY);
            int mxY = max(initY, endY);*/
            Mat copyImg = originalImage->clone();
            
            for (int row = mnY ; row <= mxY; row++)
            {
                copyImg.at<Vec3b>(row, mnX+1) = Vec3b(0, 0, 0);
                for (int col = mnX; col <= mxX ; col++)
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
            int width = mxX-mnX + 1;
            int height = mxY-mnY + 1;
            Mat org = originalImage->clone();
            Mat croppedImg = org(Rect(mnX, mnY, width, height));
            imshow("Cropped ROI", croppedImg);

        
        

        
    }
}

int main()
{   
    //"D:/Image Processing/W2P1TOP.bmp"
    //C:/Users/FSMB/Downloads/ababil.jpg
    cv::Mat img = cv:: imread("D:/Image Processing/W2P1TOP.bmp");
    Mat org = img.clone();
    Mat cop = img.clone();
    cout << "The size of the image is " << img.rows << " x " << img.cols << endl;
    //resize(img, img, Size(600, 400));
    namedWindow("First OpenCV Application");
    imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 90, 45);
    Mat result, outputImage;
    flip(img, result, 1);
    //resize(result, outputImage, Size(600, 400));
    

    //Flipping the image
    // 
    //namedWindow("Flip Operation Result");
    //cout << "The size of the output image is " << outputImage.rows << " X " << outputImage.cols << endl;
    ///*int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    //int screenHeight = GetSystemMetrics(SM_CYSCREEN);*/
    //imshow("Flip Operation Result", result);
    //cv::moveWindow("Flip Operation Result", 700, 45);


    //Converting the RGB image to gray scale image
    Mat gray;
    Mat threshGray = img.clone();
    Mat cannyGray = img.clone();
    cvtColor(img, gray, COLOR_BGR2GRAY);
    namedWindow("Gray Scale Image");
    imshow("Gray Scale Image", gray);
    moveWindow("Gray Scale Image", 90, 490);

    //Extract Line Information

    ofstream outputFile("pixelValues.csv");
    if (!outputFile.is_open())
    {
        cerr << "Could not open the output file" << endl;
        return -1;
    }
    vector<int> rowPixels;
    cout <<"I am gray Cols--->>"<< gray.cols << endl;
    for (int col=0;col<gray.cols;col++)
    {
        uchar pixelValue = gray.at<uchar>(507, col);
        //cop.at<cv::Vec3b>(507, col) = cv::Vec3b(0, 0, 0);
        outputFile << static_cast<int>(static_cast<int>(gray.at<uchar>(507, col)));
        rowPixels.push_back(static_cast<int>(gray.at<uchar>(507, col)));
        if (col < gray.cols - 1)
        {
            outputFile << ",";
        }
    }
    outputFile.close();
    imshow("Extract Row 507", cop);


    //smoothing on the line 508 using 1*3 filter
    ofstream smoothFile("SmoothedFile.csv");
    if (!smoothFile.is_open())
    {
        cerr << "Could not open the smoothedFile" << endl;
        return -1;
    }
    int left = 0, avg = 0;
    int padSum = rowPixels[0] + rowPixels[1] + rowPixels[2] + rowPixels[0] + rowPixels[0] +static_cast<int>(gray.at<uchar>(506,0)*3)+static_cast<int>(gray.at<uchar>(508, 0) * 3) + static_cast<int>(gray.at<uchar>(508, 1) + static_cast<int>(gray.at<uchar>(508, 2))) + static_cast<int>(gray.at<uchar>(506, 1) + static_cast<int>(gray.at<uchar>(506, 2)));
    padSum += static_cast<int>(gray.at<uchar>(505, 0) * 3) + static_cast<int>(gray.at<uchar>(509, 0) * 3) + static_cast<int>(gray.at<uchar>(509, 1) + static_cast<int>(gray.at<uchar>(509, 2))) + static_cast<int>(gray.at<uchar>(505, 1) + static_cast<int>(gray.at<uchar>(505, 2)));
    avg = padSum / 25;
    smoothFile << avg;
    smoothFile << ",";
    padSum -= (rowPixels[0] + static_cast<int>(gray.at<uchar>(505, 0)) + static_cast<int>(gray.at<uchar>(509, 0)) + static_cast<int>(gray.at<uchar>(506, 0)) + static_cast<int>(gray.at<uchar>(508, 0)));
    padSum += static_cast<int>(gray.at<uchar>(506, 3)) + static_cast<int>(gray.at<uchar>(505, 3)) + static_cast<int>(gray.at<uchar>(508, 3)) + static_cast<int>(gray.at<uchar>(509, 3)) + rowPixels[3];
    avg = padSum / 25;
    smoothFile << avg;
    smoothFile << ",";
    int sum = padSum - (rowPixels[0] + static_cast<int>(gray.at<uchar>(505, 0)) + static_cast<int>(gray.at<uchar>(509, 0)) + static_cast<int>(gray.at<uchar>(506, 0)) + static_cast<int>(gray.at<uchar>(508, 0)));
    sum+= static_cast<int>(gray.at<uchar>(506, 4)) + static_cast<int>(gray.at<uchar>(505, 4)) + static_cast<int>(gray.at<uchar>(508, 4)) + static_cast<int>(gray.at<uchar>(509, 4))+ rowPixels[4];
   
    for (int idx = 5; idx < rowPixels.size(); idx++) {
        avg = sum / 25;
        smoothFile << avg;
        sum -= (rowPixels[left] + static_cast<int>(gray.at<uchar>(505, left)) + static_cast<int>(gray.at<uchar>(509, left)) + static_cast<int>(gray.at<uchar>(506, left)) + static_cast<int>(gray.at<uchar>(508, left)));;
        sum += static_cast<int>(gray.at<uchar>(506, idx)) + static_cast<int>(gray.at<uchar>(505, idx)) + static_cast<int>(gray.at<uchar>(508, idx)) + static_cast<int>(gray.at<uchar>(509, idx)) + rowPixels[idx];
        smoothFile << ",";    
        left++;
        cout << avg << " ";
    }
    avg = sum / 25;
    cout << avg << endl;
    smoothFile << avg;
    smoothFile << ",";
    sum -= (rowPixels[(int)rowPixels.size() - 3] + static_cast<int>(gray.at<uchar>(505, (int)rowPixels.size() - 3)) + static_cast<int>(gray.at<uchar>(509, (int)rowPixels.size() - 3)) + static_cast<int>(gray.at<uchar>(506, (int)rowPixels.size() - 3)) + static_cast<int>(gray.at<uchar>(508, (int)rowPixels.size() - 3)));
    sum += static_cast<int>(gray.at<uchar>(506, (int)rowPixels.size() - 2)) + static_cast<int>(gray.at<uchar>(505, (int)rowPixels.size() - 2)) + static_cast<int>(gray.at<uchar>(508, (int)rowPixels.size() - 2)) + static_cast<int>(gray.at<uchar>(509, (int)rowPixels.size() - 2)) + rowPixels[(int)rowPixels.size() - 2];
    //padSum = rowPixels[(int)rowPixels.size() - 4] + rowPixels[(int)rowPixels.size() - 3] + rowPixels[(int)rowPixels.size()-2] + rowPixels[(int)rowPixels.size() - 1] + rowPixels[(int)rowPixels.size() - 1];
    avg = sum / 25;
    smoothFile << avg;
    smoothFile << ",";
    sum -= (rowPixels[(int)rowPixels.size() - 2] + static_cast<int>(gray.at<uchar>(505, (int)rowPixels.size() - 2)) + static_cast<int>(gray.at<uchar>(509, (int)rowPixels.size() - 2)) + static_cast<int>(gray.at<uchar>(506, (int)rowPixels.size() - 2)) + static_cast<int>(gray.at<uchar>(508, (int)rowPixels.size() - 2)));
    sum += static_cast<int>(gray.at<uchar>(506, (int)rowPixels.size() - 1)) + static_cast<int>(gray.at<uchar>(505, (int)rowPixels.size() - 1)) + static_cast<int>(gray.at<uchar>(508, (int)rowPixels.size() - 1)) + static_cast<int>(gray.at<uchar>(509, (int)rowPixels.size() - 1)) + rowPixels[(int)rowPixels.size() - 1];
    //padSum = rowPixels[(int)rowPixels.size() - 1] + rowPixels[(int)rowPixels.size() - 3] + rowPixels[(int)rowPixels.size() - 2] + rowPixels[(int)rowPixels.size() - 1] + rowPixels[(int)rowPixels.size() - 1];
    avg = sum / 25;
    smoothFile << avg;
    smoothFile.close();

    //Step Height of the CD
    int stepHeight = 0, curMin = 1e9 + 7, curMax = 0;
    bool goingLow = false;
    int prevVal = rowPixels.front();
    
    for (auto i : rowPixels)
    {
        if (i < prevVal && !goingLow) {
            curMin = i;
            goingLow = true;
        }
        else if (i > prevVal){
            goingLow = false;
            //cout << curMax << " " << curMin << "-->"<<curMax-curMin<< endl;
            stepHeight = max(stepHeight, curMax - curMin);
            curMax = i;
        }
        prevVal = i;
    }
    cout << "The Step Height of the CD is ---> " << stepHeight << endl;

    //Hough Circle Detection
  
    //imshow("I am gray Image", gray);
    GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);
    //imshow("I am gaussian blur img", gray);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows/16, 20, 20, 0, 0);
    Mat linedImage = img.clone();
    for (const auto& circle : circles) {
        cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
        int radius = cvRound(circle[2]);
        cv::circle(img, center, 1, cv::Scalar(0, 255, 0), -1, 8, 0);
        cv::circle(img, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }
    imshow("Detected Circles", img);


    //Drawing a line on the Image on 30 degree angle

    Point startPoint(1, 1);
    Point endPoint(1280, 1280*tan(30*CV_PI/180.0));
    Scalar lineColor(0, 222, 0);
    line(linedImage, startPoint, endPoint, lineColor, 1);
    imshow("Image with 30 Degree line", linedImage);

    //Binary Thresholding

    threshold(gray, threshGray, 100, 255, cv::THRESH_BINARY);
    imshow("Thresholded Image",threshGray);

    //Canny Edge Detection
    Mat cannyImage;
    Canny(gray, cannyImage, 10, 60);
    imshow("Canny Edge Detected", cannyImage);

    //Dynamic region selection
    Mat regImg = org.clone();
    namedWindow("Painter");
    imshow("Painter", regImg);
    setMouseCallback("Painter", onEvent, &regImg);

    //Adding Trackbar to Control Dynamic Region Selection
    namedWindow("Tracker");
    createTrackbar("Size", "Tracker", &initialTrackbarValue, 200, onTrackbarChange, &regImg);

    /*cv::waitKey(0);
    cv::destroyAllWindows();*/
    //return 0;

    //Pattern Matching
    cv::Mat sourceImage = cv::imread("D:/Image Processing/D2IR.bmp", cv::IMREAD_COLOR);
    cv::Mat templateImage = cv::imread("D:/Image Processing/cropped_image.jpg", cv::IMREAD_COLOR);

    if (sourceImage.empty() || templateImage.empty()) {
        std::cerr << "Could not open or find the images" << std::endl;
        return -1;
    }

    // Create a result image to store the match result
    int resultWidth = sourceImage.cols - templateImage.cols + 1;
    int resultHeight = sourceImage.rows - templateImage.rows + 1;
    cv::Mat resultImage(resultHeight, resultWidth, CV_32FC1); // CV_32FC1 is for floating-point results

    // Perform template matching
    cv::matchTemplate(sourceImage, templateImage, resultImage, cv::TM_CCOEFF_NORMED);

    // Find the location of the best match (maximum value)
    double minValue, maxValue;
    cv::Point minLocation, maxLocation;
    cv::minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation);

    // Draw a rectangle around the best match
    cv::Rect bestMatchRect(maxLocation, cv::Size(templateImage.cols, templateImage.rows));
    cv::rectangle(sourceImage, bestMatchRect, cv::Scalar(0, 0, 255), 2); // Red rectangle

    // Display the result
    cv::imshow("Template Matching Result", sourceImage);
    cv::waitKey(0);
    //cv::Mat sourceImage = cv::imread("D:/Image Processing/W2P1TOP.bmp", cv::IMREAD_COLOR);
    //cv::Mat templateImage = cv::imread("D:/Image Processing/cropped_image.jpg", cv::IMREAD_COLOR);

    //if (sourceImage.empty() || templateImage.empty()) {
    //    std::cerr << "Could not open or find the image" << std::endl;
    //    return -1;
    //}

    //// Perform template matching
    //cv::Mat res;
    //cv::matchTemplate(sourceImage, templateImage, res, cv::TM_CCOEFF_NORMED);

    //double threshold = 0.1; // Adjust this threshold as needed
    //while (true) {
    //    double minVal, maxVal;
    //    cv::Point minLoc, maxLoc;
    //    cv::minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);

    //    if (maxVal >= threshold) {
    //        // Draw a rectangle around the found instance
    //        cv::Rect matchRect(maxLoc, cv::Size(templateImage.cols, templateImage.rows));
    //        cv::rectangle(sourceImage, matchRect, cv::Scalar(0, 0, 255), 2);

    //        // Mark this location as already processed (set the region to a low value)
    //        cv::floodFill(res, maxLoc, cv::Scalar(0), 0, cv::Scalar(0.1), cv::Scalar(1.0));

    //    }
    //    else {
    //        break; // No more matches found
    //    }
    //}

    //// Display the source image with matches marked
    //cv::imshow("Pattern Matching", sourceImage);
    //cv::waitKey(0);

}