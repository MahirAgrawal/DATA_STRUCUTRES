#include<iostream>
#include"stack_duplicate.h"
#include<string.h>
stack<char> temp;
stack<char> exp;
bool is_operator(char c)
{
if(c == '/' || c == '*' || c == '+' || c == '-')
	return true;
else
	return false;
}
void transform(const char *str)
{
int size = strlen(str);
for(int i = size - 1;i >= 0;i--)//to read from right to left as postfix expression
  {
  if(is_operator(str[i]))
		  temp.push(str[i]);
  else if(str[i] == ' ')
	  continue;
  else{
  exp.push(str[i]);
  if(i > 0){
  exp.push(temp.peek());
  temp.pop();}
  }
  }
exp.display();
}	
int main()
{
char expression[30];
cout<<"ENTER THE POSTFIX EXPRESSION: ";
cin.getline(expression,30);
transform(expression);
return 0;
}

