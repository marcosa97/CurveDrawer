#include "curves.h"

void PixelPoint2D::displayData() {
	std::cout << "Pixel Point: (" << x << "," << y << ")" << std::endl;
}

PixelPoint2D WorldPoint2D::convertWCtoPP(BoundingBox BBData) {

	PixelPoint2D pp;
	//int resolution = 360; //HARDCODED, 400 - 40, cuz 20 for margin on each side
	//int margin = 20;
	int resolution = BBData.boxResolution - 2 * BBData.boxMargin;
	int margin = BBData.boxMargin;
    float deltaX = BBData.xMax - BBData.xMin;
    float deltaY = BBData.yMax - BBData.yMin;
    
    float maxDelta = deltaX;
    if (deltaY > maxDelta) 
    	maxDelta = deltaY;

	//Transform to Normalized Device Coordinates (NDC)
	float xNDC = (x - BBData.xMin) / maxDelta;
	float yNDC = (y - BBData.yMin) / maxDelta;
    
    /*
    std::cout << "xNDC = " << xNDC << std::endl;
    std::cout << "yNDC = " << yNDC << std::endl;
    std::cout << "zNDC = " << zNDC << std::endl;
    */

    //Now tranform to pixel coordintates
    pp.x = roundf( (resolution - 1) * xNDC) + margin;
    pp.y = roundf( (resolution - 1) * yNDC) + margin;

    return pp;
}

WorldPoint2D WorldPoint2D::operator+(const WorldPoint2D& p) {
	WorldPoint2D result;
	result.x = this->x + p.x;
	result.y = this->y + p.y;

	return result;
}

WorldPoint2D WorldPoint2D::operator*(const float a) {
	WorldPoint2D result;
	result.x = this->x * a;
	result.y = this->y * a;

	return result;
}

WorldPoint2D BezierCurve::deCasteljauPoint(float t) {
    /* Calculate Bezier curve point using deCasteljau algorithm */

    //Matrix used to calculate a bezier point, size n x n
    int n = controlPoints.size() - 1;
    WorldPoint2D matrix[n + 1][n + 1];

    //Generation "0" points are the original points
    for (int i = 0; i <= n; i++) {
    	matrix[0][i] = controlPoints[i];
    }

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i <= n - j; i++) {
        	matrix[j][i] = ( matrix[j-1][i] * (1 - t) ) + ( matrix[j-1][i+1] * t );
        }
    }

    //result stored in matrix[n][0]
    return matrix[n][0];
}

std::vector<PixelPoint2D> BezierCurve::calculateCurvePoints(BoundingBox BBData) {

    std::vector<PixelPoint2D> bcPixelPoints;
    WorldPoint2D bcWorldPoints[ resolution + 1 ];
    float t = 0;

    //Calculate Bezier curve points as World Points
    for (int i = 0; i <= resolution; i++) {
        t = (float) i / (float) resolution;
    	bcWorldPoints[i] = deCasteljauPoint(t);

    	//Convert curve points from World Points to Pixel Points
    	bcPixelPoints.push_back( PixelPoint2D() );
    	bcPixelPoints[i] = bcWorldPoints[i].convertWCtoPP(BBData);
    }

    return bcPixelPoints;
}

void BezierCurve::displayData() {
	std::cout << "    Current resolution: " << resolution << " line segments.\n";
	std::cout << "    Control Points: \n";
	for (int i = 0; i < controlPoints.size(); i++) {
	    std::cout << "    x:" << controlPoints[i].x << " , y:" << controlPoints[i].y << "\n";
    }
}

void BezierCurve::drawCurve(PixelBuffer *pb, BoundingBox BBData) {

    //Convert control points to pixel coordinates
    PixelPoint2D pp[ controlPoints.size() ];

    for (int i = 0; i < controlPoints.size(); i++) {
        pp[i] = controlPoints[i].convertWCtoPP(BBData);
    }

    //Calculate Bezier curve points
    std::vector<PixelPoint2D> bcPoints;
    bcPoints = calculateCurvePoints(BBData);

    /* DRAW CONTROL LINES */
    for (int i = 0; i < controlPoints.size() - 1; i++) {
    	lineDDAColor( pp[i].x, pp[i].y, pp[i + 1].x, pp[i + 1].y, pb, 0.0, 0.65, 0.65);
    }

    /* DRAW CALCULATED BEZIER CURVE */
    for (int i = 0; i < bcPoints.size() - 1; i++) {
    	lineDDAColor( bcPoints[i].x, bcPoints[i].y, bcPoints[i+1].x, bcPoints[i+1].y,
    		          pb, 1.0, 1.0, 1.0);
    }
}

void BezierCurve::setResolution(int r) {
	resolution = r;
}

void BSplineCurve::setResolution(int r) {
	resolution = r;
}

/* BSPLINE CURVE */

