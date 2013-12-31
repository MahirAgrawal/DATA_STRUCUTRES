#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
 
//SUBROUTINE OF MERGING
template<class X>
X* merge(X *arr1,X *arr2,int n1,int n2){

  X *mergedArray = new X[n1+n2];
  int index = 0;
  auto temparr1 = arr1;
  auto temparr2 = arr2;
  while(temparr1 < arr1 + n1 && temparr2 < arr2 + n2){
    if(*temparr1 < *temparr2)
      mergedArray[index++] = *(temparr1++);
    else if(*temparr1 > *temparr2)
      mergedArray[index++] = *(temparr2++);
    else{
      mergedArray[index++] = *(temparr1++);
      mergedArray[index++] = *(temparr2++);
    }
  }

  while(temparr1 < arr1 + n1)
    mergedArray[index++] = *(temparr1++);

  while(temparr2 < arr2 + n2)
    mergedArray[index++] = *(temparr2++);
  return mergedArray;
}

//MERGE SORT ROUTINE
template<class X>
X* mergeSort(X *front,X *end){

  int n = end - front + 1;
  if(n == 1)  //BASE CASE
    return front;
  auto arr1 = mergeSort(front,front+n/2-1);
  auto arr2 = mergeSort(front+n/2,end);

  return (merge(arr1,arr2,(n/2),n-(n/2)));
}

template<class X>
void sort(X *front, X *end){
  X *sortedArray = mergeSort(front,end);
  X *temp = sortedArray;
  while(front <= end)//COPYING SORTED ARRAY ::CAN SKIP THIS STEP AND DIRECTLY RETURN SORTED ARRAY
    *(front++) = *(sortedArray++);
  delete [] temp;
}

/*int main(){
  int n = 7;
  int int_array[n] = {34,23,2,5,3,3222,11};
  char char_array[n] = {'n','f','s','e','w','i','p'};
  double double_array[n] = {4.22,2.5,76.7,54.2,21,9.98,0.23};
 
  cout<<"BEFORE SORT integer array: "<<endl;
  for(int i = 0;i < n;i++)
    cout<<int_array[i]<<" "; 
  sort(int_array,int_array+n-1);
  cout<<"\nAFTER SORT: "<<endl;
  for(int i = 0;i < n;i++)
    cout<<int_array[i]<<" ";

  cout<<"\n\n\nBEFORE SORT character array: "<<endl;
  for(int i = 0;i < n;i++)
    cout<<char_array[i]<<" "; 
  sort(char_array,char_array+n-1);
  cout<<"\nAFTER SORT: "<<endl;
  for(int i = 0;i < n;i++)
    cout<<char_array[i]<<" ";

  cout<<"\n\n\nBEFORE SORT double array: "<<endl;
  for(int i = 0;i < n;i++)
    cout<<double_array[i]<<" "; 
  sort(double_array,double_array+n-1);
  cout<<"\nAFTER SORT: "<<endl;
  for(int i = 0;i < n;i++)
    cout<<double_array[i]<<" ";
  return 0;
}
*/
