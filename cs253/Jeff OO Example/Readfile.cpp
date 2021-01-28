#include <Readfile.h>
#include <Point3D.h>
#include <PoseDisplay.h>
#include <iostream>
#include <float.h>
#include <string>
#include <sstream>
#include <math.h>
using std::stringstream;
using std::istringstream;
using std::cout;
using std::cerr;
using std::endl;

/* \file readfile.cpp: implements the readfile class */

int Readfile::Read(ifstream& input_stream)
{
  if (input_stream.fail())
  {
    cerr << "Error: Input file does not exist for reading." << endl;
    return -1;
  }
  if (input_stream.peek() == EOF)
  {
    cerr << "Error: File is empty." << endl;
    return -1;
  }

  return 0;
}

int Readfile::Write(fstream& output_stream)
{
  if (output_stream.fail())
  {
    cerr << "Error: Output file does not exist for writing." << endl;
    return -1;
  } else if (output_stream.is_open()) {
    //DO NOTHING
  } else {
    cerr << "Error: Couldn't open file." << endl;
    return -1;
  }

  return 0;
}

int Readfile::Scanning_File(ifstream& input_stream, std::vector<double>& body_points, int &line_counter)
{
  if (input_stream.is_open())
  {
    string line;
    line_counter = 0;
    int line_number = 1;
    int input_counter = 1;
    double input_value = 0.0;

    while (getline (input_stream, line))
    {
      stringstream(line) >> input_value;
      int eof_value = input_stream.peek();
      bool is_eof = (eof_value == EOF);
      if (line.empty())
      {
        if (is_eof)
        {
          line_counter--;
        } else {
          cerr << "Error: Empty line found." << endl;
          return -1;
        }
      }
      istringstream line_in(line);
      while (line_in >> input_value)
      {
        if (input_counter > 75)
        {
          cerr << "Error: Exceeded over 75 inputs" << endl;
          return -1;
        }
        body_points.push_back(input_value);
        input_counter++;
      }
      input_counter--;  //decrement to be 75 unless invalid
      line_number++;    //increment line counter of file
      if (input_value == 0)
      {
        cerr << "Error: Invalid input found." << endl;
        return -1;
      }
      if (is_eof)
      {
        if (input_counter == 0)
        { //do nothing
        } else if (input_counter < 75) {
          cerr << "Error: Not enough inputs for 25 points for Point3D" << endl;
          return -1;
        }
      } else if (input_counter < 75) {
        cerr << "Error: Not enough inputs for 25 points for Point3D" << endl;
        return -1;
      }
      input_counter = 1;
      line_counter++;
    }
  } else {
    return -1;
  }
  return 0;
}

int Readfile::Frame_Check(const int& line_counter)
{
  if (line_counter < 1)
  {
    cerr << "Error: Must have 2 or more frames of poses." << endl;
    return -1;
  }
  return 0;
}

void Readfile::Translating_File(std::vector<double>& body_points, const int &line_counter)
{
  int point_counter = 0;
  double x_sum = 0.0;
  double y_sum = 0.0;
  double z_sum = 0.0;

  //Finding the sum of the 1st out of 25 points of x,y,z
  while (point_counter < (int)body_points.size())
  {
    x_sum += body_points[point_counter + 0];
    y_sum += body_points[point_counter + 1];
    z_sum += body_points[point_counter + 2];
    point_counter += 75;
  }
  point_counter = 0; //reset point_counter

  //Computing averages for xyz
  double x_average = x_sum / line_counter;
  double y_average = y_sum / line_counter;
  double z_average = z_sum / line_counter;

  //Subtracting the averages from every point
  while (point_counter < (int)body_points.size())
  {
    body_points[point_counter + 0] -= x_average;
    body_points[point_counter + 1] -= y_average;
    body_points[point_counter + 2] -= z_average;
    point_counter += 3;
  }
  point_counter = 0;
}

int Readfile::Max_Value_and_Scaling(std::vector<double>& body_points, const int& line_counter)
{
  int point_counter = 0;
  double max_value = DBL_MIN;
  //Finding the max abs value after translation
  while (point_counter < (int)body_points.size())
  {
    double value = body_points[point_counter];
    if (value < 0.0)
    {
      double copy = value;
      copy *= -1;
      if (copy > max_value)
      {
        max_value = copy;
      }
    }
    if (value > max_value)
    {
      max_value = value;
    }
    point_counter++;
  }
  point_counter = 0;

  //Scaling every points
  if (max_value < 0.00001)
  {
    cerr << "Error: Can not scale with 0." << endl;
    return -1;
  } else if (max_value == 1.0) { //DO NOTHING
  } else {
    double scale = (1.0 / max_value);
    while (point_counter < (int)body_points.size())
    {
      body_points[point_counter] *= scale;
      if ((-1 > body_points[point_counter]) || (body_points[point_counter] > 1))
      {
        cerr << "Error: Scaling is out of bounds. Must be within -1 and 1." << endl;
        return -1;
      }
      point_counter++;
    }
  }
  return 0;
}

void Readfile::Display_File(const std::vector<double>& body_points, PoseDisplay& display_points)
{
  vector<Point3D> point;
  int point_counter = 0;
  while (point_counter < (int)body_points.size())
  {
    double x_value = body_points[point_counter + 0];
    double y_value = body_points[point_counter + 1];
    double z_value = body_points[point_counter + 2];
    point.push_back(Point3D(x_value, y_value, z_value));
    point_counter += 3;
    if ((point_counter % 75) == 0)
    {
      display_points.Pose(point);
      cout << "Point is : " << point.at(0) << endl;
      point.clear();
    }
  }
  point_counter = 0;
}

void Readfile::Calculating_Distance(const std::vector<double>& body_points, fstream& output_stream)
{
  int point_counter = 0;
  double sum_poses = 0.0;
  double distance_value = 0.0;
  while (point_counter < ((int)body_points.size() - 75))
  {
    double x_posA = body_points[point_counter + 0];
    double y_posA = body_points[point_counter + 1];
    double z_posA = body_points[point_counter + 2];
    double x_posB = body_points[point_counter + 75];
    double y_posB = body_points[point_counter + 76];
    double z_posB = body_points[point_counter + 77];

    point_counter += 3;

    double x_value = (x_posA - x_posB);
    x_value = x_value * x_value;
    double y_value = (y_posA - y_posB);
    y_value = y_value * y_value;
    double z_value = (z_posA - z_posB);
    z_value = z_value * z_value;

    sum_poses = (x_value + y_value + z_value);
    distance_value += sqrt(sum_poses);

    if (point_counter % 75 == 0)
    {
      output_stream << distance_value << endl;
      sum_poses = 0.0;
      distance_value = 0.0;
    }
  }
}
