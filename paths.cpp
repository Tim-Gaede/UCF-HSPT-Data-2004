/*******************************************************************************
    2004 UCF High School Programming Contest
    Problem: Paths
    Author: Arup Guha
    Judge C++ Solution: Nick Beato
    
    Intro...
    This problem is nasty.  Well, not that nasty.  It appears evil, but really
    can be broken down into a simple solution.
    
    As the solver, there are many things the problem allows me to "cheat" with.
    I'm not really cheating, just exploiting the nature of the problem.
    
    1) Nick can only walk up or down, not both
    2) Nick can only walk left or right, not both
    
    Both of these REALLY help.  The SHORTEST path is ALWAYS given by the start
    and end locations.  You don't have to figure out how to navigate through a
    maze of ugly intersections.  You just walk a set number of times.  No matter
    which path you take, you will always end up walking horizontally the same
    number of times and vertically the same number of times. Neat!
    
    The trick to this problem is figuring out how many ways Nick can TURN at
    an intersections.  Without the ugly intersections, the answer is larger
    than you may think.  On a 10x10 grid, if Nick travels from (0,0) to (9,9),
    there are C(20, 10) ways to walk there.  That is 20! / (10! 10!).  If you
    don't like numbers that much, there are 184756 ways for Nick to get there!
    The maximum grid size allows almost 10^30 ways to get there (THAT IS A LOT!)
    
    3) The specification lowers the max case drastically!
    
    4) Finally, the last thing that helps is that the roads are all connected
    at exact distances.  This allows us to visualize the problem on a two-
    dimensional array with ease.  Array[i][j] is adjacent to 4 different
    squares.  They are Array[i-1][j], Array[i+1][j], Array[i][j-1], and
    Array[i][j+1].  Neat huh?
    
    Ok, keep reading for the joyous adventures of Nick...
*******************************************************************************/

/*******************************************************************************
    standard includes
*******************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

/*******************************************************************************
    First thing to address in this problem: The bounds.  I decided to make a few
    constants to address the bounds of the problem.
    
    MAX_INTERSECTIONS: this is the maximum number of intersections that can
        occur in one test case.  It is used to declare the array of
        intersections.
        
    MAX_GRID_SIZE: This is also used for array allocation, note that the problem
        states 0 <= m <= 50.  This means there are *51* x *51* possible
        intersections.  The array should NOT be size 50 x 50!  We definately DID
        test for this one :)
        
    UNKNOWN: This is used to mark when Nick (hmm that's my name too...) doesn't
        know how many ways he can travel somewhere.  I am not a fan of forward
        references, but I have to do it! I'll explain this in more detail when
        I explain the next function
*******************************************************************************/

const int MAX_INTERSECTIONS = 10;
const int MAX_GRID_SIZE = 10;
const int UNKNOWN = -1;

