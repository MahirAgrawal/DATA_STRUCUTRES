#include<iostream>
#include<cstdio>
#define cout std::cout
#define cin std::cin
#define endl std::endl
namespace my_stack{
template<class X>
class stack;
template<class X>
class node{
X data;
node *next = NULL;
public:
node()
  {next = NULL;}
node(X d)
  {
  this -> data = d;
  next = NULL;
  }
~node()
  {
  X garbage;
  data = garbage;
  next = NULL;
  }
friend class stack<X>;
};
template<class X>
class stack{
node<X> *head = NULL;
node<X> *tail = NULL;
public:
stack()
  { 
  head = NULL;
  tail = NULL;
  }
void push(X d)
  {
  if(head == NULL)
    {
    head = new node<X>(d);
    tail = head;
    }
  else
    {
    tail -> next = new node<X>(d);
    tail = tail -> next;
    }
  }
X pop()
  {
  X garbage_value;
  if(head == NULL)
    {
    cout<<"THE STACK IS EMPTY GRABAGE VALUE!!";
    return garbage_value;
    }
  X temp_data;
  if(head -> next == NULL)
    {
    temp_data = head -> data;
    delete tail;
    head = NULL;
    tail = NULL;
    }
  else
    {
    node<X> *to_be_deleted = head;
    while(to_be_deleted -> next != tail)
      to_be_deleted = to_be_deleted -> next;
    temp_data = tail -> data;
    delete tail;
    tail = to_be_deleted;
    to_be_deleted -> next = NULL;
    }
  return temp_data;
  }
X peek()
  {
  X garbage;
  if(tail == NULL)
    return garbage;
  else
    return (tail -> data);
  }
void print(node<X> *ptr = NULL)
  {
  if(ptr == NULL)
    {
    ptr = head;
    cout<<"DATA: ";
    }
  if(ptr != tail)
    {
    print(ptr -> next);
    cout<<ptr -> data<<" ";
    }
  else
    cout<<ptr -> data<<" ";
  if(ptr == head)
    cout<<endl;
  }
bool empty()
  {
  if(head == NULL)
    return true;
  else
    return false;
  }
~stack()
  {
  while(head != NULL)
    X temp_temp = pop();
  }
};}
/*int main()
{
my_stack::stack<int> s;
s.push(12);
s.print();
s.push(1);
s.print();
s.push(13);
s.print();
s.push(18);
s.print();
s.push(90);
s.print();
s.push(65);
s.print();
s.push(32);
s.print();
cout<<"EMPTY: "<<s.empty()<<endl;
s.push(46);
s.print();
cout<<s.pop();
cout<<s.pop();
cout<<s.pop();
cout<<s.pop();
s.print();
cout<<"EMPTY: "<<s.empty()<<endl;
cout<<s.pop();
cout<<s.pop();
cout<<s.pop();
s.push(46);
s.print();
s.pop();
s.pop();
cout<<"EMPTY: "<<s.empty()<<endl;
return 0;
}*/
