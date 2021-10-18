/*******************************************************************************
    2004 UCF High School Proogramming Contest
    Problem: Array
    Author: Ben Douglass
    C++ Judge Solution: Nick Beato
*******************************************************************************/

/*******************************************************************************
    standard includes
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*******************************************************************************
    main entry point
*******************************************************************************/

int main()
{	

    /***************************************************************************
        This should start simple, open the file.  As far as i know, there are no
        programming contests that require you to check for a valid file.  So
        just assume it is valid and keep going.
    ***************************************************************************/
    ifstream inFile("array.in");
    
    /***************************************************************************
        Here are all the variables I plan to use:
        
        n: identical to the n in the problem statement.  It represents how
            many programs need to be checked.  If it is 0, end the program.
            
        martinChecksum: This is a string that is the equivalent of Martin's
            checksum. We want to see if any other program has this exact same
            checksum.
        
        programName: This is a string representing the name of the current
            program that we are evaluating.  We want to see if Martin has
            infected this program.
            
        programChecksum: This is a string representing the name of the current
            program's checksum.  If the checksum matches, then Martin infected
            the program and we need to report that.
            
        
        **Judge's note** If you are not familiar with strings, they are much
            easier to use then normal c routines or character arrays.  I know 
            the AP program used to use the apstring class.  Java also has a
            built-in string class.  Either way, strings are much nicer than
            arrays! I'd recommend reading "The C++ Standard Temple Library" by 
            Josuttis, if you are serious about learning programming.  Strings 
            are a great tool.
    ***************************************************************************/
    int n;
    string martinChecksum;
    string programName;
    string programChecksum;
    
    /***************************************************************************
        The remainder of the program should be rather straight forward...
        
        -Read a number from the input file.
        -While that number is not 0, read in Martin's checksum, followed by the 
            same number of lines.
        -For each line, if the checksum matches Martin's, print the program's
            name.  Otherwise, ignore it.
        -Don't forget to output the end-line after every data set. (Even if the
            data set had no other values printed!)
    ***************************************************************************/
    
    inFile >> n;
    
    while(n != 0) // if n == 0, bail the program
    {
        inFile >> martinChecksum; // get martin's checksum
        
        //  read in n lines from the input file
        for(int programNum = 0; programNum < n; programNum++)
        {
            // each line has a program name and checksum.  because
            // the program name and checksum are gauranteed to be "base-62",
            // you can be assured that no other whitespace exists in the file,
            // so just read the individual tokens
            inFile >> programName >> programChecksum;
            
            // if the checksums match, print the program name
            if(programChecksum == martinChecksum)
                cout << programName << endl;
        }
    
        cout << endl;
        
        // read in the beginning of the next case
        inFile >> n;
    }
    
    /***************************************************************************
        It's a good idea to close files when you don't need them anymore.
        When the program dies, the operating system normally closes the file for
        you, but that is not an excuse :)
    ***************************************************************************/
    inFile.close();
    return 0;
}

/*******************************************************************************
    eof
*******************************************************************************/
