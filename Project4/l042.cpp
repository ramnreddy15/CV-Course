// Ram Reddy
// Period 4
// 12/12/2021

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>
#include <chrono>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <vector>
#include <stack>

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
    double calcDistanceNS(Point pt2)
    {
        return pow((pt2.getX() - x), 2) + pow((pt2.getY() - y), 2);
    }
    string toString()
    {
        ostringstream temp;
        temp << fixed << setprecision(23) << "(" << x << "," << y << ")";
        return temp.str();
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
    int image[400][400][3] = {{{0}}};
    int rows;
    int cols;

public:
    // This is the constructor
    PPMGenerator()
    {
        rows = sizeof(image) / sizeof(image[0]);
        cols = sizeof(image) / sizeof(image[1]);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                for (int c = 0; c < 3; c++)
                {
                    image[i][j][c] = 255;
                }
            }
        }
    }

    // This method creates a PPM file from the image array when called
    void createPPMFile(string filename)
    {
        ofstream outfile(filename);
        outfile << "P3 " + to_string(rows) + " " + to_string(cols) + " 255" << endl; // columns by rows
        for (int i = 0; i < cols; i++)
        {
            string temp = "";
            for (int j = 0; j < rows; j++)
            {
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
    void setPixel(int x, int y, int shadeR, int shadeG, int shadeB)
    {
        if (x >= 0 && y >= 0 && y < rows && x < cols)
        {
            image[y][x][0] = shadeR;
            image[y][x][1] = shadeG;
            image[y][x][2] = shadeB;
        }
    }

    // Case 1 and 2 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
    void case1and2(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = y1;
        int error = changeY - changeX;

        for (int i = x1; i < x2; i++)
        {
            setPixel(i, j, 0, 0, 0);
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
            setPixel(i, y, 0, 0, 0);
        }
    }

    // Case 5 and 6 when drawing a line: (x2 < x1 and y2 > y1) or ( x2 > x1 and y2 < y1)
    void case5and6(int x1, int y1, int x2, int y2, int changeX, int changeY)
    {
        int j = y1;
        int error = changeY - changeX;

        for (int i = x1; i >= x2; i--)
        {
            setPixel(i, j, 0, 0, 0);
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
            setPixel(j, i, 0, 0, 0);
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
            setPixel(j, i, 0, 0, 0);
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
            setPixel(x, i, 0, 0, 0);
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
        slope =
            (point1.getY() - point2.getY()) / (point1.getX() - point2.getX());
        if (isfinite(slope))
        {
            b = point1.getY() - (slope * point1.getX());
            bresenhamLine(Point((0 - b) / slope, 0),
                          Point((rows - b) / slope, rows), scaler);
        }
        else
        {
            bresenhamLine(Point(point2.getX() * scaler, 0),
                          Point(point2.getX() * scaler, rows), scaler);
        }
    }

    // Draws a circle given the center coordinates and radius
    void drawCircle(int centerX, int centerY, int r, int shade[3])
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
            setPixel(centerX + x, centerY + y, shade[0], shade[1], shade[2]);
            setPixel(centerX + x, centerY + -y, shade[0], shade[1], shade[2]);
            setPixel(centerX + -x, centerY + y, shade[0], shade[1], shade[2]);
            setPixel(centerX + -x, centerY + -y, shade[0], shade[1], shade[2]);
            setPixel(centerX + y, centerY + x, shade[0], shade[1], shade[2]);
            setPixel(centerX + y, centerY + -x, shade[0], shade[1], shade[2]);
            setPixel(centerX + -y, centerY + x, shade[0], shade[1], shade[2]);
            setPixel(centerX + -y, centerY + -x, shade[0], shade[1], shade[2]);
            y2_new -= (2 * x) - 3;
        }
    }
};

void generatePointstoFile(int amount, string place)
{
    ofstream outfile(place);
    random_device rd;
    uniform_real_distribution<double> uRD(0.0, 1.0);
    for (int i = 0; i < amount; i++)
    {
        double x = uRD(rd);
        double y = uRD(rd);
        outfile << setprecision(23) << x << "  " << y << endl;
    }
    outfile.close();
}

void readFile(string file, string delimiter, vector<Point> &genPoints)
{
    ifstream input(file);
    string s1 = "";
    int loc = 0;
    for (string line; getline(input, line);)
    {
        s1 = line;
        for (char i : s1)
        {
            loc = s1.find(delimiter, 0);
        }
        genPoints.push_back(Point(stod(s1.substr(0, loc - 1)), stod(s1.substr(loc + delimiter.size(), s1.size()))));
        s1.erase();
    }
}

double calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return 0.5 * abs((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)));
}

