#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
using namespace std;
class Point
{
private:
    double x, y;
    static bool sortFunct(Point i, Point j) { return (j.y > i.y); }; // compare by y-value
public:
    Point()
    { // constructs random point in unit square
        x = double(rand()) / RAND_MAX;
        y = double(rand()) / RAND_MAX;
    }
    string toString(void) { return std::to_string(x) + " " + std::to_string(y); }
    list<Point> getSorted(list<Point> listOfPoints)
    {
        listOfPoints.sort(sortFunct); // invoke system sort with sortFunct comparator
        return listOfPoints;
    }
};
int main(void)
{
    srand(time(NULL));  // use clock to seed random number generator
    list<Point> points; // creates list for point insertion Point usecase;
                        //just used to call methods, has no value;
    for (int i = 0; i < 10; i++)
    {
        points.push_back(Point());
    } //randomly generates 10 points
    cout << "Before Sorting by Y-Value:"
         << "\n"
         << endl;
    for (auto &i : points)
    {
        cout << i.toString() << endl;
    } //iterates through points and prints them out
    cout << "\n"
         << "After Sorting by Y-Value:"
         << "\n"
         << endl;
    for (auto &i : Point::getSorted(points))
    {
        cout << i.toString() << endl;
    } //iterates through the sorted list
}