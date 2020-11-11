#include<iostream>
#include<exception>
#define cout std::cout
#define cin std::cin
#define endl std::endl
//DEQUEUE IMPLEMENTED USING DOUBLY LINKED LIST BECAUSE ENQUEUE AND DEQUEUE MUST BE CONSTANT TIME OPERATIONS BUT IN SINGLY LINKED      LIST WE CAN'T REMOVE LAST ELEMENT IN O(1) AS WE HAVE GO TO SECOND LAST ELEMENT AND THEN DELETE THE LAST ELEMENT BUT IT WILL TAKE    O(N) TIME
//SO USED DOUBLY LINKED LIST AND QUEUE IS JUST A SUBSET OF DEQUEUE i.e. HAS LIMITED FUNCTIONALITY OF ADDING AT LAST AND REMOVING      FROM FIRST
template<class X>
class Dequeue;
template<class Y>
class Node{
  Node<Y> *previous;
  Y data;
  Node<Y> *next;
  Node(Y d,Node<Y> *p = NULL,Node<Y> *n = NULL){
    this -> previous = p;
    this -> data = d;
    this -> next = n;
    }
  ~Node(){
    this -> next = NULL;
    this -> previous = NULL;
    }
  friend class Dequeue<Y>;
  };
template<class X>
class Dequeue{
  Node<X> *head = NULL;
  Node<X> *tail = NULL;
  public:
  Dequeue(){
    head = NULL;
    tail = NULL;
    }
  void enqueueRear(X data){
    if(head == NULL){
      head = new Node<X>(data);
      tail = head; 
      }
    else{
      tail -> next = new Node<X>(data,tail);
      tail = tail -> next;
      }
    }
  void enqueueFront(X data){
    if(head == NULL){
      head = new Node<X>(data);
      tail = head; 
      }
    else{
      head -> previous = new Node<X>(data,NULL,head);
      head = head -> previous;
      }
    }
  void dequeueFront(){
    if(head == NULL){
      cout<<"QUEUE IS EMPTY!!"<<endl;
      return;
      }
    else if(head == tail){
      delete head;
      head = NULL;
      tail = NULL;
      }
    else{
      Node<X> *ptr = head;
      head = head -> next;
      head -> previous = NULL;
      delete ptr;
      }
    }
  void dequeueRear(){
    if(head == NULL){
      cout<<"QUEUE IS EMPTY!!"<<endl;
      return;
      }
    else if(head == tail){
      delete tail;
      tail = NULL;
      head = NULL;
      }
    else{
      Node<X> *ptr = tail;
      tail = tail -> previous;
      tail -> next = NULL;
      delete ptr;
      }
    }
  void display(){ 
    Node<X> *ptr = head;
    while(ptr != NULL){
      cout<<ptr -> data<<" ";
      ptr = ptr -> next;
      }
    cout<<endl;
    }
  X peek(){  
    if(head == NULL)
      throw std::out_of_range("OUT_OF_BOUNDS!!");
    return (head -> data);
    }
  bool empty(){
    if(head == NULL)
      return true;
    else
      return false;
    }
  ~Dequeue(){
    while(!(this -> empty()))
      this -> dequeueFront();
    }
};
/*
int main(){
Dequeue<int> q;
q.dequeueFront();q.dequeueRear();
q.enqueueRear(45);
q.display();
q.enqueueRear(54);
q.enqueueFront(22);
q.display();
q.enqueueFront(12);
cout<<"FRONT: "<<q.peek()<<endl;
q.display();
cout<<"EMPTY: "<<q.empty()<<endl;
q.dequeueFront();
q.dequeueRear();
q.dequeueFront();
q.dequeueRear();
cout<<"EMPTY: "<<q.empty()<<endl;
return 0; 
}*/
