#include<iostream>
#include<conio.h>
#include<cstdio>
#include<windows.h>
#include"mihir.h"
#include<math.h>
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
void gotoxy(COORD point)
{
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(h,point);
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
else	{
	  (this -> info).slope = (((-1) * a)/(b));
	  (this -> info).type = 'U';
	}
}
public:
line()
{
a = 0,b = 0,c = 0;
info.type = '?';
info.slope = 0;
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
cout<<"THE SLOPE OF LINE: "<<info.slope<<endl;
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
if(!(*this||l))
	return false;
float k1,k2,k3;
if(info.type == 'V' && l.info.type == 'V')
	{
	if(a == l.a)
		return true;
	else
		return false;
	}
else if(info.type == 'H' && l.info.type == 'H')
	{
	if(b == l.b)
		return true;
	else
		return false;
	}
else if(info.type == 'U' && l.info.type == 'U')
	{ 
	if((a == l.a) && (b == l.b) && (c == l.c))
		return true;
	if(c == 0 && l.c == 0)
	{
	k1 = a/l.a;
	k2 = b/l.b;
	if(k1 == k2)
		return true;
	else
		return false;
	}
	else if(c == 0 || l.c == 0)
	{
	if(c == 0){
		k1 = a/l.a;
		k2 = b/l.b;
		k3 = c/l.c;
		}
	else if(l.c == 0){
		k1 = l.a/a;
		k2 = l.b/b;
		k3 = l.c/c;
		}
	if(k1 == k2 && k1 == k3)
		return true;
	else
		return false;
	}
	else{
	k1 = l.a/a;
	k2 = l.b/b;
	k3 = l.c/c;
	if((k1 == k2) && (k1 == k3))
		return true;
	else
		return false;
	}
}}
bool operator ||(line& l)
{
if(info.type == 'V' && l.info.type == 'V')
	return true;
else if(info.type == 'H' && l.info.type == 'H')
	return true;
else if(info.type == 'U' && l.info.type == 'U')
	{
	if(info.slope == l.info.slope)
		return true;
	}
return false;
}
void graph()
{
system("cls");
int iteration = 0;
axes();
COORD *point = new COORD[100];
if(a == 0){
iteration = 80;
for(int i = 0;i < MAX_COLUMN;i++)
	{
	point[i].X = i;
	point[i].Y = 25 - floor(c/b);
	}
}
else if(b == 0){
iteration = 25; 
for(int i = 0;i < MAX_ROW;i++)
	{
	point[i].X = floor(c/a);
	point[i].Y = i;
	}
}
else{
int trial = 0;
for(int i = 0;i < 80;i++)
	{
	trial = floor((c - (a*i))/b);
	if(trial < MIN_ROW || trial > MAX_ROW)  
		continue;
	point[i].X = i;
	point[i].Y = 25 - trial;
	iteration++;
	}
}
HighlightText(14,0);
for(int i = 0;i < iteration;i++)
	{
	gotoxy(point[i]);
	cout<<"*";
	}
HighlightText(7,0);
delete []point;
}
};
int main()
{
line l;
l.set();
l.display();
l.graph();
getch();
/*
line l2;
l2.set();
l2.display();
if(l2 == l)
	cout<<"SAME"<<endl;
if(l2 || l)
	cout<<"PARALLEL"<<endl;
cout<<floor(4.5)<<endl;*/
return 0;
}