void findHull(vector<Point> set, Point p1, Point p2, vector<Point> &hull)
{
    if (set.size() == 0)
    {
        return;
    }

    double maxDist = 0;
    double error = 1e-13;
    Point maxPoint;
    vector<Point> s1, s2;
    Line temp = Line(p2, p1);

    for (long unsigned int i = 0; i < set.size(); i++)
    {
        if ((set[i].getX() != p1.getX() || set[i].getY() != p1.getY()) && (set[i].getX() != p2.getX() || set[i].getY() != p2.getY()))
        {
            if (abs(temp.getA() * set[i].getX() + temp.getB() * set[i].getY() - temp.getC()) / sqrt(pow(temp.getA(), 2) + pow(temp.getB(), 2)) > maxDist)
            {
                maxDist = abs(temp.getA() * set[i].getX() + temp.getB() * set[i].getY() - temp.getC()) / sqrt(pow(temp.getA(), 2) + pow(temp.getB(), 2));
                maxPoint = set[i];
            }
        }
    }

    for (long unsigned int i = 0; i < hull.size(); i++)
    {
        if (hull[i].getX() == p1.getX() && hull[i].getY() == p1.getY())
        {
            hull.insert(hull.begin() + i + 1, maxPoint);
            i = hull.size() + 1;
        }
    }

    for (long unsigned int i = 0; i < set.size(); i++)
    {
        if (abs((calcTriangleArea(set[i].getX(), set[i].getY(), p1.getX(), p1.getY(), p2.getX(), p2.getY()) +
                 calcTriangleArea(set[i].getX(), set[i].getY(), maxPoint.getX(), maxPoint.getY(), p2.getX(), p2.getY()) +
                 calcTriangleArea(set[i].getX(), set[i].getY(), maxPoint.getX(), maxPoint.getY(), p1.getX(), p1.getY())) -
                calcTriangleArea(p1.getX(), p1.getY(), p2.getX(), p2.getY(), maxPoint.getX(), maxPoint.getY())) > error)
        {
            if (maxPoint.getX() < set[i].getX())
            {
                s2.push_back(set[i]);
            }
            else if (maxPoint.getX() > set[i].getX())
            {
                s1.push_back(set[i]);
            }
        }
    }

    findHull(s1, p1, maxPoint, hull);
    findHull(s2, maxPoint, p2, hull);
}

