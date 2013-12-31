#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define LEFT(x) (2*x+1)
#define RIGHT(x) (2*x+2)
#define PARENT(x) ((x-1)/2)
//THIS DOESN'T WORK 
//SEE HEAP SECTION IN DS NOTEBOOK TO READ WHY IT NOT GOOD TO DO ADD AND REMOVE SIMULTANEOUSLY AND TO DO ADD AND REMOVE ALL ELEMENTS   AT ONE TIME i.e. ADD ALL AND THEN REMOVE ALL TO SORT THEM
//ALSO IT CAN WORK WITH CIRCULAR QUEUE LIKE DATA STRUCTURE

template<class X>
class Heap{//MAX HEAP
  template<class Y>
  class Node{
    int key;
    Y data;
    Node(int key,Y data){
      this -> key = key;
      this -> data = data;
      }
    ~Node(){
      key = 0;
      }
    friend class Heap<Y>;
    };
  Node<X> **mainHeap;//POINTER TO ADDRESS OF NODES
  int offset;
  int heap_size;
  public:
  Heap(){
    heap_size = 100;
    offset = 100; 
    mainHeap = new Node<X>*[heap_size];
    }
  void add(int key,X data){
    offset--;
    if(offset == -1){
      //RESIZING!!
      //RESIZE RETURNS NEW OFFSET
      return;
      }
    mainHeap[offset] = new Node<X>(key,data); 
    rebalanceHeap(offset);
    }
  private:
  void rebalanceHeap(int index){
    int max = index;//INDEX OF NODE ADDRESS HAVING MAX KEY
    while(true){
      if(LEFT(index)-index < heap_size && mainHeap[LEFT(index)-index]->key > mainHeap[max]->key)
        max = LEFT(index)-index;
      if(RIGHT(index)-index < heap_size && mainHeap[RIGHT(index)-index]->key > mainHeap[max]->key)
	max = RIGHT(index)-index;
      if(max != index){
	auto temp = mainHeap[index];
	mainHeap[index] = mainHeap[max];
	mainHeap[max] = temp;
        }
      else
        break;
      }
    }
  public:
  X remove(){
    
    }
  ~Heap(){
    heap_size = 0;
    offset = 0;
    delete mainHeap;
    }
  };
