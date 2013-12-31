#include<iostream>
#include<math.h>
#include"my_time.h"
#include<string.h>
//#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl

//TO CALCULATE HASH FOR THE FIRST TIME
unsigned int getHash(int prime,char *pattern,int length){
  auto l = length;
  unsigned int hash = 0;
  for(int i = 0;i < l;i++){
    hash += pattern[i]*pow(prime,i);
  }
  return hash;
}

//ipos = OLD HASH'S FIRST INDEX TO REMOVE AND jpos = NEW INDEX TO ADD THE CHARACTER TO FORM NEW HASH
//lengthofPattern = TO GET THE POWER FOR RAISING AT NEW INDEX POSITION'S CHARACTER
unsigned int reHash(int prime,unsigned int oldHash,char *text,int ipos,int jpos,int lengthofPattern){
  oldHash -= text[ipos];
  //cout<<"OLD HASH :" <<oldHash<<endl;
  //getch();
  oldHash /= prime;
  //cout<<"OLD HASH :" <<oldHash<<endl;
  //getch();
  //cout<<"TEXT[JPOS]: "<<text[jpos]<<" "<<lengthofPattern-1<<endl;
  oldHash += (text[jpos] * pow(prime,lengthofPattern-1));
  //cout<<"OLD HASH :" <<oldHash<<endl;
  //getch();
  return oldHash; 
}

bool match(char *text,char *pattern,int start,int lengthofPattern){
  //cout<<"COLLISION: "<<start;
  //cout<<text+start<<endl;
  for(int i = start;i <	 lengthofPattern;i++)
    if(text[i] != pattern[i])
      return false;
  return true;
}

//n = length of text   m = length of pattern
int getMatchingPosition(char *text,char *pattern){
  auto n = strlen(text);
  auto m = strlen(pattern);
  cout<<"STRLEN TEXT: "<<n<<endl;
  int prime = 3;
  if(m > n){
    cout<<"PATTERN IS LARGER THAN TEXT ITSELF!!"<<endl;
    return -1;
  }
  auto patternHash = getHash(prime,pattern,m);//PATTERN HASH TO MATCH WITH EVERY HASH
  auto textHash = getHash(prime,text,m);//HASH OF FRONT LETTERS WHOSE LENGTH EQUAL TO PATTERN
  //cout<<"HASH ORIGINAL: "<<patternHash<<" TEXT HASH: "<<textHash<<endl;
  for(int i = 0,j = m-1;j < n;){
    if((textHash == patternHash) && match(text,pattern,i,m)){
      return i;
    }
    else{ 
      if(j < n - 1)
        textHash = reHash(prime,textHash,text,i,j+1,m);
      //cout<<"NEW HASH: "<<textHash<<endl;
      i++,j++;
    }
  }
  return -1;
}

int main(){
  cout<<"ENTER THE TEXT: ";
  char *text = new char[2000];
  cin.getline(text,2000);
  cout<<"ENTER THE PATTERN TO FIND IN TEXT: ";
  char *pattern = new char[100];
  cin.getline(pattern,100);
  int index = -1;
  timer t;
  index = getMatchingPosition(text,pattern);  
  t.stop();
  cout<<"HEY FOUND YOUR PATTERN AT "<<index<<endl;
  delete []pattern;
  delete []text;
  return 0;
}

