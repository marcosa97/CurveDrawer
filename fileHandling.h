#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstdio>
#include <vector>

#include "curves.h"

//#include curve object file
void readFile(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

void writeOutput(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

#endif //FILE_HANDLING_H
