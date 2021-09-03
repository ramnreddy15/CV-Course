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

class PPMGenerator
{
private:
    int image[800][800] = {{0}};
    int threePoints[6] = {0};
    int rows;
    int cols;

public:
    PPMGenerator()
    {
        rows = sizeof(image) / sizeof(image[0]);
        cols = sizeof(image[0]) / sizeof(int);
    }
    void test()
    {
        cout << "test" << endl;
    }
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
    void setPixel(int x, int y, int shade)
    {
        if (x >= 0 && y >= 0 && y < rows && x < cols)
        {
            image[x][y] = shade;
        }
    }
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
    void case3and4(int x1, int y, int x2)
    {
        for (int i = x1; i < x2; i++)
        {
            setPixel(i, y, 1);
        }
    }
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
    void case11and12(int x, int y1, int y2)
    {
        for (int i = y1; i < y2; i++)
        {
            setPixel(x, i, 1);
        }
    }
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
            else if (x2 < x1 && y2 < y1)
            { // Case 8: x2 < x1 and y2 < y1
                cout << "Case 8" << endl;
                case7and8(x2, y2, x1, y1, changeX, changeY);
            }
            else if (x2 > x1 && y2 < y1)
            { // Case 9: x2 > x1 and y2 < y1
                cout << "Case 9" << endl;
                case9and10(x1, y1, x2, y2, changeX, changeY);
            }
            else if (x2 < x1 && y2 > y1)
            { // Case 10: x2 < x1 and y2 > y1
                cout << "Case 10" << endl;
                case9and10(x2, y2, x1, y1, changeX, changeY);
            }
            else if (x2 = x1 && y2 > y1)
            { // Case 11: x2 = x1 and y2 > y1
                cout << "Case 11" << endl;
                case3and4(x1, y1, y2);
            }
            else
            { // Case 12: x2 = x1 and y2 < y1
                cout << "Case 12" << endl;
                case3and4(x1, y2, y1);
            }
        }
    }
    void drawTriangle()
    {
        srand(time(0));

        int distinctPoints = 1;
        bool distinct = true;
        while (distinctPoints < 4)
        {
            int x = rand() % rows;
            int y = rand() % cols;
            for (int i = 0; i < distinctPoints; i++)
            {
                if (threePoints[i] == x && threePoints[i + 1] == y)
                {
                    distinct = false;
                }
            }
            if (distinct)
            {
                threePoints[(distinctPoints * 2) - 2] = x;
                threePoints[(distinctPoints * 2) - 1] = y;
            }
            distinctPoints += 1;
        }
        for (int i = 0; i < 6; i++)
        {
            cout << to_string(threePoints[i]) + " ";
        }
        cout << endl;
        cout << "Random points have been generated." << endl;
        bresenhamLine(threePoints[0], threePoints[1], threePoints[2], threePoints[3]);
        cout << "Line 1 has been drawn." << endl;
        bresenhamLine(threePoints[0], threePoints[1], threePoints[4], threePoints[5]);
        cout << "Line 2 has been drawn." << endl;
        bresenhamLine(threePoints[2], threePoints[3], threePoints[4], threePoints[5]);
        cout << "Triangle has been drawn." << endl;
    }
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
    void calcIncenter(double *intersectX, double *intersectY, double *r)
    {
        double a = 0.0, b = 0.0, c = 0.0, s = 0.0;

        a = sqrt(pow(threePoints[0] - threePoints[2], 2) + pow(threePoints[1] - threePoints[3], 2)); // AB
        b = sqrt(pow(threePoints[0] - threePoints[4], 2) + pow(threePoints[1] - threePoints[5], 2)); // BC
        c = sqrt(pow(threePoints[2] - threePoints[4], 2) + pow(threePoints[3] - threePoints[5], 2)); // AC
        s = 0.5 * (a + b + c);
        *r = sqrt(((s - a) * (s - b) * (s - c)) / s);

        *intersectX = (c * threePoints[0] + a * threePoints[4] + b * threePoints[2]) / (a + b + c);
        *intersectY = (c * threePoints[1] + a * threePoints[5] + b * threePoints[3]) / (a + b + c);
    }
    void drawIncircle()
    {
        double r = 0.0, intersectX = 0.0, intersectY = 0.0;

        calcIncenter(&intersectX, &intersectY, &r);

        drawCircle((int)intersectX, (int)intersectY, (int)r);
        cout << "Incircle has been drawn" << endl;
    }
    void calcCircumcenter(double *intersectX, double *intersectY, double *R)
    {
        double a = 0.0, b = 0.0, c = 0.0, s = 0.0, r = 0.0, angleA = 0.0, angleB = 0.0, angleC = 0.0;

        a = sqrt(pow(threePoints[0] - threePoints[2], 2) + pow(threePoints[1] - threePoints[3], 2)); // AB
        b = sqrt(pow(threePoints[0] - threePoints[4], 2) + pow(threePoints[1] - threePoints[5], 2)); // BC
        c = sqrt(pow(threePoints[2] - threePoints[4], 2) + pow(threePoints[3] - threePoints[5], 2)); // AC

        s = 0.5 * (a + b + c);
        r = sqrt(((s - a) * (s - b) * (s - c)) / s);
        *R = (a * b * c) / (4 * r * s);

        angleC = acos((pow(c, 2) - pow(a, 2) - pow(b, 2)) / (-2 * a * b)); //Calculates in radians
        angleB = acos((pow(b, 2) - pow(a, 2) - pow(c, 2)) / (-2 * a * c));
        angleA = acos((pow(a, 2) - pow(b, 2) - pow(c, 2)) / (-2 * b * c));

        *intersectX = ((threePoints[0] * sin(2 * angleC)) + (threePoints[2] * sin(2 * angleB)) + (threePoints[4] * sin(2 * angleA))) / (sin(2 * angleA) + sin(2 * angleB) + sin(2 * angleC));
        *intersectY = ((threePoints[1] * sin(2 * angleC)) + (threePoints[3] * sin(2 * angleB)) + (threePoints[5] * sin(2 * angleA))) / (sin(2 * angleA) + sin(2 * angleB) + sin(2 * angleC));
    }
    void drawCircumcircle()
    {
        double R = 0.0, intersectX = 0.0, intersectY = 0.0;

        calcCircumcenter(&intersectX, &intersectY, &R);

        drawCircle((int)intersectX, (int)intersectY, (int)R);
        cout << "Circumcircle has been drawn" << endl;
    }
    void calcCentroid(double *intersectX, double *intersectY)
    {
        *intersectX = (threePoints[0] + threePoints[2] + threePoints[4]) / 3;
        *intersectY = (threePoints[1] + threePoints[3] + threePoints[5]) / 3;
    }
    void drawEulerLine()
    {
        double circumX = 0.0, circumY = 0.0, centroidX = 0.0, centroidY = 0.0, slope = 0.0, b = 0.0, temp = 0.0;

        calcCircumcenter(&circumX, &circumY, &temp);
        calcCentroid(&centroidX, &centroidY);
        slope = (circumY - centroidY) / (circumX - centroidX);
        b = centroidY - (slope * centroidX);

        bresenhamLine((0 - b) / slope, 0, (800 - b) / slope, 800);
    }
    ~PPMGenerator() { cout << "PPMGenerator has been deleted." << endl; }
};

int main()
{
    PPMGenerator *c = new PPMGenerator();
    c->test();
    c->drawTriangle();
    cout << "here" << endl;
    c->drawIncircle();
    c->drawCircumcircle();
    c->drawEulerLine();
    c->createPPMFile();
    delete c;
    return 0;
}
