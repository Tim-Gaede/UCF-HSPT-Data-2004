#include <stdio.h>

int main(void)
{
	FILE* fin; // Input file

	int sets; // Number of scenarios
	int set; // Current scenario

	int transactions; // Number of transactions

	int cashSum; // Running total of transactions
	int cash; // Cash value of transaction

	int i; // Index variable

	// Open input file to be read
	fin = fopen("sweet.in", "r");

	// Read the number of scenarios
	fscanf(fin,"%d ",&sets);

	// Loop through each scenario
	for(set=1;set<=sets;set++)
	{
		// Read the number of transactions in this scenario
		fscanf(fin,"%d ",&transactions);

		// Brandon starts out with no money
		cashSum = 0;
	
		// Print scenario header
		printf("Scenario %d:\n",set);

		// Loop through each transaction
		for(i=0;i<transactions;i++)
		{
			// Read transaction
			fscanf(fin,"%d ",&cash);

			// Add the current transaction to the running total
			cashSum += cash;

			// If Brandon has enough money...
			if(cashSum >= 50)
			{
				// Then he buys a game
				cashSum -= 50;
				printf("Sweet!\n");

			}
			else
			{
				// Otherwise he must wait
				printf("Bummer, I need to wait.\n");
			}
		}

		// Print a blank line after each scenario
		printf("\n");
	}

	return 0;
}