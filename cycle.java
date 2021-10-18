import java.io.*;
import java.util.*;

public class cycle
{
	BufferedReader br = null;
	
	public cycle()
	{
		try
		{
			//open the input file
			 br = new BufferedReader(new FileReader("cycle.in"));
		}catch(Exception e) {}	
	}
	
	public void run() throws Exception
	{
		//initialize all variables
		int num = 0;
		int at = -1;
		StringTokenizer st = null;
		String theline = null;
		String token = null;
		
		//initializes the vector to zero elements and it expands by 1 
		//every time it needs to
		Vector thePath = new Vector(0,1);
		
		String theoutput = null;
		int counter = 0;
		
		
		
		do
		{
		
		//read the line from the file	
			theline = br.readLine();
		//split it up by spaces
			st = new StringTokenizer(theline, " ");
			
		//read in the first value and convert it to an integer
			num = Integer.valueOf((String)st.nextToken()).intValue();
		
		//if the end case then end
			if(num == 0) break;
			
		//empty out the vector.
			thePath.clear();
			
		//start output
			theoutput = "Case " + (++counter) + ":";
			
		//go through the number of tokens you're suppose to.	
			for(int i = 0; i < num; i++)
			{
				//get the next element
				token = st.nextToken();
				
				//if we already have it remove everything after 
				//the first occurance so far
				//the index of function returns a negative one when
				//a match is not found
				if((at = thePath.indexOf(token)) != -1)
				{
					//remove everything after the first occurance
					while(thePath.size() > at+1)
						thePath.remove(at+1);					
				}
				else
				{
					//this means that we haven't seen this point before
					//add it to the path list
					thePath.add(token);
				}
			}
			
			//Output the path as shown by the sample
			for(int i = 0; i < thePath.size(); i++)
			{
				theoutput += " " + (String)thePath.get(i);	
			}
			
			System.out.println(theoutput);
			
		}while(true);


		br.close();
			
	}
	
	public static void main(String[] args) throws Exception
	{
		//create  a new instance of the class and call the run function
		cycle t = new cycle();
		t.run();
	}
}