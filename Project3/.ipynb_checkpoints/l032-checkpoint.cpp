// Ram Reddy
// Period 4
// 10/19/2021

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
#include <list>

using namespace std;

// This is a point class
class Point
{
private:
  double x;
  double y;

public:
    Point ()
  {
    this->x = 0;
    this->y = 0;
  }
  Point (double x, double y)
  {
    this->x = x;
    this->y = y;
  }
  double getX ()
  {
    return x;
  }
  double getY ()
  {
    return y;
  }
  void setX (double x)
  {
    this->x = x;
  }
  void setY (double y)
  {
    this->y = y;
  }
  double calcDistance (Point pt2)
  {
    return sqrt (pow ((pt2.getX () - x), 2) + pow ((pt2.getY () - y), 2));
  }
  string toString ()
  {
    return "(" + to_string (x) + "," + to_string (y) + ")";
  }
};

// This is a class that can generate a PPM3 file
class PPMGenerator
{
private:
  int image[800][800][3] = { {{0}} };
  int rows;
  int cols;

public:
  // This is the constructor
  PPMGenerator ()
  {
    rows = sizeof (image) / sizeof (image[0]);
    cols = sizeof (image) / sizeof (image[1]);
    for (int i = 0; i < 800; i++)
      {
	for (int j = 0; j < 800; j++)
	  {
	    for (int c = 0; c < 3; c++)
	      {
		image[i][j][c] = 255;
	      }
	  }
      }
  }

  // This method creates a PPM file from the image array when called
  void createPPMFile (string filename)
  {
    ofstream outfile (filename);
    outfile << "P3 " + to_string (rows) + " " + to_string (cols) + " 255" << endl;	// columns by rows
    for (int i = 0; i < cols; i++)
      {
	string temp = "";
	for (int j = 0; j < rows; j++)
	  {
	    temp +=
	      to_string (image[i][j][0]) + " " + to_string (image[i][j][1]) +
	      " " + to_string (image[i][j][2]) + " ";
	  }
	outfile << temp << endl;
	temp.clear ();
      }
    outfile.close ();
  }

  // This method sets a pixel in the array when called
  void setPixel (int x, int y, int shadeR, int shadeG, int shadeB)
  {
    if (x >= 0 && y >= 0 && y < rows && x < cols)
      {
	image[y][x][0] = shadeR;
	image[y][x][1] = shadeG;
	image[y][x][2] = shadeB;
      }
  }

  // Case 1 and 2 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
  void case1and2 (int x1, int y1, int x2, int y2, int changeX, int changeY)
  {
    int j = y1;
    int error = changeY - changeX;

    for (int i = x1; i < x2; i++)
      {
	setPixel (i, j, 0, 0, 0);
	if (error >= 0)
	  {
	    j += 1;
	    error -= changeX;
	  }
	error += changeY;
      }
  }

  // Case 3 and 4 when drawing a line: (x2 > x1 and y2 = y1) or (Case 4: x2 < x1 and y2 = y1)
  void case3and4 (int x1, int y, int x2)
  {
    for (int i = x1; i < x2; i++)
      {
	setPixel (i, y, 0, 0, 0);
      }
  }

  // Case 5 and 6 when drawing a line: (x2 < x1 and y2 > y1) or ( x2 > x1 and y2 < y1)
  void case5and6 (int x1, int y1, int x2, int y2, int changeX, int changeY)
  {
    int j = y1;
    int error = changeY - changeX;

    for (int i = x1; i >= x2; i--)
      {
	setPixel (i, j, 0, 0, 0);
	if (error >= 0)
	  {
	    j += 1;
	    error -= changeX;
	  }
	error += changeY;
      }
  }

