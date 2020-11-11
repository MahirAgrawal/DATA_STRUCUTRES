#include<iostream>
#include<cstdio>
#define cout std::cout
#define cin std::cin
#define endl std::endl
namespace my_queue{
template<class X>
class queue;
template<class X>
class node{
X data;
node *next = NULL;
public:
node()
  {
  next = NULL;
  }
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
friend class queue<X>;
};
template<class X>
class queue{
node<X> *head = NULL;
node<X> *tail = NULL;
public:
queue()
  { 
  head = NULL;
  tail = NULL;
  }
void enqueue(X d)
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
X dequeue()
  {
  X garbage_value;
  if(head == NULL)
    {
    cout<<"THE QUEUE IS EMPTY GRABAGE VALUE!!";
    return garbage_value;
    }
  X temp_data;
  if(head -> next == NULL)
    {
    temp_data = head -> data;
    delete head;
    head = NULL;
    tail = NULL;
    }
  else
    {
    node<X> *to_be_deleted = head;
    temp_data = head -> data;
    head = head -> next;
    delete to_be_deleted;
    }
  return temp_data;
  }
void print()
  {
  cout<<"DATA: ";
  node<X> *ptr = head;
  while(ptr != NULL)
    {
    cout<<ptr -> data<<" ";
    ptr = ptr -> next;
    }
  cout<<endl;
  }
bool empty()
  {
  if(head == NULL)
    return true;
  else
    return false;
  }
~queue()
  {
  while(head != NULL)
    X temp_temp = dequeue();
  }
};
}
/*int main()
{
my_queue::queue<int> q;
q.enqueue(34);
q.enqueue(75);
q.enqueue(3);
q.enqueue(45);
q.enqueue(12);
q.print();
cout<<q.dequeue();
q.print();
cout<<"empty:"<<q.empty()<<endl;
q.print();
cout<<q.dequeue()<<"empty:"<<q.empty()<<endl;
q.print();
cout<<q.dequeue()<<"empty:"<<q.empty()<<endl;
q.print();
cout<<q.dequeue();
cout<<"empty:"<<q.empty()<<endl;
q.print();
cout<<q.dequeue();
cout<<"empty:"<<q.empty()<<endl;
q.print();
cout<<q.dequeue();
cout<<"empty:"<<q.empty()<<endl;
q.print();
return 0;
}*/