WorldPoint2D BSplineCurve::deBoorAlgorithmPoint(float u) {
    //Matrix used to calculate a b-spline point
    
    int n = controlPoints.size() - 1;
    WorldPoint2D matrix[n + 1][n + 1];
    
    //Generation "0" points are the original points
    for (int i = 0; i <= n; i++) {
    	matrix[0][i] = controlPoints[i];
    }
    
    //WorldPoint2D matrix[k+1][k+1];

    //Find index I such that u_I <= u < u_(I+1)
    int I = 0;
    for (int i = 0; i < knotValues.size(); i++) {
    	//std::cout << "knotValues[" << i << "] : " << knotValues[i] << std::endl;
    	if (u < knotValues[i]) {
            I = i - 1;
            break;
    	}
    }

    //std::cout << "I = " << I << "\n";

    for (int j = 1; j <= k - 1; j++) {
    	for (int i = I - (k - 1); i <= I - j; i++) {
    		//std::cout << "MATRIX[" << j << "][" << i << "]\n";
            matrix[j][i] = ( matrix[j-1][i] * ( (knotValues[i+k] - u) / (knotValues[i+k] - knotValues[i+j]) ) ) +
                           ( matrix[j-1][i+1] * ( (u - knotValues[i+j]) / (knotValues[i+k] - knotValues[i+j]) ) );
    	}
    }

    return matrix[k-1][I - (k -1)];
}

std::vector<PixelPoint2D> BSplineCurve::calculateCurvePoints(BoundingBox BBData) {
    std::vector<PixelPoint2D> bscPixelPoints;
    WorldPoint2D bscWorldPoints [resolution + 1];
    float u = 0;

    //Get domain
    //u_k-1
    float u_min = knotValues[ k - 1 ];
    //u_n+1, n = controlPoints.size() - 1
    float u_max = knotValues[ controlPoints.size() - 1 + 1];

    float delta = u_max - u_min;

    for (int i = 0; i < resolution; i++) {
    	float ratio = (float) i / (float) resolution;
    	u = (ratio * delta) + u_min;

    	bscWorldPoints[i] = deBoorAlgorithmPoint(u);

        //std::cout << "u: " << u << "\n";
    	//std::cout << "x: " << bscWorldPoints[i].x << ", y: " << bscWorldPoints[i].y << "\n";

    	//Convert curve points from World points to Pixel Points
    	bscPixelPoints.push_back( PixelPoint2D() );
    	bscPixelPoints[i] = bscWorldPoints[i].convertWCtoPP(BBData);
    }

    return bscPixelPoints;
}

void BSplineCurve::displayData() {
	std::cout << "    Current resolution: " << resolution << " line segments.\n";
	std::cout << "    Control Points: \n";
	for (int i = 0; i < controlPoints.size(); i++) {
	    std::cout << "    x:" << controlPoints[i].x << " , y:" << controlPoints[i].y << "\n";
    }
    std::cout << "    k value: " << k << std::endl;
    std::cout << "    Knot Values: \n";
    for (int i = 0; i < knotValues.size(); i++) {
    	std::cout << "    u_" << i << ": " << knotValues[i] << "\n";
    }
}

void BSplineCurve::drawCurve(PixelBuffer *pb, BoundingBox BBData) {
    
    //Convert control points to pixel coordinates
    PixelPoint2D pp[ controlPoints.size() ];
    for (int i = 0; i < controlPoints.size(); i++) {
    	pp[i] = controlPoints[i].convertWCtoPP(BBData);
    }

    //Calculate B-Spline curve points
    std::vector<PixelPoint2D> bscPoints;
    bscPoints = calculateCurvePoints(BBData);

    /* DRAW CONTROL LINES */
    for (int i = 0; i < controlPoints.size() - 1; i++) {
    	lineDDAColor( pp[i].x, pp[i].y, pp[i+1].x, pp[i+1].y, pb, 0.65, 0.0, 0.65);
    }

    /* DRAW CALCULATED B-SPLINE CURVE */
    for (int i = 0; i < bscPoints.size() - 1; i++) {
    	lineDDAColor( bscPoints[i].x, bscPoints[i].y, bscPoints[i+1].x, bscPoints[i+1].y,
    		          pb, 1.0, 1.0, 1.0);
    }

}

void BSplineCurve::setK(int _k) {
    k = _k;
}

int BezierCurve::getResolution() {
	return resolution;
}

int BSplineCurve::getResolution() {
	return resolution;
}

int BSplineCurve::getK() {
	return k;
}

/* Function for updating screen */
void redrawScene(PixelBuffer *pb, BoundingBox BBData, std::vector<BezierCurve> bc, std::vector<BSplineCurve> bsc) {
    //Clear bufer first
    pb->clearBuffer();

    BBData.updateBoundingBox(bc, bsc);

    for (int i = 0; i < bc.size(); i++) {
    	bc[i].drawCurve(pb, BBData);
    }

    for (int i = 0; i < bsc.size(); i++) {
    	bsc[i].drawCurve(pb, BBData);
    }
}