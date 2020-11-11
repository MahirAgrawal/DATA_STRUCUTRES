#include<iostream>
#include<string>
#include"Stack.h"
#define Stack My_Stack::Stack
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl std::endl
//DONE BY STACK OF STRINGS 
//FIRST WE COLLECT OPERANDS BY SCANNING FROM LEFT TO RIGHT
//THEN IF WE ENCOUNTER A 'OPERATOR' THEN WE FETCH TOP TWO OPERANDS FROM STACK AND CONCANATE OPERATOR AT BEGIN OF THOSE TWO OPERANDS   LIKE THIS : A B * -> * A B
//ADDED ERROR CHECKING ALSO WHICH CHECKS FOR MISSING OPERATOR OR OPERAND AND ALSO ACCEPTS MULTI DIGIT NUMBER
bool is_operand(char c){
  if(c >= '0' && c <= '9')
    return true;
  else
    return false;
  }
bool is_operator(char c){
  if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    return true;
  else
    return false;
  }
string Postfix_Prefix(string& postfix){
  Stack<string> exp;string number;
  for(int i = 0;i < postfix.length();i++){
    if(is_operand(postfix[i])){
      while(i < postfix.length() && is_operand(postfix[i])){ 
        number += postfix[i];
	i++;
        }
      exp.push(number);
      number.clear();
      i--;
      }
    else if(is_operator(postfix[i])){
      string num1,num2;
      if(!exp.empty()){
        num2 = ' ' + exp.peek();
        exp.pop();
        }
      else{
        cout<<"MISSING OPERAND!!"<<endl;
	return "";
        }
      if(!exp.empty()){
        num1 = ' ' + exp.peek();
	exp.pop();
        }
      else{
        cout<<"MISSING OPERAND!!"<<endl;
	return "";
        }
      number = postfix[i] + num1 + num2;
      exp.push(number);
      num1.clear();num2.clear();
      number.clear();
      }
    else if(postfix[i] == ' ');
    else{
      cout<<"NO CHARACTERS ALLOWED OTHER THAN OPERATORS AND NUMBER(OPERANDS)!!"<<endl;
      return "";
      }
    }
  number = exp.peek();
  exp.pop();
  if(exp.empty())
    return number;
  else{
    cout<<"MISSING OPERATOR!!"<<endl;
    return "";
    }
  }
int main(){
string postfix;
cout<<"POSTFIX: ";
getline(cin,postfix);
cout<<"PREFIX: "<<Postfix_Prefix(postfix)<<endl;
return 0;   
}
