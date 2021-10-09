// Ram Reddy
// Period 4
// 09/09/2021

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>
#include <time.h>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <vector>

using namespace std;

// This is a point class
class Point
{
private:
    double x;
    double y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double getX()
    {
        return x;
    }
    double getY()
    {
        return y;
    }
    void setX(double x)
    {
        this->x = x;
    }
    void setY(double y)
    {
        this->y = y;
    }
    double calcDistance(Point pt2)
    {
        return sqrt(pow((pt2.getX() - x), 2) + pow((pt2.getY() - y), 2));
    }
    string toString()
    {
        return "(" + to_string(x) + "," + to_string(y) + ")";
    }
};

// This is a line class
class Line
{
private:
    Point pt1;
    Point pt2;
    double a;
    double b;
    double c;

public:
    Line() {}
    Line(Point pt1, Point pt2)
    {
        this->pt1 = pt1;
        this->pt2 = pt2;
        this->a = -1 * (pt2.getY() - pt1.getY());
        this->b = pt2.getX() - pt1.getX();
        this->c = a * pt1.getX() + b * pt1.getY();
    }
    double getXfromY(double y)
    {
        if (b == 0)
        {
            return pt1.getX();
        }
        else if (a == 0)
        {
            return -numeric_limits<double>::infinity();
        }
        else
        {
            return (c - b * y) / a;
        }
    }

    double getYfromX(double x)
    {
        if (a == 0)
        {
            return -numeric_limits<double>::infinity();
        }
        else if (b == 0)
        {
            return pt1.getY();
        }
        else
        {
            return (c - a * x) / b;
        }
    }

    Point *getIntersection(Line ln2)
    {
        double denominator = a * ln2.getB() - b * ln2.getA();
        if (denominator == 0)
        { // No solution or parallel
            return NULL;
        }
        else
        {
            return new Point((c * ln2.getB() - b * ln2.getC()) / denominator, (a * ln2.getC() - c * ln2.getA()) / denominator);
        }
    }
    Line *getPerpendicular(Point pt3)
    {
        if (a == 0)
        {
            return new Line(Point(pt3.getX(), getYfromX(pt3.getX())), pt3);
        }
        if (b == 0)
        {
            return new Line(Point(getXfromY(pt3.getY()), pt3.getY()), pt3);
        }
        double slope = b / a;
        return new Line(Point(pt3.getX() + 1, pt3.getY() + slope), pt3);
    }
    string toString()
    {
        return to_string(a) + "*x + " + to_string(b) + "*y = " + to_string(c);
    }
    Point getPt1()
    {
        return pt1;
    }
    Point getPt2()
    {
        return pt2;
    }
    double getA()
    {
        return a;
    }
    double getB()
    {
        return b;
    }
    double getC()
    {
        return c;
    }
};

