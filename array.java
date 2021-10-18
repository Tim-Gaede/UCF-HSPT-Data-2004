import java.lang.*;
import java.io.*;
import java.util.StringTokenizer;

public class array
{
    public void solve() throws IOException
    {
        String line;
        StringTokenizer tokens;
        int numPrograms;
        String martinChecksum;
        String program, checksum;
        int i;

        // Open the input file into a buffered reader
        FileInputStream inFile = new FileInputStream("array.in");
        BufferedReader inReader = 
            new BufferedReader(new InputStreamReader(inFile));

        // Read the first line and parse the number of programs
        line = inReader.readLine();
        numPrograms = Integer.parseInt(line.trim());

        // Repeat until the number of programs is zero
        while (numPrograms > 0)
        {
            // Read Officer Martin's checksum from the next line
            martinChecksum = inReader.readLine().trim();

            // For each program, read its name and checksum.  If the
            // checksum matches Martin's, print the program's name
            for (i = 0; i < numPrograms; i++)
            {
                // Read the next program line and tokenize it
                line = inReader.readLine().trim();
                tokens = new StringTokenizer(line);

                // The first token is the program name
                program = tokens.nextToken();

                // The second token is the checksum
                checksum = tokens.nextToken();

                // Compare the checksum to Martin's checksum and print
                // the program name if they match
                if (checksum.equals(martinChecksum))
                    System.out.println(program);
            }

            // Print a blank line, indicating the end of the program set
            System.out.println();

            // Read the first line of the next set and parse the number 
            // of programs
            line = inReader.readLine();
            numPrograms = Integer.parseInt(line.trim());
        }

        // Close the input file
        inReader.close();
    }

    public static void main(String args[]) throws Exception
    {
        // Create an instance of the array class and call the solve
        // method to solve the problem
        array program = new array();
        program.solve();
    }
}
