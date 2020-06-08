#include"stack_duplicate.h"
#include<string.h>
stack<char> exp;//original stack on which prefix expression is written
stack<char> temp;//to push and pop operators
bool is_operand(char c)
{
if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'|| c == '6'|| c == '7'|| c == '8'|| c == '9')
	return true;
else
	return false;
}
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
	exp.push(' ');
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
	exp.push(' ');
	temp.pop();
	}
      temp.pop();
     }
   else if(is_operand(str[i]))
     {
     while(is_operand(str[i]))
       {
       exp.push(str[i]);
       i--;
       }
     exp.push(' ');
     i++;
     }
   else{};
  }
while(!temp.is_empty())
  {
  exp.push(temp.peek());
  exp.push(' ');
  temp.pop();
  }
}
int evaluate(stack<char>& temp_s)
{
stack<int> e;
stack<char> temp_temp;
int integer = 0,answer = 0,index = 0;
while(!temp_s.is_empty())
  {
  if(is_operand(temp_s.peek()))
    {
    while(is_operand(temp_s.peek()))
      {
      temp_temp.push(temp_s.peek());
      temp_s.pop();
      }
    integer = 0;
    index = temp_temp.size();
    for(int i = 0;i < index;i++)
      {
      integer = integer * 10 + (temp_temp.peek() - '0');
      temp_temp.pop();
      }
    temp_temp.clear();
    cout<<"INTEGER: "<<integer<<endl;
    e.push(integer);
    temp_s.pop();
    }
  else if(is_operator(temp_s.peek()))
    {
     answer = 0;
     if(temp_s.peek() == '+')
       {
       answer += e.peek();
       e.pop();
       answer += e.peek();
       e.pop();
       }
     else if(temp_s.peek() == '-')
       {
       answer += e.peek();
       e.pop();
       answer -= e.peek();
       e.pop();
       }
     else if(temp_s.peek() == '*')
       {
       answer += e.peek();
       e.pop();
       answer *= e.peek();
       e.pop();
       }
     else if(temp_s.peek() == '/')
       {
       answer += e.peek();
       e.pop();
       answer /= e.peek();
       e.pop();
       }
     e.push(answer);
     temp_s.pop();
    }
  else if(temp_s.peek() == ' ')
    temp_s.pop();
  }
return e.peek();
}
int main()
{
char expression[100];
cout<<"ENTER THE INFIX EXPRESSION: ";
cin.getline(expression,100);
fflush(stdin);
transform(expression);
cout<<"PREFIX EQUIVALENT: ";
exp.display();
exp.reverse();
cout<<"RESULT: "<<evaluate(exp);
return 0;
}
