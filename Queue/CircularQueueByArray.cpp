//CIRCULAR QUEUE
#include<iostream>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
template<class X>
class CQueue{//CIRCULAR QUEUE
X *arr;
unsigned int front_p,rear_p,size;
public:
CQueue(unsigned int size = 10){
  this -> size = size;
  arr = new X[size];
  front_p = -1;
  rear_p = -1;
  }
void enqueue(X data){
  if(front_p == -1 && rear_p == -1){
    arr[++rear_p] = data;
    front_p++;
    }
  else if((rear_p+1)%size == front_p) 
    cout<<"QUEUE IS FULL!!"<<endl;
  else{
    rear_p = (rear_p+1) % size;
    arr[rear_p] = data;
    //cout<<"rear_p: "<<rear_p<<endl;
    //cout<<"arr: "<<rear_p<<" "<<arr[rear_p]<<endl;
    }
  }
X dequeue(){
  if(front_p == -1 && rear_p == -1){
    cout<<"QUEUE IS EMPTY!!"<<endl;
    return INT_MAX;
    }
  else if((front_p+1)%size == (rear_p+1)%size){
    X temp = arr[front_p];
    front_p = -1;
    rear_p = -1;
    return temp;
    }
  else{
    X temp = arr[front_p];
    front_p = (front_p+1) % size;
    //cout<<"front_p: "<<front_p<<endl;
    return temp;
    }
  }
bool empty(){
  if(front_p == -1 && rear_p == -1)
    return true;
  return false;
  }
};
int main(){
  CQueue<int> list;
  cout<<"IS EMPTY: "<<list.empty()<<endl;
  list.dequeue();
  getch();
  for(int i = 0;i < 5;i++){
    list.enqueue(i);
    if(i%2)
      cout<<"DEQUEUED: "<<list.dequeue()<<endl;
    }
  cout<<"IS EMPTY: "<<list.empty()<<endl;
  for(int i = 0;i < 6;i++)
    cout<<list.dequeue()<<" ";
  cout<<endl;
  return 0;  
  }
