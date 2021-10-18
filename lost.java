// Arup Guha
// 4/24/04
// Java Solution to 2004 UCF High School Programming Contest Problem Lost

import java.io.*;
import java.util.StringTokenizer;

// Small class to store information about a single landmark.
class landmark {

  // Stores the name and the coordinate location of the landmark object.
  String name;
  int x;
  int y;

  // Constructor...
  public landmark(String n, int xval, int yval) {
    name = n;
    x = xval;
    y = yval;
  }

}

public class lost {

  // A lost object just contains an array of buildings.
  landmark[] allbuildings;

  public static void main(String [] args) throws IOException {

    int index;

    // Open the input file.
    BufferedReader fin = new BufferedReader(new FileReader("lost.in"));

    // Read in the number of buildings and initialize the lost oject.
    int numb = Integer.parseInt(fin.readLine().trim());
    lost mydir = new lost(numb);
    fin = mydir.init(fin);

    // Read in the number of cases to process.
    int numcases = Integer.parseInt(fin.readLine().trim());

    // Process each case.
    for (index = 0; index < numcases; index++) {

      // Read in the information about the current case.
      StringTokenizer tok = new StringTokenizer(fin.readLine());
      String loc1 = tok.nextToken();
      double heading1 = (Double.valueOf(tok.nextToken())).doubleValue();
      tok = new StringTokenizer(fin.readLine());
      String loc2 = tok.nextToken();
      double heading2 = (Double.valueOf(tok.nextToken())).doubleValue();

      // Find the indexes to the mydir object that store the two landmarks
      // being used to find the unknown position.
      int loc1index = mydir.findloc(loc1);
      int loc2index = mydir.findloc(loc2);

      // Convert the headings to both landmarks into ordinary radians.
      heading1 = convertToRadians(heading1);
      heading2 = convertToRadians(heading2);

      // Determine the distance between the two landmarks.
      double distance= mydir.getDistance(loc1index, loc2index);

      // Determine the angle formed with the lost position as the
      // vertex and the two landmarks.
      double angle1 = getAngle(heading1, heading2);

      // Determine the heading from the first landmark to the second one.
      double heading3 = getHeading(mydir.getXvect(loc1index, loc2index),
	  		           mydir.getYvect(loc1index, loc2index));

      // Determine the angle opposite the side of the triangle connecting
      // the second landmark to the lost position.
      double angle2 = getAngle(heading3, flip(heading1));

/* Printing info for debugging
      System.out.println("Angle1 = "+180*angle1/Math.PI);
      System.out.println("Angle2 = "+180*angle2/Math.PI);
      System.out.println("Heading1 = "+180*heading1/Math.PI);
      System.out.println("Heading2 flip = "+180*flip(heading2)/Math.PI);
      System.out.println("Heading3 = "+180*heading3/Math.PI);
      System.out.println("distance btw land = "+distance);
*/
      // Due to the problem specification, you are guaranteed that the
      // triangle formed by the lost position and the two landmarks is not
      // degenerate. So, there's no need to check any of the angle values
      // before dividing by the sine of angle1.

      // Use the law of sines to determine the distance between the
      // lost position and the second landmark.
      double distanceToL2 = distance*Math.sin(angle2)/Math.sin(angle1);

      // Use the distance above, along with the given heading information
      // to calculate both the x and y values of the lost position.
      double xlocation = mydir.allbuildings[loc2index].x+distanceToL2*Math.cos(flip(heading2));
      double ylocation = mydir.allbuildings[loc2index].y+distanceToL2*Math.sin(flip(heading2));

      // Round these to the nearest integer.
      long xloc = Math.round(xlocation);
      long yloc = Math.round(ylocation);

      // Produce the output for the case.
      System.out.println("The team is lost at "+xloc+", "+yloc+"!");

    } // end for index loop through all the cases.

  }

  // Constructor allocates space for the number of buildings passed in.
  public lost(int numbuildings) {
    allbuildings = new landmark[numbuildings];
  }

