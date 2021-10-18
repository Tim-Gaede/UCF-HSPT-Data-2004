#include<iostream>
#include<fstream>
using namespace std;


int main()
{
	//Open the data file
    ifstream in("sweet.in");
    

	//init. Variables
    int scencount = 0; //Number of scenarios to run
    int trans = 0; //Number of trans.
    int money = 0; //Total money for this scen
    int temp = 0; //Temporary read value
    
    in >> scencount; //Read in the number of scenarios
    
    for(int i = 0; i < scencount; i++)
    {
		//output the first line
        cout << "Scenario " << (i+1) << ":" << endl;

		//load in the number of transactions
        in >> trans;
        
		//reset the money variable so that Brandon starts with 0$ every scen.
        money = 0;
        
		//loop through the transactions
        for(int j = 0; j < trans; j++)
        {
			//read in the money value
                in >> temp;
			//add it to the current amount of Brandon's money
                money += temp;

			//if he has enough for a game
                if(money >= 50)
                {
                  money -= 50; //pay for the game
                  cout << "Sweet!" << endl; //output Sweet!
                }
                else
                {
                  cout << "Bummer, I need to wait." << endl; //just output wait
                }
        }
        
		//blank line per case
        cout << endl;
    }


	//close input file
    in.close();
    
    
    return 0;
}