  // Case 7 and 8 when drawing a line: (x2 > x1 and y2 > y1) or (x2 < x1 and y2 < y1)
  void case7and8 (int x1, int y1, int x2, int y2, int changeX, int changeY)
  {
    int j = x1;
    int error = changeX - changeY;

    for (int i = y1; i < y2; i++)
      {
	setPixel (j, i, 0, 0, 0);
	if (error >= 0)
	  {
	    j += 1;
	    error -= changeY;
	  }
	error += changeX;
      }
  }

  // Case 9 and 10 when drawing a line: (x2 > x1 and y2 < y1) or (x2 < x1 and y2 > y1)
  void case9and10 (int x1, int y1, int x2, int y2, int changeX, int changeY)
  {
    int j = x1;
    int error = changeX - changeY;

    for (int i = y1; i >= y2; i--)
      {
	setPixel (j, i, 0, 0, 0);
	if (error >= 0)
	  {
	    j += 1;
	    error -= changeY;
	  }
	error += changeX;
      }
  }

  // Case 11 and 12 when drawing a line: (x2 < x1 and y2 > y1) or (x2 = x1 and y2 < y1)
  void case11and12 (int x, int y1, int y2)
  {
    for (int i = y1; i < y2; i++)
      {
	setPixel (x, i, 0, 0, 0);
      }
  }

  // This method creates a line in the image array when callled
  void bresenhamLine (Point point1, Point point2, int scaler)
  {
    int x1 = (int) (point1.getX () * scaler);
    int y1 = (int) (point1.getY () * scaler);
    int x2 = (int) (point2.getX () * scaler);
    int y2 = (int) (point2.getY () * scaler);

    int changeX = abs (x2 - x1);
    int changeY = abs (y2 - y1);

    // 12 cases
    if (changeX >= changeY)	// 6 cases for X Direct Axis
      {
	if (x2 > x1 && y2 > y1)	// Case 1: x2 > x1 and y2 > y1
	  {
	    cout << "Case 1" << endl;
	    case1and2 (x1, y1, x2, y2, changeX, changeY);
	  }
	else if (x2 < x1 && y2 < y1)	// Case 2: x2 < x1 and y2 < y1
	  {
	    cout << "Case 2" << endl;
	    case1and2 (x2, y2, x1, y1, changeX, changeY);
	  }
	else if (x2 > x1 && y2 == y1)	// Case 3: x2 > x1 and y2 = y1
	  {
	    cout << "Case 3" << endl;
	    case3and4 (x1, y1, x2);
	  }
	else if (x2 < x1 && y2 == y1)	// Case 4: x2 < x1 and y2 = y1
	  {
	    cout << "Case 4" << endl;
	    case3and4 (x2, y1, x1);
	  }
	else if (x2 < x1 && y2 > y1)	// Case 5: x2 < x1 and y2 > y1
	  {
	    cout << "Case 5" << endl;
	    case5and6 (x1, y1, x2, y2, changeX, changeY);
	  }
	else if (x2 > x1 && y2 < y1)	// Case 6: x2 > x1 and y2 < y1
	  {
	    cout << "Case 6" << endl;
	    case5and6 (x2, y2, x1, y1, changeX, changeY);
	  }
      }
    else			// 6 cases for Y Direct Axis
      {
	if (x2 > x1 && y2 > y1)	// Case 7: x2 > x1 and y2 > y1
	  {
	    cout << "Case 7" << endl;
	    case7and8 (x1, y1, x2, y2, changeX, changeY);
	  }
	else if (x2 < x1 && y2 < y1)	// Case 8: x2 < x1 and y2 < y1
	  {
	    cout << "Case 8" << endl;
	    case7and8 (x2, y2, x1, y1, changeX, changeY);
	  }
	else if (x2 > x1 && y2 < y1)	// Case 9: x2 > x1 and y2 < y1
	  {
	    cout << "Case 9" << endl;
	    case9and10 (x1, y1, x2, y2, changeX, changeY);
	  }
	else if (x2 < x1 && y2 > y1)	// Case 10: x2 < x1 and y2 > y1
	  {
	    cout << "Case 10" << endl;
	    case9and10 (x2, y2, x1, y1, changeX, changeY);
	  }
	else if (x2 == x1 && y2 > y1)	// Case 11: x2 = x1 and y2 > y1
	  {
	    cout << "Case 11" << endl;
	    case11and12 (x1, y1, y2);
	  }
	else			// Case 12: x2 = x1 and y2 < y1
	  {
	    cout << "Case 12" << endl;
	    case11and12 (x1, y2, y1);
	  }
      }
  }

