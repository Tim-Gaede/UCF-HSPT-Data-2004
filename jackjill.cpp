#include <stdio.h>

int main(void)
{
	FILE* fin; // Input file

	int x; // Length of hill
	int y; // Height of hill

	// Open input file to be read
	fin = fopen("jackjill.in", "r");

	// Loop through each scenario
	while(1)
	{
		// Read the dimensions of the hill
		fscanf(fin, "%d %d ", &x, &y);

		// Input is terminated when x or y is zero
		if(x==0 || y==0)
			return 0;

		// If the hill is steeper than 45 degrees...
		if(y>x)
		{
			// Then Jack and Jill both break their crowns
			printf("Jack and Jill broke their crowns!\n");
		}
		else
		{
			// Otherwise only Jack is hurt
			printf("Jack broke his crown!\n");
		}

	}

	return 0;
}