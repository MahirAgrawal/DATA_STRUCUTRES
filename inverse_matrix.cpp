#include<iostream>
#include<cmath>
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
return (determinant(arr,order-1));
}
int determinant(int *arr,int order){
  int answer = 0;
  if(order == 1)
    answer = *arr;
  else if(order == 2){
    answer = (arr[0] * arr[3] - arr[1] * arr[2]);
    }
  else{
    for(int i = 0;i < order;i++){
      if(i%2 == 1)
        answer += (-1*arr[i]*cofactor(order,arr,0,i));
      else
        answer += (arr[i]*cofactor(order,arr,0,i));
      }
    }
  return answer;
  }
double* inverse(int *arr,int order){
  int ans = determinant(arr,order);
  if(ans == 0)
    return NULL;
  int *new_matrix = new int[order*order];
  for(int i = 0;i < order;i++){
    for(int j = 0;j < order;j++){
      if(pow(-1,i+j) == -1)
        new_matrix[i*order+j] = -1*cofactor(order,arr,i,j);
      else 
        new_matrix[i*order+j] = cofactor(order,arr,i,j);
      }
    }
  double *ptr = new double[order*order];
  for(int i = 0;i < order;i++){
    for(int j= 0;j < order;j++)
      ptr[i+order*j] = (double)new_matrix[i*order+j];
    }
  delete []new_matrix;
  for(int i = 0;i < order;i++){
    for(int j= 0;j < order;j++)
      ptr[i*order+j] /= ans;
    }
  return ptr;
  }
int main(){
int order = 1;
cout<<"ENTER THE ORDER OF MATRIX: ";
cin>>order;
int arr[order*order];
cout<<"ENTER THE "<<order<<" x "<<order<<"MATRIX: "<<endl;
for(int i = 0;i < order;i++){
  for(int j= 0;j < order;j++)
    cin>>arr[i*order+j];
  cout<<endl;
  }
double *ans = inverse(arr,order);
if(ans == NULL)
  cout<<"DETERMINANT IS ZERO SO INVERSE DOESN'T EXIST!"<<endl;
else{
for(int i = 0;i < order;i++){
  for(int j= 0;j < order;j++)
    cout<<ans[i*order+j]<<" ";
  cout<<endl;
  }
cout<<"\nINVERSE OF ABOVE MATRIX IS:\n"<<endl;
for(int i = 0;i < order;i++){
  for(int j= 0;j < order;j++)
    cout<<ans[i*order+j]<<" ";
  cout<<endl;
  }
}
return 0;
}
