#include<iostream>
using namespace std;

int gcd,x,y;

void extended_euclid(int a,int b)
{
	if(b==0)
	{
		gcd=a;
		x=1;
		y=0;
		return;
	}
	extended_euclid(b,a%b);
	int x1,y1;
	x1=y;
	y1=x-(a/b)*y;
	x=x1,y=y1;
}

int main()
{
	int a,b;
	cout<<"Enter Two Numbers :";
	cin>>a>>b;
	extended_euclid(a,b);
	cout<<"Gcd("<<a<<","<<b<<") = "<<gcd<<endl;
	cout<<"x = "<<x<<" and y = "<<y<<endl;
}
