#include<string.h>
#include"stack_duplicate.h"
stack<char> exp;
stack<char> temp;
bool is_operator(char o)
{
if(o == '+' || o == '-' || o == '*' || o == '/')
	return true;
else
	return false;
}
bool compare(char a,char b)
{
if(a == '*' || a == '/')
	return true;
else if(a == '+' || a == '-')
	{
	if(b == '+' || b == '-')
		return true;
	else
		return false;
	}
else
	return false;
}
void transform(const char *str)
{
int s = strlen(str);
for(int i = 0;i < s;i++)
 {
 if(is_operator(str[i]))
   {
   if(temp.is_empty());
   while(compare(temp.peek(),str[i]))
   	{
	exp.push(temp.peek());
	temp.pop();
	}
   temp.push(str[i]);
   }
 else if(str[i] == '(')
     temp.push(str[i]);
 else if(str[i] == ')')
     {
     while(temp.peek() != '(')
     	{
	exp.push(temp.peek());
	temp.pop();
	}
     temp.pop();
     }
 else
     exp.push(str[i]);
 }
while(!temp.is_empty())
 {
 exp.push(temp.peek());
 temp.pop();
 }
}
int  main()
{
char expression[30];
cin.getline(expression,30);
transform(expression);
exp.reverse_display();
return 0;
}
