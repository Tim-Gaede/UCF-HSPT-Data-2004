import java.util.*;
import java.io.*;
import java.text.*;

public class exchange
{
  public static void main(String[] argv)
  {
    BufferedReader in;
    StringTokenizer st;
    DecimalFormat df;
    int numCases;
    double initUS;
    double exchangeRate;
    double costForeign;
    double costUS;
    double moneyLeft;
    int dollarsLeft;
    int centsLeft;

    try {
      // Instantiate a BufferedReader to handle the input
      in = new BufferedReader(new FileReader("exchange.in"));

      // Set up the decimel format to handle output
      df = new DecimalFormat("00");

      // Read in the number of input cases
      numCases = Integer.parseInt(in.readLine().trim());

      // Iterate through each case
      for (int n = 0; n < numCases; n++)
      {
        // Build a string tokenizer to read the current input line
        st = new StringTokenizer(in.readLine().trim(), " \t");

        // Read in the three values
        initUS = Double.parseDouble(st.nextToken());
        exchangeRate = Double.parseDouble(st.nextToken());
        costForeign = Double.parseDouble(st.nextToken());

        // Find out how much was spent in US currency
        costUS = costForeign / exchangeRate;

        // Subtract this amount from the initial US figure
        moneyLeft = initUS - costUS;

        // Retreive the dollar and cent values from the result
        dollarsLeft = (int)(moneyLeft);
        centsLeft = ((int)((moneyLeft) * 100)) % 100;

        // Output the value, using the DecimalFormat to ensure that both
        // zeroes are displayed in the cents place
        System.out.println("$" + dollarsLeft + "." + df.format(centsLeft));
      }
    } catch (IOException e) {

        // Handle the exception in case there was any problem
        System.out.println("Crash: " + e);
        return;
    }
  }
}
