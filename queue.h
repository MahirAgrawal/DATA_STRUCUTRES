#include<iostream>
#include<cstdio>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define MAX_INDEX 50
namespace my_queue{
template<class X>
class parent_queue;
template<class X>
class node{
node<X> *previous;
X data;
node<X> *next;
public:
node()
{
previous = NULL;
next = NULL;
}
~node()
{
previous = NULL;
next = NULL;
}
friend class parent_queue<X>;
};
template<class X>
class parent_queue{
node<X> *head;
node<X> *tail;
int index = 0;
public:
parent_queue()
  {
  cout<<"CONSTRUCTOR WAS CALLED!!"<<endl;
  int index = 0;
  head = NULL;
  tail = NULL;
  }
void atfirst(X d)
  {
  head = new node<X>;
  head -> previous = NULL;
  head -> data = d;
  head -> next = NULL;
  tail = head;
  }
void enqueue_rear(X d)
  {
  if(index >= MAX_INDEX)
    {
    cout<<"QUEUE OVERFLOW!!"<<endl;
    return;
    }
  if(head == NULL)
    atfirst(d);
  else
    {
    node<X> *ptr = new node<X>;
    ptr -> next = NULL;
    ptr -> data = d;
    ptr -> previous = tail;
    tail -> next = ptr;
    tail = ptr;
    }
  index++;
  }
void enqueue_front(X d)
  {
  if(index >= MAX_INDEX)
    {
    cout<<"QUEUE OVERFLOW!!"<<endl;
    return;
    }
  if(head == NULL)
    atfirst(d);
  else
    {
    node<X> *ptr = new node<X>;
    ptr -> previous = NULL;
    ptr -> data = d;
    ptr -> next = head;
    head -> previous = ptr;
    head = ptr;
    }
  index++;
  }
void dequeue_front()
  {
  if(head == NULL)
    printf("QUEUE UNDERFLOW\n");
  else
    {
    if(head == tail)
      clear();
    else
      {
      node<X> *ptr = head;
      head = head -> next;
      head -> previous = NULL;
      delete ptr;
      index--;
      }
    }
  }
void dequeue_rear()
  { 
  if(head == NULL)
    {
    cout<<"QUEUE UNDERFLOW!!\n"<<endl;
    return;
    }
  else
    {
    if(head == tail)
	    clear();
    else
      {
      node<X> *ptr = tail -> previous;
      ptr -> next = NULL;
      delete tail;
      tail = ptr;
      index--;
      }
    }
  }
int size()
  {
  return index;
  }
void display()
  {
  node<X> *ptr = head;
  while(ptr != NULL)
    {
    cout<<ptr -> data<<" ";
    ptr = ptr -> next;
    }
  cout<<endl;
  }  
X seek()
{
return head -> data;
}
void clear()
  {
  if(head == NULL);
  else if(head == tail)
    delete head;
  else
    {
    node<X> *ptr = head;
    node<X> *ptr_2 = ptr;
    for(int i = 0;i < index;i++)
      {  
      ptr_2 = ptr -> next;
      delete ptr;
      ptr = ptr_2;
      }
    }
  head = NULL;
  tail = NULL;
  index = 0;
  }
  bool is_empty()
  {
  if(head == NULL)
    return true;
  else
    return false;
  }
  X peek()
  {
  return (head -> data);	  
  }
~parent_queue()
  {
  clear();
  }
};
template<class X>
class queue:public parent_queue<X>{
public:
void enqueue(X d)
  {
  this -> enqueue_rear(d);
  }
void dequeue()
  {
  this -> dequeue_front();
  }
void show()
  {
  this -> display();
  }
int get_size()
  {
  this -> size();
  }
void delete_queue()
  {
  this -> clear();
  }
};}
/*int main()
{
my_queue::queue<int> q;
cout<<"MYNAME"<<endl;
q.enqueue(12);
cout<<q.peek()<<endl;
//q.show();
q.enqueue(13);
//q.show();
cout<<q.peek()<<endl;
q.enqueue(14);
q.show();
q.enqueue(15);
q.show();
q.enqueue(16);
q.show();
q.enqueue(17);
q.show();
q.enqueue(18);
q.show();
q.enqueue(19);
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
q.dequeue();
q.show();
cout<<q.get_size()<<endl;
q.dequeue();
q.show();
cout<<q.get_size()<<endl;
q.dequeue();
q.show();
q.dequeue();
q.show();
return 0;
}*/
