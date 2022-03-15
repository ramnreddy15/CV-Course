 // Ram Reddy
 // Period 4
 // 1/11/2022

 #include <iostream>

 #include <iomanip>

 #include <fstream>

 #include <sstream>

 #include <iterator>

 #include <random>

 #include <string>

 #include <cmath>

 #include <cstring>

 #include <chrono>

 #include <algorithm>

 #include <limits>

 #include <cstdlib>

 #include <vector>

 #include <stack>

 #define PI M_PI
 //3.14159265

 using namespace std;

 // This is a point class
 class Point {
     private:
         double x;
     double y;

     public:
         Point() {
             this -> x = 0;
             this -> y = 0;
         }
     Point(double x, double y) {
         this -> x = x;
         this -> y = y;
     }
     double getX() {
         return x;
     }
     double getY() {
         return y;
     }
     void setX(double x) {
         this -> x = x;
     }
     void setY(double y) {
         this -> y = y;
     }
     double calcDistance(Point pt2) {
         return sqrt(pow((pt2.getX() - x), 2) + pow((pt2.getY() - y), 2));
     }
     double calcDistanceNS(Point pt2) {
         return pow((pt2.getX() - x), 2) + pow((pt2.getY() - y), 2);
     }
     string toString() {
         ostringstream temp;
         temp << fixed << setprecision(23) << "(" << x << "," << y << ")";
         return temp.str();
     }
     bool coinEquals(Point p2) {
         if (x <= p2.getX() + 85 && x >= p2.getX() - 85 && y <= p2.getY() + 85 && y >= p2.getY() - 85) {
             return true;
         } else {
             return false;
         }
     }
 };

 // This is a line class
 class Line {
     private:
         Point pt1;
     Point pt2;
     double a;
     double b;
     double c;

     public:
         Line() {}
     Line(Point pt1, Point pt2) {
         this -> pt1 = pt1;
         this -> pt2 = pt2;
         this -> a = -1 * (pt2.getY() - pt1.getY());
         this -> b = pt2.getX() - pt1.getX();
         this -> c = a * pt1.getX() + b * pt1.getY();
     }
     double getXfromY(double y) {
         if (b == 0) {
             return pt1.getX();
         } else if (a == 0) {
             return -numeric_limits < double > ::infinity();
         } else {
             return (c - b * y) / a;
         }
     }

     double getYfromX(double x) {
         if (a == 0) {
             return -numeric_limits < double > ::infinity();
         } else if (b == 0) {
             return pt1.getY();
         } else {
             return (c - a * x) / b;
         }
     }

     Point * getIntersection(Line ln2) {
         double denominator = a * ln2.getB() - b * ln2.getA();
         if (denominator == 0) { // No solution or parallel
             return NULL;
         } else {
             return new Point((c * ln2.getB() - b * ln2.getC()) / denominator, (a * ln2.getC() - c * ln2.getA()) / denominator);
         }
     }
     Line * getPerpendicular(Point pt3) {
         if (a == 0) {
             return new Line(Point(pt3.getX(), getYfromX(pt3.getX())), pt3);
         }
         if (b == 0) {
             return new Line(Point(getXfromY(pt3.getY()), pt3.getY()), pt3);
         }
         double slope = b / a;
         return new Line(Point(pt3.getX() + 1, pt3.getY() + slope), pt3);
     }
     string toString() {
         return to_string(a) + "*x + " + to_string(b) + "*y = " + to_string(c);
     }
     Point getPt1() {
         return pt1;
     }
     Point getPt2() {
         return pt2;
     }
     double getA() {
         return a;
     }
     double getB() {
         return b;
     }
     double getC() {
         return c;
     }
 };

 // This is a class that can generate a PPM3 file
 class PPMGenerator {
     private:
         vector < vector < vector < int >>> image;
     vector < vector < int >> incrementVec;
     vector < vector < vector < int > >> originalImage;
     int rows;
     int cols;
     int maxValue;

     public:
         // This is the constructor
         PPMGenerator(int row, int col, int maxVal) {
             cols = col;
             rows = row;
             maxValue = maxVal;
             image.resize(rows);
             for (int i = 0; i < rows; ++i) {
                 image[i].resize(cols);
             }
             for (int i = 0; i < rows; i++) {
                 for (int j = 0; j < cols; j++) {
                     for (int c = 0; c < 3; c++) {
                         image[i][j].push_back(maxValue);
                     }
                 }
             }
             incrementVec.resize(rows);
             for (int i = 0; i < rows; ++i) {
                 incrementVec[i].resize(cols);
             }
             originalImage.resize(rows);
             for (int i = 0; i < rows; ++i) {
                 originalImage[i].resize(cols);
             }
             for (int i = 0; i < rows; i++) {
                 for (int j = 0; j < cols; j++) {
                     for (int c = 0; c < 3; c++) {
                         originalImage[i][j].push_back(maxValue);
                     }
                 }
             }
         }

     PPMGenerator(string filename) {
         ifstream readFile(filename);
         string temp;
         getline(readFile, temp);
         while (count(temp.begin(), temp.end(), ' ') != 1) {
             getline(readFile, temp);
         }
         cols = stoi(temp.substr(0, temp.find(" ")));
         rows = stoi(temp.substr(temp.find(" "), temp.size()));
         incrementVec.resize(rows);
         for (int i = 0; i < rows; ++i) {
             incrementVec[i].resize(cols);
         }
         originalImage.resize(rows);
         for (int i = 0; i < rows; ++i) {
             originalImage[i].resize(cols);
         }
         getline(readFile, temp);
         maxValue = stoi(temp);
         image.resize(rows);
         for (int i = 0; i < rows; ++i) {
             image[i].resize(cols);
         }

         int i = 0, j = 0, c = 0;
         vector < string > v;
         for (string line; getline(readFile, line);) {
             istringstream ss(line);
             istream_iterator < string > begin(ss), end;
             vector < string > arrayTokens(begin, end);
             for (string s: arrayTokens) {
                 v.push_back(s);
             }
         }

         for (long unsigned int k = 0; k < v.size(); c++) {
             i = c / cols;
             j = c % cols;
             image[i][j].push_back(stoi(v[k]));
             image[i][j].push_back(stoi(v[k + 1]));
             image[i][j].push_back(stoi(v[k + 2]));
             k += 3;
         }
         readFile.close();
         originalImage.resize(rows);
         for (int i = 0; i < rows; ++i) {
             originalImage[i].resize(cols);
         }
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 originalImage[i][j].push_back(image[i][j][0]);
                 originalImage[i][j].push_back(image[i][j][1]);
                 originalImage[i][j].push_back(image[i][j][2]);
             }
         }
     }

     // This method creates a PPM file from the image array when called
     void createPPMFile(string filename) {
         ofstream outfile(filename);
         outfile << "P3 " + to_string(cols) + " " + to_string(rows) + " " + to_string(maxValue) << endl; // columns by rows
         for (int i = 0; i < rows; i++) {
             string temp = "";
             for (int j = 0; j < cols; j++) {
                 temp +=
                     to_string(image[i][j][0]) + " " + to_string(image[i][j][1]) +
                     " " + to_string(image[i][j][2]) + " ";
             }
             outfile << temp << endl;
             temp.clear();
         }
         outfile.close();
     }

     // This method sets a pixel in the array when called
     void setPixel(int x, int y, int shadeR, int shadeG, int shadeB, bool increment) {
         if (x >= 0 && y >= 0 && x < cols && y < rows) {
             if (increment) {
                 incrementVec[y][x] = incrementVec[y][x] + 1;
             } else {
                 image[y][x][0] = shadeR;
                 image[y][x][1] = shadeG;
                 image[y][x][2] = shadeB;
             }
         }
     }

     // Case 1 and 2 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
     void case1and2(int x1, int y1, int x2, int y2, int changeX, int changeY, int shade[3], bool increment) {
         int j = y1;
         int error = changeY - changeX;

         for (int i = x1; i < x2; i++) {
             if (increment) {
                 setPixel(i, j, shade[0], shade[1], shade[2], true);
             } else {
                 setPixel(i, j, shade[0], shade[1], shade[2], false);
             }

             if (error >= 0) {
                 j += 1;
                 error -= changeX;
             }
             error += changeY;
         }
     }

     // Case 3 and 4 when drawing a line: (x2 > x1 and y2 = y1) or (Case 4: x2 < x1 and y2 = y1)
     void case3and4(int x1, int y, int x2, int shade[3], bool increment) {
         for (int i = x1; i < x2; i++) {
             if (increment) {
                 setPixel(i, y, shade[0], shade[1], shade[2], true);
             } else {
                 setPixel(i, y, shade[0], shade[1], shade[2], false);
             }
         }
     }

     // Case 5 and 6 when drawing a line: (x2 < x1 and y2 > y1) or ( x2 > x1 and y2 < y1)
     void case5and6(int x1, int y1, int x2, int y2, int changeX, int changeY, int shade[3], bool increment) {
         int j = y1;
         int error = changeY - changeX;

         for (int i = x1; i >= x2; i--) {
             if (increment) {
                 setPixel(i, j, shade[0], shade[1], shade[2], true);
             } else {
                 setPixel(i, j, shade[0], shade[1], shade[2], false);
             }
             if (error >= 0) {
                 j += 1;
                 error -= changeX;
             }
             error += changeY;
         }
     }

     // Case 7 and 8 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
     void case7and8(int x1, int y1, int x2, int y2, int changeX, int changeY, int shade[3], bool increment) {
         int j = x1;
         int error = changeX - changeY;

         for (int i = y1; i < y2; i++) {
             if (increment) {
                 setPixel(j, i, shade[0], shade[1], shade[2], true);
             } else {
                 setPixel(j, i, shade[0], shade[1], shade[2], false);
             }
             if (error >= 0) {
                 j += 1;
                 error -= changeY;
             }
             error += changeX;
         }
     }

     // Case 9 and 10 when drawing a line: (x2 > x1 and y2 < y1) or (x2 < x1 and y2 > y1)
     void case9and10(int x1, int y1, int x2, int y2, int changeX, int changeY, int shade[3], bool increment) {
         int j = x1;
         int error = changeX - changeY;

         for (int i = y1; i >= y2; i--) {
             if (increment) {
                 setPixel(j, i, shade[0], shade[1], shade[2], true);
             } else {
                 setPixel(j, i, shade[0], shade[1], shade[2], false);
             }
             if (error >= 0) {
                 j += 1;
                 error -= changeY;
             }
             error += changeX;
         }
     }

     // Case 11 and 12 when drawing a line: (x2 < x1 and y2 > y1) or (x2 = x1 and y2 < y1)
     void case11and12(int x, int y1, int y2, int shade[3], bool increment) {
         for (int i = y1; i < y2; i++) {
             if (increment) {
                 setPixel(x, i, shade[0], shade[1], shade[2], true);
             } else {
                 setPixel(x, i, shade[0], shade[1], shade[2], false);
             }
         }
     }

     // This method creates a line in the image array when callled
     void bresenhamLine(Point point1, Point point2, int scaler, int shade[3], bool increment) {
         int x1 = (int)(point1.getX() * scaler);
         int y1 = (int)(point1.getY() * scaler);
         int x2 = (int)(point2.getX() * scaler);
         int y2 = (int)(point2.getY() * scaler);

         int changeX = abs(x2 - x1);
         int changeY = abs(y2 - y1);

         // 12 cases
         if (changeX >= changeY) // 6 cases for X Direct Axis
         {
             if (x2 > x1 && y2 > y1) // Case 1: x2 > x1 and y2 > y1
             {
                 case1and2(x1, y1, x2, y2, changeX, changeY, shade, increment);
             } else if (x2 < x1 && y2 < y1) // Case 2: x2 < x1 and y2 < y1
             {
                 case1and2(x2, y2, x1, y1, changeX, changeY, shade, increment);
             } else if (x2 > x1 && y2 == y1) // Case 3: x2 > x1 and y2 = y1
             {
                 case3and4(x1, y1, x2, shade, increment);
             } else if (x2 < x1 && y2 == y1) // Case 4: x2 < x1 and y2 = y1
             {
                 case3and4(x2, y1, x1, shade, increment);
             } else if (x2 < x1 && y2 > y1) // Case 5: x2 < x1 and y2 > y1
             {
                 case5and6(x1, y1, x2, y2, changeX, changeY, shade, increment);
             } else if (x2 > x1 && y2 < y1) // Case 6: x2 > x1 and y2 < y1
             {
                 case5and6(x2, y2, x1, y1, changeX, changeY, shade, increment);
             }
         } else // 6 cases for Y Direct Axis
         {
             if (x2 > x1 && y2 > y1) // Case 7: x2 > x1 and y2 > y1
             {
                 case7and8(x1, y1, x2, y2, changeX, changeY, shade, increment);
             } else if (x2 < x1 && y2 < y1) // Case 8: x2 < x1 and y2 < y1
             {
                 case7and8(x2, y2, x1, y1, changeX, changeY, shade, increment);
             } else if (x2 > x1 && y2 < y1) // Case 9: x2 > x1 and y2 < y1
             {
                 case9and10(x1, y1, x2, y2, changeX, changeY, shade, increment);
             } else if (x2 < x1 && y2 > y1) // Case 10: x2 < x1 and y2 > y1
             {
                 case9and10(x2, y2, x1, y1, changeX, changeY, shade, increment);
             } else if (x2 == x1 && y2 > y1) // Case 11: x2 = x1 and y2 > y1
             {
                 case11and12(x1, y1, y2, shade, increment);
             } else // Case 12: x2 = x1 and y2 < y1
             {
                 case11and12(x1, y2, y1, shade, increment);
             }
         }
     }

     void screenLine(Point point1, Point point2, int scaler, int shade[3], bool increment) {
         double slope = 0.0, b = 0.0;
         slope = (point1.getY() - point2.getY()) / (point1.getX() - point2.getX());
         if (isfinite(slope)) {
             b = point1.getY() - (slope * point1.getX());
             bresenhamLine(Point((0 - b) / slope, 0),
                 Point((rows - b) / slope, rows), scaler, shade, increment);
         } else {
             bresenhamLine(Point(point2.getX() * scaler, 0),
                 Point(point2.getX() * scaler, rows), scaler, shade, increment);
         }
     }

     // Draws a circle given the center coordinates and radius
     void drawCircle(int centerX, int centerY, int r, int shade[3]) {
         int x = 0, y = 0, xmax = 0, y2 = 0, y2_new = 0, ty = 0;
         xmax = (int)(r * 0.70710678); // maximum x at radius/sqrt(2)
         y = r;
         y2 = y * y;
         ty = (2 * y) - 1;
         y2_new = y2;
         for (x = 0; x <= xmax + 2; x++) {
             if ((y2 - y2_new) >= ty) {
                 y2 -= ty;
                 y -= 1;
                 ty -= 2;
             }
             setPixel(centerX + x, centerY + y, shade[0], shade[1], shade[2], false);
             setPixel(centerX + x, centerY + -y, shade[0], shade[1], shade[2], false);
             setPixel(centerX + -x, centerY + y, shade[0], shade[1], shade[2], false);
             setPixel(centerX + -x, centerY + -y, shade[0], shade[1], shade[2], false);
             setPixel(centerX + y, centerY + x, shade[0], shade[1], shade[2], false);
             setPixel(centerX + y, centerY + -x, shade[0], shade[1], shade[2], false);
             setPixel(centerX + -y, centerY + x, shade[0], shade[1], shade[2], false);
             setPixel(centerX + -y, centerY + -x, shade[0], shade[1], shade[2], false);
             y2_new -= (2 * x) - 3;
         }
     }

     void convertBW() {
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 int temp = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3;
                 image[i][j][0] = temp;
                 image[i][j][1] = temp;
                 image[i][j][2] = temp;
             }
         }
     }

     void cannyEdgeDetect(int threshold) {
         convertBW();
         createPPMFile("imageg.ppm");
         vector < vector < vector < int >>> temp;
         copy(image.begin(), image.end(), back_inserter(temp));
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (i == 0 || j == 0 || j == cols - 1 || i == rows - 1) {
                     image[i][j][0] = 0;
                     image[i][j][1] = 0;
                     image[i][j][2] = 0;
                 } else {
                     int mathOperation = pow(temp[i - 1][j - 1][0] + temp[i][j - 1][0] * 2 + temp[i + 1][j - 1][0] + temp[i - 1][j + 1][0] * -1 + temp[i][j + 1][0] * -2 + temp[i + 1][j + 1][0] * -1, 2) + pow(temp[i - 1][j - 1][0] + temp[i - 1][j][0] * 2 + temp[i - 1][j + 1][0] + temp[i + 1][j - 1][0] * -1 + temp[i + 1][j][0] * -2 + temp[i + 1][j + 1][0] * -1, 2);
                     if (mathOperation > threshold) {
                         image[i][j][0] = 1;
                         image[i][j][1] = 1;
                         image[i][j][2] = 1;
                     } else {
                         image[i][j][0] = 0;
                         image[i][j][1] = 0;
                         image[i][j][2] = 0;
                     }
                 }
             }
         }
         int temp2 = maxValue;
         maxValue = 1;
         createPPMFile("imagem.ppm");
         maxValue = temp2;
     }

     void hystersis(int row, int col, vector < vector < int > > & imageArr) {
         if (row < 0 || row >= rows || col < 0 || col >= cols || imageArr[row][col] == 1 || imageArr[row][col] == 0) {
             return;
         }
         imageArr[row][col] = 1;
         hystersis(row + 1, col, imageArr);
         hystersis(row + 1, col + 1, imageArr);
         hystersis(row, col + 1, imageArr);
         hystersis(row - 1, col, imageArr);
         hystersis(row - 1, col - 1, imageArr);
         hystersis(row, col - 1, imageArr);
         hystersis(row + 1, col - 1, imageArr);
         hystersis(row - 1, col + 1, imageArr);
     }

     vector < vector < double >> hystersisAlgoWAngles(int threshold1, int threshold2) {
         convertBW();
         vector < vector < vector < int >>> temp;
         vector < vector < int >> angles(rows, vector < int > (cols, 0));
         vector < vector < double >> unRAngles(rows, vector < double > (cols, 0.0));
         vector < vector < int >> magnitudes(rows, vector < int > (cols, 0));
         copy(image.begin(), image.end(), back_inserter(temp));
         vector < Point > places;
         vector < vector < int >> imaget(rows, vector < int > (cols, 0));
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 imaget[i][j] = image[i][j][0];
             }
         }
         double tempAngle = 0.0;

         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (i == 0 || j == 0 || j == cols - 1 || i == rows - 1) {
                     imaget[i][j] = 0;
                 } else {
                     double gX = (temp[i - 1][j - 1][0] * -1 + temp[i][j - 1][0] * -2 + temp[i + 1][j - 1][0] * -1 + temp[i - 1][j + 1][0] + temp[i][j + 1][0] * 2 + temp[i + 1][j + 1][0]);
                     double gY = (temp[i - 1][j - 1][0] * -1 + temp[i - 1][j][0] * -2 + temp[i - 1][j + 1][0] * -1 + temp[i + 1][j - 1][0] + temp[i + 1][j][0] * 2 + temp[i + 1][j + 1][0]);
                     //           double gX = temp[i+1][j+1][0] - temp[i+1][j-1][0] + 2*temp[i][j+1][0] - 2*temp[i][j-1][0] + temp[i-1][j+1][0] - temp[i-1][j-1][0];
                     //           double gY = -1 * (temp[i+1][j+1][0] + 2*(temp[i+1][j][0]) + temp[i+1][j-1][0]) + temp[i-1][j-1][0] + 2*temp[i-1][j][0] + temp[i-1][j+1][0];
                     int mathOperation = pow(gX, 2) + pow(gY, 2);
                     if (mathOperation > threshold2) {
                         imaget[i][j] = 3;
                         places.push_back(Point(j, i));
                     } else if (mathOperation > threshold1) {
                         imaget[i][j] = 2;
                     } else {
                         imaget[i][j] = 0;
                     }
                     magnitudes[i][j] = mathOperation;
                     unRAngles[i][j] = atan2(gY, gX);
                     tempAngle = unRAngles[i][j] * 180 / PI;

                     if (tempAngle < 0) {
                         tempAngle = tempAngle + 180;
                     }
                     if (tempAngle >= 0 && tempAngle <= 22.5) {
                         angles[i][j] = 0;
                     } else if (tempAngle > 22.5 && tempAngle <= 67.5) {
                         angles[i][j] = 45;
                     } else if (tempAngle > 67.5 && tempAngle <= 112.5) {
                         angles[i][j] = 90;
                     } else if (tempAngle > 112.5 && tempAngle <= 157.5) {
                         angles[i][j] = 135;
                     } else if (tempAngle > 157.5 && tempAngle <= 180) {
                         angles[i][j] = 0;
                     }
                 }
             }
         }

         for (Point p: places) {
             hystersis(p.getY(), p.getX(), imaget);
         }

         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 image[i][j][0] = imaget[i][j];
                 image[i][j][1] = imaget[i][j];
                 image[i][j][2] = imaget[i][j];
                 if (image[i][j][0] == 2) {
                     image[i][j][0] = 0;
                     image[i][j][1] = 0;
                     image[i][j][2] = 0;
                 }
             }
         }
         int temp2 = maxValue;
         maxValue = 1;
         createPPMFile("image1.ppm");
         maxValue = temp2;

         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (i != 0 && j != 0 && j != cols - 1 && i != rows - 1) {
                     //           if(imaget[i][j] == 1) {

                     //           }
                     int value = magnitudes[i][j];
                     tempAngle = angles[i][j];
                     if (tempAngle == 0) {
                         if (value >= magnitudes[i][j + 1] && value >= magnitudes[i][j - 1]) {
                             value = 1;
                         } else {
                             value = 0;
                         }
                     } else if (tempAngle == 135) {
                         if (value >= magnitudes[i - 1][j + 1] && value >= magnitudes[i + 1][j - 1]) {
                             value = 1;
                         } else {
                             value = 0;
                         }
                     } else if (tempAngle == 90) {
                         if (value >= magnitudes[i + 1][j] && value >= magnitudes[i - 1][j]) {
                             value = 1;
                         } else {
                             value = 0;
                         }
                     } else {
                         if (value >= magnitudes[i + 1][j + 1] && value >= magnitudes[i - 1][j - 1]) {
                             value = 1;
                         } else {
                             value = 0;
                         }
                     }
                     image[i][j][0] = value;
                     image[i][j][1] = value;
                     image[i][j][2] = value;
                 } else {
                     image[i][j][0] = 1;
                     image[i][j][1] = 1;
                     image[i][j][2] = 1;
                 }
             }
         }
         temp2 = maxValue;
         maxValue = 1;
         createPPMFile("image2.ppm");
         maxValue = temp2;

         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (imaget[i][j] == 1 && image[i][j][0] == 1) {
                     image[i][j][0] = 1;
                     image[i][j][1] = 1;
                     image[i][j][2] = 1;
                 } else {
                     image[i][j][0] = 0;
                     image[i][j][1] = 0;
                     image[i][j][2] = 0;
                 }
             }
         }
         temp2 = maxValue;
         maxValue = 1;
         createPPMFile("imagef.ppm");
         maxValue = temp2;
         return unRAngles;
     }

     vector < Point > findCenter(int threshold1, int threshold2, int votes, int numSquares) {
         int shade[3] = {
             255,
             165,
             0
         };
         vector < vector < int >> edges(rows, vector < int > (cols, 0));
         vector < int > squares;
         vector < Point > centers;
         vector < vector < vector < int >>> original;
         vector < vector < int >> addedValues(rows, vector < int > (cols, 0));
         copy(image.begin(), image.end(), back_inserter(original));
         vector < vector < double >> angles = hystersisAlgoWAngles(threshold1, threshold2);
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 edges[i][j] = image[i][j][0];
             }
         }
         int squareNum = sqrt(numSquares);
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (edges[i][j] == 1) {
                     screenLine(Point(j, i), Point(((double) j) + cols * cos(angles[i][j]), ((double) i) + cols * sin(angles[i][j])), 1, shade, true);

                 }
             }
         }

         int max = 0;
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (incrementVec[i][j] > max) {
                     max = incrementVec[i][j];

                 }
             }
         }
         ofstream outfile("imagev.ppm");
         outfile << "P3 " + to_string(cols) + " " + to_string(rows) + " " + to_string(max) << endl; // columns by rows
         for (int i = 0; i < rows; i++) {
             string temp1 = "";
             for (int j = 0; j < cols; j++) {

                 temp1 +=
                     to_string((incrementVec[i][j])) + " " + to_string(0) +
                     " " + to_string(0) + " ";

             }
             outfile << temp1 << endl;
             temp1.clear();
         }
         outfile.close();
         for (int l = 0; l < squareNum; l++) {
             for (int k = 0; k < squareNum; k++) {
                 int averageAmount = 0;
                 for (int i = 0; i < rows / squareNum; i++) {
                     for (int j = 0; j < cols / squareNum; j++) {
                         averageAmount += incrementVec[i + ((rows / squareNum) * l)][j + ((cols / squareNum) * k)];
                     }

                 }
                 squares.push_back((averageAmount / ((rows / squareNum) * (cols / squareNum))) * 1.3);
             }
         }
         shade[0] = 255;
         shade[1] = 0;
         shade[2] = 0;
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 setPixel(j, i, original[i][j][0], original[i][j][1], original[i][j][2], false);

             }
         }
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 if (incrementVec[i][j] >= votes && abs(((original[i][j][0] + original[i][j][1] + original[i][j][2]) / 3) - 200) > 20 && abs(((original[i][j][0] + original[i][j][1] + original[i][j][2]) / 3) - 170) > 20) {
                     if (squares[floor(i / (rows / squareNum)) * squareNum + ceil(j / (cols / squareNum))] > votes) {
                         if (incrementVec[i][j] > squares[floor(i / (rows / squareNum)) * squareNum + ceil(j / (cols / squareNum))]) {
                             centers.push_back(Point(j, i));
                             drawCircle(j, i, 1, shade);
                             drawCircle(j, i, 2, shade);
                             drawCircle(j, i, 3, shade);
                             drawCircle(j, i, 4, shade);
                         }
                     } else {
                         centers.push_back(Point(j, i));
                         drawCircle(j, i, 1, shade);
                         drawCircle(j, i, 2, shade);
                         drawCircle(j, i, 3, shade);
                         drawCircle(j, i, 4, shade);
                     }

                 }
             }
         }
         createPPMFile("imageCC.ppm");
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 image[i][j][0] = edges[i][j];
                 image[i][j][1] = edges[i][j];
                 image[i][j][2] = edges[i][j];
             }
         }
         return centers;
     }

     double percentageCircle(int centerX, int centerY, int r) {
         double totalPixels = 0;
         double capturedPixels = 0;
         int x = 0, y = 0, xmax = 0, y2 = 0, y2_new = 0, ty = 0, tempCX = 0, tempCY = 0;
         xmax = (int)(r * 0.70710678); // maximum x at radius/sqrt(2)
         y = r;
         y2 = y * y;
         ty = (2 * y) - 1;
         y2_new = y2;
         for (x = 0; x <= xmax + 2; x++) {
             if ((y2 - y2_new) >= ty) {
                 y2 -= ty;
                 y -= 1;
                 ty -= 2;
             }
             tempCX = centerX + x;
             tempCY = centerY + y;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCY = centerY - y;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCX = centerX - x;
             tempCY = centerY + y;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCY = centerY - y;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCX = centerX + y;
             tempCY = centerY + x;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCY = centerY - x;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCX = centerX - y;
             tempCY = centerY + x;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             tempCY = centerY - x;
             if (tempCX < cols && tempCX >= 0 && tempCY < rows && tempCY >= 0 && image[tempCY][tempCX][0] == 1) {
                 capturedPixels++;
             }
             totalPixels += 8;
             y2_new -= (2 * x) - 3;
         }
         return capturedPixels / totalPixels;
     }
     void add(vector < Point > & realCenters, vector < Point > & combo, Point p, vector < vector < double >> & percentage, int number, int size) {
         for (long unsigned int i = 0; i < realCenters.size(); i++) {
             if (p.coinEquals(realCenters[i])) {
                 if (percentage[number][size] > percentage[combo[i].getX()][combo[i].getY()]) {
                     combo[i] = Point(number, size);
                     realCenters[i] = p;
                 }
                 return;
             }
         }
         realCenters.push_back(p);
         combo.push_back(Point(number, size));

     }

     void findCoins(int threshold1, int threshold2, int votes, int numSquares, double circlePercentage, int smallestRadius) {
         int shadeP[3] = {
             255,
             0,
             0
         };
         int shadeN[3] = {
             128,
             0,
             128
         };
         int shadeD[3] = {
             0,
             0,
             255
         };
         int shadeQ[3] = {
             0,
             255,
             0
         };
         int shadeS[3] = {
             255,
             255,
             0
         };

         int coinSize = 180-smallestRadius;
         int start = smallestRadius;
         vector < Point > centers = findCenter(threshold1, threshold2, votes, numSquares);
         vector < vector < double >> percentage(centers.size(), vector < double > (coinSize, 0));
         double max = 0;
         vector < Point > realCenter;
         vector < Point > combo;
         double amount = 0;
         int stupidSumR, stupidSumG, stupidSumB, coinsP = 0, coinsN = 0, coinsD = 0, coinsQ = 0, coinsS = 0;
         vector < int > coinTypes;
         for (long unsigned int num = 0; num < centers.size(); num++) {
             for (int place = start; place < coinSize + start; place++) {

                 percentage[num][place - start] = percentageCircle(centers[num].getX(), centers[num].getY(), place);
             }

         }

         for (long unsigned int i = 0; i < centers.size(); i++) {
             for (int j = 0; j < coinSize; j++) {
                 if (percentage[i][j] > max) {
                     max = percentage[i][j];
                 }
             }
         }
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < cols; j++) {
                 image[i][j][0] = originalImage[i][j][0];
                 image[i][j][1] = originalImage[i][j][1];
                 image[i][j][2] = originalImage[i][j][2];
             }
         }

         for (long unsigned int i = 0; i < centers.size(); i++) {
             for (int j = 0; j < coinSize; j++) {
                 if (percentage[i][j] > circlePercentage * max) {
                     add(realCenter, combo, centers[i], percentage, i, j);
                 }
             }
         }

         for (long unsigned int i = 0; i < realCenter.size(); i++) {
             int midRadius = (combo[i].getY() + start) / 2;
             stupidSumR = image[realCenter[i].getY()][realCenter[i].getX()][0] + image[realCenter[i].getY() + midRadius][realCenter[i].getX()][0] + image[realCenter[i].getY()][realCenter[i].getX() + midRadius][0] + image[realCenter[i].getY() - midRadius][realCenter[i].getX()][0] + image[realCenter[i].getY()][realCenter[i].getX() - midRadius][0];
             stupidSumG = image[realCenter[i].getY()][realCenter[i].getX()][1] + image[realCenter[i].getY() + midRadius][realCenter[i].getX()][1] + image[realCenter[i].getY()][realCenter[i].getX() + midRadius][1] + image[realCenter[i].getY() - midRadius][realCenter[i].getX()][1] + image[realCenter[i].getY()][realCenter[i].getX() - midRadius][1];
             stupidSumB = image[realCenter[i].getY()][realCenter[i].getX()][2] + image[realCenter[i].getY() + midRadius][realCenter[i].getX()][2] + image[realCenter[i].getY()][realCenter[i].getX() + midRadius][2] + image[realCenter[i].getY() - midRadius][realCenter[i].getX()][2] + image[realCenter[i].getY()][realCenter[i].getX() - midRadius][2];
             stupidSumR = stupidSumR / 5;
             stupidSumG = stupidSumG / 5;
             stupidSumB = stupidSumB / 5;

              if (combo[i].getY() + start >= 150) {
                 if (stupidSumR > 1.3 * stupidSumB) {
                      realCenter.erase(realCenter.begin() +i);
                      combo.erase(combo.begin() +i);
                      i--;
                      amount+=0;                     
                 } else {
                 amount += 1;
                 coinTypes.push_back(5);
                 coinsS += 1; 
               }
              } else if (combo[i].getY() + start >= 103) {
                 if (stupidSumR > 1.3 * stupidSumB) {
                      realCenter.erase(realCenter.begin() +i);
                      combo.erase(combo.begin() +i);
                      i--;
                      amount+=0;                     
                 } else {
                     amount += .25;
                     coinTypes.push_back(1);
                     coinsQ += 1;                     
                 }

             }
             else if (combo[i].getY() + start > 80 && combo[i].getY() + start < 103) {
                 if (stupidSumR > 1.3 * stupidSumB) {
                     amount += .01;
                     coinTypes.push_back(3);
                     coinsP += 1;
                 } else {
                     amount += .05;
                     coinTypes.push_back(2);
                     coinsN += 1;
                 }
             } else {
                  if (stupidSumR > 1.3 * stupidSumB) {
                     amount += .01;
                     coinTypes.push_back(3);
                     coinsP += 1;
                 } else {
                     coinsD += 1;
                     amount += .1;
                     coinTypes.push_back(4);
                  }

             }
         }
         for (long unsigned int i = 0; i < realCenter.size(); i++) {
             if (coinTypes[i] == 1) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeQ);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeQ);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeQ[0], shadeQ[1], shadeQ[2], false);
             } else if (coinTypes[i] == 2) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeN);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeN);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeN[0], shadeN[1], shadeN[2], false);
             } else if (coinTypes[i] == 3) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeP);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeP);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeP[0], shadeP[1], shadeP[2], false);
             } else if (coinTypes[i] == 4) {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeD);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeD);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeD[0], shadeD[1], shadeD[2], false);
             } else {
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 1, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), combo[i].getY() + start + 2, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 4, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 3, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 2, shadeS);
                 drawCircle(realCenter[i].getX(), realCenter[i].getY(), 1, shadeS);
                 setPixel(realCenter[i].getX(), realCenter[i].getY(), shadeS[0], shadeS[1], shadeS[2], false);
             }

         }
         cout << coinsS << " Silver Dollars, " << coinsQ << " Quarters, " << coinsD << " Dimes, " << coinsN << " Nickels, " << coinsP << " Pennies, " << "Total Sum: $" << amount << endl;
         ofstream outfile("results.txt");
         outfile << coinsS << " Silver Dollars, " << coinsQ << " Quarters, " << coinsD << " Dimes, " << coinsN << " Nickels, " << coinsP << " Pennies, " << "Total Sum: $" << amount << endl;
         outfile.close();
         createPPMFile("coins.ppm");

     }
 };

 void part1(int threshold1, int threshold2, string filename, int vote, int squares) {
     PPMGenerator * cd = new PPMGenerator(filename);
     cd -> findCenter(threshold1, threshold2, vote, squares);
     delete cd;
 }

 void part2(int threshold1, int threshold2, string filename, int vote, int squares, double percentage, int smallestRadius) {
     PPMGenerator * cd = new PPMGenerator(filename);
     cd -> findCoins(threshold1, threshold2, vote, squares, percentage, smallestRadius);
     delete cd;
 }

 int main(int argc, char ** argv) {
     if (argc == 1) {
         part2(6400, 22500, "image.ppm", 65, 169, .3, 70);
     } else {
         int i;
         int threshold1 = 6400;
         int threshold2 = 22500;
         int votes = 65;
         int squares = 169;
         double circlePercentage = .3;
         int smallestRadius = 70;
         string filename = "image.ppm";
         for (i = 0; i < argc; i++) {
             if (strcmp(argv[i], "-L") == 0) {
                 threshold1 = stoi(string(argv[i + 1]));
                 threshold1 = threshold1 * threshold1;
             }
             if (strcmp(argv[i], "-H") == 0) {
                 threshold2 = stoi(string(argv[i + 1]));
                 threshold2 = threshold2 * threshold2;
             }
             if (strcmp(argv[i], "-F") == 0) {
                 filename = string(argv[i + 1]);
             }
             if (strcmp(argv[i], "-TC") == 0) {
                 votes = stoi(string(argv[i + 1]));
             }
             if (strcmp(argv[i], "-S") == 0) {
                 squares = stoi(string(argv[i + 1]));
             }
             if (strcmp(argv[i], "-TCircle") == 0) {
                 circlePercentage = stod(string(argv[i + 1])) / 100;
             }
             if (strcmp(argv[i], "-SRadius") == 0) {
                 smallestRadius = stoi(string(argv[i + 1]));
             }
         }
         part2(threshold1, threshold2, filename, votes, squares, circlePercentage, smallestRadius);
     }
     return 0;
 }