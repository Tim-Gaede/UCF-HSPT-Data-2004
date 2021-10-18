import java.util.*;
import java.io.*;

public class jackjill
{
  public static void main(String[] argv)
  {
    BufferedReader in;
    StringTokenizer st;
    int rise;
    int run;

    try {
      // Instantiate a BufferedReader to handle the input
      in = new BufferedReader(new FileReader("jackjill.in"));

      // Create a string tokenizer for the first line of input
      st = new StringTokenizer(in.readLine().trim(), " \t");

      // Read the first two values for rise and run
      run = Integer.parseInt(st.nextToken());
      rise = Integer.parseInt(st.nextToken());

      // Loop until the terminating case is reached
      while ((run > 0) && (rise > 0))
      {
        // Check the slope
        if (rise > run)
        {
          // The slope is greater than 45 degrees
          System.out.println("Jack and Jill broke their crowns!");
        }
        else
        {
          // The slope is less than (or equal to) 45 degrees
          System.out.println("Jack broke his crown!");
        }

        // Read the next input case
        st = new StringTokenizer(in.readLine().trim(), " \t");
        run = Integer.parseInt(st.nextToken());
        rise = Integer.parseInt(st.nextToken());
      }

    } catch (IOException e) {

        // Handle the exception in case there was any problem
        System.out.println("Crash: " + e);
        return;
    }
  }
}
