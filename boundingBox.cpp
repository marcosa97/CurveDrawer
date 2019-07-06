
#include "boundingBox.h"

#include "curves.h"

//Calculates bounding box based on current objects in the scene
void BoundingBox::updateBoundingBox(std::vector<BezierCurve> p, std::vector<BSplineCurve> bsc) {
	if (p.size() > 0 || bsc.size() > 0) {

		float _xMin = 0;
	    float _xMax = 0;
	    float _yMin = 0;
	    float _yMax = 0;

	    //Find minimums and maximums
	    if (p.size() != 0) {
	        _xMin = p[0].controlPoints[0].x;
	        _xMax = p[0].controlPoints[0].x;
	        _yMin = p[0].controlPoints[0].y;
	        _yMax = p[0].controlPoints[0].y;
	    } else {
	    	_xMin = bsc[0].controlPoints[0].x;
	        _xMax = bsc[0].controlPoints[0].x;
	        _yMin = bsc[0].controlPoints[0].y;
	        _yMax = bsc[0].controlPoints[0].y;
	    }

	    //Check Bezier curves
	    for (int i = 0; i < p.size(); i++) {
	    	for (int j = 0; j < p[i].controlPoints.size(); j++) {
	    		//Find mins
	    		if (p[i].controlPoints[j].x < _xMin) {
	    			_xMin = p[i].controlPoints[j].x;
	    		}
	    		if (p[i].controlPoints[j].y < _yMin) {
	    			_yMin = p[i].controlPoints[j].y;
	    		}
                
                //Find maxs
                if (p[i].controlPoints[j].x > _xMax) {
                	_xMax = p[i].controlPoints[j].x;
                }
                if (p[i].controlPoints[j].y > _yMax) {
                	_yMax = p[i].controlPoints[j].y;
                }
	    	} 
	    }

	    //Check B-Spline Curves
	    for (int i = 0; i < bsc.size(); i++) {
            for (int j = 0; j < bsc[i].controlPoints.size(); j++) {
            	//Find mins if any
            	if (bsc[i].controlPoints[j].x < _xMin) {
            		_xMin = bsc[i].controlPoints[j].x;
            	}
            	if (bsc[i].controlPoints[j].y < _yMin) {
            		_yMin = bsc[i].controlPoints[j].y;
            	}

            	//Find maxs if any
            	if (bsc[i].controlPoints[j].x > _xMax) {
            		_xMax = bsc[i].controlPoints[j].x;
            	}
            	if (bsc[i].controlPoints[j].y > _yMax) {
            		_yMax = bsc[i].controlPoints[j].y;
            	}
            }
	    }

        //Update variables
        xMin = _xMin;
        xMax = _xMax;
        yMin = _yMin;
        yMax = _yMax;
    }
}

void BoundingBox::displayBBData() {
	std::cout << "CURRENT BOUNDING BOX:\n";
	std::cout << "xMin = " << xMin << std::endl;
	std::cout << "xMax = " << xMax << std::endl;
	std::cout << "yMin = " << yMin << std::endl;
	std::cout << "yMax = " << yMax << std::endl;
}