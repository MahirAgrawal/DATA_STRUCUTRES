#include<iostream>
#include<string.h>
#include"my_time.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl
//KMP ALGORITHM TO FIND PATTERN IN STRING IN O(N) WHERE N IS THE LENGTH OF STRING

//PREPROCCESSED TABLE IN O(M) WHERE 'M' IS THE LENGTH OF PATTERN GIVEN
short int* getSkipTable(char *pattern,int length){//GET THE TABLE TO KNOW WHERE TO SKIP WHEN THERE MISMATCH
  auto l = length;
  auto table = (short int*)calloc(sizeof(short int) , l);  
  table[0] = 0;//SETTING 0th INDEX'S JUMP = 0
  for(int i = 0,j = 1; j < l; ){
    if(pattern[i] == pattern[j]){
      table[j] = i+1;
      i++,j++;
    }
    else{
      if(i > 0) 
        i = table[i-1];
      else{
        table[j] = 0;
        j++;
      }
    }
  }
  return table;
}

//FUNCTION WHICH ACTUALLY GETS THE INDEX OF MATCHED PATTERN
int getPatternIndex(char *text,char *pattern){
  auto n = strlen(text);
  auto m = strlen(pattern);
  if(m > n){//IF PATTERN ITSELF IS LARGER THAN TEXT SO NOT POSSIBLE
    cout<<"PATTERN IS LARGER THAN TEXT!!"<<endl;
    throw ("PATTERN OVERSIZED THAN TEXT ITSELF");
  } 

  auto table = getSkipTable(pattern,m);

  for(int i = 0,j = 0; i < n;){
    if(text[i] == pattern[j])
      i++,j++;
    else{
      if(j > 0)
        j = table[j-1];
      else
        i++;
    }

    if(j == m)//FOUND AND MATCHED ALL CHARACTERS IN PATTERN SO FOUND PATTERN
      return (i-m);
  }
  free(table);
  return -1;//PATTERN NOT FOUND
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
  try{
    index = getPatternIndex(text,pattern);  
    t.stop();
  }
  catch(const char *str){
    cout<<str<<endl;
  }
  cout<<"HEY FOUND YOUR PATTERN AT "<<index<<endl;
  delete []pattern;
  delete []text;
  return 0;
}

