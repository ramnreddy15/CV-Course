// Ram Reddy
// Period 4
// 08/28/2021

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <time.h>
#include <cmath>
#include <limits>

using namespace std;

// This class has the methods for coordinate geometry
class CoordinateGeometry
{
public:
    // This method generates random pixels from an array
    void generatePoints(int size, double arr[])
    {
        if (size % 2 == 0)
        {
            srand(time(0)); // Generates random seed

            int distinctPoints = 1;
            bool distinct = true;
            while (distinctPoints < (size / 2) + 1) // Gets random points
            {
                double x = (float)rand() / RAND_MAX;
                double y = (float)rand() / RAND_MAX;
                for (int i = 0; i < distinctPoints; i++)
                {
                    if (arr[i] == x && arr[i + 1] == y)
                    {
                        distinct = false;
                    }
                }
                if (distinct)
                {
                    arr[(distinctPoints * 2) - 2] = x;
                    arr[(distinctPoints * 2) - 1] = y;
                    distinctPoints += 1;
                }
                else
                {
                    distinct == true;
                }
            }
        }
        cout << "Random points have been generated." << endl;
    }

    // This method calculates the incenter coordinates given the sides and semi perimeter of the trinagle
    void calcIncenter(double sideA, double sideB, double sideC, double s, double *intersectX, double *intersectY, double *r, double threePoints[6])
    {
        *r = sqrt(((s - sideA) * (s - sideB) * (s - sideC)) / s);

        *intersectX = (sideC * threePoints[0] + sideA * threePoints[4] + sideB * threePoints[2]) / (sideA + sideB + sideC);
        *intersectY = (sideC * threePoints[1] + sideA * threePoints[5] + sideB * threePoints[3]) / (sideA + sideB + sideC);
    }

    // This method calculates the circumcenter coordinates given the sides and semi perimeter
    void calcCircumcenter(double sideA, double sideB, double sideC, double s, double *intersectX, double *intersectY, double *R, double threePoints[6])
    {
        double r = 0.0, perpM1 = 0.0, perpM2 = 0.0, perpB1 = 0.0, perpB2 = 0.0;

        r = sqrt(((s - sideA) * (s - sideB) * (s - sideC)) / s);
        *R = (sideA * sideB * sideC) / (4 * r * s);

        perpM1 = -1 * pow((threePoints[3] - threePoints[1]) / (threePoints[2] - threePoints[0]), -1);
        perpB1 = ((threePoints[1] + threePoints[3]) / 2) - (perpM1 * ((threePoints[0] + threePoints[2]) / 2));

        perpM2 = -1 * pow((threePoints[5] - threePoints[1]) / (threePoints[4] - threePoints[0]), -1);
        perpB2 = ((threePoints[1] + threePoints[5]) / 2) - (perpM2 * ((threePoints[0] + threePoints[4]) / 2));

        if (!isfinite(perpM2))
        {
            *intersectX = (threePoints[0] + threePoints[4]) / 2;
        }
        else if (!isfinite(perpM1))
        {
            *intersectX = (threePoints[0] + threePoints[2]) / 2;
        }
        else
        {
            *intersectX = (perpB2 - perpB1) / (perpM1 - perpM2);
        }
        *intersectY = (perpM1 * *intersectX) + perpB1;
    }

    // This method calculates the centroid of a triangle
    void calcCentroid(double *intersectX, double *intersectY, double threePoints[6])
    {
        *intersectX = (threePoints[0] + threePoints[2] + threePoints[4]) / 3;
        *intersectY = (threePoints[1] + threePoints[3] + threePoints[5]) / 3;
    }

    // This method calculates the orthocenter of the triangle
    void calcOrthocenter(double *intersectX, double *intersectY, double threePoints[6])
    {
        double perpM1 = 0.0, perpM2 = 0.0, perpB1 = 0.0, perpB2 = 0.0;

        perpM1 = -1 * pow((threePoints[3] - threePoints[1]) / (threePoints[2] - threePoints[0]), -1);
        perpB1 = threePoints[5] - (perpM1 * threePoints[4]);

        perpM2 = -1 * pow((threePoints[5] - threePoints[1]) / (threePoints[4] - threePoints[0]), -1);
        perpB2 = threePoints[3] - (perpM2 * threePoints[2]);

        if (!isfinite(perpM2))
        {
            perpM2 = -1 * pow((threePoints[5] - threePoints[3]) / (threePoints[4] - threePoints[2]), -1);
            perpB2 = threePoints[1] - (perpM2 * threePoints[0]);
        }
        else if (!isfinite(perpM1))
        {
            perpM1 = -1 * pow((threePoints[5] - threePoints[3]) / (threePoints[4] - threePoints[2]), -1);
            perpB1 = threePoints[1] - (perpM1 * threePoints[0]);
        }

        *intersectX = (perpB2 - perpB1) / (perpM1 - perpM2);
        *intersectY = (perpM1 * *intersectX) + perpB1;
    }

