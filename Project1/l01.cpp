// Ram Reddy
// Period 4
// 08/28/2021

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cmath>
using namespace std;

class PPMGenerator
{
private:
    int image[50][50] = {{0}};
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
    void case1and2(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = y1;
        int error = changeY - changeX;

        for (int i = x1; i < x2; i++)
        {
            image[i][j] = 1;
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
            image[i][y] = 1;
        }
    }
    void case5and6(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = y1;
        int error = changeY - changeX;

        for (int i = x1; i >= x2; i--)
        {
            image[i][j] = 1;
            if (error >= 0)
            {
                j += 1;
                error -= changeX;
            }
            error += changeY;
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
        }

        // Case 7: x2 > x1 and y2 > y1
        // Case 8: x2 < x1 and y2 < y1
        // Case 9: x2 > x1 and y2 < y1
        // Case 10: x2 < x1 and y2 > y1
        // Case 11: x2 = x1 and y2 > y1
        // Case 12: x2 = x1 and y2 < y1
    }
    void drawTriangle()
    {
        int distinctPoints = 1;
        bool distinct = true;
        int threePoints[6] = {0};
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
        bresenhamLine(threePoints[0], threePoints[1], threePoints[2], threePoints[2]);
        cout << "Line 1 has been drawn." << endl;
        bresenhamLine(threePoints[0], threePoints[1], threePoints[4], threePoints[5]);
        cout << "Line 2 has been drawn." << endl;
        bresenhamLine(threePoints[2], threePoints[3], threePoints[4], threePoints[5]);
        cout << "Triangle has been drawn." << endl;
    }
    ~PPMGenerator() { cout << "PPMGenerator has been deleted." << endl; }
};

int main()
{
    PPMGenerator *c = new PPMGenerator();
    c->test();
    // c->drawTriangle();
    // 33 36 27 15 43 35
    c->bresenhamLine(3, 0, 0, 3);
    c->createPPMFile();
    delete c;
    return 0;
}
