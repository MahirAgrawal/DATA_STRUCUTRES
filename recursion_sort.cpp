#include<iostream>
#include<cstdio>
#define endl std::endl
#define cout std::cout
#define cin std::cin
int arr[10] = {55,4,3232,22,12,45,33,69,54,332};
char str[11] = {'m','i','h','i','r','a','g','r','a','w','\0'};
template<class X>
void swap(X *a,X *b)
{
X temp = *a;
*a = *b;
*b = temp;
}
template<class X>
void recursion_sort(X *start,X *end)
{
int n = end - start + 1;
if(n == 1 || n <= 0)
  return;
else//just place the largest at end and smallest at start of list
  {
  X *temp = start;
  X *max = end;
  X *min = start;
  for(int i = 0;i < n ;i++)
    {
    if(*max < temp[i])
      max = temp + i;
    }
    if(max != end)
      swap(max,end);
   for(int i = 0;i < n ;i++)
    {
    if(*min > temp[i])
      min = temp + i;
    }
    if(min != start)
      swap(min,start);
  recursion_sort(start+1,end-1);//again i.e. second time calling same fuction with smaller list so now largest and smallest of this list actually becomes second largest and second smallest so second largest and second smallest are placed at coorect position in this call and then if this was the third time function call then the list would be smaller and in it third largest and third smallest are placed at their correct position
  return;
  }
}
int main()
{
for(int i = 0;i < 10;i++)
  arr[i] = 10-i;
recursion_sort(arr,arr+9);
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<endl;
cout<<"Original:"<<str<<endl;
recursion_sort(str,str+9);
cout<<str;
return 0;
}
