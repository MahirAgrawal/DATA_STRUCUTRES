#include<iostream>
#include<cstdio>
#include<cstdlib>
template<class X>
class array{
X *arr = NULL;
X *begin = NULL;
X *end = NULL;
bool is_empty = true;
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
is_empty = true;
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
is_empty = false;
arr++;
if(arr > end)
	resize(); 
}
void pop_back()
{
if(is_empty)
{
printf("ARRAY IS EMPTY!!!\n");
return;
}
else
	{
	arr--;
	if(arr == begin)
		is_empty = true;	
	}
}
void display()
{
X *ptr = begin; 
	while(ptr != arr)
	{
	cout<<"ELEMENTS: "<<*ptr<<" ";
	ptr++;
	}
//
cout<<"ARR"<<arr<<endl;
cout<<"BEGIN:"<<begin<<endl;
cout<<"END:"<<end<<endl;
cout<<"IS_EMPTY"<<is_empty<<endl;
cout<<"IS_FULL"<<is_full<<endl;
cout<<"MAX_SIZE:"<<max_size<<endl;
cout<<"SIZE:"<<size<<endl;
//
}
X& at(int index)
/*{
X& temp = begin[index];
return temp;
}*/
};
int main()
{
array<int> marks;
marks.push_back(122);
marks.display();
marks.push_back(22);
marks.display();
marks.push_back(12);	
marks.display();
marks.push_back(143);
marks.display();
marks.push_back(233);
marks.display();
marks.push_back(1111);
marks.display();
return 0;
}
