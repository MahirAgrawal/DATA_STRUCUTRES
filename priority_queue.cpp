#include<iostream>
#include<string.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define MAX_INDEX 50


//PRIORITY IN BASED ON: LOWER THE NUMBER , HIGHER THE PRIORITY
template<class X>
class p_queue;
template<class X>
class node{
int priority = 0;
X data;
node *next = NULL;
public:
node()
  {
  priority = 0;
  next = NULL;
  }
~node()
  {
  priority = 0;
  next = NULL;
  }
friend class p_queue<X>;
};
template<class X>
class p_queue{
node<X> *head = NULL;
node<X> *tail = NULL;
int index = 0;
public:
void atfirst(X d,int p)
  {
  node<X> *ptr = new node<X>;
  ptr -> data = d;
  ptr -> next = NULL;
  ptr -> priority = p;
  head = ptr;
  tail = ptr;
  index++;
  }
void enqueue(X d,int p)
  {
  if(index >= MAX_INDEX)
    {
    cout<<"QUEUE IS FULL!!"<<endl;
    return;
    }
  if(head == NULL)
    {
    atfirst(d,p);
    return;
    }
  node<X> *ptr = new node<X>;
  ptr -> data = d;
  ptr -> priority = p;
  if(head == tail)
    {
    if(head -> priority <= p)
      {
      ptr -> next = NULL;
      head -> next = ptr;
      tail = ptr;
      }
    else if(head -> priority > p)
      {
      ptr -> next = head;
      head = ptr;
      }
    }
  else
    {
      if(tail -> priority <= p)//EDGE CASES
      {  
      tail -> next = ptr;
      ptr -> next = NULL;
      tail = ptr;
      }
    else if(head -> priority > p)//EDGE CASES
      {  
      ptr -> next = head;
      head = ptr;
      }
    else
      {
      bool flag = true;
      node<X> *temp_ptr = head;
      node<X> *temp_pre = head;
      while(temp_ptr != NULL && flag)
        {
	if((temp_ptr -> priority > p))
	  {
	  temp_pre -> next = ptr;
	  ptr -> next = temp_ptr;
	  flag = false;
	  }
	temp_pre = temp_ptr;
	temp_ptr = temp_ptr -> next;
	}
      }
    }
  index++;
  }
void dequeue()
  {
  if(head == NULL)
    {
    cout<<"QUEUE IS EMPTY!!"<<endl;
    return;
    }
  else if(head == tail)
    {
    cout<<"YOU DELETED:"<<head->data<<" PRIORITY:"<<head->priority<<endl;
    clear();
    }
  else
    {
    node<X> *ptr = head;
    head = head -> next;
    cout<<"YOU DELETED "<<ptr -> data<<" PRIORITY :"<<ptr -> priority<<endl;
    delete ptr;
    index--;
    }
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
int size()
  {
  return index;
  }
X peek()
  {
  return (head -> data);
  }
void clear()
  { 
  if(head == NULL);
  else if(head == tail)
    delete head;
  else
    {
    tail = head;
    for(int i = 0;i < index;i++)
      {
      tail = head -> next;
      delete head;
      head = tail;
      }
    }
  index = 0;
  head = NULL; 
  tail = NULL;
  }
p_queue()
  {
  head = NULL;
  tail = NULL;
  index = 0;
  }
~p_queue()
  {
  clear();
  }
};
int main()
{
p_queue<char> p_list;
p_list.display();
p_list.dequeue();
p_list.display();
p_list.enqueue('i',34);
p_list.display();
p_list.enqueue('h',1);
p_list.display();
p_list.enqueue('m',23);
p_list.display();
p_list.enqueue('t',32);
p_list.display();
p_list.enqueue('y',53);
p_list.display();
p_list.enqueue('i',87);
p_list.display();
p_list.enqueue('n',254);
p_list.display();
p_list.enqueue('m',35);
p_list.display();
p_list.enqueue('q',2);
p_list.display();
p_list.enqueue('e',10);
p_list.display();
p_list.enqueue('p',17);
p_list.display();
p_list.enqueue('j',45);
p_list.display();
p_list.enqueue('v',50);
p_list.display();
cout<<"SIZE:"<<p_list.size();
cout<<"PEEK:"<<p_list.peek();
p_list.dequeue();
p_list.display();
p_list.dequeue();
p_list.display();
return 0;
}
