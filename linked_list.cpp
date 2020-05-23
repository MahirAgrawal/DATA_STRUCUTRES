#include<cstdio>
#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;
template<class X>
class node{
public:
X data;
node *next = NULL;
node()
{
next = NULL;
}
~node()
{
cout<<"NODE WAS DESTROYED"<<endl;
next = NULL;
}
};
template<class X>
class list{
int index = 0;
node<X> *head;
bool empty = true;
public:
list()
{
index = 0;
head = NULL;
bool empty = true;
}
public:
bool is_empty()
{
return empty;
}
void push_back(X value)
{
if(head == NULL)
	{
	head = new node<X>;
	head -> data = value; 
	head -> next = NULL;
	}
else
	{
	node<X> *ptr = head;
	while((ptr->next) != NULL)
		ptr = (ptr -> next);
	(ptr -> next) = new node<X>;
	ptr = ptr -> next;
	ptr -> data = value;
	ptr -> next = NULL;
	}
index++;
empty = false;
}
void push_front(X value)
{
if(head == NULL)
	{
	head = new node<X>;
	head -> data = value; 
	head -> next = NULL;
	}
else{
node<X> *ptr = new node<X>;
ptr -> data = value;
ptr -> next = head;
head = ptr;
}
index++;
empty = false;
}
void pop_back()
{
if(head == NULL)
	return;
node<X> *ptr = head;
if((ptr -> next) == NULL)
	{
	head = NULL;
	delete ptr;
	}
else{
for(int i = 0;i < (index-2);i++)
	ptr = ptr -> next;
node<X> *temp = ptr -> next;
ptr -> next = NULL;
delete temp;}
index--;
}
void pop_front()
{
if(head == NULL)
	return;
node<X>* ptr = head;
head = head -> next;
delete ptr;
index--;
}
void pop(int i = 0)
{
if(head == NULL)
	return;
if(i >= index || i < 0)
	return;
else if(i == 0)
	pop_front();
else if(i == (index-1))
	pop_back();
else{
	node<X>* temp = head;
	node<X>* ptr = NULL;
	int count = 0;
	while(count < i-1)
	{
	temp = temp -> next;
	count++;
	}
    ptr = temp -> next;
    ptr = ptr -> next;
    delete (temp -> next);
    temp -> next = ptr;
    index--;
    }
}
void push(int i,X value)//pushes the given value at a given index and if provided index larger than the actual index of list which is because of its currents, then the given value will be added to end by default
//for eg. index of list is 4 due to 4 nodes but you give 10th index to be filled then it will by default add given value to end that is at 5th index.
{
if(head == NULL)
	return;
else if(i < 0)
	return;
else if(i == 0)
	push_front(value);
else if(i >= index)
	push_back(value);
else{
	node<X>* temp = head;
	node<X>* ptr = NULL;
	int count = 0;
	while(count < i-1)
	{
	temp = temp -> next;
	count++;
	}
    ptr = temp -> next;
    node<X> *temp_2 = new node<X>;
    temp_2 -> data = value;
    temp_2 -> next = ptr;
    temp -> next = temp_2;
    index++;
    }
}
void operator +(list &l)
{
node<X>* ptr = l.head;
while(ptr != NULL)
	{
	push_back(ptr -> data);
	ptr = ptr -> next;
	}
}
int size()
{
return index;
}
void clear()
{
while(head != NULL)
	pop_back();
}
X at(int i)
{
if(head == NULL)
	return 0;
if(i >= index || i < 0)
	return 0;
else{
	node<X>* temp = head;
	int count = 0;
	while(count != i)
	{
	temp = temp -> next;
	count++;
	}
return (temp -> data);
}
}
void sort()
{
if((head == NULL) || (head -> next == NULL))
	return;
else{
node<X>* ptr = NULL;
node<X>* temp = NULL;
for(int i = 0;i < (index - 1);i++)
{
ptr = head;
temp = ptr -> next;
int count = 0;
	for(int j = 0;j < (index-1-i);j++)
	{
	if((ptr -> data) > (temp -> data))
		{
		X temp_data = ptr -> data;
		ptr -> data = temp -> data;
		temp -> data = temp_data;
		count++;
		}
	ptr = temp;
	temp = temp -> next;
	}
if(count == 0)
	break;
}
}}
void display()
{
if(head == NULL)
	return;
node<X> *ptr = head;
cout<<"ELEMENTS: ";
while(ptr != NULL)
	{
	cout<<(ptr -> data)<<" ";
	ptr = ptr -> next;
	}
cout<<'\n';
}
};
class dog{
char name[20];
float price;
public:
void add()
{
cout<<"ENTER THE NAME OF DOG: ";
cin.getline(name,20,'\n');
cout<<"ENTER THE PRICE OF DOG: ";
cin>>price;
fflush(stdin);
}
int operator <(dog& d)
{
if(this -> price < d.price)
	return 1;
else 
	return 0;
}
int operator >(dog& d)
{
if(price > d.price)
	return 1;
else 
	return 0;
}
~dog()
{
name[0] = 'n';
name[1] = 'u';
name[2] = 'l';
name[3] = 'l';
name[4] = '\0';
price = 0;
cout<<"dog was destroyed"<<endl;
}
};
int main()
{
/*list<dog> l;
for(int i = 0;i < 4;i++)
{
dog *d = new dog;
dog -> add();
l.push_back();
}*/
list<char> l;
l.push_back('m');
l.display();
l.pop_back();
l.display();
cout<<"SIZE:"<<l.size();
l.push_back('i');
l.display();
l.push_front('b');
l.display();
l.pop_front();
l.display();
l.push_back('i');
l.display();
l.push_front('b');
l.display();
l.pop_back();
l.display();
list<char> l2;
cout<<"LIST 2\n";
l2.push_back('i');
l2.display();
l2.push_front('u');
l2.display();
l2.push_front('t');
l2.display();
l2.push_front('r');
l2.display();
l2.sort();
cout<<"sorted:"<<endl;
l2.display();
cout<<l2.at(4)<<endl;
cout<<l2.at(0)<<endl;
cout<<l2.at(1)<<endl;
l + l2;
l.display();
cout<<"SIZE:"<<l.size();
cout<<"sorted:"<<endl;
l.sort();
l.display();
l.pop(3);
l.display();
l.push(0,'x');
l.display();
l.push(3,'x');
l.display();
l.push(0,'x');
l.display();
l.pop(9);
l.display();
cout<<"SIZE:"<<l.size();
l.clear();
l.display();
cout<<"SIZE:"<<l.size();
return 0;
}
