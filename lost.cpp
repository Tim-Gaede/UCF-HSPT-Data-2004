#include <fstream>   //for file input
#include <iostream>  //for screen output
#include <cmath>      //for trigonometric functions
#include <cstring>    //for string compare

using namespace std;

//this is the data structure for a landmark
struct place
{
 char name[16];  //extra space for '\0', recommend to put more extra spaces in general
 double x,y;     //all calculations will be in double
};

//this function search the landmark with the given name
int find(place *v,int len,char *name)
{
 int i;
 for(i=0;i<len;i++)
 if(!strcmp(v[i].name,name)) //strcmp(a,b)==0 if a and b are same literal string (!0->1)
   return i; 
 return -1000;
}

//this function computes x,y coordinate of intersection of 2 given lines a and b
//where line a is in the from (ax,ay)+(at)*(adx,ady), line b similar
//the lines are assumed to be non-parallel from input specification
void inter(double ax,double ay,double adx,double ady,
	   double bx,double by,double bdx,double bdy,double &x,double &y)
{
 //we use Cramer's Rule
 double det,at;
 det=ady*bdx-adx*bdy;
 at=((ax-bx)*bdy+(by-ay)*bdx)/det; //we are guarateed to have det!=0 by non-parallelism
 x=ax+at*adx;
 y=ay+at*ady;
}

int main()
{
 ifstream cin("lost.in");//open input file
 cout.precision(0);      //0 decimal places
 cout.setf(ios::fixed);  //prevent scientific notation output
 int i,j,loc1,loc2,M,N;
 char name1[16],name2[16];
 double angle1,angle2,px,py;
 const double pi=acos(-1.0),esp=1e-7;
 place v[100]; //holds all landmarks
 //read landmarks
 cin>>M;
 for(i=0;i<M;i++)
 {
  cin>>v[i].name>>v[i].x>>v[i].y;
 }
 //read test cases
 cin>>N;
 for(i=0;i<N;i++)
 {
  cin>>name1>>angle1>>name2>>angle2;
  //search for landmark, thus to retrieve their locations
  loc1=find(v,M,name1);
  loc2=find(v,M,name2);
  //convert angles to normal angle starts from x-axis and increases counter-clockwise
  //then convert angles to radians
  angle1=(90-angle1)/180*pi;
  angle2=(90-angle2)/180*pi;
  //find intersection
  inter(v[loc1].x,v[loc1].y,cos(angle1),sin(angle1),
        v[loc2].x,v[loc2].y,cos(angle2),sin(angle2),px,py);
  //the +esp is to avoid "-0" when the negatives are caused by precision error
  cout<<"The team is lost at "<<px+esp<<", "<<py+esp<<"!"<<endl;
 }
 return 0;
}
