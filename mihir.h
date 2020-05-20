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