// This is a class that can generate a PPM3 file
class PPMGenerator
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
    void createPPMFile(string filename)
    {
        ofstream outfile(filename);
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
            image[y][x] = shade;
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
    void bresenhamLine(Point point1, Point point2, int scaler)
    {
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
            else if (x2 == x1 && y2 > y1) // Case 11: x2 = x1 and y2 > y1
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

    void screenLine(Point point1, Point point2, int scaler)
    {
        double slope = 0.0, b = 0.0;
        slope = (point1.getY() - point2.getY()) / (point1.getX() - point2.getX());
        if (isfinite(slope))
        {
            b = point1.getY() - (slope * point1.getX());
            bresenhamLine(Point((0 - b) / slope, 0), Point((rows - b) / slope, rows), scaler);
        }
        else
        {
            bresenhamLine(Point(point2.getX() * scaler, 0), Point(point2.getX() * scaler, rows), scaler);
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
};
// This method generates random pixels from an array
vector<Point> generatePoints(int size, vector<Point> genPoints)
{

    if (size % 2 == 0)
    {
        double tempPoints[size] = {0};
        random_device rd;
        uniform_real_distribution<double> uRD(0.0, 1.0);

        int distinctPoints = 1;
        bool distinct = true;
        while (distinctPoints < (size / 2) + 1) // Gets random points
        {
            double x = uRD(rd);
            double y = uRD(rd);
            for (int i = 0; i < distinctPoints; i++)
            {
                if (tempPoints[i] == x && tempPoints[i + 1] == y)
                {
                    distinct = false;
                }
            }
            if (distinct == true)
            {
                tempPoints[(distinctPoints * 2) - 2] = x;
                tempPoints[(distinctPoints * 2) - 1] = y;
                distinctPoints += 1;
            }
            else
            {
                distinct = true;
            }
        }
        genPoints.clear();
        for (int i = 0; i < size / 2; i++)
        {
            genPoints.push_back(Point(tempPoints[i * 2], tempPoints[i * 2 + 1]));
        }
    }

    return genPoints;
}
vector<Point> readFile(string file, string delimiter, vector<Point> genPoints)
{
    ifstream input(file);
    string s1 = "";
    string s2 = "";
    for (string line; getline(input, line);)
    {
        s1 += line;
    }
    for (char i : s1)
    {
        if (s2.size() == 0 && i != '(')
        {
        }
        else if (i != ')')
        {
            s2 += i;
        }
        if (i == ')')
        {
            int loc = s2.find(delimiter, 0);
            genPoints.push_back(Point(stod(s2.substr(1, loc - 1)), stod(s2.substr(loc + 1, s2.size()))));
            s2.erase();
        }
    }
    return genPoints;
}

void permute(string str, vector<string> *permutations, int l, int r)
{
    if (l == r)
    {
        permutations->push_back(str);
    }

    for (int i = l; i <= r; i++)
    {
        swap(str[l], str[i]);
        permute(str, permutations, l + 1, r);
        swap(str[l], str[i]);
    }
}

Point *findE(Point from, Line current, double distance)
{

    double slope = -1 * current.getA() / current.getB();
    double times = sqrt(pow(slope, 2) + 1);
    return new Point(from.getX() + distance / times, from.getY() + slope * (distance / times));
}

vector<Point> smallestSquare(Point a, Point b, Point c, Point d)
{
    vector<Point> genPoints;
    Line *line1 = new Line(a, c);
    Line *helperLn = line1->getPerpendicular(b);
    Point *e = new Point();
    e = findE(b, *helperLn, c.calcDistance(a));
    Line *lineE = new Line(*e, d);
    Line *helperLn1 = lineE->getPerpendicular(a);
    Line *helperLn2 = lineE->getPerpendicular(c);
    Line *helperLn3 = helperLn1->getPerpendicular(b);
    Point *pointA = lineE->getIntersection(*helperLn1);
    Point *pointB = lineE->getIntersection(*helperLn2);
    Point *pointC = helperLn3->getIntersection(*helperLn1);
    Point *pointD = helperLn3->getIntersection(*helperLn2);
    genPoints.push_back(*pointA);
    genPoints.push_back(*pointB);
    genPoints.push_back(*pointC);
    genPoints.push_back(*pointD);
    delete line1, delete e, delete lineE, delete helperLn1, delete helperLn2, delete helperLn3, delete pointA, delete pointB, delete pointC, delete pointD;
    return genPoints;
}

void part2()
{
    PPMGenerator *c = new PPMGenerator();
    vector<Point> genPoints;
    genPoints = readFile("points.txt", ",", genPoints);
    for (Point i : genPoints)
    {
        c->drawCircle((int)(i.getX() * 800), (int)(i.getY() * 800), 2);
    }

    vector<vector<Point>> squares;
    vector<double> areas;
    vector<string> *permutations = new vector<string>;
    permute("1234", permutations, 0, 3);
    for (string str : *permutations)
    {
        vector<Point> genSquare = smallestSquare(genPoints[stoi(str.substr(0, 1)) - 1], genPoints[stoi(str.substr(1, 1)) - 1], genPoints[stoi(str.substr(2, 1)) - 1], genPoints[stoi(str.substr(3, 1)) - 1]);
        double area = pow(genSquare[0].calcDistance(genSquare[1]), 2);
        bool isIn = false;
        for (double sArea : areas)
        {
            if (abs(sArea - area) < 1e-10)
            {
                isIn = true;
            }
        }
        if (isIn == false)
        {
            areas.push_back(area);
            squares.push_back(genSquare);
        }
    }
    ofstream outfile("output.txt");
    outfile << setprecision(17) << "(" << genPoints[0].getX() << "," << genPoints[0].getY() << ") ,  (" << genPoints[1].getX() << "," << genPoints[1].getY() << ") ,  (" << genPoints[2].getX() << "," << genPoints[2].getY() << ") ,  (" << genPoints[3].getX() << "," << genPoints[3].getY() << ")" << endl;
    for (int i = 0; i < 6; i++)
    {
        outfile << setprecision(17) << "(" << squares[i][0].getX() << "," << squares[i][0].getY() << ") ,  (" << squares[i][1].getX() << "," << squares[i][1].getY() << ") ,  (" << squares[i][2].getX() << "," << squares[i][2].getY() << ") ,  (" << squares[i][3].getX() << "," << squares[i][3].getY() << ") Area = " << areas[i] << endl;
    }
    outfile.close();
    int min = min_element(areas.begin(), areas.end()) - areas.begin();
    c->screenLine(squares[min][0], squares[min][1], 800);
    c->screenLine(squares[min][0], squares[min][2], 800);
    c->screenLine(squares[min][3], squares[min][1], 800);
    c->screenLine(squares[min][3], squares[min][2], 800);
    for (Point p : squares[min])
    {
        c->drawCircle((int)(p.getX() * 800), (int)(p.getY() * 800), 5);
    }
    c->createPPMFile("output.ppm");

    delete c, delete permutations;
}

// This method calculates and returns a triangle area from three points
double calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return 0.5 * abs((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)));
}

void part1()
{
    vector<Point> points = {Point(), Point(), Point()};
    vector<Point> lastPoint = {Point()};
    double error = 1e-13;
    while ((points[0].getX() * (points[1].getY() - points[2].getY())) + (points[1].getX() * (points[2].getY() - points[0].getY())) + (points[2].getX() * (points[0].getY() - points[1].getY())) == 0) // Checks coliniarity
    {
        points = generatePoints(6, points);
    }

    lastPoint = generatePoints(2, lastPoint);

    // Below loop checks the three triangle area between whole triangle
    while (abs((calcTriangleArea(points[0].getX(), points[0].getY(), points[1].getX(), points[1].getY(), lastPoint[0].getX(), lastPoint[0].getY()) +
                calcTriangleArea(points[0].getX(), points[0].getY(), lastPoint[0].getX(), lastPoint[0].getY(), points[2].getX(), points[2].getY()) +
                calcTriangleArea(lastPoint[0].getX(), lastPoint[0].getY(), points[1].getX(), points[1].getY(), points[2].getX(), points[2].getY())) -
               calcTriangleArea(points[0].getX(), points[0].getY(), points[1].getX(), points[1].getY(), points[2].getX(), points[2].getY())) < error)
    {
        cout << "regenerating" << endl;
        lastPoint = generatePoints(2, lastPoint);
    }

    ofstream outfile("points.txt");
    for (int i = 0; i < 4; i++)
    {
        if (i < 3)
        {
            outfile << setprecision(17) << "(" << points[i].getX() << "," << points[i].getY() << ") , ";
        }
        else
        {
            outfile << setprecision(17) << "(" << lastPoint[0].getX() << "," << lastPoint[0].getY() << ")";
        }
    }
    outfile.close();
    cout << "Created file." << endl;
}

int main()
{
    //     part1();
    part2();
    return 0;
}