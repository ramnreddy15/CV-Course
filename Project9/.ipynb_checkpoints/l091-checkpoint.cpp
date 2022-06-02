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
    vector < vector < Point3f > > objpoints, objpointsAll;
    vector < Point2f > projectionPoints;
    vector < Point3f > cubePoints;
    vector < vector < Point2f > > imgpoints, imgpointsAll;
    std::vector < cv::Point3f > objp;
    Size patternsize(7, 7);
    Mat gray;
    vector < Point2f > corners, cubeCorners;
    capture.open("withChessBoard.MOV");

    cubePoints.push_back(Point3f(1, 1, -2));
    cubePoints.push_back(Point3f(1, -1, -2));
    cubePoints.push_back(Point3f(-1, -1, -2));
    cubePoints.push_back(Point3f(-1, 1, -2));
    cubePoints.push_back(Point3f(1, 1, 0));
    cubePoints.push_back(Point3f(1, -1, 0));
    cubePoints.push_back(Point3f(-1, -1, 0));
    cubePoints.push_back(Point3f(-1, 1, 0));

    objp.push_back(Point3f(-1, -1, 0));
    objp.push_back(Point3f(-1, 1, 0));
    objp.push_back(Point3f(1, 1, 0));
    objp.push_back(Point3f(1, -1, 0));

    capture.read(frame);
    int count = 0;
    VideoWriter output("vr.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), capture.get(CAP_PROP_FPS), frame.size());
    while (!frame.empty()) {
        rotate(frame, frame, ROTATE_180);
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        vector < Point2f > newCorners;
        vector < uchar > status;
        vector < float > err;
        corners.clear();
        bool patternfound = findChessboardCorners(gray, patternsize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
        if (patternfound) {
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            for (Point2f p: corners) {
                circle(frame, p, 10, (255, 0, 0));
            }
            cubeCorners.clear();
            cubeCorners.push_back(corners[18]);
            cubeCorners.push_back(corners[16]);
            cubeCorners.push_back(corners[30]);
            cubeCorners.push_back(corners[32]);
            objpointsAll.push_back(objp);
            imgpointsAll.push_back(cubeCorners);
            if (count % 5 == 0) {
                objpoints.push_back(objp);
                imgpoints.push_back(cubeCorners);
            }


        } else {
            TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
            calcOpticalFlowPyrLK(prev, gray, cubeCorners, newCorners, status, err, Size(15, 15), 2, criteria);
            cubeCorners = newCorners;
            objpointsAll.push_back(objp);
            imgpointsAll.push_back(newCorners);
            if (count % 5 == 0) {
                objpoints.push_back(objp);
                imgpoints.push_back(newCorners);
            }
        }
        count++;
        gray.copyTo(prev);
        capture.read(frame);

    }
    capture.release();

    Mat cameraMatrix, distCoeffs, R, T;
    calibrateCamera(objpoints, imgpoints, gray.size(), cameraMatrix, distCoeffs, R, T);
    capture.open("withChessBoard.MOV");
    vector < Point2i > lines;
    for (int i = 0; i < cubePoints.size(); i++) {
        for (int j = i + 1; j < cubePoints.size(); j++) {
            int y = cubePoints[i].y;
            int z = cubePoints[i].z;
            int x1 = cubePoints[j].x;
            int y1 = cubePoints[j].y;
            int z1 = cubePoints[j].z;
            int x = cubePoints[i].x;
            if (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2) + pow(z1 - z, 2)) == 2) {
                lines.push_back(Point2i(i, j));
            }
        }
    }
    count = 0;
    capture.read(frame);
    while (!frame.empty()) {
        rotate(frame, frame, ROTATE_180);
        solvePnP(objpointsAll[count], imgpointsAll[count], cameraMatrix, distCoeffs, R, T);
        projectPoints(cubePoints, R, T, cameraMatrix, distCoeffs, projectionPoints);
        for (Point2f p: projectionPoints) {
            circle(frame, p, 10, (0, 255, 255));
        }
        for (Point2i l: lines) {
            line(frame, projectionPoints[l.x], projectionPoints[l.y], Scalar(255, 0, 0), 5);
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