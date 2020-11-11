#include"stack_duplicate.h"
#include<iostream>
#include<stdlib.h>
#include<string.h>
stack<char> exp;
stack<char> temp;
bool is_operator(char c)
{
if(c == '+' || c == '/' || c == '*' || c == '-')
	return true;
else
	return false;
}
void transform(const char *str)
{
int size = strlen(str);
for(int i = 0;i < size;i++)
  { 
  if(is_operator(str[i]))
	  temp.push(str[i]);//pushes operator in seperate stack
  else
   {
   exp.push(str[i]);
   if(i < size-1){
   exp.push(temp.peek());
  // cout<<"I:"<<i;
   temp.pop();}
   }
  }
exp.reverse_display();
}
int main(int argc,char *argv[])
{
cout<<argv[1];
char expression[30];
cin.getline(expression,30);
transform(expression);
return 0;
}
