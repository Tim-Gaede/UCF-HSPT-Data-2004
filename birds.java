// Arup Guha
// 4/24/04
// Java Solution to 2004 UCF HS Programming Contest Problem Birds
 
import java.io.*;
import java.util.*;

// Create a small class to store a bird object.
class bird {

  int x; // x coordinate of the bird
  int y; // y coordinate of the bird
  int size; // bird's size
  int rank; // order in which it arrived to the pond.

  // Create a bird object with all the given information.
  public bird(int xcor, int ycor, int weight, int r) {
    x = xcor;
    y = ycor;
    size = weight;
    rank = r;
  }

  // Returns the distance from the current bird to the spot
  // (xbread, ybread).
  public double distance(int xbread, int ybread) {
    return Math.sqrt((x-xbread)*(x-xbread)+(y-ybread)*(y-ybread));
  }

} // end class bird

public class birds {

  public final static int NOT_FOUND = -1;

  public static void main(String [] args) throws IOException {

    BufferedReader fin = new BufferedReader(new FileReader("birds.in"));
    
    // Read in the number of birds
    int numbirds = Integer.parseInt(fin.readLine().trim());

    int set = 1;    
    // Go through each data set.
    while (numbirds > 0) {
      
      bird[] ducks = new bird[numbirds]; // Allocate space for the birds.

      // Read in the bird data and store it.
      for (int i=0; i<numbirds; i++) {

        StringTokenizer tok = new StringTokenizer(fin.readLine());
        int x = Integer.parseInt(tok.nextToken());
        int y = Integer.parseInt(tok.nextToken());
        int size = Integer.parseInt(tok.nextToken());
        int rank = i+1;
        ducks[i] = new bird(x,y,size,rank);
      } // end for numbirds

      System.out.println("Data Set #"+set+":");

      // Read in the number of pieces of bread for the data set.
      int numpieces = Integer.parseInt(fin.readLine().trim());
      for (int i=0; i<numpieces; i++) {

	// Read in the position of the bread.
        StringTokenizer tok = new StringTokenizer(fin.readLine());
        int breadx = Integer.parseInt(tok.nextToken());
        int bready = Integer.parseInt(tok.nextToken());

	// Find the closest bird and its distance from the bread.
	double closest = ducks[0].distance(breadx, bready);
	for (int j=1; j<numbirds; j++) {
	  if (ducks[j].distance(breadx, bready) < closest) 
	    closest = ducks[j].distance(breadx, bready);
  	}

	// Loop through each bird, updating the winning bird if we find
	// one that is close enough but "bigger". Ties are broken
	// properly by going through the birds in the order they arrived.
        int winner = NOT_FOUND;
        for (int j=0; j<numbirds; j++) {
          if (ducks[j].distance(breadx, bready)<= closest+1) {
	    if (winner == NOT_FOUND)
	      winner = j;
	    else if (ducks[j].size > ducks[winner].size)
              winner = j;
	  }
	}

        System.out.println("   Bird #"+(winner+1)+" gets the bread!");
      } // end for numpieces

      System.out.println();
      numbirds = Integer.parseInt(fin.readLine().trim());
      set++;
    } // end while

  } // end main

} // end class birds
