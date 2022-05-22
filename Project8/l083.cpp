// Ram Reddy
// Period 4
// 04/29/2022

#include <stdio.h>

#define _USE_MATH_DEFINES

#include <cmath>

#include <iostream>

#include <fstream>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;
// yaw, pitch, roll == x, y, x
Mat generateRotationMat(double x, double y, double z) {
    return (Mat_ < double > (3, 3) << cos(x) * cos(y), cos(x) * sin(y) * sin(z) - sin(x) * sin(y), cos(x) * sin(y) * cos(z) + sin(x) * sin(z), sin(x) * cos(y), sin(x) * sin(y) * sin(z) + cos(x) * cos(z), sin(x) * sin(y) * cos(z) - cos(x) * sin(z), (-1) * sin(y), cos(y) * sin(z), cos(y) * cos(z));
}

vector < Mat > getPoints(int vertices) {
    vector < Mat > shapePoints;
    double phi = 0.5 * (1 + sqrt(5));
    if (vertices == 4) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 1 / sqrt(3), 0, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 0, 2 / sqrt(6)));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1 * (sqrt(3) / 6), 0.5, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1 * (sqrt(3) / 6), -0.5, 0));
    } else if (vertices == 8) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, -1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, -1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 1, 1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, -1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, -1, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 1, -1));
    } else if (vertices == 6) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 1, 0, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1, 0, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 1, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 0, -1));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, 0, 1));
    } else if (vertices == 12) {
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
    } else if (vertices == 20) {
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, phi, -1 / phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -phi, -1 / phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, phi, 1 / phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 0, -phi, 1 / phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1 / phi, 0, phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -1 / phi, 0, -phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1 / phi, 0, phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << 1 / phi, 0, -phi));
        shapePoints.push_back((Mat_ < double > (3, 1) << -phi, 1 / phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << -phi, -1 / phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << phi, 1 / phi, 0));
        shapePoints.push_back((Mat_ < double > (3, 1) << phi, -1 / phi, 0));
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
    int angle = 1, scale = 100, rows = 800, cols = 600, translateX = 300, translateY = 400;
    double phi = 0.5 * (1 + sqrt(5));
    double x1, x2, y1, y2, z1, z2;
    vector < int > vertices = {
        8,
        4,
        6,
        12,
        20
    };
    vector < double > sideLength = {
        2,
        1,
        sqrt(2),
        2,
        sqrt(5) - 1
    };
    Mat rotationMatrix = generateRotationMat(0, (angle * M_PI) / 180, (angle * M_PI) / 180);
    VideoWriter output("rotation.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(cols, rows));
    Mat frame = Mat::zeros(Size(cols, rows), CV_8UC3);
    ofstream outfile("coordinates.txt");
    for (int type = 0; type < vertices.size(); type++) {
        vector < Mat > shapePoints = getPoints(vertices[type]);
        vector < Point > pointPairs;
        for (int i = 0; i < shapePoints.size(); i++) {
            for (int j = i; j < shapePoints.size(); j++) {
                x1 = shapePoints[i].at < double > (0, 0), y1 = shapePoints[i].at < double > (1, 0), z1 = shapePoints[i].at < double > (2, 0), x2 = shapePoints[j].at < double > (0, 0), y2 = shapePoints[j].at < double > (1, 0), z2 = shapePoints[j].at < double > (2, 0);
                if (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == sideLength[type] || (vertices[type] == 20 && sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == 2 / phi)) {
                    pointPairs.push_back(Point(i, j));
                }
            }
        }
        for (int i = 0; i < 360; i += angle) {
            if (i != 0) {
                for (int j = 0; j < shapePoints.size(); j++) {
                    shapePoints[j] = rotationMatrix * shapePoints[j];
                }
            }
            if (type == 0 && i <= 3) {
                for (int j = 0; j < shapePoints.size(); j++) {
                    x2 = shapePoints[j].at < double > (0, 0), y2 = shapePoints[j].at < double > (1, 0), z2 = shapePoints[j].at < double > (2, 0);
                    if(i!=0) {
                        outfile << "(" << x2*scale << "," << y2*scale << "," << z2*scale << ")";
                    } else {
                        outfile << "(" << x2 << "," << y2 << "," << z2 << ")";
                    }
                    if (j != shapePoints.size() - 1) {
                        outfile << ", ";
                    }
                }
                outfile << endl;
            } else if (type == 0 && i == 4) {
                outfile.close();
            }
            for (Point p: pointPairs) {
                x1 = shapePoints[p.x].at < double > (0, 0), y1 = shapePoints[p.x].at < double > (1, 0), x2 = shapePoints[p.y].at < double > (0, 0), y2 = shapePoints[p.y].at < double > (1, 0);
                line(frame, Point(x1 * scale + translateX, y1 * scale + translateY), Point(x2 * scale + translateX, y2 * scale + translateY), Scalar(0, 127, 255), 1, LINE_AA);
            }
            output.write(frame);
            frame = Mat::zeros(Size(cols, rows), CV_8UC3);
        }
    }
    output.release();
}

