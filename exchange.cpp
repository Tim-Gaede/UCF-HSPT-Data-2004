#include <stdio.h>

int main(void)
{
	FILE* fin; // Input file

	int sets; // Number of trips
	int set; // Current trip

	double starting; // Amount of cash to begin with
	double rate; // Exchange rate
	double spending; // Amount of cash spent abroad
	double result; // Amount of money left over

	// Open input file to be read
	fin = fopen("exchange.in", "r");

	// Read the number of trips
	fscanf(fin,"%d ",&sets);

	// Loop through each trip
	for(set=1;set<=sets;set++)
	{
		// Read the information for the trip
		fscanf(fin,"%lf %lf %lf ",&starting, &rate, &spending);

		// Calculate and round the amount of money left over
		result = starting - (spending/rate) - 0.005;
		
		// Print the amount of money remaining after the trip
		// The rounding used may cause a result of $-0.00, so this is necessary
		if(result<0) 
		{
			printf("$0.00\n");
		}
		else
		{
			printf("$%.2lf\n", result);
		}
	}

	return 0;
}