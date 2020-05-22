/*template<class X>
class array{
X *arr = NULL;
X *begin = NULL;
X *end = NULL;
bool is_empty = true;
bool is_full = false;
int max_size = 16;
int size_a = 2;
public:
array(int s = 2)
{
begin =  new X[s];
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
X* begin_p()
{
return begin;
}
X* end_p()
{
return end;
}
X* arr_p()
{
return arr;
}
int size()
{
int count = 0;
X *i = begin;
while(i != arr)
	{count++;i++;}
return count;
}
bool resize()
{
if((end - begin + 1) == max_size)
	{is_full = true;return false;as array is not resized}	
else	 
{
X *temp = new X[2*size_a];	
for(int i = 0;i < size_a;i++)
	temp[i] = begin[i];
delete []begin;
begin = temp;
arr = begin + size_a;
size_a *= 2;
end = begin + size_a - 1;
return true;//as array is resized
}
}
void push_back(X value)
{
bool answer = true;
if(arr > end)
	answer = resize();
if(answer == false)
{
cout<<"ARRAY IS USED AT IT'S FULL CAPACATIY!!"<<endl;	
cout<<"CANNOT ADD MORE ELEMENTS!!"<<endl;
return;
}
begin[arr-begin] = value;
is_empty = false;
arr++;
}
void pop_back()
{
if(is_empty)
	return;
else
{
arr--;
if(arr == begin)
	{
	is_empty = true;	
	arr = begin;
	}
}
}
void pop(X *address)
{
if(is_empty)
	return;
if(address < begin || address >= arr)
	{
	cerr<<"POSITION  IS INVALID!!\n";
	return;
	}
int deletions = arr - address - 1; 
for(int i = 0;i < deletions;i++)
	address[i]  = address[i+1];
arr--;
if(arr == begin)
	is_empty = true;
}
void display()
{
if(is_empty)
	{
	cout<<"ARRAY IS EMPTY\n";
	return;
	}
X *ptr = begin; 
cout<<"ELEMENTS: ";
while(ptr != arr)
	{
	cout<<*ptr<<" ";
	ptr++;
	}
cout<<"\n";
}
X at(X *address)
{
if(address < begin || address > arr)
	{
	cout<<"INVALID ADDRESS!\n";
	return -1;
	}
else{
return *address;}
}
void insert(X *address,X value)
{
int address_pos = address - begin;
if(address < begin || address > end)
	{
	cerr<<"POSITION  IS INVALID!!\n";
	return;
	}
bool answer = true;
if(arr > end)
	answer = resize();
if(answer == false)
{
cout<<"ARRAY IS USED AT IT'S FULL CAPACATIY!!"<<endl;	
cout<<"CANNOT ADD MORE ELEMENTS!!"<<endl;
return;
}
else{
address = begin + address_pos;
int insertions = arr - address;
for(int i = insertions;i > 0;i--)
	address[i]  = address[i-1];
address[0] = value;
is_empty = false;
arr++;}
}
void clear()
{
arr = begin;
is_empty = true;
}
~array()
{
delete []begin;
}
};*/
#include"mihir.h"
int main()
{
array<char> marks;
marks.push_back('m');
marks.display();
marks.push_back('i');	
marks.display();
marks.push_back('h');
marks.display();
marks.push_back('i');
marks.display();
marks.pop_back();
marks.display();
marks.insert(marks.begin_p()+1,'r');
marks.display();
marks.insert(marks.begin_p()+3,'t');
marks.display();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.pop_back();
marks.display();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.pop_back();
marks.display();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.pop_back();
marks.display();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.pop_back();
marks.display();
marks.pop_back();
marks.display();
marks.pop_back();
marks.display();
marks.pop_back();
marks.display();
marks.push_back('e');
marks.display();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.push_back('u');
marks.display();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.clear();
cout<<"MARKS' SIZE:"<<marks.size()<<endl;
marks.display();
marks.push_back('m');
marks.display();
marks.push_back('m');
marks.display();
marks.pop(marks.begin_p()+0);
//cout<<marks.at(marks.begin_p()+10);
marks.display();
marks.pop(marks.begin_p()+0);
marks.display();
cout<<marks.max_size()<<endl;
return 0;
}