/*******************************************************************************
    The majority of the problem solving occurs in one function.  To understand
    it, it would probably help to explain two things: Recursion and Memorization
    (sometimes called Memoization because CS people like to make up words).  If
    both those phrases are confusing, let me try to explain...
    
    In the simplest terms, a recursive function is a function that calls itself.
    The best and most known example of a recursive function is the Fibonacci
    sequence (1 1 2 3 5 8 13 21 34...):
        F(0) = F(1) = 1
        F(n) = F(n-1) + F(n-2) when n >= 2
    To calculate a Fibonacci number, you just add the two previous Fibonacci
    numbers.  Of course, to calculate the two previous Fibonacci numbers, you
    have to calculate the two previous Fibonacci numbers for each one... For
    Example, look at F(4)
        F(4) = F(3) + F(2) 
             = (F(2) + F(1)) + (F(1) + F(0))
             = ((F(1) + F(0)) + F(1)) + (F(1) + F(0))
             = ((1 + 1) + 1) + (1 + 1)
             = 5
    Try F(10), it is more work than you may think :) The Fibonacci sequence
    really has nothing to do with pretty scenery walking through a city.  So
    let's return to recursion... A recursive function has two main properties:
    1) It has a terminating condition (ie. F(0) = F(1) = 1)
    2) It uses itself with smaller version of the entire problem.  It breaks
       the main problem into sub-problems that can be calculated with the exact
       same function.
       
    Here is how this helps us.  Nick decides to walk into a square.  He is only
    allowed to walk towards his destination, so he can recursively try to walk
    again, but this time he starts at a closer point.
    
    For example, using a 3x3 grid:
        ..D            ..D            ..D
        ... walk right ... or walk up N..
        N..            .N.            ...
        
    These are the only things that Nick can do to get to his destination.  This
    produces two smaller problems.  We can recursively solve the problem by
    adding the number of ways to get to D when moving RIGHT to the number of
    ways to get to D when moving RIGHT.
    
    So what is the terminating condition? Well, there is exactly ONE way to get
    to D if you are at D, so you see if you are at the destination :)
    
    So what does WalkCycle do? This function takes a lot of parameters and
    recursively calculates how many ways Nick can walk from the current position
    to the destination moving in one of the two directions supplied.
    
    cur_x, cur_y: the current x and y position of Nick on the grid
    dest_x, dest_y: the destination's x and y coordinates.  If Nick is here, we
        found the terminating case
    dir_x, dir_y, the directions that Nick can walk (-1 or +1 in both cases)
    city_grid, a grid that Nick is using to mark how he can get somewhere.
    
    The first few arguments should be straight forward, but what is city_grid??
    Here is where memoization comes in. Memoization is a way to cache, or
    remember, values that are known.  For example, let's say we have a 3x4...
    
    One outcome is:
        ...D    ...D    N..D       .N.D       ..ND
        .... UP N... UP .... RIGHT .... RIGHT .... etc
        N...    ....    ....       ....       ....
        
    Another outcome is:
        ...D       ...D        ...D   ...D    ..ND
        .... RIGHT .... RIGHT .... UP ..N. UP .... etc
        N...       .N..        ..N.   ....    ....
        
    We notices that we are recursively calculating the last board position
    more than once.  Why?? Memoization addresses this.  Imagine if Nick were to
    write down how many ways he could get to the destination from each 
    intersection.  That would help him tremendously if he ever came to the same 
    interesction. Memoization is like giving Nick a piece of chalk and making 
    him write down how many ways he can get to the interesction.  Instead of 
    walking every possible way to the destination, he can just look at the
    number in chalk.  If the number is not there, then he has to walk it :(
    This would surely save Nick a considerable amount of walking.  He can just
    read the number from the table!
    
    city_grid is initially set to UNKNOWN, this means the pavement has not been
    written on yet.  As he walks around, he writes down how many ways he can
    take to get to the end of the trip.  Intersections that he wants to avoid
    have a 0 in them, because there is no way to get to the destination through
    one of these intersections.  He must fill them all in, but it certainly
    beats the extra walking :)
    
    
    The function walk cycle returns how many ways Nick can get to the 
    destination from the current interesction.
*******************************************************************************/

int WalkCycle(int cur_x, int cur_y,
              const int dest_x, const int dest_y, 
              const int x_dir, const int y_dir,
              int city_grid[MAX_GRID_SIZE][MAX_GRID_SIZE]);

/*******************************************************************************
    main entry point
*******************************************************************************/

