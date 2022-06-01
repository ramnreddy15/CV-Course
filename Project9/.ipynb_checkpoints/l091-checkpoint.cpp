// Ram Reddy
// Period 4
// 05/29/2022

#include <stdio.h>

#define _USE_MATH_DEFINES

#include <cmath>

#include <iostream>

#include <fstream>

#include <opencv2/imgproc/types_c.h>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;

void part1() {
    Mat frame, prev, flow, temp;
    VideoCapture capture;
    vector<vector<Point3f> > objpoints, objpointsAll;
    vector<Point2f> projectionPoints;
    vector<Point3f> cubePoints;
    vector<vector<Point2f> > imgpoints, imgpointsAll;
    std::vector<cv::Point3f> objp;
    Size patternsize(7,7); //interior number of corners
    
    Mat gray;
    cubePoints.push_back(Point3f(1, 1, -2));
    cubePoints.push_back(Point3f(1, -1, -2));
    cubePoints.push_back(Point3f(-1, -1, -2));
    cubePoints.push_back(Point3f(-1, 1, -2));
    cubePoints.push_back(Point3f(1, 1, 0));
    cubePoints.push_back(Point3f(1, -1, 0));
    cubePoints.push_back(Point3f(-1, -1, 0));
    cubePoints.push_back(Point3f(-1, 1, 0));
    // for(int i{0}; i<7; i++)
    // {
    //     for(int j{0}; j<7; j++) {

    //     objp.push_back(cv::Point3f(j,i,0));
    //     }
    // }

    objp.push_back(Point3f(-1,-1,0));
    objp.push_back(Point3f(-1,1,0));
    objp.push_back(Point3f(0,0,0));
    objp.push_back(Point3f(1,1,0));
    objp.push_back(Point3f(1,-1,0));
    vector<Point2f> corners, cubeCorners;
    capture.open("withChessBoard.MOV");
    capture.read(frame);
    int count = 0;
    VideoWriter output("vr.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), capture.get(CAP_PROP_FPS), cv::Size(frame.cols, frame.rows));
    while(!frame.empty()) {
        // rotate(frame,frame,ROTATE_180);
 //source image
        cvtColor(frame, gray, CV_BGR2GRAY);
        vector<Point2f> newCorners = cubeCorners;
        vector<uchar> status;
        vector<float> err;
         //this will be filled by the detected corners
        //CALIB_CB_FAST_CHECK saves a lot of time on images
        //that do not contain any chessboard corners
        corners.clear();
        bool patternfound = findChessboardCorners(gray, patternsize, corners,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
        + CALIB_CB_FAST_CHECK);
        if(patternfound) {
                cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
                for (Point2f p : corners) {
                    circle(frame, p,10,(255,0,0));
                }
                vector<Point2f> temp;
                temp.push_back(corners[18]);
                temp.push_back(corners[16]);
                temp.push_back(corners[24]);
                temp.push_back(corners[30]);
                temp.push_back(corners[32]);
                objpointsAll.push_back(objp);
                imgpointsAll.push_back(temp);
                if(count%5 == 0) {
                    objpoints.push_back(objp);
                    imgpoints.push_back(temp);                    
                }

            
                cubeCorners.clear();
                cubeCorners.push_back(corners[18]);
                cubeCorners.push_back(corners[16]);
                cubeCorners.push_back(corners[24]);
                cubeCorners.push_back(corners[30]);
                cubeCorners.push_back(corners[32]);
                 circle(frame, corners[18],10,(0,0,255));
                  circle(frame, corners[16],10,(0,0,255));
            circle(frame, corners[24],10,(0,0,255));
                   circle(frame, corners[30],10,(0,0,255));
                    circle(frame, corners[32],10,(0,0,255));
            
        } 
        else {
            TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
            calcOpticalFlowPyrLK(prev, gray, cubeCorners, newCorners, status, err, Size(15,15), 2, criteria);
            cubeCorners = newCorners;
            vector<Point2f> temp;
            temp.push_back(cubeCorners[0]);
            temp.push_back(cubeCorners[1]);
            temp.push_back(cubeCorners[2]);
            temp.push_back(cubeCorners[3]);
            temp.push_back(cubeCorners[4]);
            objpointsAll.push_back(objp);
            imgpointsAll.push_back(temp);   
            if(count %5 == 0) {
                objpoints.push_back(objp);
                imgpoints.push_back(temp);                
            }

            for (Point2f p : cubeCorners) {
                circle(frame, p,10,(255,0,0));
            }
        }
        count++;
        output.write(frame);
        
        gray.copyTo(prev);
        capture.read(frame);

    }
    cout << objpoints.size() << endl;
    capture.release();
    Mat cameraMatrix,distCoeffs,R,T;
    calibrateCamera(objpoints, imgpoints, cv::Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);
    std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
    std::cout << "distCoeffs : " << distCoeffs << std::endl;
    capture.open("withChessBoard.MOV");
    vector<Point2i> lines;
    for(int i =0; i<cubePoints.size(); i++) {
    for(int j=i+1; j<cubePoints.size(); j++) {
        int y = cubePoints[i].y;
        int z = cubePoints[i].z;
        int x1 = cubePoints[j].x;
        int y1 = cubePoints[j].y;
        int z1 = cubePoints[j].z;
        int x = cubePoints[i].x;
        if(sqrt(pow(x1-x,2)+pow(y1-y,2)+pow(z1-z,2)) == 2) {
            lines.push_back(Point2i(i,j));
        }
    }
}
    count = 0;
    capture.read(frame);
    while(!frame.empty()) {
        solvePnP(objpointsAll[count], imgpointsAll[count], cameraMatrix, distCoeffs, R,T);
        projectPoints(cubePoints,R,T,cameraMatrix,distCoeffs,projectionPoints);
        for(Point2f p: projectionPoints) {           
            circle(frame, p,10,(0,255,2505));
        }    
        for(Point2i l:lines) {
            line(frame, projectionPoints[l.x], projectionPoints[l.y], Scalar(255,0,0),5);
        }
        count++;
        output.write(frame);
        capture.read(frame);
    }
    
    output.release();

}

int main() {
    part1();
    return 0;
}