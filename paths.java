import java.io.*;

public class paths
{
 static final double esp=1e-7;
 public static void main(String []args) throws IOException
 {
  //StreamTokenizer works like StringTokenizer, but it takes a Stream and breaks it down 
  //into parts rather then taking a String
  StreamTokenizer stok=new StreamTokenizer(new BufferedReader(new FileReader("paths.in")));
  int N,M,P,data,casecount,x,y,dx,dy,startx,starty,targetx,targety,path[][],i;
  boolean[][] block;
  N=nextInt(stok);
  for(data=1;data<=N;data++)
  {
   //takes care of blank line between Data Set
   out("Data Set "+data+":");
	out("");
	//reads number of intersections to avoid
	M=nextInt(stok);
	//java initialize the entire matrix to false
	block=new boolean[10][10];
	for(i=0;i<M;i++)
	{
    x=nextInt(stok);
	 y=nextInt(stok);
	 block[x][y]=true; //the coordinates read in are blocked
	}
	P=nextInt(stok);
	for(casecount=1;casecount<=P;casecount++)
	{
	 startx=nextInt(stok);
	 starty=nextInt(stok);
	 targetx=nextInt(stok);
	 targety=nextInt(stok);
	 path=new int[10][10];
	 //dx,dy are the directions to move, we can only move 1 direction in x and 1 direction in y
	 //they are either 1 or -1
	 if(targetx>startx) dx=1; else dx=-1;
	 if(targety>starty) dy=1; else dy=-1;
	 //base case is we can only have 1 way to go if we're only going 1 direction only
	 //only goes dx direction, y is fixed to starty
	 for(x=startx;x!=targetx+dx && !block[x][starty];x+=dx) path[x][starty]=1;
	 //similarly here we go for dy only
	 for(y=starty;y!=targety+dy && !block[startx][y];y+=dy) path[startx][y]=1;
	 /*
	 //Now we do recursion on the array, path[x][y] is the 
	 //number of ways to go from (startx,stary) to (x,y)
	 //If you use real recursion, the solution can be timed out easily 
	 //because there are 2 recursive calls (thus making it exponential time)
	 //using array to store the value instead can speed this up, 
	 //this is similar to Fibonacci Numbers Algorithm
	 //The strategy is known as "Dynamic Programming" or "Memorization"
	 
	 //Brute Force Searching all possible paths and counting them will
	 //also be acceptable for this problem size (10). But for bigger grid 
	 //sizes (say 500), Dynamic Programming will be necessary for running 
	 //within time limit
	 */
	 for(x=startx+dx;x!=targetx+dx;x+=dx)
	 {
  	  for(y=starty+dy;y!=targety+dy;y+=dy)
 	  if(!block[x][y]) 
	  { 
	   //if an intersection is not blocked, then we can inherit from
      //the reverse of the 2 directions, and sum up the ways,
		//so you can either go to (x-dx,y) then +dx on x to reach (x,y)
		//or you can go to (x,y-dy) then +dy on y to reach (x,y)
	   path[x][y]=path[x-dx][y]+path[x][y-dy];
	  }
	 }
	 out("  Test Case "+casecount+": Nick can take "+
	                                 //incorrect if used (path[targetx][targety]>1?"s":"") to check
	    path[targetx][targety]+" perfect path"+(path[targetx][targety]==1?"":"s")+".");
	}
    out("");
  }
 }
 
 //This function is to make outputing easier
 public static void out(String s)
 {
  System.out.println(s);
 }
 
 //This function takes the next Token, since we know all data in input
 //are integers, so we can savely assume that a number is scanned and read
 //it from nval field of stok
 public static int nextInt(StreamTokenizer stok) throws IOException
 {
  stok.nextToken();
  return (int)(stok.nval+esp); //+esp is to prevent possible precision errors.
 }
}