int main()
{
    // open the file
    ifstream inFile("paths.in");

    int n; // the number of test cases
    int m; // the number of intersections to avoid (case dependant)
    int p; // the number of trips for the case
    
    // the x, y of an intersection to avoid
    int intersections_x[MAX_INTERSECTIONS];
    int intersections_y[MAX_INTERSECTIONS];
    
    // the city_grid
    int city_grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
    
    // the start and end points
    int start_x, start_y;
    int end_x, end_y;
    
    // which directions can he walk?
    int x_direction, y_direction;
    
    // the answer
    int total;
    
    // how many test cases?
    inFile >> n;
    
    // do the following for each test case
    for(int dataSet = 1; dataSet <= n; dataSet++)
    {
        // how many intersections to avoid?
        inFile >> m;
                
        // what are those intersections?
        for(int intersectionNum = 0; intersectionNum < m; intersectionNum++)
        {
            inFile >> intersections_x[intersectionNum];
            inFile >> intersections_y[intersectionNum];
        }
        
        // how many trips?
        inFile >> p;
        
        cout << "Data Set " << dataSet << ":" << endl << endl;  
        
        for(int testCase = 1; testCase <= p; testCase++)
        {            
            // get the start/end information
            inFile >> start_x >> start_y;
            inFile >> end_x >> end_y;
            
            // which way is he going?
            // it only makes sense to walk TOWARDS the destination
            if(end_x > start_x)
                x_direction = 1;
            else
                x_direction = -1;
                
            if(end_y > start_y)
                y_direction = 1;
            else
                y_direction = -1;
                
            // set the city_grid to UNKNOWN again
            // this is like erasing the pavement
            for(int xIter = 0; xIter < MAX_GRID_SIZE; xIter++)
                for(int yIter = 0; yIter < MAX_GRID_SIZE; yIter++)
                    city_grid[xIter][yIter] = UNKNOWN;
                    
            // now set all of the bad intersection to 0
            // this means that there are NO ways to get from the 
            // destination from these intersections
            for(int avoidNum = 0; avoidNum < m; avoidNum++)
            {
                int tempX = intersections_x[avoidNum];
                int tempY = intersections_y[avoidNum];
                
                city_grid[tempX][tempY] = 0;
            }
            
            // how many ways can he get there?
            // we call the recursive function from the start position
            // it will fill in city_grid as it runs
            total = WalkCycle(start_x, start_y,         // start
                              end_x, end_y,             // destination
                              x_direction, y_direction, // directions
                              city_grid);               // the grid
                     
            // print the result         
            cout << "  Test Case " << testCase << ": ";
            
            // if total is 1, we need to print the result in singular.
            // this just takes care of that little detail
            if(total == 1)
            {
                 cout << "Nick can take 1 perfect path." << endl;
            }
            else
            {
                 cout << "Nick can take " << total << " perfect paths." << endl;
            }
        }
        
        cout << endl;
    }
     
    // close the file and exit
    inFile.close();
    return 0;
}

int WalkCycle(int cur_x, int cur_y,
              const int dest_x, const int dest_y, 
              const int x_dir, const int y_dir,
              int city_grid[MAX_GRID_SIZE][MAX_GRID_SIZE])
{
            
    // now check if we got there!
    // if so, there was 1 way to get there
    // why? well there is exactly one way for you to sit down in your chair 
    // right now... you are doing it already!
    if(cur_x == dest_x && cur_y == dest_y)
        return 1;
        
    // otherwise, find out how many ways if we go both ways possible
    int total = 0;
    
    // this is the memoization code (the look up part)
    // here is where we look at the pavement to see if we already walked
    // there from this intersection.
    if(city_grid[cur_x][cur_y] != UNKNOWN)
        return city_grid[cur_x][cur_y];
        
        
    // now here is the recursive part of the program...
    // we simply add how many ways we can get to the destination provided
    // we walked went either of the valid ways to get to the destination
    
    // go in the y direction, only if it makes sense
    // if we on the same horizontal plane as the destination (east-west road),
    // there is NO REASON AT ALL to try walking because it violates
    // the rules to this problem. make sure you check for it!!!
    if(cur_y != dest_y)
    {
        total += WalkCycle(cur_x, cur_y + y_dir, 
                           dest_x, dest_y,
                           x_dir, y_dir,
                           city_grid);
    }
    
    // likewise, the same thing happens when you are on the same north-south
    // road as the destination
    if(cur_x != dest_x)
    {
        total += WalkCycle(cur_x + x_dir, cur_y, 
                           dest_x, dest_y,
                           x_dir, y_dir,
                           city_grid);
    }
    
    // this is the rest of the memoization code
    // make sure we write the answer in the table!!
    // if it isn't written down then we will recalculate everything!
    // remove this line and run the program if you want to see the difference
    // it makes :)
    // again, the max case was changed, so this is required at all
    city_grid[cur_x][cur_y] = total;
    
    return total;
}

/*******************************************************************************
    eof
*******************************************************************************/