  void screenLine (Point point1, Point point2, int scaler)
  {
    double slope = 0.0, b = 0.0;
    slope =
      (point1.getY () - point2.getY ()) / (point1.getX () - point2.getX ());
    if (isfinite (slope))
      {
	b = point1.getY () - (slope * point1.getX ());
	bresenhamLine (Point ((0 - b) / slope, 0),
		       Point ((rows - b) / slope, rows), scaler);
      }
    else
      {
	bresenhamLine (Point (point2.getX () * scaler, 0),
		       Point (point2.getX () * scaler, rows), scaler);
      }
  }

  // Draws a circle given the center coordinates and radius
  void drawCircle (int centerX, int centerY, int r, int shade[3])
  {
    int x = 0, y = 0, xmax = 0, y2 = 0, y2_new = 0, ty = 0;
    xmax = (int) (r * 0.70710678);	// maximum x at radius/sqrt(2)
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
	setPixel (centerX + x, centerY + y, shade[0], shade[1], shade[2]);
	setPixel (centerX + x, centerY + -y, shade[0], shade[1], shade[2]);
	setPixel (centerX + -x, centerY + y, shade[0], shade[1], shade[2]);
	setPixel (centerX + -x, centerY + -y, shade[0], shade[1], shade[2]);
	setPixel (centerX + y, centerY + x, shade[0], shade[1], shade[2]);
	setPixel (centerX + y, centerY + -x, shade[0], shade[1], shade[2]);
	setPixel (centerX + -y, centerY + x, shade[0], shade[1], shade[2]);
	setPixel (centerX + -y, centerY + -x, shade[0], shade[1], shade[2]);
	y2_new -= (2 * x) - 3;
      }
  }
};

Point p1M1;
Point p2M1;
Point p1M2;
Point p2M2;
double min1;
double min2;
double time1;
double time2;

// This method generates random pixels from an array
list < Point > generatePoints (int size, list < Point > genPoints)
{
  random_device rd;
  uniform_real_distribution < double >uRD (0.0, 1.0);
  for (int i = 0; i < size; i++)
    {
      double x = uRD (rd);
      double y = uRD (rd);
      genPoints.push_back (Point (x, y));
    }
  return genPoints;
}

void
part1 (int numPoints)
{
  PPMGenerator *c = new PPMGenerator ();
  list < Point > genPoints;
  genPoints = generatePoints (numPoints, genPoints);
  double min = 1.5;		// a little more than 1sqrt2
  int temp = 0, temp1 = 0, point1 = 0, point2 = 0;

  auto start = std::chrono::high_resolution_clock::now ();
  for (list < Point >::iterator itP = genPoints.begin ();
       itP != genPoints.end (); ++itP)
    {
      list < Point >::iterator itP2 = itP;
      temp1 = temp + 1;
      for (itP2 = ++itP2; itP2 != genPoints.end (); ++itP2)
	{
	  double distance = itP->calcDistance (*itP2);
	  if (min > distance)
	    {
	      min = distance;
	      point1 = temp;
	      point2 = temp1;
	    }
	  temp1++;
	}
      temp++;
    }
  auto end = std::chrono::high_resolution_clock::now ();
  std::chrono::duration < float >duration = end - start;

  time1 = duration.count ();
  min1 = min;


  ofstream outfile ("points.txt");
for (Point p:genPoints)
    {
      outfile <<fixed<< setprecision (23) << p.getX () << "  " << p.getY () << endl;
    }
  outfile.close ();

  temp = 0;
    int redShade[3] = {255, 0, 0};
    int blackShade[3] = {0, 0, 0};
  for (list < Point >::iterator itP = genPoints.begin ();
       itP != genPoints.end (); ++itP)
    {
      if (temp == point1 || temp == point2)
	{
	  if (temp == point1)
	    {
	      p1M1 = *itP;
	    }
	  else
	    {
	      p2M1 = *itP;
	    }
	  c->drawCircle((int)(itP->getX() * 800), (int)(itP->getY() * 800), 2, redShade);
	  c->drawCircle((int)(itP->getX() * 800), (int)(itP->getY() * 800), 3, redShade);
	}
        else
        {
            c->drawCircle((int)(itP->getX() * 800), (int)(itP->getY() * 800), 2, blackShade);
            c->drawCircle((int)(itP->getX() * 800), (int)(itP->getY() * 800), 3, blackShade);
        }
      temp++;
    }
    c->createPPMFile("points.ppm");

  delete c, genPoints;
}

