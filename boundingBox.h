#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <iostream>
#include <vector>

//Forward declare
class BezierCurve;
class BSplineCurve;

//Keeps track of data needed to calcualte bounding box
class BoundingBox {
public:
	int boxResolution; //in pixels
	int boxMargin; //margin in pixels
    float xMin, xMax;
    float yMin, yMax;

    BoundingBox() {
    	boxResolution = 800; //HARDCODED
    	boxMargin = 20;
    	xMin = 0;
    	xMax = 0;
    	yMin = 0;
    	yMax = 0;
    }

    void updateBoundingBox(std::vector<BezierCurve> p, std::vector<BSplineCurve> bsc);
    void displayBBData(); //FOR DEBUGGING
};

#endif //BOUNDING_BOX_H