#include<iostream>
#include<cstdio>
#define cout std::cout
#define cin std::cin
#define endl std::endl
template<class X>
void swap(X *a,X *b)
{
X data = *a;
*a = *b;
*b = data;
}
template<class X>
X* merge(X *arr1,X *end1,X *arr2,X *end2)
{
int n1 = end1 - arr1 + 1;
int n2 = end2 - arr2 + 1;
X *new_arr = new X[n1+n2]; 
int i = 0;
while(arr1 && arr2)
  {
  if(*arr1 < *arr2)
    {
    new_arr[i] = *arr1;
    arr1++;
    i++;
    }
  else if(*arr1 > *arr2)
    {
    new_arr[i] = *arr2;
    arr2++;
    i++;
    }
  else if(*arr1 == *arr2)
    {
    new_arr[i] = *arr1;i++;arr1++;
    new_arr[i] = *arr2;i++;arr2++;
    }
  if(arr1 > end1)
    arr1 = NULL;
  if(arr2 > end2)
    arr2 = NULL;
  }
if(arr1)
  {
  for(int k = i;k < (n1+n2);k++,arr1++)
    new_arr[k] = *arr1;
  }
if(arr2)
  {
  for(int k = i;k < (n1+n2);k++,arr2++)
    new_arr[k] = *arr2;
  }
return new_arr;
}
template<class X>
X* merge_sort(X *start,X *end)
{
//cout<<(unsigned int)start<<":"<<(unsigned int)end<<endl;
int n = end - start;
if(n == 0)
  return start;
else
  {
  X *arr1 = start;
  X *end1 = start + n/2;
  X *arr2 = start + n/2 + 1;
  X *end2 = end;
  arr1 = merge_sort(arr1,end1);
  arr2 = merge_sort(arr2,end2);
  X *arr = merge(arr1,arr1+n/2,arr2,arr2+n-(n/2)-1);
  //cout<<"merged into:"<<(unsigned int)arr<<"merged:"<<(unsigned int)arr1<<" "<<(unsigned int)(arr1+n/2)<<" "<<(unsigned int)arr2<<" "<<(unsigned int)(arr2+n-(n/2)-1)<<"N:"<<n<<endl;
  //delete []arr1;
  //delete []arr2;
  return arr;
  }
}
int main()
{
int n = 10e4;
int arr[n];
for(int i = 0;i < n;i++)
  arr[i] = n - i;
for(int i = 0;i < 100;i++)
  cout<<arr[i]<<" ";
cout<<endl;
int *arr2 = merge_sort(arr,arr + n - 1);
cout<<"sorted"<<endl;
for(int i = 0;i < 100;i++)
  cout<<arr2[i]<<" ";
cout<<endl;
char str[12] = {'m','i','h','i','r','a','g','r','a','w','a','l'};
//cout<<"start:"<<(unsigned int)arr<<":"<<(unsigned int)(arr+4)<<endl;
int *a = merge_sort(arr,arr+4);
for(int i = 0;i < 5;i++)
  cout<<a[i]<<" ";
char *str2 = merge_sort(str,str+11);
for(int i = 0;i < 12;i++)
  cout<<str2[i];
cout<<endl;
}