void
readFile (string file, string delimiter, vector < Point > &genPoints)
{
  ifstream input (file);
  string s1 = "";
  int loc = 0;
  for (string line; getline (input, line);)
    {
      s1 = line;
    for (char i:s1)
	{
	  loc = s1.find (delimiter, 0);
	}
      genPoints.
	push_back (Point
		   (stod (s1.substr (0, loc - 1)),
		    stod (s1.substr (loc + delimiter.size (), s1.size ()))));
      s1.erase ();
    }
}

bool
compare (Point p1, Point p2)
{
  return (p1.getX () < p2.getX ());
}

double
minDistance (vector < Point > &points, Point & p1, Point & p2, int low,
	     int high)
{
  double min = 100;
  for (int i = low; i < high; i++)
    {
      for (int j = i + 1; j <= high; j++)
	{
	  double distance = points[i].calcDistance (points[j]);
	  if (distance < min)
	    {
	      p1 = points[i];
	      p2 = points[j];
	      min = distance;
	    }
	}
    }
  return min;
}

double
minDistanceStrip (vector < Point > &points, Point & p1, Point & p2, int low,
		  int middle, int high)
{
  double min = 100;
  for (int i = low; i < middle; i++)
    {
      for (int j = middle; j <= high; j++)
	{
	  double distance = points[i].calcDistance (points[j]);
	  if (distance < min)
	    {
	      p1 = points[i];
	      p2 = points[j];
	      min = distance;
	    }
	}
    }
  return min;
}

double
minFromStrip (vector < Point > &points, Point & p1, Point & p2, double middle,
	      double minDistanceP, int lowA, int highA)
{
  int low = -1, high = -1, middleL = floor (middle), middleH =
    ceil (middle), i = 0;
  double strip = (points[middleH].getX () + points[middleL].getX ()) / 2;
  double lowX = strip - minDistanceP;
  double highX = strip + minDistanceP;
  while (low == -1 && middleL - i >= lowA)
    {
        
      if (lowX > points[middleL - i].getX ())
	{
	  low = middleL - i;
	}
      i++;
    }
  if (low == -1)
    {
      low = lowA;
    }
  i = 0;
  while (high == -1 && middleH + i <= highA)
    {
      if (highX < points[middleH + i].getX ())
	{
	  high = middleH + i;
	}
      i++;
    }
  if (high == -1)
    {
      high = highA;
    }

    if(middleL == middleH) {
        return minDistance (points, p1, p2, low, high);
    } else {
        return minDistanceStrip(points, p1, p2, low,middleH, high);
     }
}

