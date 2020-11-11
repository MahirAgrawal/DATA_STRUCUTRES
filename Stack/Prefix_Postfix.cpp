#include<iostream>
#include<algorithm>
#include<string>
#include"Stack.h"
#define Stack My_Stack::Stack
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl std::endl
//DONE BY STACK OF STRINGS 
//FIRST WE COLLECT OPERANDS BY SCANNING FROM RIGHT TO LEFT
//THEN IF WE ENCOUNTER A 'OPERATOR' THEN WE FETCH TOP TWO OPERANDS FROM STACK AND CONCANATE OPERATOR AT END   OF THOSE TWO OPERANDS LIKE THIS : * A B -> A B *
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
string Prefix_Postfix(string& prefix){
  Stack<string> exp;string number;
  for(int i = prefix.length()-1;i >= 0;i--){
    if(is_operand(prefix[i])){
      while(is_operand(prefix[i])){ 
        number += prefix[i];
	i--;
        }
      reverse(number.begin(),number.end());
      exp.push(number);
      number.clear();
      i++;
      }
    else if(is_operator(prefix[i])){
      if(!exp.empty()){
        number = exp.peek() + ' ';
        exp.pop();
        }
      else{
        cout<<"MISSING OPERAND!!"<<endl;
	return "";
        }
      if(!exp.empty()){
        number +=  exp.peek() + ' ' + prefix[i];
	exp.pop();
        }
      else{
        cout<<"MISSING OPERAND!!"<<endl;
	return "";
        }
      exp.push(number);
      number.clear();
      }
    else if(prefix[i] == ' ');
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
string prefix;
cout<<"PREFIX: ";
getline(cin,prefix);
cout<<"POSTFIX: "<<Prefix_Postfix(prefix)<<endl;
return 0;   
}
