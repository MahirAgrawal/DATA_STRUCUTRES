#include<iostream>
#include<string>
#define cout std::cout
#define cin std::cin
#define endl '\n'
#define string std::string

//BELOW IS THE CODE FOR THREADED BINARY TREE
//WHY THREADED BINARY TREE?
//BECAUSE FOR ALL LEAF NODES TWO POINTERS : LEFT AND RIGHT ARE NULL AND SO SPACE IS WASTED
//1)SO IN THREADED TREE WE STORE INORDER SUCCESSOR AND PREDECESSOR IN PLACE OF null POINTER AND SO SPACE IS NOT WASTED
//2)ALSO WE CAN TRAVERSE WHOLE BINARY TREE WITHOUT STACK OR RECURSION SO MEMORY IS SAVED THERE AS IT ONLY REQUIRES A LOOP TO TRAVERSE NODES AS ALL INORDER SUCCESSOR    AND PREDECESSOR IS SAVED IN LEFT/RIGHT POINTER OF LEAF NODE OR EMPTY SPACE

//DISADVANTAGES:
//1)INSERTION AND TRAVERSAL CODE BECOMES HARD AS NOW NO NODES HAS NULL ADDRESS TO STOP LOOP OR FUNCTION
//2)DELETION ALSO BECOMES HARD

template<class X>
class T_BinaryTree;

template<class X>
class Node{
  int key;
  X data;
  Node<X> *left;
  Node<X> *right;
  bool isLeftThreaded = 1;//TO TELL IF THREADED LINK IS THERE OR ANY NORMAL LINK
  bool isRightThreaded = 1;//TO TELL IF THREADED LINK IS THERE OR ANY NORMAL LINK
  Node(int key,X data,Node<X> *left = NULL,Node<X> *right = NULL){
    this -> key = key;
    this -> data = data;
    this -> left = left;
    this -> right = right;
    this -> isLeftThreaded = 1;
    this -> isRightThreaded = 1;
  }

  ~Node(){
    this -> key = INT_MIN;
    this -> left = NULL;
    this -> right = NULL;
   } 
  friend class T_BinaryTree<X>;//Threaded Binary Tree
};

template<class X>
class T_BinaryTree{
  Node<X> *root;
  
  public:
  T_BinaryTree(){
    root = NULL;
  }

  void insert(int key,X data){
    auto new_node = new Node<X>(key,data);
    if(!root){
      root = new_node;
      return;
    }
    Node<X> *parent = NULL;
    auto traversalptr = root;
    while(traversalptr){
      if(key < traversalptr -> key){//KEY CAN BE INSERTED AT LEFT
	parent = traversalptr;//PRESERVING PARENT FOR INSERTION WHEN WE FIND A NULL NODE AND END THE LOOP
	//cout<<key<<" "<<"ON LEFT OF: "<<traversalptr -> key<<" "<<traversalptr -> isLeftThreaded<<traversalptr -> isRightThreaded<<endl;
	if(traversalptr -> isLeftThreaded)
	  traversalptr = NULL;
	else
          traversalptr = traversalptr -> left;
      }
      else if(key > traversalptr -> key){//KEY CAN BE INSERTED AT RIGHT
        //cout<<key<<" "<<"ON RIGHT OF: "<<traversalptr -> key<<" "<<traversalptr -> isLeftThreaded<<traversalptr -> isRightThreaded<<endl;
	parent = traversalptr;//PRESERVING PARENT FOR INSERTION WHEN WE FIND A NULL NODE AND END THE LOOP
	if(traversalptr -> isRightThreaded)
	  traversalptr = NULL;
	else
	  traversalptr = traversalptr -> right;
      }
      else{//KEY IS ALREADY PRESENT
	std::cerr<<"KEY IS ALREADY PRESENT!! TRY UPDATION INSTEAD!!"<<endl;
	return;
      }
    }

    if(parent -> key > key){//TO INSERT THE KEY AT LEFT OF PARENT
      auto threadLink = parent -> left;//STORING PARENT LINK AS IT WOULD BE THREADED LINK
      parent -> left = new_node;
      parent -> isLeftThreaded = false;
      new_node -> right = parent; //STORING INORDER SUCCESSOR
      new_node -> left = threadLink;//STORING THREADLINK OF PARENT WHICH WILL BE INORDER PREDECESSOR
    }
    else{//TO INSERT THE KEY AT RIGHT OF PARENT
      auto threadLink = parent -> right;//STORING PARENT LINK AS IT WOULD BE THREADED LINK
      parent -> right = new_node;
      parent -> isRightThreaded = false;
      new_node -> left = parent; //STORING INORDER PREDECESSOR
      new_node -> right = threadLink;//STORING THREADLINK OF PARENT WHICH WILL BE INORDER SUCCESSOR
    }
  }