double
recursiveMinDistanceFind (vector < Point > &points, Point & p1, Point & p2,
			  int low, int high)
{
  int difference = (high-low)+1;
  if (difference > 3)
    {
      double middle = ((double) (low + high)) / 2;
      Point *p3 = new Point (0, 0);
      Point *p4 = new Point (0, 0);
      Point *p5 = new Point (0, 0);
      Point *p6 = new Point (0, 0);
      double distance1 =
	recursiveMinDistanceFind (points, p1, p2, low, middle);
      double distance2 =
	recursiveMinDistanceFind (points, *p5, *p6, middle + 1, high);
      if (distance1 < distance2)
	{
	  double distance3 =
	    minFromStrip (points, *p3, *p4, (low+high)/2, distance1, low, high);
	  if (distance3 < distance1)
	    {
	      p1 = *p3;
	      p2 = *p4;
	      return distance3;
	    }
	  else
	    {
	      return distance1;
	    }

	}
      else
	{
	  double distance3 =
	    minFromStrip (points, *p3, *p4, (low+high)/2, distance2, low, high);
	  if (distance3 < distance2)
	    {
	      p1 = *p3;
	      p2 = *p4;
	      return distance3;
	    }
	  else
	    {
	      p1 = *p5;
	      p2 = *p6;
	      return distance2;
	    }
	}
    }
  else if (difference > 2)
    {
      return minDistance (points, p1, p2, low, high);
    }
  else
    {
      p1 = points[low];
      p2 = points[high];
      return points[low].calcDistance (points[high]);
    }
}

void
part2 ()
{
  PPMGenerator *c = new PPMGenerator ();
  vector < Point > *genPoints = new vector < Point >;
  readFile ("points.txt", "  ", *genPoints);

  auto start = std::chrono::high_resolution_clock::now ();
  sort (genPoints->begin (), genPoints->end (), compare);
  Point *p1 = new Point (0, 0);
  Point *p2 = new Point (5, 5);
  double distance =
    recursiveMinDistanceFind (*genPoints, *p1, *p2, 0,
			      genPoints->size () - 1);
  auto end = std::chrono::high_resolution_clock::now ();
  std::chrono::duration < float >duration = end - start;
  time2 = duration.count ();
  p1M2 = *p1;
  p2M2 = *p2;
  min2 = distance;

  delete c, p1, p2, genPoints;
}

void writePoints (int size)
{
  random_device rd;
  ofstream outfile ("points.txt");
  uniform_real_distribution < double >uRD (0.0, 1.0);
  for (int i = 0; i < size; i++)
    {
      double x = uRD (rd);
      double y = uRD (rd);
      outfile <<fixed<< setprecision (23) << x << "  " << y << endl;     
    }
  outfile.close ();
}

void
logData (int minNodes, int maxNodes, int avgCase, int multiplier)
{
  ofstream outfile ("log.csv");
  outfile << "Number of Nodes,Part 1,Part 2\n";
  double avgTime1 = 0, avgTime2 = 0;
  for (int i = minNodes; i < maxNodes; i = i * multiplier)
    {
      for (int j = 0; j < avgCase; j++)
	{
      if (i < 10000) {
	  part1 (i);
	  avgTime1 += time1;
      } else {
          writePoints(i);
      }
	  part2 ();
	  avgTime2 += time2;
      
	}
      outfile << fixed << setprecision(10) << i << "," << avgTime1 / 3 << "," << avgTime2 / 3 << "\n";
      avgTime1 = 0;
      avgTime2 = 0;
    }
  outfile.close ();
}

int
main ()
{
    ofstream outfile ("results.txt");
    part1(1000);
    part2();
    outfile << "For method 1\nPoints are: " << p1M1.toString() << " " << p2M1.toString() << " \nMinimum distance is: " << min1 << " \nTime is: " << time1 << endl;
    outfile << "For method 2\nPoints are: " << p1M2.toString() << " " << p2M2.toString() << " \nMinimum distance is: " << min2 << " \nTime is: " << time2 << endl;
    outfile.close ();

  return 0;
}
