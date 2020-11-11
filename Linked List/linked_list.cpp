#include<cstdio>
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<string.h>
using namespace std;
template<class X>
class list;
template<class X>
class node{
private:
X data;
node *next = NULL;
node()
{
next = NULL;
}
~node()
{
//cout<<"NODE WAS DESTROYED"<<endl;
next = NULL;
}
friend class list<X>;
};
template<class X>
class list{
int index;
node<X> *head;
bool empty;
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
void push_back(X& value)
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
void push_front(X& value)
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
void push(int i,X& value)//pushes the given value at a given index and if provided index larger than the actual index of list which is because of its currents, then the given value will be added to end by default
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
void swap(int index1 = -1,int index2 = -1)
{
if(index1 >= index || index1 < 0 || index2 >= index || index2 < 0)
	return;
else{
node<X>* ptr1 = head;
node<X>* ptr2 = head;
for(int  i = 0;i < index1;i++)
	ptr1 = ptr1 -> next;
for(int  i = 0;i < index2;i++)
	ptr2 = ptr2 -> next;
X temp_data = ptr1 -> data;
ptr1 -> data = ptr2 -> data;
ptr2 -> data = temp_data;
}
}
node<X>* get_head()
{
return head;
}
void reverse()
{
node<X>* ptr1 = head;
node<X>* ptr2 = NULL;
node<X>* ptr3 = NULL;
ptr2 = (ptr1 -> next);
(ptr1 -> next) = NULL;
ptr3 = ptr1;
ptr1 = ptr2;
while(ptr1 != NULL)
{
ptr2 = (ptr1 -> next);
ptr1 -> next = ptr3;
ptr3 = ptr1;
ptr1 = ptr2;
}
head = ptr3;
}
void reverse(node<X> *ptr)
{
node<X>* ptr1 = ptr -> next; 
if((ptr1 -> next) == NULL)
	{
	head = ptr1;
	ptr1 -> next = ptr;
	return;
	}
else{
reverse(ptr -> next);
ptr1 -> next = ptr;
}
ptr -> next = NULL;
}
void reverse(int index1 = 0,int index2 = - 1)
{
if(index1 >= index || index1 < 0 || index2 >= index || index2 < 0)
	return;
if(index2 - index1 < 0)
	{
	int temp = index1;
	index1 = index2;
	index2 = temp;
	}
if(index2 - index1 == 0 || index2 - index1 == 1)
	{
	if(index2 - index1 == 1)
		{
		swap(index1,index2);
		}
	}
else
	{
	reverse(index1 + 1,index2 - 1);
	swap(index1,index2);
	}
}
void display()
{
if(head == NULL)
	return;
node<X> *ptr = head;
while(ptr != NULL)
	{
	std::cout<<(ptr -> data);
	cout<<"\n";
	ptr = ptr -> next;
	}
cout<<'\n';
}
};
//linked list is class but 
//before using it for storing your user defined class,do the following:
//create '<' and '>' overloaded functions in your class for sort function 
//create '=' overloaded function in your class for copying values from one variable to another
//create friend function of ostream in which '<<' is overloaded to display data in object
//BELOW FULL EXAMPLE IS GIVEN OF DOG CLASS AND '<<' OVERLOADED  
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
void operator =(dog& d)
{
//cout<<"= was CALLED!!!!\n";
strcpy(name,d.name);
price = d.price;
}
~dog()
{
name[0] = 'n';
name[1] = 'u';
name[2] = 'l';
name[3] = 'l';
name[4] = '\0';
price = 0;
//cout<<"dog was destroyed"<<endl;
}
friend ostream& operator <<(ostream &out,const dog& d);
};
ostream& operator <<(ostream &out,const dog& d)
{
cout<<"I WAS USED!!!\n";
out<<"NAME OF DOG: "<<d.name<<endl;
out<<"PRICE OF DOG: "<<d.price<<endl;
return out;
}

int main()
{
list<dog> l;
for(int i = 0;i < 4;i++)
{
dog *d = new dog;
d -> add();
l.push_back(*d);
delete d;
}
l.sort();
l.display();
dog *d = new dog;
d -> add();
l.push(3,*d);
cout<<"BEFORE SWAP..."<<endl;
l.display();
delete d;
cout<<"AFTER REVERSE..."<<endl;
l.reverse(l.get_head());
//l.reverse(0,l.size()-1);
//l.swap(1,2);
l.display();
//l.swap(6,7);
//cout<<"REVERSING FROM 2 TO 4..."<<endl;
/*l.reverse(2,4);
l.display();*/
l.clear();
return 0;
}
