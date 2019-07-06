#ifndef CURVES_H
#define CURVES_H

#include <vector>
#include <iostream>
#include "lineAlgorithms.h"
#include "boundingBox.h"

class PixelPoint2D {
public:
    int x, y;
    PixelPoint2D() {
        x = 0;
        y = 0;
    }
    PixelPoint2D(int ix, int iy) {
        x = ix;
        y = iy;
    }
    PixelPoint2D(const PixelPoint2D &p) {
        x = p.x;
        y = p.y;
    }

    void displayData();
};

class WorldPoint2D {
public:
	float x, y;
	WorldPoint2D() {
		x = 0;
		y = 0;
	}
	WorldPoint2D(float ix, float iy) {
		x = ix;
		y = iy;
	}
	WorldPoint2D(const WorldPoint2D &p) {
		x = p.x;
		y = p.y;
	}

    WorldPoint2D operator+(const WorldPoint2D& p);
	WorldPoint2D operator*(const float a);
	PixelPoint2D convertWCtoPP(BoundingBox BBData);
};

class BezierCurve {
private:
	int resolution;
    
    WorldPoint2D deCasteljauPoint(float t);
	std::vector<PixelPoint2D> calculateCurvePoints(BoundingBox BBData);
public:
	std::vector<WorldPoint2D> controlPoints;

    BezierCurve() {}
    BezierCurve(const BezierCurve &b) {
    	resolution = b.resolution;
    	controlPoints = b.controlPoints;
    }
    ~BezierCurve() {}

    void displayData();
    void drawCurve(PixelBuffer *pb, BoundingBox BBData);
    void setResolution(int r);
    int getResolution();
};

class BSplineCurve {
private:
    int resolution;
    int k;

    WorldPoint2D deBoorAlgorithmPoint(float u);
    std::vector<PixelPoint2D> calculateCurvePoints(BoundingBox BBData);
public:
	std::vector<WorldPoint2D> controlPoints;
	std::vector<float> knotValues;

	BSplineCurve() {}
	BSplineCurve(const BSplineCurve &b) {
		k = b.k;
		resolution = b.resolution;
		knotValues = b.knotValues;
		controlPoints = b.controlPoints;
	}
	~BSplineCurve() {}

    void displayData();
    void drawCurve(PixelBuffer *pb, BoundingBox BBData);
    void setResolution(int r);
    void setK(int _k);

    int getResolution();
    int getK();
};

/* Function for updating screen */
void redrawScene(PixelBuffer *pb, BoundingBox BBData, std::vector<BezierCurve> bc, std::vector<BSplineCurve> bsc);

#endif //CURVES_H
