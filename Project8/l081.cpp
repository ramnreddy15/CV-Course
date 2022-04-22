// Ram Reddy
// Period 4
// 04/17/2022

#include <stdio.h>

#define _USE_MATH_DEFINES

#include <cmath>

#include <iostream>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;
// yaw, pitch, roll == x, y, x
Mat generateRotationMat(double x, double y, double z) {
  return (Mat_ < double > (3, 3) << cos(x) * cos(y), cos(x) * sin(y) * sin(z) - sin(x) * sin(y), cos(x) * sin(y) * cos(z) + sin(x) * sin(z), sin(x) * cos(y), sin(x) * sin(y) * sin(z) + cos(x) * cos(z), sin(x) * sin(y) * cos(z) - cos(x) * sin(z), (-1) * sin(y), cos(y) * sin(z), cos(y) * cos(z));
}

vector<Mat> getPoints(int vertices) {
    vector < Mat > shapePoints;
    double phi = 0.5*(1+sqrt(5));
    if(vertices == 4) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 1/sqrt(3), 0, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 0, 2/sqrt(6)));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1*(sqrt(3)/6), 0.5, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1*(sqrt(3)/6), -0.5, 0));       
    } else if (vertices == 8) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, -1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, -1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, -1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, -1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 1, -1));
    } else if (vertices == 6) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 0, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 0, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 0, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 0, 1));
    } else if(vertices == 12) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, phi, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -phi, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, phi, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -phi, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 0, phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 0, phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 0, -phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 0, -phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << phi, -1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << phi, 1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -phi, -1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -phi, 1, 0));
    } else if(vertices == 20) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, phi, -1/phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -phi, -1/phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, phi, 1/phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -phi, 1/phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1/phi, 0, phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1/phi, 0, -phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1/phi, 0, phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1/phi, 0, -phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -phi, 1/phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -phi, -1/phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << phi, 1/phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << phi, -1/phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, -1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, -1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, -1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, -1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 1, -1));
    }
    return shapePoints;
}

void part1() {
  int angle = 1;
  vector<int> vertices = {8,4,6,12,20};
  vector<double> sideLength = {2,1,sqrt(2),2,sqrt(5)+1};
  Mat rotationMatrix = generateRotationMat(0, (angle * M_PI) / 180, (angle * M_PI) / 180);
  VideoWriter output("rotation.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(600, 800));
  Mat frame = Mat::zeros(Size(600, 800), CV_8UC3);
  for(int type = 0; type<vertices.size(); type++) {
        vector < Mat > shapePoints = getPoints(vertices[type]);
      vector < Point > pointPairs;
      for (int i = 0; i < shapePoints.size(); i++) {
        for (int j = i; j < shapePoints.size(); j++) {
          double x1 = shapePoints[i].at < double > (0, 0), y1 = shapePoints[i].at < double > (1, 0), z1 = shapePoints[i].at < double > (2, 0), x2 = shapePoints[j].at < double > (0, 0), y2 = shapePoints[j].at < double > (1, 0), z2 = shapePoints[j].at < double > (2, 0);
          if (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == sideLength[type]) {
            pointPairs.push_back(Point(i, j));
          }
        }
      }
      for (int i = 0; i < 360 / angle; i++) {
        if (i != 0) {
          for (int j = 0; j < shapePoints.size(); j++) {
            shapePoints[j] = rotationMatrix * shapePoints[j];
          }
        }
        for (Point p: pointPairs) {
          double x1 = shapePoints[p.x].at < double > (0, 0), y1 = shapePoints[p.x].at < double > (1, 0), x2 = shapePoints[p.y].at < double > (0, 0), y2 = shapePoints[p.y].at < double > (1, 0);
          line(frame, Point(x1 * 50 + 300, y1 * 50 + 400), Point(x2 * 50 + 300, y2 * 50 + 400), Scalar(0, 127, 255), 1, LINE_AA);
        }
        output.write(frame);
        frame = Mat::zeros(Size(600, 800), CV_8UC3);
      }
  }
  output.release();
}

int main() {
  part1();
  return 0;
}