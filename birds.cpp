#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Floating-point tolerance is defined by the problem statement. 
// This is a tolerance that we would never really use in a real 
// program, but the nature of this problem dictates this value.
#define TOLERANCE 1.0

// A simple struct to hold the data for a bird.
typedef struct bird {
  int x, y;
  int size;
} bird;

// Utility function to caluclate the distance formula. 
double distance(double x1, double y1, double x2, double y2) {
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

int main() {
  ifstream in("birds.in");

  // An STL vector to store the bird data.
  vector<bird> birdList;

  // A counter for the output of case numbers.
  int count = 0;
  
  while (true) {

    // For each case, we need to be sure to clear the vector.
    // Otherwise, birds from the last case will leak into this
    // one. And we don't want that.
    birdList.clear();

    int nBirds;
    in >> nBirds;

    // Check if this is the terminating case. 
    if (nBirds < 0)
      break;

    cout << "Data Set #" << ++count << ":" << endl;

    // Read all the birds. 
    for (int i = 0; i < nBirds; i++) {
      bird b;
      in >> b.x >> b.y >> b.size;
      birdList.push_back(b);
    }

    // Read the bread and do the computation as we go. 
    int nBread;
    in >> nBread;
    for (int k = 0; k < nBread; k++) {
      int x, y;
      in >> x >> y;

      // Iterate through the birds and search for the minimum. 
      // So we don't have to do a special check, bestDistance
      // is initalized to an unreasonably large value, so that any
      // value for the first bird will be less and therefore pass
      // the condition to replace it. 
      int bestIdx = -1;
      double bestDistance = 1e99;
      for (int i = 0; i < birdList.size(); i++) {
		double dist = distance(x, y, birdList[i].x, birdList[i].y);

		
		
		if (dist < bestDistance) {
			// Update the best bird if the new distance is smaller.
			bestIdx = i;
			bestDistance = dist;
		}
      }

	  // Now that we know which bird is the minimum, we have to determine
	  // which birds are "equal" to it and determine which is actually the winner.
	  //cout << "Min is " << bestIdx << " at " << bestDistance << endl;
	  bestIdx = -1;
	  for (int i = 0; i < birdList.size(); i++) {
			double dist = distance(x, y, birdList[i].x, birdList[i].y);
			if (dist - bestDistance <= TOLERANCE) {
					//cout << i << " is 'equal' with " << dist << endl;
					if (bestIdx == -1 || birdList[i].size > birdList[bestIdx].size) {
							bestIdx = i;
					}
			}
	  }
      
      // Note that we add one to the index here, since the output expects the
      // bird number to be one-based.
      cout << "   Bird #" << bestIdx+1 << " gets the bread!" << endl;
    }

    // And don't forget the newline between cases.
    cout << endl;
  }
}

/*
// Check for floating point equality
		if (fabs(dist - bestDistance) <= TOLERANCE) {
		// If the distances are "equal," compare the size of the birds.

		// Here's the tricky part.
		// Suppose that bird 1 is 1 cm away from the bread and is size 1.
		// Suppose that bird 2 is 2 cm away from the bread and is size 2.
		// Suppose that bird 3 is 3 cm away from the bread and is size 3.
		// Bird 1, intuitively, is the closest, so it should get to the bread
		// first. However, because of the definition of equality, birds 1 and 2
		// are the "same" distance away, and therefore the larger bird, bird 2, 
		// would win over bird 1. 
		// Bird 3, similarly, has a distance "equal" to that of bird 2. Being 
		// larger, it wins over bird 2. 
		// BUT, bird 1 and bird 3 are NOT at an equal distance. Therefore bird 1 
		// should win over bird 3. 
		// This seems to be confusing and circular, until you understand that 
		// it should be ONLY the closest "class" of equivalent birds that is 
		// considered for the secondary criterion. Bird 1 is not the "same" distance
		// away as bird 3, so it is eliminated from the beginning; only bird 1 and bird 2
		// should be considered in terms of size. Then, between the two, bird 2 is the larger,
		// and therefore it is the completely nonintuitive winner in this
		// scenario.
		if (dist < realBestDistance) {
	  		realBestDistance = dist;
		}

		if (birdList[i].size > birdList[bestIdx].size) {
			// If the new bird's size is greater, replace the current
			// best with the new bird. 
			// Otherwise, we leave everything alone; if the sizes are equal,
			// then the bird that was already read remains the best.
			bestIdx = i;
		}
*/