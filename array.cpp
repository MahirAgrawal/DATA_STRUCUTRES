#include<iostream>
#include<cstdio>
#include<cstdlib>
template<class X>
class array{
X *arr = NULL;
X *begin = NULL;
X *end = NULL;
//bool is_empty = true;
bool is_full = false;
int max_size = 16;
int size = 2;
public:
array(int s = 2)
{
begin =  (X *)calloc(s,sizeof(X));
if(begin == NULL)
	{
	printf("ARRAY CANNOT BE ALLOCATED!!\n");
	return;
	}
arr = begin;
end = begin + s - 1;
//is_empty = true;
is_full = false;
}
void resize()
{
if((end - begin + 1) == max_size)
	is_full = true;	
else	
{
arr = realloc(arr,size*sizeof(X));	
end += size;
size *= 2;
}
}
void push_back(X value)
{
if(is_full == true)
{
cout<<"ARRAY IS USED AT IT'S FULL CAPACATIY!!\n"<<endl;	
cout<<"CANNOT ADD MORE ELEMENTS!!"<<endl;
return;
}	
arr[arr-begin] = value;
arr++;
if(arr > end)
	resize(); 
}
void pop_back()
{
if(arr == begin)
{
printf("ARRAY IS EMPTY!!!\n");
return;
}
else
	arr--;
}
void display()
{
X *ptr = begin; 
	while(ptr != arr)
	{
	cout<<"ELEMENTS: "<<*ptr<<" ";
	ptr++;
	}
}
X at(int index)
{
index()
}
};
int main()
{
arra
return 0;
}
