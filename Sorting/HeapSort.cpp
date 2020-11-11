#include<iostream>
#include<conio.h>
#include"my_time.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
template<class X>
void HeapSort(X *start,int n){
int insertionindex,max = 0;
//BUILIDNG HEAP BY HEAPIFY IN O(N)
for(int i = n-1;i >= 0;i--){
  insertionindex = i;
  while(insertionindex < n){//IF LEFT CHILD OF insertionindex IS VALID THEN NO NEED TO CHECK FOR RIGHT WE CAN DO IT IN LOOP ONLY
    max = insertionindex;  
    if(LEFT(insertionindex) < n && start[LEFT(insertionindex)] > start[max])
      max = LEFT(insertionindex);
    if(RIGHT(insertionindex) < n && start[RIGHT(insertionindex)] > start[max])  
      max = RIGHT(insertionindex);
    if(max != insertionindex){
      X temp = start[insertionindex];
      start[insertionindex] = start[max];
      start[max] = temp;
      }
    else
      break;
    insertionindex = max;
    }
  }
//DELETING AND HENCE GETTING SORTED ORDER
for(int i = n-1;i > 0;i--){
  X temp = *start;
  *start = start[i];
  start[i] = temp;
  insertionindex = 0;
  while(insertionindex < i){//IF LEFT CHILD OF insertionindex IS VALID THEN NO NEED TO CHECK FOR RIGHT WE CAN DO IT IN LOOP ONLY
    max = insertionindex;  
    if(LEFT(insertionindex) < i && start[LEFT(insertionindex)] > start[max])
      max = LEFT(insertionindex);
    if(RIGHT(insertionindex) < i && start[RIGHT(insertionindex)] > start[max])  
      max = RIGHT(insertionindex);
    if(max != insertionindex){
      X temp = start[insertionindex];
      start[insertionindex] = start[max];
      start[max] = temp;
      }
    else
      break;
    insertionindex = max;
    }
  }
}
int main(){
int n;
cout<<"ENTER THE SIZE OF ARRAY YOU WANT: ";
cin>>n;
auto arr = new int[n];
for(int i = 0;i < n;i++)
  arr[i] = rand()%n;
timer t;
HeapSort(arr,n);
t.stop();
getch();
for(int i = 0;i < n;i++)
  cout<<arr[i]<<" ";
cout<<endl;
return 0;
}
