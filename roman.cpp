#include<iostream>
#include<string.h>
#include<stdlib.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
class roman{
int roman_num = 0;
char *roman_str = NULL;
int value(char alpha)
{
if(alpha == 'M' || alpha == 'm')
	return 1000;
else if(alpha == 'D' || alpha == 'd')
	return 500;
else if(alpha == 'C' || alpha == 'c')
	return 100;
else if(alpha == 'L' || alpha == 'l')
	return 50;
else if(alpha == 'X' || alpha == 'x')
	return 10;
else if(alpha == 'V' || alpha == 'v')
	return 5;
else if(alpha == 'I' || alpha == 'i')
	return 1;
else{
cout<<"SOMETHING WRONG HAS HAPPENED WITH YOUR INPUT!!!<<endl";
exit(1);
}
}
void set_roman_num(char *s)
{
int *temp_num = NULL;
int size = strlen(s);
//cout<<"SIZE: "<<size<<endl;
temp_num = new int[size];
temp_num[0] = value(s[0]);
for(int i = 0;i < (size-1);i++)
{
if(value(s[i]) < value(s[i+1]))
	{
	cout<<"INSIDE IF..."<<endl;
	temp_num[i] = (-1)*value(s[i]);
	temp_num[i+1] = value(s[i+1]);	
	}
else
	temp_num[i+1] = value(s[i+1]);
}
for(int i = 0;i < size;i++)
	roman_num += temp_num[i];
delete []temp_num;
}
public:
roman()
{
roman_num = 0;
roman_str = NULL;
}
roman(const char *temp_str)
{
roman_str = (char *)temp_str;
set_roman_num(roman_str);
}
void add()
{
char name[10];
cout<<"ENTER THE ROMAN NUMBER: ";
cin>>name;
int size = strlen(name);
roman_str = new char[size+1];
strcpy(roman_str,name);
set_roman_num(roman_str);
}
void display()
{
cout<<"ROMAN NUMBER: "<<roman_str<<endl;
cout<<"DECIMAL EQUIVALENT: "<<roman_num<<endl;
}
};
int main()
{
roman r("XL");
r.display();
roman r2;
r2.add();
r2.display();
r2.add();
r2.display();
r2.add();
r2.display();
r2.add();
r2.display();
}
