#include<iostream>
#include<cmath>
#include"my_time.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl

int* countingSort(int *arr,int n,int baseplace){
  
  auto frequency = (int*) calloc(10,sizeof(int));
  for(int i = 0;i < n;i++){
    int index = arr[i]/pow(10,baseplace);
    index %= 10;
    frequency[index]++;
  }
  
  for(int i = 1;i < 10;i++)
    frequency[i] += frequency[i-1];
   
  auto sortedArray = new int[n];
  for(int i = n-1;i >= 0;i--){
    int index = arr[i]/pow(10,baseplace);
    index %= 10;
    sortedArray[--frequency[index]] = arr[i];
  }
  
  delete []arr;
  free(frequency);
  return sortedArray;
}

void RadixSort(int *arr,int n){ 
  int max  = *arr;
  for(int i = 1;i < n;i++)
    if(*(arr+i) > max)
      max = *(arr+i);
  
  int i = 0;
  auto sortedArray = new int[n];
  for(int i = 0;i < n;i++)
    sortedArray[i] = arr[i];
  while(max != 0){
    sortedArray = countingSort(sortedArray,n,i);
    max /= 10;
    i++;
  }

  for(int i = 0;i < n;i++)
    arr[i] = sortedArray[i];
}

/*
int main(){
  int n;
  cout<<"ENTER THE NUMBER OF ELEMENTS: ";
  cin>>n;
  int *arr = new int[n];
  srand((unsigned int)arr);
  cout<<"ENTER THE ELEMENTS: "<<endl;

  for(int i = 0;i < n;i++)
    //cin>>arr[i];
    arr[i] = rand()%10000;

  
  timer t;
  RadixSort(arr,n);
  t.stop();
  cout<<"SIZE:"<<sizeof(int)<<" "<<sizeof(int *)<<endl;
  cout<<"done!!"<<endl;
  return 0;
}
*/
