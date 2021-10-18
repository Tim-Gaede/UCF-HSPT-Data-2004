import java.util.*;
import java.io.*;

public class sweet
{
  public static void main(String[] argv)
  {
    BufferedReader in;
    StringTokenizer st;
    int curScenario;
    int numScenarios;
    int curTrans;
    int numTrans;
    int curFunds;

    try {
      // Instantiate a BufferedReader to handle the input
      in = new BufferedReader(new FileReader("sweet.in"));

      // Read in the number of scenarios to process
      numScenarios = Integer.parseInt(in.readLine().trim());

      // Loop for each scenario
      for (curScenario = 1; curScenario <= numScenarios; curScenario++)
      {
        // Read the number of transactions for the current scenario
        numTrans= Integer.parseInt(in.readLine().trim());

        // Reset the current amount of money
        curFunds = 0;

        // Print the scenario header
        System.out.println("Scenario " + curScenario + ":");

        // Loop through each transaction
        for (curTrans= 0; curTrans < numTrans; curTrans++)
        {
          // Add the current transaction to his funding
          curFunds += Integer.parseInt(in.readLine().trim());

          // Threshold the value
          if (curFunds >= 50)
          {
            // If he has 50 or more dollars, print the victory message and
            // decrease his funds for that purchase
            curFunds -= 50;
            System.out.println("Sweet!");
          }
          else
          {
            // If he doesn't have 50 dollars yet, print the failure message
            System.out.println("Bummer, I need to wait.");
          }
        }

        // Print the blank line that comes after each scenario unless
        // this is the last one (in which case no line is needed)
        if (curScenario <= numScenarios)
        {
          System.out.println();
        }
      }
    } catch (IOException e) {

        // Handle the exception in case there was any problem
        System.out.println("Crash: " + e);
        return;
    }
  }
}