  // Reads information from the file that fin is a reference to, and 
  // initializes each building in the object.
  public BufferedReader init(BufferedReader fin) throws IOException {
    
    int index;  

    // Loop through all the buildings.
    for (index=0; index<allbuildings.length; index++) {

      // Read in the name, x location and y location.
      StringTokenizer tok = new StringTokenizer(fin.readLine());
      String building = tok.nextToken();
      int x = Integer.parseInt(tok.nextToken());
      int y = Integer.parseInt(tok.nextToken());

      // Create the building object.
      allbuildings[index] = new landmark(building, x, y);
    }
    return fin; // Return the BufferedReader (is this necessary?)
  }

  // Finds the index that the building name is stored in, in the current
  // object.
  public int findloc(String name) {

    int index;

    // Loop through all the buildings until one of the names matches.
    for (index=0; index<allbuildings.length; index++)
      if (name.equals(allbuildings[index].name))
        return index;

    return -1; // This is the error case. Based on the problem 
               // specification, this will never be reached.
  }

  // Returns the distance between the landmark stored at index loc1index
  // and the landmark stored at index loc2index in the current object.
  public double getDistance(int loc1index, int loc2index) {

    // Apply the distance formula.
    double xdiff = Math.pow(allbuildings[loc1index].x-allbuildings[loc2index].x,2);
    double ydiff = Math.pow(allbuildings[loc1index].y-allbuildings[loc2index].y,2);
    return Math.sqrt(xdiff+ydiff);
  }

  // Returns the change in x value from the landmark stored in index
  // loc1index to the landmark stored in index loc2index of the current
  // object.
  public double getXvect(int loc1index, int loc2index) {
    return allbuildings[loc2index].x-allbuildings[loc1index].x;
  }

  // Returns the change in y value from the landmark stored in index
  // loc1index to the landmark stored in index loc2index of the current
  // object.
  public double getYvect(int loc1index, int loc2index) {
    return allbuildings[loc2index].y-allbuildings[loc1index].y;
  }

  // Gets the angle between two different headings
  public static double getAngle(double heading1, double heading2) {

    // The initial computation is the difference in the headings.
    double angle = Math.abs(heading1-heading2);

    // Adjust for an angle greater than PI radians (180 degrees).
    if (angle > Math.PI)
      angle = 2*Math.PI - angle;
    return angle;
  }

  // Get the heading (in radians) of a vector with the x and y
  // components respectively that are passed in as parameters.
  public static double getHeading(double x, double y) {

    // Deal with the case where the x vector is 0.
    if (x==0) { 
      if (y>0)
        return Math.PI/2;
      else
        return 3*Math.PI/2;
    }

    // Deal with the normal case by using the arctan function to get the
    // desired angle, in radians in between 0 and 2*PI. (2*PI is not 
    // included in the range, but 0 is.)
    double angle = Math.atan(y/x);

    // Adjust if the actual angle you want is in the second or third
    // quadrant.
    if (x < 0)
      angle += Math.PI;

    // Adjust for an angle in the fourth quadrant, since arctan returns
    // a negative angle value here.
    if (x > 0 && y < 0)
      angle += 2*Math.PI;

    return angle;
  }

  // Returns the heading of the opposite direction of the heading passed
  // into the function.
  public static double flip(double heading) {

    // Determine whether to add or subtract PI (180 degrees) based on
    // the value of the heading passed in.
    if (heading < Math.PI)
      heading += Math.PI;
    else
      heading -= Math.PI;
    return heading;
  }

  // Given a heading as specified in the problem specification, the
  // corresponding value in radians is returned.
  public static double convertToRadians(double heading) {

    // Makes the initial calculation in regular degrees, since the heading
    // starts at North and goes clockwise instead of counterclockwise.
    heading = 90 - heading;

    // Adjust for negative degrees by getting them in range.
    if (heading < 0)
      heading += 360;

    // Convert the degree value in between 0 and 360 and return the
    // corresponding radian value.
    return heading*Math.PI/180;
  }

}
