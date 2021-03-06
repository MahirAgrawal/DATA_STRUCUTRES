#include<bits/stdc++.h>
using namespace std;

//gives the same behavior as c++ stl upper_bound in O(log2N)
//IT DOES THIS BY REMEMBERING THE LAST LARGER VALUE THAN GIVEN ELEMENT IT HAS SEEN IN THE 'ELSE' CONDITION
//THE INITIAL VALUE OF UPPER BOUND IS -1
//NOW IF IT HAS SEEN A LARGER VALUE THAN ELEMENT THEN LIKE IN BINARY SEARCH IT WILL REDUCE THE END = MIDDLE-1 HENCE
//SEARCHING FOR ELEMENT IN LEFT OF ITS LARGER VALUE ADDITIONALLY FOR UPPER BOUND IT WILL ALSO NOTE THE LAST ELEMENT
//LARGER THAN ELEMENT. NOW AFTER NOTING DOWN THE VALUE IT GOES TO LEFT OF MIDDLE INDEX TO FIND THE ELEMENT
//SO AGAIN IF IT ENCOUNTERS A INDEX WHICH IS LARGER THAN ELEMENT THEN IT NOTES DOWN THE INDEX BECAUSE WE WANT
//SMALLEST NUMBER JUST LARGER THAN ELEMENT SO WE WILL NOTE THE LEFTEST GREATER VALUE AND AGAIN DO END = MIDDLE -1
//TO SEARCH THE ELEMENT IN LEFT AND SO ON..
//
//ALSO IF WE FOUND THAT ELEMENT, THEN ALSO WE DON'T STOP AND TRY TO FIND GREATER ELEMENT BY GOING TO MIDDLE+1 THAT
//IS TO THE RIGHT SO THAT WE CAN GET A GREATER NUMBER THAN ELEMENT
//
//ALSO THERE MIGHT BE A CASE WHERE WE CANNOT FIND NUMBER GREATER THAN ELEMENT THAT IS ALL NUMBERS ARE SMALLER THAN
//ELEMENT SO IN THIS CASE ONLY START VALUE WILL CHANGE AND NOT THE END VALUE AND SO WE WILL ALWAYS GO TO 
//RIGHT OF MIDDLE INDEX AND HENCE WILL NEVER GO INSIDE ELSE CONDITION SO GREATER VALUE WILL BE -1 
//WHICH REPRESENT THAT GREATER VALUE DOESN'T EXIST
int UpperBound(vector<int>& top,int ele){
  int index = -1;
  int start = 0,end = top.size()-1,middle;
  while(start <= end){
    middle = (start+end)/2;
    if(ele == top[middle])
      start = middle + 1;

    else if(ele > top[middle])
      start = middle+1;
    else{
      end = middle-1;
      index = middle;
    }
  }
  
  return index;
}


int main(){
  return 0;
}

