#include<iostream>
#include<conio.h>
#include<cstdio>
#include<windows.h>
#include"mihir.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define MAX_ROW 25
#define MAX_COLUMN 80
#define MIN_ROW 0
#define MIN_COLUMN 0
void mark(int x,int y,char marking = '*')
{
COORD point;
point.X = x;point.Y = y;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(h,point);
cout<<marking;
}
void axes()
{
for(int i = MIN_ROW;i < MAX_ROW;i++)
	mark(MIN_COLUMN,i,'|');	
for(int i = MIN_COLUMN;i < MAX_COLUMN;i++)
	mark(i,MAX_ROW-1,'_');
}
struct line_info{
public:
float slope = 0;
char type = '?';
};
class line{
int a = 0,b = 0,c = 0;
line_info info;
void set_slope()
{
if((this -> b) == 0)
	(this -> info).type = 'V';
else if((this -> a) == 0)
	{
	(this -> info).type = 'H';
	(this -> info).slope = 0;
	}
else
	(this -> info).slope = (((-1) * a)/(b));
}
public:
line()
{
a = 0,b = 0,c = 0;
}
line(int a,int b,int c)
{
this -> a = a;
this -> b = b;
this -> c = c;
set_slope();
}
void set()
{
cout<<"ENTER THE a's COEFFICIENT: ";
cin>>a;
cout<<"ENTER THE b's COEFFICIENT: ";
cin>>b;
cout<<"ENTER THE c's COEFFICIENT: ";
cin>>c;
cout<<"YOUR LINE IS SET!!";
set_slope();
}
void display()
{
cout<<"THE EQUATION OF LINE: "<<a<<"x"<<" + "<<b<<"y"<<" = "<<c<<endl;
cout<<"THE SLOPE OF LINE: "<<slope<<endl;
}
void operator =(line &l)
{
cout<<"OPERATOR WAS CALLED!!"<<endl;
a = l.a;
b = l.b;
c = l.c;
}
bool operator ==(line &l)
{
if((a == l.a) && (b == l.b) && (c == l.c))
	return true;
float k1,k2,k3;
if(a >= l.a)
	k1 = a/l.a; k2 = b/l.b; k3 = c/l.c;
else
	k1 = l.a/a; k2 = l.b/b; k3 = l.c/c;
if((k1 == k2) && (k1 == k3))
	return true;
}
bool operator ?(line& l)
{

}
};
int main()
{
line l(12,4,3);
l.display();
line l2;
l2 = l;
l2.display();
//axes();
//getch();
return 0;
}
