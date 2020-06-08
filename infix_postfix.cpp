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
bool is_operand(char c)
{
if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'|| c == '6'|| c == '7'|| c == '8'|| c == '9')
	return true;
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
        exp.push(' ');
	temp.pop();
	}
   temp.push(str[i]);
   }
 else if(str[i] == '('){
     temp.push(str[i]);
     }
 else if(str[i] == ')')
     {
     while(temp.peek() != '(')
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
          i++;
          }
     exp.push(' ');
     i--;     
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
stack<int> e;//for converting integer equivalent of characters in postfix expression
int sum = 0;int total = 0;
while(!temp_s.is_empty())//while our postfix expression stack is not empty
 {
 if(is_operand(temp_s.peek()))
     {
     sum = 0;
     while(is_operand(temp_s.peek()))//converts number from character to integer equivalent
        {
	sum = sum * 10 + temp_s.peek() - '0';
	temp_s.pop();//pops the postfix expression stack
	}
     e.push(sum);
     temp_s.pop();//pops space which comes immediately after number
     }
 else if(is_operator(temp_s.peek()))
     {
     total = 0;
     if(temp_s.peek() == '+')
       {
       total += e.peek();//picks first integer from e stack
       e.pop();//as picked so pops it because we want next number below it
       total += e.peek();//we picks second integer form e stack and do operation on it as per the condition : addition
       e.pop();//like earlier we pop it right away
       }
     else if(temp_s.peek() == '-')
       {
       total += e.peek();
       e.pop();
       total = e.peek() - total;
       e.pop();
       //same operations as in :addition
       }
     else if(temp_s.peek() == '*')
       {
       total += e.peek();
       e.pop();
       total *= e.peek();
       e.pop();
       //same
       }
     else if(temp_s.peek() == '/')
       {
       total += e.peek();
       e.pop();
       total = e.peek()/total;
       e.pop();
       //same
       }
     e.push(total);//after performing operation on two top integers we put answer on top of e stack only
     temp_s.pop();//poping space immediately after operator sign in postfix stack
     }
 else if(temp_s.peek() == ' ')//for unexpected spaces
     temp_s.pop();
 }
return (e.peek());//returns main answer as it is stored on top of e stack
}
int  main()
{
char expression[100];
cout<<"ENTER THE INFIX EXPRESSION: ";
cin.getline(expression,100);
transform(expression);
exp.reverse();
exp.display();
cout<<"RESULT : "<<evaluate(exp)<<'\n';
return 0;
}
