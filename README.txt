ECS175 PROJECT 4:
Name: Marcos Alcantar
Student ID: 913133174
email: mualcantar@ucdavis.edu

|***************|
| INSTRUCTIONS: |
|***************|

1) Once the file is unzipped, navigate to the directory containing all the project files "mualcant91313317" and
   type in the command "make" to compile the program.

2) Run the executable file using the command "./p4.out"

3) The following Menu will be displayed in the terminal, along with another window for displaying curves:

		Please enter the number for which operation you wish to perform: 
        1) Read in 2D curves from a .txt file.
        2) Remove a curve from the scene.
        3) Remove all objects (clear screen).
        4) Print current control points' coordinates.
        5) Add a control point to a curve.
        6) Remove a control point from a curve.
        7) Modify a control point from a curve.
        8) Specify a resolution (number of segments).
        9) (B-Spline ONLY) Change k order for a B-Spline curve.
        10) Exit Program and write scene to file 'output.txt'.


    Type the number for the operation you want to perform and press ENTER. You willl 
    first want to read in curves from a file, so enter 1.
    (Some sample files have been provided, named "test.txt", "test2.txt" and "test3.txt")

4) Once you have read in curve objects, they will be drawn on screen in white color.
   The control polygons are drawn in a different color as well. 

   ***Bezier Curves will have a light blue color control polygon.
   ***B-Spline Curves will have a light violet color control polygon.

|************************|
| INFO ABOUT OPERATIONS: |
|************************| 

  * OPERATION 1) To read in objects from a file, you will need to have the text file in the same directory
    as all of the program files. When you choose this option, you will be prompted to enter the 
    file's name. 
    	
    	***A sample file, called test.txt, has been provided, with 2 Bezier curves an 2 B-Spline curves***

    INPUT FILE FORMAT: (Coordinates are in World Coordinates)
    2             //Number of Bezier Curves in the file
    2             //Number of B-Spline Curves in the file
                  //1st Bezier Curve object follows after a blank line
    20            //Resolution (number of line segments) for 1st Bezier curve 
    4             //Number of control points for 1st Bezier curve
    42.0 45.3     //Control point 1 coordinates
    50.5 50.45    //Control point 2
    55.4 61.56    //Control point 3
    65.125 46.0   //Control point 4 (last one)

    5             //Next Bezier Curve's info: resolution
    3             //Number of control points
    70.0 70.0     //control points
    65.0 85.0
    80.0 80.0

    20            //This is a B-Spline Curve's info: resolution
    4             //Num control points
    12.0 15.3     //Control points coordinates
    20.5 30.45
    25.4 31.56
    35.125 16.0
    2             //k value (order number) for this curve
    0             //These are the values of the knots. They go from 0 to n+k by default here.
    1
    2
    3
    4
    5             //End of this B-Spline curve

    20            //Next B-Spline Curve's info
    5
    40.0 10.0
    50.0 30.0
    60.0 50.0
    63.0 20.0
    55.0 15.0
    3
    0
    1
    2
    3
    4
    5
    6
    7             //End of file


    ***NOTES: All Bezier curves must be listed before the B-Spline curves.
              Each object is separated by a blank line.
              Each curve can have a different resolution, so they have their own resolution number.
              B-Spline curves have the order number and the knot values in them as well.

  * OPERATION 2 and 3) Curves can be removed from the scene. Use operation 2 to remove a single one, 
    and operation 3 to remove all of them.

  * OPERATION 4) Lists all of the curves' information in the terminal and indicates which ones are Bezier and B-Spline curves.

  * OPERATION 5) Adding a control point is done in the terminal by typing in the points' coordinates. Control points
    can be added either between existing (consecutive) control points, or at the ends of the "control polygons".

  * OPERATION 6 and 7) A list of all the points will be printed first. Enter the number for the point
    that you want to you want to remove or modify. 

  * OPERATION 8) You can change either a single curve's resolution or all of them to the same value at the same time.
    If you choose to do a single one, the curves' information will be listed and you choose which one you want to change.

  * OPERATION 9) This changes the order number of a B-Spline curve. k values of 2 and 3 work pretty well,
    but 4 and beyond may get buggy.

  * OPERATION 10) The scene's information will be written to a file named "output.txt". You can use this as input
    when you start the program again.

|*************************|
| ALGORITHMS IMPLEMENTED: |
|*************************|

  de Casteljau Algorithm in curves.cpp, lines 54-74,                            (deCasteljauPoint function)
  de Boor Algorithm in curves.cpp, lines 138-172,                               (deBoorAlgorithmPoint function)  
  NDC mapping conversions in curves.cpp, lines 7-36,                            (convertWCtoPP function)
  Resolution line calculations in curves.cpp, lines 76-93, 174-199              (calculateCurvePoints functions) 