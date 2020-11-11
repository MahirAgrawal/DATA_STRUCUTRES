#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
template<class X>
void swap(X *a,X *b)
{
X temp = *a;
*a = *b;
*b = temp;
}
template<class X>
void insertion_sort(X *start,X *end)
{
int n = end - start + 1;
for(int i = 0;i < n;i++)
  {
  for(int j = i;j > 0;j--)
    {
    if(start[j] < start[j-1])
      swap(start+j,start+j-1);
    else
      break;
    }
  }
}
int main()
{
int arr[10];
for(int i = 0;i < 10;i++)
  cin>>arr[i];
insertion_sort(arr,arr+9);
cout<<'\n';
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<'\n';
char str[6] = {'m','i','h','i','r','\0'};
insertion_sort(str,str+4);
cout<<str<<'\n';
return 0;
}
