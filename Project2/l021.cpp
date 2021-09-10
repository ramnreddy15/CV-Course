// Ram Reddy
// Period 4
// 09/09/2021

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <time.h>

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
                } else {
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
    
    double calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3) {
        return 0.5*abs((x1*(y2-y3)) + (x2*(y3-y1)) + (x3*(y1-y2)));
    }
    
};

void part1() {
    CoordinateGeometry *c = new CoordinateGeometry();
    double points[6] = {0};
    double lastPoint[2] = {0};
    
    
    while ((points[0]*(points[3]-points[5])) + (points[2]*(points[5]-points[1])) + (points[4]*(points[1]-points[3])) == 0) { // Checks coliniarity
        c->generatePoints(6, points);  
    }
    
    for(double x:points) {
        cout << x << endl;
    }
    cout << "end" << endl;
    
    c->generatePoints(2, lastPoint);
    
    for(double x:lastPoint) {
        cout << x << endl;
    }
    cout << "ca" << endl;
     cout << (c->calcTriangleArea(points[0], points[1], points[2], points[3],lastPoint[0],lastPoint[1]) + c->calcTriangleArea(points[0], points[1], lastPoint[0], lastPoint[1], points[4], points[5]) +c->calcTriangleArea(lastPoint[0], lastPoint[1], points[2], points[3], points[4], points[5])) << endl;
    
    cout << c->calcTriangleArea(points[0], points[1], points[2], points[3], points[4], points[5]) << endl;
//     while( +  +  == ) {
//         cout << "regenerating" << endl;
//         c->generatePoints(2, lastPoint);
//     }
    
    for(double x:lastPoint) {
        cout << x << endl;
    }

}

int main() {
    part1();
   
    return 0;
}