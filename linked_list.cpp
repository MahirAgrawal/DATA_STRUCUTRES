#include<cstdio>
#include<iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;
template<class X>
class node{
public:
X *ptr = NULL;
X data;
void display()
{
cout<<"DATA:"<<data<<":"<<(unsigned int)&(this->data)<<endl;
printf("PTR:%u\n",ptr);
}
};
template<class X>
class list{
public:
X head;
node<X> n;
void display()
{
cout<<"HEAD:"<<head<<endl;
n.display();
}
};
int main()
{
node<char>n;
n.data = 'c';
n.ptr = &(n.data);
n.display();
list<char>l;
l.head = 'g';
l.n.data = 'f';
l.n.ptr = &(l.n.data);
l.display();
node<int> *ptr = new node<int>;
ptr -> data = 34;
ptr -> ptr = &(ptr -> data);
ptr -> display();
return 0;
}
