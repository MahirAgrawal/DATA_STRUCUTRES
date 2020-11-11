#include<iostream>
#include<string.h>
#include"my_time.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl
int getPatternIndex(char *text,char *pattern){
  auto n = strlen(text);
  auto m = strlen(pattern);
  cout<<"LENGTH: "<<n<<endl;
  for(int i = 0;i < n;){
    if(text[i] == pattern[0]){
      int j = 0;
      for(j = 0;j < m && j+i < n;j++){
        if(pattern[j] != text[i+j]){
          i++;
	  break;  
	}
      }
      if(j == m)//FOUND THE PATTERN
        return i;
    }
    else
      i++; 
  }
  return -1;
}

int main(){
  cout<<"ENTER THE TEXT: ";
  char *text = new char[2000];
  cin.getline(text,1000);
  cout<<"ENTER THE PATTERN TO FIND IN TEXT: ";
  char *pattern = new char[100];
  cin.getline(pattern,100);
  int index = -1;
  timer t;
  index = getPatternIndex(text,pattern);  
  t.stop();
  cout<<"HEY FOUND YOUR PATTERN AT "<<index<<endl;
  delete []pattern;
  delete []text;
  return 0;
}

