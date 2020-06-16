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
void bubble_sort(X *start,X *end)
{
int flag = 0,count_swap = 0;
int n = end - start + 1;
for(int i = 0;i < n-1;i++)
  {
  count_swap = 0;
  for(int j = 0;j < n-1-i;j++)
    {
    if(*(start+j) > *(start+j+1))
      {
      swap<X>(start+j,start+j+1);
      count_swap++;
      }
    }
  if(!count_swap)
    {  
    flag = 1;
    break;
    }
  }
  if(flag)
    cout<<"BREAKED DUE TO SORTED!!";
}
class point{
int x,y;
public:
point(int x = 0,int y = 0)
{
this -> x = x;this -> y = y;
}
bool operator >(point& p)
{
if(x > p.x)
  return true;
else
  return false;
}
bool operator !=(point& p)
{
if(x != p.x)
  return true;
else if(y != p.y)
  return true;
else
  return false;
}
~point()
{
x = 0;y = 0;
}
friend ostream& operator <<(ostream& obj,point& p);
};
ostream& operator <<(ostream& obj,point& p)
{
obj<<"["<<p.x<<" "<<p.y<<"]";
return obj;
}
int main()
{
int arr[10] = {0};
for(int i = 0;i < 10;i++)
  arr[i] = 10-i;
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<endl;
cout<<"starting!!";
bubble_sort<int>(arr,arr+9);
cout<<"EXECUTED!!";
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<endl;
char str[11] = {'m','i','h','i','r','l','a','g','r','a','\0'};
bubble_sort<char>(str,str+9);
cout<<str<<endl;
point p[10] = {{3,5},{2,3},{53,2},{1,2},{-13,32},{3,5},{2,6},{4,6},{9,4},{35}};
bubble_sort<point>(p,p+9);
for(int i = 0;i < 10;i++)
  cout<<(p[i])<<" ";
cout<<"completed!!";
return 0;
}