void quickHull(vector<Point> &genPoints)
{
    int min = 0, max = 0;
    vector<Point> s1, s2;
    vector<Point> *hullL = new vector<Point>;
    vector<Point> *hullR = new vector<Point>;
    PPMGenerator *c = new PPMGenerator();
    int shade[3] = {0, 0, 0};

    for (long unsigned int i = 1; i < genPoints.size(); i++)
    {
        if (genPoints[min].getX() > genPoints[i].getX())
        {
            min = i;
        }
        if (genPoints[max].getX() < genPoints[i].getX())
        {
            max = i;
        }
    }

    hullL->push_back(genPoints[min]);
    hullL->push_back(genPoints[max]);
    hullR->push_back(genPoints[min]);
    hullR->push_back(genPoints[max]);

    Line startL = Line(genPoints[min], genPoints[max]);
    for (Point p : genPoints)
    {
        if (p.getY() > startL.getYfromX(p.getX()))
        {
            s1.push_back(p);
        }
        else if (p.getY() < startL.getYfromX(p.getX()))
        {
            s2.push_back(p);
        }
    }

    findHull(s1, genPoints[min], genPoints[max], *hullL);
    findHull(s2, genPoints[min], genPoints[max], *hullR);

    for (long unsigned int i = 0; i < genPoints.size(); i++)
    {
        c->drawCircle((int)(genPoints[i].getX() * 400), (int)(genPoints[i].getY() * 400), 3, shade);
    }

    for (long unsigned int i = 0; i < hullL->size() - 1; i++)
    {
        c->bresenhamLine(hullL->operator[](i), hullL->operator[](i + 1), 400);
    }

    for (long unsigned int i = 0; i < hullR->size() - 1; i++)
    {
        c->bresenhamLine(hullR->operator[](i), hullR->operator[](i + 1), 400);
    }

    c->createPPMFile("quichull.ppm");
    delete c, hullL, hullR;
}

void part1()
{
    generatePointstoFile(60, "points.txt");
    vector<Point> *genPoints = new vector<Point>;
    readFile("points.txt", "  ", *genPoints);
    quickHull(*genPoints);
    delete genPoints;
}

Point p0 = Point(100, 100);

bool polarSort(Point p1, Point p2)
{
    return atan2(p1.getY() - p0.getY(), p1.getX() - p0.getX()) < atan2(p2.getY() - p0.getY(), p2.getX() - p0.getX()); // change thi lstaerasd
}

bool ccw(Point p1, Point p2, Point p3)
{
    if ((p2.getX() - p1.getX()) * (p3.getY() - p2.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p2.getX()) < 0.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void grahamScan(vector<Point> &genPoints)
{
    stack<Point> hull;
    vector<Point> hullVec;
    Point tempTop, tempPrevTop, p1;
    bool loop = true;
    PPMGenerator *c = new PPMGenerator();
    int shade[3] = {0, 0, 0};
    for (Point p : genPoints)
    {
        if (p.getY() < p0.getY())
        {
            p0 = p;
        }
        else if (p.getY() == p0.getY())
        {
            if (p.getX() < p0.getX())
            {
                p0 = p;
            }
        }
    }
    sort(genPoints.begin(), genPoints.end(), polarSort);
    p1 = genPoints[1];
    genPoints.erase(genPoints.begin());
    genPoints.erase(genPoints.begin());

    hull.push(p0);
    hull.push(p1);

    for (Point p : genPoints)
    {
        while (hull.size() > 1 && loop == true)
        {
            tempTop = hull.top();
            hull.pop();
            tempPrevTop = hull.top();
            if (ccw(tempPrevTop, tempTop, p) == false)
            {
                hull.push(tempTop);
                loop = false;
            }
        }
        loop = true;
        hull.push(p);
    }

    genPoints.push_back(p0);
    genPoints.push_back(p1);
    for (long unsigned int i = 0; i < genPoints.size(); i++)
    {
        c->drawCircle((int)(genPoints[i].getX() * 400), (int)(genPoints[i].getY() * 400), 3, shade);
    }

    hullVec.push_back(p0);
    while (hull.size() > 0)
    {
        hullVec.push_back(hull.top());
        hull.pop();
    }
    for (long unsigned int i = 0; i < hullVec.size() - 1; i++)
    {
        c->bresenhamLine(hullVec[i], hullVec[i + 1], 400);
    }

    c->createPPMFile("grahamscan.ppm");
    delete c;
}

void part2()
{
    generatePointstoFile(60, "points.txt");
    vector<Point> *genPoints = new vector<Point>;
    readFile("points.txt", "  ", *genPoints);
    grahamScan(*genPoints);
    delete genPoints;
}

int main()
{
    part2();
    return 0;
}