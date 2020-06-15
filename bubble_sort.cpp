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
  }
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
//bubble_sort<int>(arr,arr+99);
selection_sort(arr,arr+9);//OKAY TO NOT TO MENTION DATATYPES IN FUNCTIONS
for(int i = 0;i < 10;i++)
  cout<<arr[i]<<" ";
cout<<endl;
char str[11] = {'m','i','h','i','r','l','a','g','r','a','\0'};
//bubble_sort<char>(str,str+9);
selection_sort(str,str+9);//OKAY TO NOT TO MENTION DATATYPES IN FUNCTIONS
cout<<str<<endl;
point p[10] = {{3,5},{2,3},{53,2},{1,2},{-13,32},{3,5},{2,6},{4,6},{9,4},{35}};
//bubble_sort<point>(p,p+9);
//cout<<"compare:"<<p[0]!=p[1]<<" "<<p[1]!=p[6]<<" "<<p[0]!=p[5]<<endl;
selection_sort(p,p+9);//OKAY TO NOT TO MENTION DATATYPES IN FUNCTIONS
for(int i = 0;i < 10;i++)
  cout<<(p[i])<<" ";
return 0;
}
