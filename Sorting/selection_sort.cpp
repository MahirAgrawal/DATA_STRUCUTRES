#include<iostream>
#include<cstdio>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define ostream std::ostream
template<class X>
void swap(X *ptr1,X *ptr2)
{
X data = *ptr1;
*ptr1 = *ptr2;
*ptr2 = data;
}
template<class X>
selection_sort(X *start,X *end)
{
int n = end - start + 1;
X *max = start;
for(int i = 0;i < n-1;i++)
  { 
  for(int j = 0;j < n-i;j++)
    { 
    if(start[j] > *max)
      max = start+j;
    }
    if(max != start+n-1-i)
      swap(max,start+n-1-i);
    else
      max = start;
  }
}
int main()
{
int arr[10] = {0};
for(int i = 0;i < 10;i++)
  arr[i] = 10-i;
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<endl;
//bubble_sort<int>(arr,arr+99);
selection_sort(arr,arr+9);//OKAY TO NOT TO MENTION DATATYPES IN FUNCTIONS
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<endl;
char str[11] = {'m','i','h','i','r','l','a','g','r','a','\0'};
selection_sort(str,str+9);//OKAY TO NOT TO MENTION DATATYPES IN FUNCTIONS
cout<<str<<endl;
return 0;
}
