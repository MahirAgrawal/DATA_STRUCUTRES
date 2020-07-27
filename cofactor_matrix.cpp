#include<iostream>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
int determinant(int *,int);
int cofactor(int order,int *ptr,int row,int column){
int arr[(order-1)*(order-1)];
int counter_i = 0,counter_j = 0;
for(int i = 0;i  < order;i++){
  if(i == row)
    continue;
    counter_j = 0;
    for(int j = 0;j < order;j++){
    if(j == column)
      continue;
    else{
      arr[counter_i*(order-1)+counter_j] = *(ptr+i*order+j);
      counter_j++;
      }
    }
  counter_i++;
  }
/*for(int i = 0;i < order-1;i++){
  for(int j = 0;j < order-1;j++)
    cout<<arr[i*(order-1)+j]<<" ";
  cout<<endl;
  }*/
int answer = determinant(arr,order-1);
return answer;
}
int determinant(int *arr,int order){
  int answer = 0;
  if(order == 1)
    answer = *arr;
  else if(order == 2){
    answer = (arr[0] * arr[3] - arr[1] * arr[2]);
    //cout<<"ANSWER:"<<answer<<endl;
    //getch();
    }
  else{
    for(int i = 0;i < order;i++){
      if(i%2 == 1)
        answer += (-1*arr[i]*cofactor(order,arr,0,i));
      else
        answer += (arr[i]*cofactor(order,arr,0,i));
      }
    }
  //cout<<"FINAL ANSWER:"<<answer<<endl;
  return answer;
  }
int main(){
int order = 3;
/*int arr[order*order] = {1,2,3,4,5,6,7,8,9};
for(int i = 0;i < order;i++)
  for(int j = 0;j < order;j++)
    cout<<cofactor(order,arr,i,j)<<" ";
order = 2;
int array[order*order] = {1,2,3,4};
for(int i = 0;i < order;i++)
  for(int j = 0;j < order;j++)
    cout<<cofactor(order,array,i,j);
*/
order = 4;
int array_2[order*order] = {11,12,23,33,23,3,23,43,54,54,54,33,33,33,33,32};
//cout<<"ORDER 4:"<<endl;
/*for(int i = 0;i < order;i++){
  for(int j = 0;j < order;j++)
    cout<<cofactor(order,array_2,i,j)<<" ";
  cout<<endl;
  }*/
cout<<"DETERMINANT:"<<determinant(array_2,4)<<endl;
order = 5;
int array_3[order*order] = {12,1,2,3,13,4,3,2,4,25,54,56,54,6,4,3,2,5,4,6,3,23,23,1,0};
cout<<"DETERMINANT:"<<determinant(array_3,5)<<endl;
return 0;
}
