#include<iostream>
#include<conio.h>
#include<chrono>
#define cout std::cout
#define ccin std::cin
#define endl std::endl
template<class X>
void swap(X *a,X *b)
{
if(a == b)
  return;
X temp = *a;
*a = *b;
*b = temp;
}
template<class X>
void quick_sort(X *start,X *end)
{
if(end - start == 0)
  return;
X *new_position = start;
X *temp = start;
while(temp != end)
  {
  if(*temp <= *end)
    {
    swap(new_position,temp);
    new_position++;
    }
  temp++;
  }
swap(new_position,temp);
if(new_position != end)
  quick_sort(new_position+1,end);
if(new_position != start)
  quick_sort(start,new_position-1);
}
int main()
{
int n = 10000;
int arr[n];
srand(n);
for(int i = 0;i < n;i++)
  arr[i] = rand()%100000;
/*for(int i = 0;i < n;i++)
  cout<<arr[i]<<" ";*/
cout<<"click to sort"<<endl;
getch();
auto start = std::chrono::high_resolution_clock::now();
quick_sort(arr,arr+n-1);
auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
cout<<"TIME TAKEN: "<<duration.count()<<endl;
cout<<"sorted!! click to print";
getch();
for(int i = 0;i < n;i++)
  cout<<arr[i]<<" ";
cout<<endl;
return 0;
}
