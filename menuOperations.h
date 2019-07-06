#include <limits>
#include <vector>
#include "curves.h"

void displayCurvesInfo(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

void removeCurve(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

void changeResolution(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

void changeKOrder(std::vector<BSplineCurve> &BSCurves);

void removeControlPoint(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

void modifyControlPoint(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);

void insertControlPoint(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves);