
import java.lang.*;
import java.io.*;
import java.util.ArrayList;

public class lice
{
    private boolean isConsonant(char letter)
    {
        char lower;

        // First, return false if this is not a letter
        if (!Character.isLetter(letter))
            return false;

        // For the sake of this problem, it's easier to check if the
        // character passed in is not a vowel or 'y'.  Also for simplicity,
        // we'll do all comparisons in lower case.  First, make sure the
        // letter is lower-case
        lower = Character.toLowerCase(letter);

        // Now, see if it's a vowel or 'y'
        if ((lower == 'a') || (lower == 'e') || (lower == 'i') ||
            (lower == 'o') || (lower == 'u') || (lower == 'y'))
            return false;

        // If we've passed the tests so far, then the letter must be
        // a consonant
        return true;
    }

    private Integer getPlateValue(String plate)
    {
        int i;
        char current, last, next;
        int currentVal, lastVal, plateVal;

        // Initialize the "last" (previous) character to a special value
        // so we know when we're examining the first character in the loop
        // below.  Also initialize the last value to 0.
        last = '$';
        lastVal = 0;

        // Initialize the plate value to 0.  This will be used to accumulate
        // the value as we carry out the po-lice system of identification.
        plateVal = 0;

        // For each character in the plate, apply the rules to
        // determine the plate's value
        for (i = plate.length() - 1; i >= 0; i--)
        {
            // Grab the current character and create a Character object
            // from it (to make use of Java's nice features)
            current = plate.charAt(i);

            // See if the current character is a letter or digit
            if (Character.isDigit(current))
            {
                // Get the value of the digit
                currentVal = current - '0';
            }
            else if (isConsonant(current))
            {
                // The value of a consonant is 10
                currentVal = 10;
            }
            else if ((current == 'Y') || (current == 'y'))
            {
                // To figure out y's value we need the next and last
                // letters.  First, see if the last letter was a vowel
                if (isConsonant(last))
                {
                    // A 'y' is worth 15 if it's next to a consonant
                    currentVal = 15;
                }
                else if (i > 0)
                {
                    // Get the next character in the string for comparison.
                    // The if statement above is to make sure we don't try
                    // to get the "next" character if we're already at the
                    // end of the string.
                    next = plate.charAt(i-1);

                    // Check the next character to see if it's a consonant
                    if (isConsonant(next))
                    {
                        // A 'y' is worth 15 if it's next to a consonant
                        currentVal = 15;
                    }
                    else
                    {
                        // Neither adjacent letter is a consonant, so the
                        // 'y' is worth 10
                        currentVal = 10;
                    }
                }
                else
                {
                    // The previous character is not a vowel, and we're
                    // already at the end of the string, so this 'y' is
                    // worth 10.
                    currentVal = 10;
                }
            }
            else
            {
                // The value of a vowel is 15
                currentVal = 15;
            }

            // Now, we need to determine how to add the current value to
            // the total.  If we're at the first character, we just add
            // the current value
            if (last == '$')
            {
                plateVal += currentVal;
            }
            else if ((Character.isDigit(current) && Character.isDigit(last)) || 
                     (Character.isLetter(current) && Character.isLetter(last)))
            {
                // If both the current and last characters are the same type
                // of character, we add both the current and last values
                plateVal += currentVal + lastVal;
            }
            else
            {
                // If the characters are of different types, we just add
                // the current value
                plateVal += currentVal;
            }

            // For the next iteration, remember the current character and
            // its value
            last = current;
            lastVal = currentVal;
        }

        // Return the total plate value as an Integer object
        return new Integer(plateVal);
    }

    public void solve() throws IOException
    {
        String line;
        int numLice;
        ArrayList plateValues;
        int setNumber;
        int i;
        Integer value;

        // Open the input file into a buffered reader
        FileInputStream inFile = new FileInputStream("lice.in");
        BufferedReader inReader = 
            new BufferedReader(new InputStreamReader(inFile));

        // Initialize the data set number
        setNumber = 1;

        // Read the first line and parse the number of lice
        line = inReader.readLine();
        numLice = Integer.parseInt(line.trim());

        // Repeat until the number of lice is zero
        while (numLice > 0)
        {
            // Initialize the list of plate values
            plateValues = new ArrayList();
            
            // For each louse, calculate its head identifier
            for (i = 0; i < numLice; i++)
            {
                // Get the next louse's plate
                line = inReader.readLine().trim();

                // Calculate the value of the plate
                value = getPlateValue(line);

//				System.out.println(line+" = "+value);
                // If the plate value isn't already in the list, 
                // add it
                if (!plateValues.contains(value))
                    plateValues.add(value);
            }

            // Print out the number of values in the plate values list
            System.out.println("The lice in data set #" + setNumber +
                " came from " + plateValues.size() + " different head(s).");

            // Increment the data set number
            setNumber++;

            // Read the first line of the next set and parse the number 
            // of lice
            line = inReader.readLine();
            numLice = Integer.parseInt(line.trim());
        }
 
        // Close the input file
        inReader.close();
    }

    public static void main(String args[]) throws Exception
    {
        // Create an instance of the lice class and call the solve
        // method to deal with your lice problem ;-)
        lice program = new lice();
        program.solve();
    }
}