void part2() {
    int angle = 1, scale = 100, rows = 800, cols = 600, translateX = 300, translateY = 400;
    double eyeX = 10, eyeY=0, eyeZ=0;
    double phi = 0.5 * (1 + sqrt(5));
    double x1, x2, y1, y2, z1, z2, dx, dy, dz, dist=5;
    vector < int > vertices = {
        8,
        4,
        6,
        12,
        20
    };
    vector < double > sideLength = {
        2,
        1,
        sqrt(2),
        2,
        sqrt(5) - 1
    };
    Mat rotationMatrix = generateRotationMat(0, (angle * M_PI) / 180, (angle * M_PI) / 180);
    VideoWriter output("rotation.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(cols, rows));
    Mat frame = Mat::zeros(Size(cols, rows), CV_8UC3);
    ofstream outfile("coordinates.txt");
    for (int type = 0; type < vertices.size(); type++) {
        vector < Mat > shapePoints = getPoints(vertices[type]);
        vector < Point > pointPairs;
        for (int i = 0; i < shapePoints.size(); i++) {
            for (int j = i; j < shapePoints.size(); j++) {
                x1 = shapePoints[i].at < double > (0, 0), y1 = shapePoints[i].at < double > (1, 0), z1 = shapePoints[i].at < double > (2, 0), x2 = shapePoints[j].at < double > (0, 0), y2 = shapePoints[j].at < double > (1, 0), z2 = shapePoints[j].at < double > (2, 0);
                if (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == sideLength[type] || (vertices[type] == 20 && sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == 2 / phi)) {
                    pointPairs.push_back(Point(i, j));
                }
            }
        }
        for (int i = 0; i < 360; i += angle) {
            if (i != 0) {
                for (int j = 0; j < shapePoints.size(); j++) {
                    shapePoints[j] = rotationMatrix * shapePoints[j];
                }
            }
            if (type == 0 && i <= 3) {
                for (int j = 0; j < shapePoints.size(); j++) {
                    x1 = shapePoints[j].at < double > (0, 0), y1 = shapePoints[j].at < double > (1, 0), z1= shapePoints[j].at < double > (2, 0);
                    double t1 = (dist-eyeX)/(x1-eyeX);
                    double tempY1 = t1*y1 + (1-t1)*eyeY;
                    double tempZ1 = t1*z1 + (1-t1)*eyeZ;
                    outfile << "(" << dist*scale << "," << tempY1*scale << "," << tempZ1*scale << ")";
                    if (j != shapePoints.size() - 1) {
                        outfile << ", ";
                    }
                }
                outfile << endl;
            } else if (type == 0 && i == 4) {
                outfile.close();
            }
            for (Point p: pointPairs) {
                x1 = shapePoints[p.x].at < double > (0, 0), y1 = shapePoints[p.x].at < double > (1, 0), z1= shapePoints[p.x].at < double > (2, 0), x2 = shapePoints[p.y].at < double > (0, 0), y2 = shapePoints[p.y].at < double > (1, 0), z2=shapePoints[p.y].at < double > (2, 0);
                double t1 = (dist-eyeX)/(x1-eyeX);
                double t2 = (dist-eyeX)/(x2-eyeX);
                double tempY1 = t1*y1 + (1-t1)*eyeY;
                double tempY2 = t2*y2 + (1-t2)*eyeY;
                double tempZ1 = t1*z1 + (1-t1)*eyeZ;
                double tempZ2 = t2*z2 + (1-t2)*eyeZ;
                y1 = tempY1;
                y2 = tempY2;
                x1 = tempZ1;
                x2 = tempZ2;
                line(frame, Point(x1 * scale + translateX, y1 * scale + translateY), Point(x2 * scale + translateX, y2 * scale + translateY), Scalar(0, 127, 255), 1, LINE_AA);
            }
            output.write(frame);
            frame = Mat::zeros(Size(cols, rows), CV_8UC3);
        }
    }
    output.release();
}

void part3() {
    int angle = 1, scale = 100, rows = 800, cols = 600, translateX = 300, translateY = 400;
    double eyeX = 10, eyeY=0, eyeZ=0;
    double phi = 0.5 * (1 + sqrt(5));
    double x1, x2, y1, y2, z1, z2, dx, dy, dz, dist=5;
    Vec<double,3> a,b,w1,c,w2;
    Vec<double,3> aPlane(5,2,3), n(1,2,3), eye(8,0.5,1.23), zeroV(0,0,0);
    vector < int > vertices = {
        8,
        4,
        6,
        12,
        20
    };
    vector < double > sideLength = {
        2,
        1,
        sqrt(2),
        2,
        sqrt(5) - 1
    };
    Mat rotationMatrix = generateRotationMat(0, (angle * M_PI) / 180, (angle * M_PI) / 180);
    VideoWriter output("rotation.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(cols, rows));
    Mat frame = Mat::zeros(Size(cols, rows), CV_8UC3);
    ofstream outfile("coordinates.txt");
    for (int type = 0; type < vertices.size(); type++) {
        vector < Mat > shapePoints = getPoints(vertices[type]);
        vector < Vec<double,3> > choosenPoints;
        vector < Point > pointPairs;
        for (int i = 0; i < shapePoints.size(); i++) {
            for (int j = i; j < shapePoints.size(); j++) {
                x1 = shapePoints[i].at < double > (0, 0), y1 = shapePoints[i].at < double > (1, 0), z1 = shapePoints[i].at < double > (2, 0), x2 = shapePoints[j].at < double > (0, 0), y2 = shapePoints[j].at < double > (1, 0), z2 = shapePoints[j].at < double > (2, 0);
                if (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == sideLength[type] || (vertices[type] == 20 && sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == 2 / phi)) {
                    pointPairs.push_back(Point(i, j));
                    if(choosenPoints.size() == 0) {
                        choosenPoints.push_back((Vec<double,3>(x1,y1,z1)));
                    } 
                    else if(choosenPoints.size() < 3) {
                        x1 = choosenPoints[0][0], y1 = choosenPoints[0][1], z1 = choosenPoints[0][2];
                        if(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == sideLength[type] || (vertices[type] == 20 && sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)) == 2 / phi)){
                            choosenPoints.push_back((Vec<double,3>(x2,y2,z2)));
                        }
                    }
                }
            }
        }
        a = choosenPoints[0] - choosenPoints[1];
        b = choosenPoints[2] - choosenPoints[1];
        w1 = (1/(sqrt((a[0]*a[0])+(a[1]*a[1])+(a[2]*a[2])))) * a;
        c = b - (b.dot(a)/a.dot(a))*a;
        w2 = (1/(sqrt((c[0]*c[0])+(c[1]*c[1])+(c[2]*c[2])))) * c;
        for (int i = 0; i < 360; i += angle) {
            if (i != 0) {
                for (int j = 0; j < shapePoints.size(); j++) {
                    shapePoints[j] = rotationMatrix * shapePoints[j];
                }
            }
            bool done = false;
            for (Point p: pointPairs) {
                x1 = shapePoints[p.x].at < double > (0, 0), y1 = shapePoints[p.x].at < double > (1, 0), z1= shapePoints[p.x].at < double > (2, 0), x2 = shapePoints[p.y].at < double > (0, 0), y2 = shapePoints[p.y].at < double > (1, 0), z2=shapePoints[p.y].at < double > (2, 0);
                Vec<double,3> tempP(x1,y1,z1), tempP2(x2,y2,z2);

                double t1 = (aPlane-eye).dot(n)/(tempP-eye).dot(n);
                Vec<double,3 > P01 = t1*(zeroV-eye)+eye;
                Vec<double,3 > Pv1 = t1*(tempP-eye)+eye;

                double t2 = (aPlane-eye).dot(n)/(tempP2-eye).dot(n);
                Vec<double,3 > P02 = t2*(zeroV-eye)+eye;
                Vec<double,3 > Pv2 = t2*(tempP2-eye)+eye;

                y1 = (Pv1-P01).dot(w2)/w2.dot(w2);
                y2 = (Pv2-P02).dot(w2)/w2.dot(w2);
                x1 = (Pv1-P01).dot(w1)/w1.dot(w1);
                x2 = (Pv2-P02).dot(w1)/w1.dot(w1);
                line(frame, Point(x1 * scale + translateX, y1 * scale + translateY), Point(x2 * scale + translateX, y2 * scale + translateY), Scalar(0, 127, 255), 1, LINE_AA);
                if(i==0 && !done) {
                    outfile << "The plane defined by (x-a)*n =0 is:\n  a = (" << aPlane[0]*100 << ", " << aPlane[1]*100 << ", " << aPlane[2] << ")\n  n = (" << n[0] << ","<<n[1]<<","<<n[2] << ")\nThe eye e is:\n  e = (" << eye[0]*100 << ", " << eye[1]*100 << ", " << eye[2]*100 << ")" <<  endl;
                    outfile << "The coordinates in the plane x = p0 + u*w1 + v*w2 is:\n (where p0 is the origin, preferraby the projection of the center of the cube in first frame, w1 and w2 are 2 perpendicular vertices in the plane)" << endl;
                    outfile << "  p0 = (" <<  P01[0] << "," << P01[1] << "," << P01[2] << ")" << endl;
                    outfile << "  w1 = (" << w1[0] << "," << w1[1] << "," << w1[2] << ")" << endl;
                    outfile << "  w2 = (" << w2[0] << "," << w2[1] << "," << w2[2] << ")\n" << endl;
                    done = true;
                }
                }
                if (type == 0 && i <= 3) {

                outfile << "The frame" << i+1 << " in 3d has the following edges:" << endl;                    
                for (Point p: pointPairs) {
                    x1 = shapePoints[p.x].at < double > (0, 0), y1 = shapePoints[p.x].at < double > (1, 0), z1= shapePoints[p.x].at < double > (2, 0), x2 = shapePoints[p.y].at < double > (0, 0), y2 = shapePoints[p.y].at < double > (1, 0), z2=shapePoints[p.y].at < double > (2, 0);
                    Vec<double,3> tempP(x1,y1,z1), tempP2(x2,y2,z2);

                    double t1 = (aPlane-eye).dot(n)/(tempP-eye).dot(n);
                    Vec<double,3 > P01 = t1*(zeroV-eye)+eye;
                    Vec<double,3 > Pv1 = t1*(tempP-eye)+eye;

                    double t2 = (aPlane-eye).dot(n)/(tempP2-eye).dot(n);
                    Vec<double,3 > P02 = t2*(zeroV-eye)+eye;
                    Vec<double,3 > Pv2 = t2*(tempP2-eye)+eye;       
                    outfile << "(" << x1*100 << "," << y1*100 << "," << z1*100 << "), (" << x2*100 << "," << y2*100 << "," << z2*100 << ")" << endl;
                }
                outfile << "\nThe frame" << i+1 << " in 2d has the following edges:" << endl;                    
                for (Point p: pointPairs) {
                    x1 = shapePoints[p.x].at < double > (0, 0), y1 = shapePoints[p.x].at < double > (1, 0), z1= shapePoints[p.x].at < double > (2, 0), x2 = shapePoints[p.y].at < double > (0, 0), y2 = shapePoints[p.y].at < double > (1, 0), z2=shapePoints[p.y].at < double > (2, 0);
                    Vec<double,3> tempP(x1,y1,z1), tempP2(x2,y2,z2);

                    double t1 = (aPlane-eye).dot(n)/(tempP-eye).dot(n);
                    Vec<double,3 > P01 = t1*(zeroV-eye)+eye;
                    Vec<double,3 > Pv1 = t1*(tempP-eye)+eye;

                    double t2 = (aPlane-eye).dot(n)/(tempP2-eye).dot(n);
                    Vec<double,3 > P02 = t2*(zeroV-eye)+eye;
                    Vec<double,3 > Pv2 = t2*(tempP2-eye)+eye;

                    y1 = (Pv1-P01).dot(w2)/w2.dot(w2);
                    y2 = (Pv2-P02).dot(w2)/w2.dot(w2);
                    x1 = (Pv1-P01).dot(w1)/w1.dot(w1);
                    x2 = (Pv2-P02).dot(w1)/w1.dot(w1);         

                    outfile << "(" << x1*100 << "," << y1*100 << "), (" << x2*100 << "," << y2*100 << ")" << endl;     
                }
                outfile << endl;
            } else if (type == 0 && i == 4) {
                outfile.close();
            }
            output.write(frame);
            frame = Mat::zeros(Size(cols, rows), CV_8UC3);
        }
    }
    output.release();
}

int main() {
    part3();
    return 0;
}