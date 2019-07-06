#include "menuOperations.h"

using namespace std;

int getValidInt(int min, int max) {
    int num;

    //Get first point
    while (!(cin >> num) || !(num >= min && num <= max ) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    
    return num;
}

float getFloat() {
    float num;

    //Get first point
    while (!(cin >> num) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    
    return num;
}

void displayCurvesInfo(vector<BezierCurve> &BCurves, vector<BSplineCurve> &BSCurves) {
	int i = 0;
    for (i = 0; i < BCurves.size(); i++) {
        cout << "Curve " << i + 1 << " (Bezier): \n";
        BCurves[i].displayData();
    }

    for (int j = 0; j < BSCurves.size(); j++) {
    	cout << "Curve " << i + 1 << " (B-Spline): \n";
    	BSCurves[j].displayData();
    	i++;
    }

    cout << "\n";
    //Print B-Spline Curves data
}

void displayBSplineCurves(vector<BSplineCurve> &BSCurves) {
	for (int j = 0; j < BSCurves.size(); j++) {
    	cout << "B-Spline Curve " << j + 1 << ": \n";
    	BSCurves[j].displayData();
    }

    cout << "\n";
}

int displayCurveControlPoints(vector<BezierCurve> &BCurves ,vector<BSplineCurve> &BSCurves, int index) {
    int numPoints = 0;

	//If B-Spline curve chosen
    if ( index >= BCurves.size() ) {
        if (BCurves.size() == 0) {
            cout << "Curve " << index + 1 << " control points: " << endl;
	    	for (int i = 0; i < BSCurves[index].controlPoints.size(); i++) {
	    		cout << "    " << i + 1 << ") x=" << BSCurves[index].controlPoints[i].x;
	    		cout << ", y=" << BSCurves[index].controlPoints[i].y << endl;
	    	}
	    	numPoints = BSCurves[index].controlPoints.size();
        } else {
	    	cout << "Curve " << index + 1 << " control points: " << endl;
	    	for (int i = 0; i < BSCurves[index % BCurves.size()].controlPoints.size(); i++) {
	    		cout << "    " << i + 1 << ") x=" << BSCurves[index % BCurves.size()].controlPoints[i].x;
	    		cout << ", y=" << BSCurves[index % BCurves.size()].controlPoints[i].y << endl;
	    	}
	    	numPoints = BSCurves[index % BCurves.size()].controlPoints.size();
	        //BSCurves[index % BCurves.size()].displayData();
	    }
    } else {
    	cout << "Curve " << index + 1 << " control points: " << endl;
    	for (int i = 0; i < BCurves[index].controlPoints.size(); i++) {
    		cout << "    " << i + 1 << ") x=" << BCurves[index].controlPoints[i].x;
    		cout << ", y=" << BCurves[index].controlPoints[i].y << endl;
    	}
    	numPoints = BCurves[index].controlPoints.size();
    	//BCurves[index].displayData();
    }

    cout << endl;

    return numPoints;
}

void removeCurve(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves) {
	if ( ( BCurves.size() + BSCurves.size() ) <= 0) {
        cout << "There are no curves on the screen.\n\n";
        return;
    }

	cout << "|******** Remove Curve Mode ********|\n\n";
	displayCurvesInfo(BCurves, BSCurves);

	cout << "Select a curve to remove: ";

    int numCurves = BCurves.size() + BSCurves.size();
    int curveChoice = getValidInt(1, numCurves);
	int curveIndex = curveChoice - 1;

    //Remove point
    if (curveIndex >= BCurves.size()) {
    	if (BCurves.size() == 0)
    		BSCurves.erase( BSCurves.begin() + curveIndex);
    	else 
            BSCurves.erase( BSCurves.begin() + ( curveIndex % BCurves.size() ) );
    } else {
        BCurves.erase(BCurves.begin() + curveIndex);
    }
}

void changeResolution(vector<BezierCurve> &BCurves, vector<BSplineCurve> &BSCurves) {
    if ( ( BCurves.size() + BSCurves.size() ) <= 0) {
        cout << "There are no curves on the screen.\n\n";
        return;
    }

	cout << "|******** Resolution Change Mode ********|\n\n";
	cout << "Select an option:\n";
	cout << "    1) Change resolution for a single curve.\n";
	cout << "    2) Change resolution for all curves (all curves will have the resolution you specify).\n";
    cout << ">> ";

    //while input is invalid, get valid input
    int choice = 0;
    while (!(cin >> choice) || !(choice > 0 && choice < 2 + 1) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "\n";

    int curveChoice = 0;
    int curveIndex = 0;

    if (choice == 1) {
        displayCurvesInfo(BCurves, BSCurves);
        cout << "Select a curve to change the resolution for: ";

        int numCurves = BCurves.size() + BSCurves.size();
	    while (!(cin >> curveChoice) || !(curveChoice > 0 && curveChoice < numCurves + 1) ) {
	        cin.clear();
	        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        cout << "Invalid input. Please try again: ";
	    }

	    curveIndex = curveChoice - 1;

    }

    //Get new resolution
    cout << "Enter the new resolution: ";
    int resolution = 0;
    while (!(cin >> resolution) || !(resolution > 0) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "\n";

    switch(choice) {
    case 1:
        if (curveIndex >= BCurves.size() ) {
            if (BCurves.size() == 0)
            	BSCurves[ curveIndex ].setResolution(resolution);
            else
        	    BSCurves[ curveIndex % BCurves.size() ].setResolution(resolution);
        } else
            BCurves[curveIndex].setResolution(resolution);
        break;

    case 2:
        for (int i = 0; i < BCurves.size(); i++) {
        	BCurves[i].setResolution(resolution);
        }

        for (int i = 0; i < BSCurves.size(); i++) {
        	BSCurves[i].setResolution(resolution);
        }
        break;
    }
}

void changeKOrder(std::vector<BSplineCurve> &BSCurves) {
    if ( ( BSCurves.size() ) <= 0) {
        cout << "There are no B-Spline curves on the screen.\n\n";
        return;
    }

	cout << "|******** K Order Change Mode ********|\n\n";
    displayBSplineCurves(BSCurves);

    cout << "Select a curve to change the k order for: ";

    int curveChoice = 0;
    int numCurves = BSCurves.size();
	while (!(cin >> curveChoice) || !(curveChoice > 0 && curveChoice < numCurves + 1) ) {
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    cout << "Invalid input. Please try again: ";
	}

	//Get new k order
    cout << "Enter the new value for k: ";
    int k = 0;
    while (!(cin >> k) || !(k > 0) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }
    cout << "\n";

    //Update value of K
    BSCurves[curveChoice - 1].setK(k);
}

void removeControlPoint(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves) {
	if ( ( BCurves.size() + BSCurves.size() ) <= 0) {
        cout << "There are no curves on the screen.\n\n";
        return;
    }

	cout << "|******** Remove Control Point Mode ********|\n\n";
	displayCurvesInfo(BCurves, BSCurves);

	cout << "Select a curve to modify: ";

	int curveChoice = 0;
    int numCurves = BCurves.size() + BSCurves.size();
	while (!(cin >> curveChoice) || !(curveChoice > 0 && curveChoice < numCurves + 1) ) {
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    cout << "Invalid input. Please try again: ";
	}

	int curveIndex = curveChoice - 1;

    //Display curves info
    cout << endl;
    int numPoints = displayCurveControlPoints(BCurves, BSCurves, curveIndex);
    cout << "Enter the number for the point you wish to remove: ";

    int pointChoice = 0;
	while (!(cin >> pointChoice) || !(pointChoice > 0 && pointChoice < numPoints + 1) ) {
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    cout << "Invalid input. Please try again: ";
	}
    pointChoice--;

    //Remove point
    if (curveIndex >= BCurves.size()) {
    	if (BCurves.size() == 0) 
    		BSCurves[curveIndex].controlPoints.erase(BSCurves[curveIndex].controlPoints.begin() + pointChoice);
    	else
            BSCurves[curveIndex % BCurves.size()].controlPoints.erase(BSCurves[curveIndex % BCurves.size()].controlPoints.begin() + pointChoice);
    } else {
        BCurves[curveIndex].controlPoints.erase(BCurves[curveIndex].controlPoints.begin() + pointChoice);
    }
    
}

void modifyControlPoint(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves) {
	if ( ( BCurves.size() + BSCurves.size() ) <= 0) {
        cout << "There are no curves on the screen.\n\n";
        return;
    }

	cout << "|******** Modify Control Point Mode ********|\n\n";
	displayCurvesInfo(BCurves, BSCurves);

	cout << "Select a curve to modify: ";

	int curveChoice = 0;
    int numCurves = BCurves.size() + BSCurves.size();
	while (!(cin >> curveChoice) || !(curveChoice > 0 && curveChoice < numCurves + 1) ) {
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    cout << "Invalid input. Please try again: ";
	}

	int curveIndex = curveChoice - 1;

    //Display curves info
    cout << endl;
    int numPoints = displayCurveControlPoints(BCurves, BSCurves, curveIndex);
    cout << "Enter the number for the point you wish to modify: ";

    int pointChoice = 0;
	while (!(cin >> pointChoice) || !(pointChoice > 0 && pointChoice < numPoints + 1) ) {
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    cout << "Invalid input. Please try again: ";
	}
    pointChoice--;

    //Get new values for point
    cout << "Enter new x-value for the point: ";
    float x = getFloat();
    cout << "Enter new y-value for the point: ";
    float y = getFloat();
    WorldPoint2D newPoint(x, y);

    //Remove point
    if (curveIndex >= BCurves.size()) {
        //BSCurves[curveIndex % BCurves.size()].controlPoints.erase(BSCurves[curveIndex % BCurves.size()].controlPoints.begin() + pointChoice);
        if (BCurves.size() == 0) 
        	BSCurves[curveIndex].controlPoints[pointChoice] = newPoint;
        else
            BSCurves[curveIndex % BCurves.size()].controlPoints[pointChoice] = newPoint;
    } else {
        //BCurves[curveIndex].controlPoints.erase(BCurves[curveIndex].controlPoints.begin() + pointChoice);
        BCurves[curveIndex].controlPoints[pointChoice] = newPoint;
    }
}

void insertControlPoint(std::vector<BezierCurve> &BCurves, std::vector<BSplineCurve> &BSCurves) {
	if ( ( BCurves.size() + BSCurves.size() ) <= 0) {
        cout << "There are no curves on the screen.\n\n";
        return;
    }

	cout << "|******** Insert Control Point Mode ********|\n\n";
	displayCurvesInfo(BCurves, BSCurves);

	cout << "Select a curve to insert a control point into: ";

    int numCurves = BCurves.size() + BSCurves.size();
    int curveChoice = getValidInt(1, numCurves);
	int curveIndex = curveChoice - 1;

	cout << "Select where you want to insert a control point: \n";

	int numChoices = 0;
	//Display options
	if (curveIndex >= BCurves.size()) {
        if (BCurves.size() != 0) {
        	cout << "    1) Append to the endpoint (" << BSCurves[curveIndex % BCurves.size()].controlPoints[0].x;
        	cout << "," << BSCurves[curveIndex % BCurves.size()].controlPoints[0].y << ")\n";
            for (int i = 1; i < BSCurves[curveIndex % BCurves.size()].controlPoints.size(); i++) {
                cout << "    " << i + 1 << ") Between points (" << BSCurves[curveIndex % BCurves.size()].controlPoints[i-1].x;
                cout << "," << BSCurves[curveIndex % BCurves.size()].controlPoints[i-1].y << ") and (";
                cout << BSCurves[curveIndex % BCurves.size()].controlPoints[i].x << ",";
                cout << BSCurves[curveIndex % BCurves.size()].controlPoints[i].y << ")" << endl;
            }
            numChoices = BSCurves[curveIndex % BCurves.size()].controlPoints.size() + 1;
            cout << "    " << BSCurves[curveIndex % BCurves.size()].controlPoints.size() + 1 << ") Append to the endpoint (";
            cout << BSCurves[curveIndex % BCurves.size()].controlPoints.back().x << ",";
            cout << BSCurves[curveIndex % BCurves.size()].controlPoints.back().y << ")\n";
        } else {
            cout << "    1) Append to the endpoint (" << BSCurves[curveIndex].controlPoints[0].x;
        	cout << "," << BSCurves[curveIndex].controlPoints[0].y << ")\n";
            for (int i = 1; i < BSCurves[curveIndex].controlPoints.size(); i++) {
                cout << "    " << i + 1 << ") Between points (" << BSCurves[curveIndex].controlPoints[i-1].x;
                cout << "," << BSCurves[curveIndex].controlPoints[i-1].y << ") and (";
                cout << BSCurves[curveIndex].controlPoints[i].x << ",";
                cout << BSCurves[curveIndex].controlPoints[i].y << ")" << endl;
            }
            numChoices = BSCurves[curveIndex].controlPoints.size() + 1;
            cout << "    " << BSCurves[curveIndex].controlPoints.size() + 1 << ") Append to the endpoint (";
            cout << BSCurves[curveIndex].controlPoints.back().x << ",";
            cout << BSCurves[curveIndex].controlPoints.back().y << ")\n";
        }
	} else {
        cout << "    1) Append to the endpoint (" << BCurves[curveIndex].controlPoints[0].x;
        cout << "," << BCurves[curveIndex].controlPoints[0].y << ")\n";
        for (int i = 1; i < BCurves[curveIndex].controlPoints.size(); i++) {
            cout << "    " << i + 1 << ") Between points (" << BCurves[curveIndex].controlPoints[i-1].x;
            cout << "," << BCurves[curveIndex].controlPoints[i-1].y << ") and (";
            cout << BCurves[curveIndex].controlPoints[i].x << ",";
            cout << BCurves[curveIndex].controlPoints[i].y << ")" << endl;
        }
        numChoices = BCurves[curveIndex].controlPoints.size() + 1;
        cout << "    " << BCurves[curveIndex].controlPoints.size() + 1 << ") Append to the endpoint (";
        cout << BCurves[curveIndex].controlPoints.back().x << ",";
        cout << BCurves[curveIndex].controlPoints.back().y << ")\n";
	}

	cout << ">> ";
    
    //Get input
    int choice = getValidInt(1, numChoices);
    choice--; //for indexing

    //Get values for the new point
    cout << "Enter new x-value for the point: ";
    float x = getFloat();
    cout << "Enter new y-value for the point: ";
    float y = getFloat();
    WorldPoint2D newPoint(x, y);

    //insert according to choice
    if (choice == 0) {

    	//insert at beginning of vector;
    	if (curveIndex >= BCurves.size()) {
            if (BCurves.size() == 0) {
                BSCurves[curveIndex].controlPoints.insert( BSCurves[curveIndex].controlPoints.begin(), newPoint );
            } else {
                BSCurves[curveIndex % BCurves.size()].controlPoints.insert( BSCurves[curveIndex % BCurves.size()].controlPoints.begin(), newPoint );
            }
    	} else {
            BCurves[curveIndex].controlPoints.insert( BCurves[curveIndex].controlPoints.begin(), newPoint );
    	}
    } 
    else if (choice == numChoices - 1) {

    	//insert at end of vector;
        if (curveIndex >= BCurves.size()) {
            if (BCurves.size() == 0) {
                BSCurves[curveIndex].controlPoints.push_back( newPoint );
            } else {
            	BSCurves[curveIndex % BCurves.size()].controlPoints.push_back( newPoint );
            }
    	} else {
            BCurves[curveIndex].controlPoints.push_back( newPoint );
    	}
    } 
    else {

    	//insert after the point at index (choice - 1)
    	if (curveIndex >= BCurves.size()) {
            if (BCurves.size() == 0) {
                BSCurves[curveIndex].controlPoints.insert( BSCurves[curveIndex].controlPoints.begin() + (choice), newPoint );
            } else {
            	BSCurves[curveIndex % BCurves.size()].controlPoints.insert( BSCurves[curveIndex % BCurves.size()].controlPoints.begin() + (choice), newPoint );
            }
    	} else {
            BCurves[curveIndex].controlPoints.insert( BCurves[curveIndex].controlPoints.begin() + (choice), newPoint );
    	}

    }

    cout << endl;
}