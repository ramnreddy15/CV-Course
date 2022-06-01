// Ram Reddy
// Period 4
// 04/17/2022

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
    vector<vector<Point3f> > objpoints;
    vector<Point2f> projectionPoints;
    vector<Point3f> cubePoints;
    vector<vector<Point2f> > imgpoints;
    std::vector<cv::Point3f> objp;
    Size patternsize(7,7); //interior number of corners
    
    Mat gray;

    // cubePoints.push_back(Point3f(0, 0, 2));
    // cubePoints.push_back(Point3f(1, 2, 2));
    // cubePoints.push_back(Point3f(0, 2, 2));
    // cubePoints.push_back(Point3f(2, 2, 0));
    // cubePoints.push_back(Point3f(2, 0, 2));
    // cubePoints.push_back(Point3f(2, 0, 0));
    // cubePoints.push_back(Point3f(0, 0, 0));
    // cubePoints.push_back(Point3f(0, 2, 0));
    cubePoints.push_back(Point3f(1, 1, 2));
    cubePoints.push_back(Point3f(1, -1, 2));
    cubePoints.push_back(Point3f(-1, -1, 2));
    cubePoints.push_back(Point3f(-1, 1, 2));
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
    VideoWriter output("vr.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), capture.get(CAP_PROP_FPS), cv::Size(frame.cols, frame.rows));
    while(!frame.empty()) {
        rotate(frame,frame,ROTATE_180);
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
                objpoints.push_back(objp);
                vector<Point2f> temp;
                temp.push_back(corners[18]);
                temp.push_back(corners[16]);
                temp.push_back(corners[24]);
                temp.push_back(corners[30]);
                temp.push_back(corners[32]);
                imgpoints.push_back(temp);
            
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
            objpoints.push_back(objp);
            vector<Point2f> temp;
            temp.push_back(cubeCorners[0]);
            temp.push_back(cubeCorners[1]);
            temp.push_back(cubeCorners[2]);
            temp.push_back(cubeCorners[3]);
            temp.push_back(cubeCorners[4]);
            imgpoints.push_back(temp);
            for (Point2f p : cubeCorners) {
                circle(frame, p,10,(255,0,0));
            }
        }
        output.write(frame);


        
//         number++;
//         if (number >= 100) {
//             Mat cameraMatrix,distCoeffs,R,T,R1,P;
//             calibrateCamera(objpoints, imgpoints, cv::Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);
//             std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
//             std::cout << "distCoeffs : " << distCoeffs << std::endl;
//             std::cout << "Rotation vector : " << R << std::endl;
//             std::cout << "Translation vector : " << T << std::endl;
//             solvePnP(objpoints[0], imgpoints[0], cameraMatrix, distCoeffs, R,T);
// //             Rodrigues(R,R1);
// //             P = cameraMatrix.dot()
//             projectPoints(cubePoints,R,T,cameraMatrix,distCoeffs,projectionPoints);
//             cout << projectionPoints << endl;
//             for(Point2f p: projectionPoints) {
                
//                 circle(frame, p,10,(0,0,255));
//             }
//             //     drawChessboardCorners(frame, patternsize, Mat(corners), patternfound);
//             imwrite("tesst.jpg", frame);
//             break;
//         }
        
        gray.copyTo(prev);
        capture.read(frame);

    }
    cout << "here" << endl;

    Mat cameraMatrix,distCoeffs,R,T,R1,P;
    calibrateCamera(objpoints, imgpoints, cv::Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);
    std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
    std::cout << "distCoeffs : " << distCoeffs << std::endl;
//     std::cout << "Rotation vector : " << R << std::endl;
//     std::cout << "Translation vector : " << T << std::endl;
    
    capture.release();
    output.release();

}

int main() {
    part1();
    return 0;
}