#include<iostream>
#include<conio.h>
#include<cstdio>
#include<windows.h>
#include<stdlib.h>
#define black 0
#define blue 1
#define light_gray 7
#define white 15
#define yellow 14
#define green 2
#define light_green 10
#define red 4
#define light_red 12
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define fsream std::fstream
#define cerr std::cerr
char* allocate(const char *source)
{
int s = strlen(source);
char *destination = new char[s+1];
strcpy(destination,source);
for(int i = 0;i < s;i++)
{
if(destination[i] == '\n')
{
destination[i] = '\0';
break;
}
}
return destination;
}
void gotoxy(int x,int y)
{
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(h,coord);
}
void HighlightText(int front_color = 12,int back_color = 14)
{
WORD wCOLOR = ((back_color & 0x0F) << 4) + (front_color & 0x0F);
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hStdOut,wCOLOR);
return;
}
int menu(int n,...)
{
COORD coord = {30,10};
int selected = 1;
start:
system("cls");
va_list option_list;
va_start(option_list,n);
HighlightText(1,2);
gotoxy(25,7);
cout<<va_arg(option_list,char *);
HighlightText(light_gray,black);
for(int i = 1;i < n-1;i++)
{
gotoxy(coord.X,coord.Y);
if(i == selected)
{
HighlightText();
cout<<va_arg(option_list,char *);
HighlightText(light_gray,black);
}
else
	cout<<va_arg(option_list,char *);
coord.Y++;
}
gotoxy(5,coord.Y+2);
if(selected == n-1)
{
HighlightText();
cout<<va_arg(option_list,char *);
HighlightText(light_gray,black);
}
else{	
HighlightText(0,15);
cout<<va_arg(option_list,char *);
HighlightText(light_gray,black);
}
va_end(option_list);
int key = getch();
if(key == 13)
	{
	cout<<"\n";
	fflush(stdin);
	fflush(stdin);
	return selected;
	}
else{
key = getch();
switch(key)
	{
		case 72:
			if(selected == 1)
				selected = n - 1;
			else
				selected -= 1;
			break;
		case 77:
			break;
		case 75:
			break;
		case 80:
			if(selected == n-1)
				selected = 1;
			else
				selected += 1;
			break;
	}
coord.X = 30;
coord.Y = 10;
goto start;
}
}
char* menu_plus(const char *file_name)
{
int count = 0;
FILE *f = fopen(file_name,"r");
char name[25];
while((fgets(name,25,f)) != NULL)
{
count++;
}
fclose(f);
f = fopen(file_name,"r");
char* list[count];
int j = 0;
while((fgets(name,25,f)) != NULL)
{
list[j] = allocate(name);
j++;
}
fclose(f);
count -= 1;
COORD coord = {20,5};
int selected = 1;
start:
system("cls");
HighlightText(1,2);
gotoxy(25,2);			
cout<<list[0];
HighlightText(light_gray,black);
for(int i = 1;i < count;i++)
{
gotoxy(coord.X,coord.Y);
if(i == selected)
{
HighlightText();
cout<<list[i];
HighlightText(light_gray,black);
}
else if(i == 1)
{
HighlightText(4,10);
cout<<list[i];
HighlightText(light_gray,black);
}
else
	cout<<list[i];
coord.Y++;
}
gotoxy(5,(coord.Y)+2);
if(selected == count)
{
HighlightText();
cout<<list[count];
HighlightText(light_gray,black);
}
else{	
HighlightText(0,15);
cout<<list[count];
HighlightText(light_gray,black);
}
int key = getch();
if(key == 13)
	{
	cout<<"\n";
	for(int i = 0;i < count;i++)
	{
	if(i == selected)
		continue;
	else{
	delete []list[i];
	}
	}
	return list[selected];
	}
else{
key = getch();
switch(key)
	{
		case 72:
			if(selected == 1)
				selected = count;
			else
				selected -= 1;
			break;
		case 77:
			break;
		case 75:
			break;
		case 80:
			if(selected == count)
				selected = 1;
			else
				selected += 1;
			break;
	}
coord.X = 20;
coord.Y = 5;
goto start;
}
}
//array class
template<class X>
class array{
X *arr = NULL;
X *begin = NULL;
X *end = NULL;
bool is_empty = true;
bool is_full = false;
int max_size_a = 16;
int size_a = 2;
public:
array(int s = 2)
{
begin =  new X[s];
if(begin == NULL)
	{
	printf("ARRAY CANNOT BE ALLOCATED!!\n");
	return;
	}
arr = begin;
end = begin + s - 1;
is_empty = true;
is_full = false;
}
X* begin_p()//return pointer to first element
{
return begin;
}
X* end_p()//return pointer to end index and not the end element
{
return end;
}
X* arr_p()
{
return arr;//return pointer to current writing memory address
}
int size()//returns actual size of array based on filled elements
{
int count = 0;
X *i = begin;
while(i != arr)
	{count++;i++;}
return count;
}
int max_size()
{
return max_size_a;
}
bool resize()
{
if((end - begin + 1) == max_size_a)
	{is_full = true;return false;/*as array is not resized*/}	
else	 
{
X *temp = new X[2*size_a];	
for(int i = 0;i < size_a;i++)
	temp[i] = begin[i];
delete []begin;
begin = temp;
arr = begin + size_a;
size_a *= 2;
end = begin + size_a - 1;
return true;//as array is resized
}
}
void push_back(X value)
{
bool answer = true;
if(arr > end)
	answer = resize();
if(answer == false)
{
cout<<"ARRAY IS USED AT IT'S FULL CAPACATIY!!"<<endl;	
cout<<"CANNOT ADD MORE ELEMENTS!!"<<endl;
return;
}
begin[arr-begin] = value;
is_empty = false;
arr++;
}
void pop_back()
{
if(is_empty)
	return;
else
{
arr--;
if(arr == begin)
	{
	is_empty = true;	
	arr = begin;
	}
}
}
void pop(X *address)
{
if(is_empty)
	return;
if(address < begin || address >= arr)
	{
	cerr<<"POSITION  IS INVALID!!\n";
	return;
	}
int deletions = arr - address - 1; 
for(int i = 0;i < deletions;i++)
	address[i]  = address[i+1];
arr--;
if(arr == begin)
	is_empty = true;
}
void display()
{
if(is_empty)
	{
	cout<<"ARRAY IS EMPTY\n";
	return;
	}
X *ptr = begin; 
cout<<"ELEMENTS: ";
while(ptr != arr)
	{
	cout<<*ptr<<" ";
	ptr++;
	}
cout<<"\n";
}
X at(X *address)
{
if(address < begin || address > arr)
	{
	cout<<"INVALID ADDRESS!\n";
	return -1;
	}
else{
return *address;}
}
void insert(X *address,X value)
{
int address_pos = address - begin;
if(address < begin || address > end)
	{
	cerr<<"POSITION  IS INVALID!!\n";
	return;
	}
bool answer = true;
if(arr > end)
	answer = resize();
if(answer == false)
{
cout<<"ARRAY IS USED AT IT'S FULL CAPACATIY!!"<<endl;	
cout<<"CANNOT ADD MORE ELEMENTS!!"<<endl;
return;
}
else{
address = begin + address_pos;
int insertions = arr - address;
for(int i = insertions;i > 0;i--)
	address[i]  = address[i-1];
address[0] = value;
is_empty = false;
arr++;}
}
void clear()
{
arr = begin;
is_empty = true;
}
~array()
{
delete []begin;
}
};