    // This method calculates the nine point center of a triangle given the sides and semi perimeter
    void calcNinePointCenter(double sideA, double sideB, double sideC, double s, double *centerX, double *centerY, double threePoints[6])
    {
        double orthoCenterX = 0.0, orthoCenterY = 0.0, circumCenterX = 0.0, circumCenterY = 0.0, temp = 0.0;

        calcOrthocenter(&orthoCenterX, &orthoCenterY, threePoints);
        calcCircumcenter(sideA, sideB, sideC, s, &circumCenterX, &circumCenterY, &temp, threePoints);

        // Find mid points of orthocenter and circumcenter which is the nine point center
        *centerX = (orthoCenterX + circumCenterX) / 2;
        *centerY = (orthoCenterY + circumCenterY) / 2;
    }
};

// This is a class that can generate a PPM3 file with cool shapes
class PPMGenerator : public CoordinateGeometry
{
private:
    int image[800][800] = {{0}};
    int rows;
    int cols;

public:
    // This is the constructor
    PPMGenerator()
    {
        rows = sizeof(image) / sizeof(image[0]);
        cols = sizeof(image[0]) / sizeof(int);
    }

    // This method creates a PPM file from the image array when called
    void createPPMFile()
    {
        ofstream outfile("ppmImage.ppm");
        outfile << "P3 " + to_string(rows) + " " + to_string(cols) + " 1" << endl; // columns by rows
        for (int i = 0; i < cols; i++)
        {
            string temp = "";
            for (int j = 0; j < rows; j++)
            {
                if (image[i][j] == 0)
                {
                    temp += "1 1 1 ";
                }
                else
                {
                    temp += "0 0 0 ";
                }
            }
            outfile << temp << endl;
            temp.clear();
        }
        outfile.close();
        cout << "Created file." << endl;
    }

    // This method sets a pixel in the array when called
    void setPixel(int x, int y, int shade)
    {
        if (x >= 0 && y >= 0 && y < rows && x < cols)
        {
            image[rows - 1 - y][x] = shade;
        }
    }

    // Case 1 and 2 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
    void case1and2(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = y1;
        int error = changeY - changeX;

        for (int i = x1; i < x2; i++)
        {
            setPixel(i, j, 1);
            if (error >= 0)
            {
                j += 1;
                error -= changeX;
            }
            error += changeY;
        }
    }

    // Case 3 and 4 when drawing a line: (x2 > x1 and y2 = y1) or (Case 4: x2 < x1 and y2 = y1)
    void case3and4(int x1, int y, int x2)
    {
        for (int i = x1; i < x2; i++)
        {
            setPixel(i, y, 1);
        }
    }

    // Case 5 and 6 when drawing a line: (x2 < x1 and y2 > y1) or ( x2 > x1 and y2 < y1)
    void case5and6(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = y1;
        int error = changeY - changeX;

        for (int i = x1; i >= x2; i--)
        {
            setPixel(i, j, 1);
            if (error >= 0)
            {
                j += 1;
                error -= changeX;
            }
            error += changeY;
        }
    }

    // Case 7 and 8 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
    void case7and8(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = x1;
        int error = changeX - changeY;

        for (int i = y1; i < y2; i++)
        {
            setPixel(j, i, 1);
            if (error >= 0)
            {
                j += 1;
                error -= changeY;
            }
            error += changeX;
        }
    }

    // Case 9 and 10 when drawing a line: (x2 > x1 and y2 < y1) or (x2 < x1 and y2 > y1)
    void case9and10(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = x1;
        int error = changeX - changeY;

        for (int i = y1; i >= y2; i--)
        {
            setPixel(j, i, 1);
            if (error >= 0)
            {
                j += 1;
                error -= changeY;
            }
            error += changeX;
        }
    }

    // Case 11 and 12 when drawing a line: (x2 < x1 and y2 > y1) or (x2 = x1 and y2 < y1)
    void case11and12(int x, int y1, int y2)
    {
        for (int i = y1; i < y2; i++)
        {
            setPixel(x, i, 1);
        }
    }

