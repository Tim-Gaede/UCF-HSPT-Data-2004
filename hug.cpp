#include <stdio.h>

int main(void)
{
	FILE* fin; // Input file

	int width; // Width of the contest area
	int height; // Height of the contest area

	int people; // Number of people willing to hug Ali

	int ypos[1024]; // y-position of each person in the contest area
	int radius[1024]; // Distance that each person will walk to hug Ali

	int best; // The most hugs that Ali can get
	int current; // The number of hugs Ali can get with the current guess

	int guess; // Current guess of Ali's best y-position

	int i; // Index variable
	int j; // Index variable

	// Open input file to be read
	fin = fopen("hug.in", "r");

	// Loop through each scenario
	while(1)
	{
		// Read the dimensions of the contest area
		fscanf(fin,"%d %d ",&width, &height);
		
		// A room size of 0, 0 represents end of input
		if(width == 0 && height == 0)
			return 0;
		
		// Read the number of people willing to hug Ali
		fscanf(fin,"%d ",&people);

		// Read information about each person
		for(i=0;i<people;i++)
		{
			// x-position is irrelevant
			fscanf(fin,"%*d %d %d ", &ypos[i], &radius[i]);
		}

		// Initialize Ali's best number of hugs to 0
		best = 0;

		// Loop through each person
		for(i=0;i<people;i++)
		{
			// Consider the person's highest bound
			guess = ypos[i] + radius[i];

			current = 0;

			// See how many people will hug Ali with that guess
			for(j=0;j<people;j++)
			{
				if(guess <= ypos[j] + radius[j] && guess >= ypos[j] - radius[j])
				{
					current++;
				}
			}

			// If more people will hug Ali, then keep track of this
			if(current > best)
			{
				best = current;
			}

			// Consider the person's lowest bound
			guess = ypos[i] - radius[i];

			current = 0;

			// See how many people will hug Ali with that guess
			for(j=0;j<people;j++)
			{
				if(guess <= ypos[j] + radius[j] && guess >= ypos[j] - radius[j])
				{
					current++;
				}
			}

			// If more people will hug Ali, then keep track of this
			if(current > best)
			{
				best = current;
			}

		}

		// Print the greatest number of hugs that Ali can get
		printf("Ali can get %d hug(s)!\n",best);
	}

	return 0;
}