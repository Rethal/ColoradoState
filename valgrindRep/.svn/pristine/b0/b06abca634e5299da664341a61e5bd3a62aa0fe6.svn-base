#ifndef READFILE_H_INCLUDE
#define READFILE_H_INCLUDE

/* file Readfile.h: Declares the readfile class */

#include <Point3D.h>
#include <PoseDisplay.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::istream;
using std::ostream;

class Readfile {
public:
  //Constructor for readfile
  Readfile(int input = 0)
    : file_value(input) {}

  int Read(ifstream& input_stream);
  int Write(fstream& output_stream);
  int Scanning_File(ifstream& input_stream, std::vector<double>& body_points, int &line_counter);
  int Frame_Check(const int& line_counter);
  void Translating_File(std::vector<double>& body_points, const int &line_counter);
  int Max_Value_and_Scaling(std::vector<double>& body_points, const int &line_counter);
  void Display_File(const std::vector<double>& body_points, PoseDisplay& display_points);
  void Calculating_Distance(const std::vector<double>& body_points, fstream& output_stream);

private:
  int file_value;
};

#endif // READFILE_H_INCLUDE
