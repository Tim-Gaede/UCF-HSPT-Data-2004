/*******************************************************************************
    2004 UCF High School Programming Contest
    Problem: Cycle
    Author: Scott Vogelpohl
    Judge C++ Solution: Nick Beato
    
    This problem is a lot of misleading wording to obscure the details of what
    you actually have to do.  You are given a sequence of uppercase characters.
    There are only 26 of them (A-Z).  The characters indicate locations on a
    map.  They are presented in the order that they are seen.  You have to 
    analyze the map markers seen and remove the portion of the path in the
    cycle.  To do this, you have to find the letter that appears twice.  You
    are gauranteed that only one and exactly one character will appear twice.
    So you just need to find it.  Then, remove all of the characters between
    the letter that appears twice, and print the resulting path.
*******************************************************************************/

/*******************************************************************************
    Standard Includes
*******************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

/*******************************************************************************
    Because the locations are only upper case characters, there will only be
    at most 26 locations.
*******************************************************************************/

const int MAX_MAP_LOCATIONS = 26;

int main()
{
    // open the file
    ifstream inFile("cycle.in");
    
    /***************************************************************************
        Here are all of the variables I plan to use to solve this problem.
        
        caseNum: keeps track of the case number for output purposes.
        
        n: the number of locations seen in the input file (0 means to quit)
        
        currentMapLocation: This is the current map location we are walking
            past.  In simplest terms, it is the current character that we
            have read in from the file.  We will look to see if this character
            has already been read in, and consider it a cycle if it has later.
            
        whereWeHaveBeen: This is an array of all of the locations that we have
            walked passed.  The array is almost equivalent to the input file.
            It is used to figure out where we have been.
            
        historyIndex: This represents the next index in the array above that we
            should write to.  It is used to figure out the path.  An example
            will illustrate how it works in the algorithm section.
    ***************************************************************************/
    
    int caseNum = 1;
    int n;
    char currentMapLocation;
    char whereWeHaveBeen[MAX_MAP_LOCATIONS];
    int historyIndex;
    
    // read the number
    inFile >> n;
    
    // If it is not 0, then we keep on going.  The end of the while loop
    // will read the beginning of the next case for us.
    while(n != 0)
    {
    
        /***********************************************************************
            Here's the fun part, the algorithm.
            
            The general idea is to mark what locations have been seen as we read
            them in.  Before saying it is seen, check if you have already been
            there.  If you have not, then you just mark that you saw the
            location.  However, if you have seen the location, then you go
            back to where you were earlier and keep going. For example:
            
            The sample input:
            10 A B C D E F G B H I
            
            First set historyIndex, which indicates which positions in
            whereWeHaveBeen are used, to 0. This means we haven't used any
            of the positions.  The notation for the array and index is as
            follows
            "", 0 meaning the value of the array as a string and the value of
                  the history index.
                  
            We scan from left to right (Assuming 10 has been read in already)
            
            A B C D E F G B H I
            *
            
            A is not used, so we add it to whereWeHaveBeen and add 1 to
            the historyIndex
            "A", 1
            
            A B C D E F G B H I
              *
            gives "AB", 2
            
            A B C D E F G B H I
                *
            gives "ABC", 3
            
            this process repeats up until G
            "ABCDEFG", 7
            
            Then we have...
            A B C D E F G B H I
                          *
        
            Which should make us store
            "ABCDEFGB", 8
            
            However, B is at position 1!
            A B C D E F G B H I
              *           *
              
            To delete the cycle, we set the history back to 1, as if we
            never walked around the loop.
            "AB", 2
            
            Then we continue through the input... we see H and I and add them
            to our array.  We act like we never saw the input from before, so
            H will be the 3rd character
            "ABH", 3
            
            Followed by:
            "ABHI", 4
            
            Then we just need to print the array with proper spacing :)
            
        ***********************************************************************/
        
        // mark that we have not been anywhere yet
        historyIndex = 0;
        
        // inputIterator counts how many input values have been read
        // we need to read n of them
        for(int inputIterator = 0; inputIterator < n; inputIterator++)
        {
            // read in the next character
            inFile >> currentMapLocation;
            
            // iterate through all of the places we have been so far
            // we check if we have been here yet. if we have, we just go
            // back to that point in time and act like we never walked around
            // the cycle.
            for(int historyIterator = 0; historyIterator < historyIndex; historyIterator++)
            {
                // true if we have been to this location before
                if(whereWeHaveBeen[historyIterator] == currentMapLocation)
                {
                    // go back and stop looking for the next position
                    historyIndex = historyIterator;
                    break;
                }
            }
            
            // this just marks the current position in the history
            whereWeHaveBeen[historyIndex] = currentMapLocation;
            historyIndex++;
        }
        
        /***********************************************************************
            Yay, we got the answer! Now just output it.  The for loop outputs
            all of the characters but 1 and a space.  To get around dealing
            with an extra space at the end of the line, I print the space
            BEFORE te character and omit the space after the colon.  The first
            character will print that :)
        ***********************************************************************/
        cout << "Case " << caseNum << ":";
        
        for(int outputIterator = 0; outputIterator < historyIndex; outputIterator++)
            cout << " " << whereWeHaveBeen[outputIterator];
            
        cout << endl;
            
        caseNum++;
        inFile >> n;
    }
    
    // that's it! close the file and quit
    // Hope you enjoyed it :)
    inFile.close();
    return 0;
}

