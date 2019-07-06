#include "fileHandling.h"

void readFile(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves) {
    std::string fileName;
    std::string temp;
    int numBezierCurves, numBSplineCurves;

    //Get file name
    std::cout << "|******** File Read-In Mode ********|\n\n";
    std::cout << "Please enter the name of the file you wish to read in from: ";
    std::cin >> fileName;

    std::ifstream inputFile(fileName);
    if ( inputFile.fail() ) {
        std::cout << "ERROR: The file " << fileName << " does not exist.\n\n";
        return;
    }  

    //Read in # of Bezier and B-Spline Curves
    getline(inputFile, temp);
    std::stringstream(temp) >> numBezierCurves;
    getline(inputFile, temp);
    std::stringstream(temp) >> numBSplineCurves;

    //Read in Bezier curves first
    for (int i = 0; i < numBezierCurves; i++) {
    	BCurves.push_back( BezierCurve() );

    	//Ignore first blank line
    	getline(inputFile, temp);

    	//Resolution of curve
    	int resolution;
    	getline(inputFile, temp);
    	std::stringstream(temp) >> resolution;
    	BCurves[i].setResolution(resolution);

    	//Number of points
    	int numControlPoints;
    	getline(inputFile, temp);
    	std::stringstream(temp) >> numControlPoints;
        
        //Read in coordinate points
        for (int j = 0; j < numControlPoints; j++) {
        	float num;
        	getline(inputFile, temp);
        	BCurves[i].controlPoints.push_back( WorldPoint2D() );

        	//Split string "temp" into tokens
        	std::istringstream iss(temp);
        	std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{} };

            //x-coordinate
            std::stringstream(tokens[0]) >> num;
            BCurves[i].controlPoints[j].x = num;

            //y-coordinate
            std::stringstream(tokens[1]) >> num;
            BCurves[i].controlPoints[j].y = num;                         
        }
    }

    //Read in B-Spline curves
    for (int i = 0; i < numBSplineCurves; i++) {
        BSCurves.push_back( BSplineCurve() );

        //Ignore first blank line
        getline(inputFile, temp);

        //Resolution of curve
    	int resolution;
    	getline(inputFile, temp);
    	std::stringstream(temp) >> resolution;
    	BSCurves[i].setResolution(resolution);

        //Number of points
        int numControlPoints;
        getline(inputFile, temp);
        std::stringstream(temp) >> numControlPoints;

        //Read in coordinate points
        for (int j = 0; j < numControlPoints; j++) {
        	float num;
        	getline(inputFile, temp);
        	BSCurves[i].controlPoints.push_back( WorldPoint2D() );

        	//Split string "temp" into tokens
        	std::istringstream iss(temp);
        	std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{} };

            //x-coordinate
            std::stringstream(tokens[0]) >> num;
            BSCurves[i].controlPoints[j].x = num;

            //y-coordinate
            std::stringstream(tokens[1]) >> num;
            BSCurves[i].controlPoints[j].y = num;                                 
        }

        //Read in k value
        int k;
        getline(inputFile, temp);
        std::stringstream(temp) >> k;
        BSCurves[i].setK(k);

        //Knot values/distribution
        //There are n + k knots, n = numControlPoints - 1
        for (int j = 0; j <= (numControlPoints - 1 + k); j++) {
            float knotValue;
            getline(inputFile, temp);
            std::stringstream(temp) >> knotValue;

            BSCurves[i].knotValues.push_back(knotValue);
        }

    }

    inputFile.close();

    return;
}

void writeOutput(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves) {
	std::ofstream outputFile("output.txt");

    //Number of Bezier and B-Spline curves
	outputFile << BCurves.size() << std::endl;
    outputFile << BSCurves.size() << std::endl;

    //Write Bezier Curves
	for (int i = 0; i < BCurves.size(); i++) {
		outputFile << "\n";

		//Resolution
		outputFile << BCurves[i].getResolution() << std::endl;
		//Number of control points
		outputFile << BCurves[i].controlPoints.size() << std::endl;

		//Control points
		for (int j = 0; j < BCurves[i].controlPoints.size(); j++) {
			outputFile << BCurves[i].controlPoints[j].x << " " << BCurves[i].controlPoints[j].y << "\n"; 
		}		
	}

    //Write B-Spline Curves
    for (int i = 0; i < BSCurves.size(); i++) {
    	outputFile << "\n";

    	//Resolution
    	outputFile << BSCurves[i].getResolution() << std::endl;
    	//Number of control points
    	outputFile << BSCurves[i].controlPoints.size() << std::endl;

    	//Control points
    	for (int j = 0; j < BSCurves[i].controlPoints.size(); j++) {
    		outputFile << BSCurves[i].controlPoints[j].x << " " << BSCurves[i].controlPoints[j].y << "\n";
    	}

    	//K order
    	outputFile << BSCurves[i].getK() << std::endl;
    	//Knot values
    	for (int j = 0; j < BSCurves[i].knotValues.size(); j++) {
    		outputFile << BSCurves[i].knotValues[j] << std::endl;
    	}
    }

	outputFile.close();
}