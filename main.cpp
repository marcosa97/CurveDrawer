#include <GL/glut.h>
#include <iostream>
#include <limits>
#include <utility>

#include "PixelBuffer.h"
#include "fileHandling.h"
#include "boundingBox.h"
#include "menuOperations.h"

using namespace std;

//Global pixel buffer
PixelBuffer *pixelBuffer;

//Keeps track of data needed to calculate bounding box
BoundingBox BBData;

//Global Bezier curves
//Global B-Spline curves
vector<BezierCurve> GBezierCurves;
vector<BSplineCurve> GBSplineCurves;

void update() {
    glDrawPixels( pixelBuffer->BUFFER_WIDTH, pixelBuffer->BUFFER_HEIGHT, GL_RGB, GL_FLOAT, pixelBuffer->pixelBuffer );
    glFlush();
}

void clearBuffersAndObjects() {
    GBezierCurves.clear();
    GBSplineCurves.clear();

    pixelBuffer->clearBuffer();
}

void myIdleFunction() {
    int numChoices = 10;
    //Get input
    cout << "Please enter the number for which operation you wish to perform: " << endl;
    cout << "    1) Read in 2D curves from a .txt file." << endl;
    cout << "    2) Remove a curve from the scene." << endl;
    cout << "    3) Remove all objects (clear screen)." << endl;
    cout << "    4) Print current control points' coordinates." << endl;
    cout << "    5) Add a control point to a curve." << endl;
    cout << "    6) Remove a control point from a curve." << endl;
    cout << "    7) Modify a control point from a curve." << endl;
    cout << "    8) Specify a resolution (number of segments)." << endl;
    cout << "    9) (B-Spline ONLY) Change k order for a B-Spline curve." << endl;
    cout << "    10) Exit Program and write scene to file 'output.txt'." << endl;
    cout << ">> ";

    //while input is invalid, get valid input
    int choice = 0;
    while (!(cin >> choice) || !(choice > 0 && choice < numChoices + 1) ) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again: ";
    }

    cout << endl;

    //switch 
    switch (choice) {
        case 1: readFile(GBezierCurves, GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); displayCurvesInfo(GBezierCurves, GBSplineCurves); break;
        case 2: removeCurve(GBezierCurves, GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); break;
        case 3: clearBuffersAndObjects(); break;
        case 4: displayCurvesInfo(GBezierCurves, GBSplineCurves); break;
        case 5: insertControlPoint(GBezierCurves, GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); break;
        case 6: removeControlPoint(GBezierCurves, GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); break;
        case 7: modifyControlPoint(GBezierCurves, GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); break;
        case 8: changeResolution(GBezierCurves, GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); break;
        case 9: changeKOrder(GBSplineCurves); redrawScene(pixelBuffer, BBData, GBezierCurves, GBSplineCurves); break;
        case 10: delete pixelBuffer; writeOutput(GBezierCurves, GBSplineCurves); exit(0); return;
    }
    
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;
    //int SUBWINDOW_MARGIN = 30;

    //Intro
    cout << "==============================================" << endl;
    cout << "|**  ECS175 Project 4, by Marcos Alcantar  **|" << endl;
    cout << "==============================================" << endl << endl;

    //Initialize glut   
    glutInit(&argc, argv);
  
    glutInitDisplayMode (GLUT_SINGLE);
    
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("ECS175: Program 4");
    glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
    glutDisplayFunc(update);
    glutIdleFunc(myIdleFunction);

    //int subwindowWidth = WINDOW_WIDTH/2 - 2* SUBWINDOW_MARGIN;
    //int subwindowHeight = WINDOW_HEIGHT/2 - 2* SUBWINDOW_MARGIN;

    //Create pixel buffer dynamically
    //This 1D array specifies colors for each pixel in the pixel buffer
    pixelBuffer = new PixelBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

    /*
    BBData.boxResolution = WINDOW_WIDTH/2 - 2*SUBWINDOW_MARGIN;
    BBData.boxMargin = 20; //hardcoded
    */

    glutMainLoop();
 
    return 0;
}