    // This method creates a line in the image array when callled
    void bresenhamLine(int x1, int y1, int x2, int y2)
    {
        int changeX = abs(x2 - x1);
        int changeY = abs(y2 - y1);

        // 12 cases
        if (changeX >= changeY) // 6 cases for X Direct Axis
        {
            if (x2 > x1 && y2 > y1) // Case 1: x2 > x1 and y2 > y1
            {
                cout << "Case 1" << endl;
                case1and2(x1, y1, x2, y2, changeX, changeY);
            }
            else if (x2 < x1 && y2 < y1) // Case 2: x2 < x1 and y2 < y1
            {
                cout << "Case 2" << endl;
                case1and2(x2, y2, x1, y1, changeX, changeY);
            }
            else if (x2 > x1 && y2 == y1) // Case 3: x2 > x1 and y2 = y1
            {
                cout << "Case 3" << endl;
                case3and4(x1, y1, x2);
            }
            else if (x2 < x1 && y2 == y1) // Case 4: x2 < x1 and y2 = y1
            {
                cout << "Case 4" << endl;
                case3and4(x2, y1, x1);
            }
            else if (x2 < x1 && y2 > y1) // Case 5: x2 < x1 and y2 > y1
            {
                cout << "Case 5" << endl;
                case5and6(x1, y1, x2, y2, changeX, changeY);
            }
            else if (x2 > x1 && y2 < y1) // Case 6: x2 > x1 and y2 < y1
            {
                cout << "Case 6" << endl;
                case5and6(x2, y2, x1, y1, changeX, changeY);
            }
        }
        else // 6 cases for Y Direct Axis
        {
            if (x2 > x1 && y2 > y1) // Case 7: x2 > x1 and y2 > y1
            {
                cout << "Case 7" << endl;
                case7and8(x1, y1, x2, y2, changeX, changeY);
            }
            else if (x2 < x1 && y2 < y1) // Case 8: x2 < x1 and y2 < y1
            {
                cout << "Case 8" << endl;
                case7and8(x2, y2, x1, y1, changeX, changeY);
            }
            else if (x2 > x1 && y2 < y1) // Case 9: x2 > x1 and y2 < y1
            {
                cout << "Case 9" << endl;
                case9and10(x1, y1, x2, y2, changeX, changeY);
            }
            else if (x2 < x1 && y2 > y1) // Case 10: x2 < x1 and y2 > y1
            {
                cout << "Case 10" << endl;
                case9and10(x2, y2, x1, y1, changeX, changeY);
            }
            else if (x2 = x1 && y2 > y1) // Case 11: x2 = x1 and y2 > y1
            {
                cout << "Case 11" << endl;
                case11and12(x1, y1, y2);
            }
            else // Case 12: x2 = x1 and y2 < y1
            {
                cout << "Case 12" << endl;
                case11and12(x1, y2, y1);
            }
        }
    }