  void update(int key,X value){
    if(!root){
      cout<<"TREE IS EMPTY!"<<endl;
      return;
    }
    auto traversalptr = root;
    while(traversalptr){
      if(key < traversalptr -> key){//KEY CAN BE AT LEFT
	if(traversalptr -> isLeftThreaded)
	  traversalptr = NULL;
	else
          traversalptr = traversalptr -> left;
      }
      else if(key > traversalptr -> key){//KEY CAN BE AT RIGHT
	if(traversalptr -> isRightThreaded)
	  traversalptr = NULL;
	else
	  traversalptr = traversalptr -> right;
      }
      else{//KEY IS PRESENT
        cout<<"DATA CHANGED FROM "<<traversalptr -> data<<" TO "<<value<<endl;
	traversalptr -> data = value;
	break;
      }
    }
  }

  private:
  void printInorder(Node<X> *root){
    int i = 0;
    if(root == NULL)
      return;
    auto traversalptr = root;
    while(traversalptr){
      while(!(traversalptr -> isLeftThreaded))//GETTING TO LEFTMOST NODE
        traversalptr = traversalptr -> left;
      cout<<traversalptr -> key<<":"<<traversalptr -> data<<endl;
      while(traversalptr && traversalptr -> isRightThreaded && traversalptr -> right){//IF RIGHT THREADED THEN JUST GO TO SUCCESSOR BUT ONLY TO PRINT ITS DATA AS WE WOULD HAVE ALREADY                                                                     TRAVERSE ITS LEFT SUBTREE
	 traversalptr = traversalptr -> right;
         cout<<traversalptr -> key<<":"<<traversalptr -> data<<endl;
      }
      if(traversalptr)
        traversalptr = traversalptr -> right;
      //printf("%d\n",i);
      //i++;
    }
  }

  public:
  void printInorder(){
    cout<<"THE INORDER TRAVERSAL IS: "<<endl;
    printInorder(this -> root);
  }
 
};

int main(){
  T_BinaryTree<string> birthday_order;
  birthday_order.insert(11,"A");
  birthday_order.insert(30,"H");
  birthday_order.insert(67,"D");
  birthday_order.insert(4,"m");
  birthday_order.update(11,"Hter");
  birthday_order.insert(87,"My");
  birthday_order.insert(5,"Jaling"); 
  birthday_order.update(87,"Horter");
  birthday_order.insert(78,"MDay");
  birthday_order.insert(443,"osling");  
  birthday_order.insert(43,"Hter");
  birthday_order.insert(24,"My");
  birthday_order.insert(55,"Jing");  
  birthday_order.insert(766,"ter");
  birthday_order.insert(14,"M");
  birthday_order.insert(98,"J");  
  birthday_order.insert(6,"HaPoer");
  birthday_order.insert(2,"Ma");
  birthday_order.insert(23,"Jmesosng");  
  birthday_order.insert(54,"Harrter");
  birthday_order.insert(17,"a");
  birthday_order.insert(67,"aosling"); 
  birthday_order.insert(91,"HarryPorter");
  birthday_order.insert(101,"MayD");
  birthday_order.insert(13,"Jaming");  
  birthday_order.insert(12,"Har");
  birthday_order.insert(19,"y");
  birthday_order.insert(43,"P");  
  birthday_order.insert(34,"Hparpprr");
  birthday_order.insert(54,"MT");
  birthday_order.insert(767,"JHing"); 
  birthday_order.insert(98,"HarHr");
  birthday_order.insert(0,"MYT");
  birthday_order.insert(-1,"JaUYing");
  birthday_order.printInorder();
  return 0;
}
