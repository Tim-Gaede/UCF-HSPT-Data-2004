import java.util.*;
import java.io.*;

public class hug{

	/* Normally, it is a bad idea to have the main function
	 *   throw an Exception.  But doing this eliminates the 
	 *   need for try-catch blocks around file I/O operations
	 **/
	public static void main(String[] args) throws Exception{

		int h, w, P, x, y, d;		// input variables
		int best_count, current_count;
		BufferedReader br;		// reads in the file
		StringTokenizer tok;		// parses input
		Person[] people;		// keeps track of people data

		/* create the buffered reader to be used for reading
		 *   in the input file
		 **/
		br  = new BufferedReader(new FileReader("hug.in"));

		/* we'll break out of this loop when the w and h values
		 *   both equal zero
		 **/
		while(true){

			/* read in the w and h values, and break out of the
			 *   while loop if they both equal zero
			 **/
			tok = new StringTokenizer(br.readLine());
			w = Integer.parseInt(tok.nextToken());
			h = Integer.parseInt(tok.nextToken());
			if(h==0&&w==0) break;

			/* read in the P value
			 * the trim() function is called here to remove all
			 *   leading and trailing spaces
			 * create the people array of size P
			 **/
			P = Integer.parseInt(br.readLine().trim());
			people = new Person[P];

			/* read in all of the people
			 * call the Person(x,y,d) constructor to create a new person
			 **/
			for(int i = 0; i < P; i++){
				tok = new StringTokenizer(br.readLine());
				x = Integer.parseInt(tok.nextToken());
				y = Integer.parseInt(tok.nextToken());
				d = Integer.parseInt(tok.nextToken());
				people[i] = new Person(x, y, d);
			}

			/* this is the main algorithm
			 * the outer loop goes from 0 to h
			 * at each one of these lines across the area, 
			 *   we count the number of people within range
			 *   to hug Ali
			 * notice that there is no need to use any 
			 *   point to line distance formulas
			 **/
			best_count = 0;
			for(int i = 0; i <= h; i++){
				current_count = 0;
				for(int j = 0; j < P; j++){
					if(people[j].y - people[j].d <= i &&
					   people[j].y + people[j].d >= i){
						current_count++;
					}
				}
				best_count = Math.max(best_count, current_count);
			}
			System.out.println("Ali can get " + best_count + " hug(s)!");
		}

	}

	/* this class is used to keep track of the data for each person
	 * there is actually no need to keep track of the x-coord of a
	 *   person, but it's kept track of just to make the program
	 *   more readable
	 **/
	private static class Person{

		int x, y, d;

		public Person(int x_param, int y_param, int d_param){

			this.x = x_param;
			this.y = y_param;
			this.d = d_param;

		}

	}

}