    // This method generates points for a triangle and then draws it
    // It can also draws the different centers of the triangle + euler line
    void drawTriangle(bool drawInCircle, bool drawCircumCircle, bool drawEulerLine, bool drawNinePoint)
    {
        int size = 6;
        double threePoints[6] = {0};

        generatePoints(size, threePoints);

        cout << "Points being used are: ";
        for (int i = 0; i < size; i++)
        {
            cout << to_string(threePoints[i]) + " ";
        }
        cout << endl;

        bresenhamLine((int)(threePoints[0] * cols), (int)(threePoints[1] * rows), (int)(threePoints[2] * cols), (int)(threePoints[3] * rows));
        cout << "Line 1 has been drawn." << endl;
        bresenhamLine((int)(threePoints[0] * cols), (int)(threePoints[1] * rows), (int)(threePoints[4] * cols), (int)(threePoints[5] * rows));
        cout << "Line 2 has been drawn." << endl;
        bresenhamLine((int)(threePoints[2] * cols), (int)(threePoints[3] * rows), (int)(threePoints[4] * cols), (int)(threePoints[5] * rows));
        cout << "Triangle has been drawn." << endl;

        // Draws the center circles if arguement is true
        if (drawInCircle == true || drawEulerLine == true || drawCircumCircle == true || drawNinePoint == true)
        {
            double sideA = 0.0, sideB = 0.0, sideC = 0.0, s = 0.0;

            sideA = sqrt(pow(threePoints[0] - threePoints[2], 2) + pow(threePoints[1] - threePoints[3], 2)); // AB
            sideB = sqrt(pow(threePoints[0] - threePoints[4], 2) + pow(threePoints[1] - threePoints[5], 2)); // BC
            sideC = sqrt(pow(threePoints[2] - threePoints[4], 2) + pow(threePoints[3] - threePoints[5], 2)); // AC
            s = 0.5 * (sideA + sideB + sideC);

            if (drawInCircle) // Draws the incircle
            {
                double r = 0.0, intersectX = 0.0, intersectY = 0.0;

                calcIncenter(sideA, sideB, sideC, s, &intersectX, &intersectY, &r, threePoints);

                drawCircle((int)(intersectX * cols), (int)(intersectY * rows), (int)(r * rows));
                cout << intersectX * cols << " " << intersectY * rows << " " << r * rows << endl;
                cout << "Incircle has been drawn" << endl;
            }
            if (drawCircumCircle) // Draws the circum circle
            {
                double R = 0.0, intersectX = 0.0, intersectY = 0.0;

                calcCircumcenter(sideA, sideB, sideC, s, &intersectX, &intersectY, &R, threePoints);

                drawCircle((int)(intersectX * cols), (int)(intersectY * rows), (int)(R * rows));
                cout << intersectX * cols << " " << intersectY * rows << " " << R * rows << endl;
                cout << "Circumcircle has been drawn" << endl;
            }
            if (drawEulerLine) // Draws the euler line
            {
                double circumX = 0.0, circumY = 0.0, centroidX = 0.0, centroidY = 0.0, slope = 0.0, b = 0.0, temp = 0.0;

                calcCircumcenter(sideA, sideB, sideC, s, &circumX, &circumY, &temp, threePoints);
                calcCentroid(&centroidX, &centroidY, threePoints);

                slope = (circumY - centroidY) / (circumX - centroidX);
                if (isfinite(slope))
                {
                    b = centroidY - (slope * centroidX);
                    bresenhamLine((0 - (b * rows)) / slope, 0, (rows - (b * rows)) / slope, rows);
                    cout << slope << " " << b << endl;
                }
                else
                {
                    bresenhamLine(circumX * cols, 0, circumX * cols, rows);
                    cout << "x = " << circumX * rows << endl;
                }
                cout << "Euler line has been drawn" << endl;
            }
            if (drawNinePoint) // Draws the nine point circle
            {
                double centerX = 0.0, centerY = 0.0, r = 0.0;

                r = (sideA * sideB * sideC) / (sqrt((sideA + sideB + sideC) * (sideB + sideC - sideA) * (sideC + sideA - sideB) * (sideA + sideB - sideC)));
                r = 0.5 * r;

                calcNinePointCenter(sideA, sideB, sideC, s, &centerX, &centerY, threePoints);

                drawCircle((int)(centerX * cols), (int)(centerY * rows), (int)(r * rows));
                cout << centerX * cols << " " << centerY * rows << " " << r * rows << endl;
                cout << "Nine point circle has been drawn" << endl;
            }
        }
    }

    // Draws a circle given the center coordinates and radius
    void drawCircle(int centerX, int centerY, int r)
    {
        int x = 0, y = 0, xmax = 0, y2 = 0, y2_new = 0, ty = 0;
        xmax = (int)(r * 0.70710678); // maximum x at radius/sqrt(2)
        y = r;
        y2 = y * y;
        ty = (2 * y) - 1;
        y2_new = y2;
        for (x = 0; x <= xmax + 2; x++)
        {
            if ((y2 - y2_new) >= ty)
            {
                y2 -= ty;
                y -= 1;
                ty -= 2;
            }
            setPixel(centerX + x, centerY + y, 1);
            setPixel(centerX + x, centerY + -y, 1);
            setPixel(centerX + -x, centerY + y, 1);
            setPixel(centerX + -x, centerY + -y, 1);
            setPixel(centerX + y, centerY + x, 1);
            setPixel(centerX + y, centerY + -x, 1);
            setPixel(centerX + -y, centerY + x, 1);
            setPixel(centerX + -y, centerY + -x, 1);
            y2_new -= (2 * x) - 3;
        }
    }

    // This is the object destructor
    ~PPMGenerator() { cout << "PPMGenerator has been deleted." << endl; }
};

int main()
{
    PPMGenerator *c = new PPMGenerator();    // Creates the object
    c->drawTriangle(true, true, true, true); // Create triangle with specified centers or lines
    c->createPPMFile();                      // Creates the PPM3 file
    delete c;                                // Deletes object
    return 0;
}
