#include"stack_duplicate.h"
#include<string.h>
stack<char> exp;//original stack on which prefix expression is written
stack<char> temp;//to push and pop operators
bool is_operator(char c)
{
if(c == 42 || c == 43 || c == 45 || c == 47)
	return true;
else 
	return false;
}
bool compare(char a,char b)
{
if(a == '*' || a == '/')
	{
	if(b == '*' || b == '/')
		return false;
	else 
		return true;
	}
else
	return false;
}
void transform(const char *str)
{
int s = strlen(str)-1;
for(int i = s;i >= 0;i--)
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
	else if(str[i] == ')')
		    temp.push(str[i]);
	else if(str[i] == '(')
	    	{
		while(temp.peek() != ')')
			{
			exp.push(temp.peek());
			temp.pop();
			}
		temp.pop();
		}
	else if(str[i] == ' ')
		continue;
	else{exp.push(str[i]);}
//cout<<"SIZE:"<<temp.size()<<"I:"<<i<<endl;
	 }
while(!temp.is_empty())
	{
	exp.push(temp.peek());
	temp.pop();
	}
}
int main()
{
char expression[30];
cin.getline(expression,30);
fflush(stdin);
transform(expression);
exp.display();
cout<<endl;
//exp.display();
return 0;
}
