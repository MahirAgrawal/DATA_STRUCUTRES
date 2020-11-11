#include<iostream>
#include"my_time.h"
#include<queue>
#include<stack>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define queue std::queue
#define stack std::stack

//MY BEST VERSION OF SELF BALANCING BINARY SEARCH TREE
//---HANDLES DUPLICATES EFFICIENTLY
//---FINDS HEIGHT AND BALANCE FACTOR IN O(1) TIME COMPLEXITY
//
//FOR MORE COMPARISON SEE 'BinarySearchTree.cpp' COMMENTS

template<class X>
class BinarySearchTree;

template<class X>
class Node{
  Node<X> *left;
  X data;
  Node<X> *right;
  int height;
  int count;//TO STORE DUPLICATES or SAME KEY
  Node(X data){
    this -> data = data;
    this -> left = NULL;
    this -> right = NULL;
    this -> height = 0;
    this -> count = 0;
    }
  ~Node(){ 
    this -> left = NULL;
    this -> right = NULL;
    this -> height = 0;
    this -> count = 0;
    }
  friend class BinarySearchTree<X>;
  };

template<class X>
class BinarySearchTree{
  //MEMBER VARIABLE
  Node<X> *root;
  //MEMBER FUNCTIONS
  Node<X>* insert(X data,Node<X> *traversalptr){
    if(traversalptr == NULL)
      return new Node<X>(data);
    else if(data < traversalptr -> data)
      traversalptr -> left = insert(data,traversalptr -> left);
    else if(data == traversalptr -> data)
      (traversalptr -> count)++;
    else
      traversalptr -> right = insert(data,traversalptr -> right); 
    //GET MAX HEIGHT OF HEIGHT OF LEFT AND RIGHT SUBTREE
    traversalptr -> height = std::max(getHeight(traversalptr -> left),getHeight(traversalptr -> right))+1;
    if(balanceFactor(traversalptr) > 1){//LEFT SIDE HAS MORE NODES
      if(data > traversalptr -> left -> data)
        traversalptr = leftRightRotation(traversalptr);
      else
        traversalptr = rightRotation(traversalptr);
      }
    else if(balanceFactor(traversalptr) < -1){//RIGHT SIDE HAS MORE NODES
      if(data > traversalptr -> right -> data)
        traversalptr = leftRotation(traversalptr);
      else
        traversalptr = rightLeftRotation(traversalptr);
      }
    //AGAIN CHECKING AND UPDATING HEIGHT AFTER ROTATIONS
    //ALSO IF TRAVERSALPTR IS NODE ITSELF ON WHICH ROTATIONS ARE PERFORMED THEN THIS STEP CAN BE EXTRA FOR IT BECAUSE ROTATION
    //FUNCTION HAS ALREADY THE HEIGHT UPDATION STEP BUT AS HEIGHT UPDATION IS NOW CONSTANT SO IT DOESN'T MATTER TO DO EXTRA TIME
    traversalptr -> height = std::max(getHeight(traversalptr -> left),getHeight(traversalptr -> right))+1;
    return traversalptr;
    }
  int getHeight(Node<X> *ptr){
    if(ptr == NULL)
      return -1;
    else
      return ptr -> height;
    }
  int balanceFactor(Node<X> *ptr){ 
    if(ptr == NULL)
      return 0;
    return (getHeight(ptr -> left) - getHeight(ptr -> right));
    }
  void printPreorder(Node<X> *traversalptr){ 
    if(traversalptr == NULL)
      return;
    for(int i = 0;i <= (traversalptr -> count);i++)
      cout<<traversalptr -> data<<" ";
    printPreorder(traversalptr -> left);
    printPreorder(traversalptr -> right);
    }
  void printInorder(Node<X> *traversalptr){
    if(traversalptr == NULL)
      return;
    printInorder(traversalptr -> left);
    for(int i = 0;i <= (traversalptr -> count);i++)
      cout<<traversalptr -> data<<" ";
    printInorder(traversalptr -> right);
    }
  void printPostorder(Node<X> *traversalptr){
    if(traversalptr == NULL)
      return;
    printPostorder(traversalptr -> left);
    printPostorder(traversalptr -> right);
    for(int i = 0;i <= (traversalptr -> count);i++)
      cout<<traversalptr -> data<<" ";
    }
  void printBreadthFirst(Node<X> *ptr){
    queue<Node<X>*> q;
    if(ptr != NULL)
      q.push(ptr);
    while(!q.empty()){
      for(int i = 0;i <= (q.front() -> count);i++)
        cout<<q.front()->data<<" ";//<<q.front()->height<<endl;
      if(q.front() -> left != NULL)
        q.push(q.front()->left);
      if(q.front() -> right != NULL)
        q.push(q.front()->right);
      q.pop();
      }
    }
  Node<X>* remove(X data,Node<X> *traversalptr){
    if(traversalptr == NULL)
      cout<<"NO SUCH DATA!!"<<endl;
    else if(traversalptr -> data == data && traversalptr -> count > 0){
      (traversalptr -> count)--;
      cout<<"DECREMENTING COUNT!!"<<endl;
      }
    else if(traversalptr -> data == data && traversalptr -> count == 0){
      if(traversalptr -> left == NULL && traversalptr -> right == NULL){//NO CHILD
        delete traversalptr;
	traversalptr = NULL;
        }
      else if(traversalptr -> left == NULL || traversalptr -> right == NULL){//ONE CHILD
        Node<X> *to_preserve = NULL;
	if(traversalptr -> left)//LEFT CHILD IS PRESENT
	  to_preserve = traversalptr -> left;
	else//RIGHT CHILD IS PRESENT
	  to_preserve = traversalptr -> right;
	delete traversalptr;
	traversalptr = to_preserve;
        }
      else{//TWO CHILDREN
	auto successor = inorderSuccessor(traversalptr);
        traversalptr -> data = successor -> data;
	traversalptr -> count = successor -> count;
	successor -> count = 0;//SO THAT IT JUST DON'T DECREMENT COUNT IN CASE IF SUCCESSOR VALUE HAS DUPLICATES AND ACTUALLY REMOVE
        traversalptr -> right = remove(traversalptr -> data,traversalptr -> right);
        }
      }
    else if(data > traversalptr -> data)//IF DATA IS NOT FOUND AND CAN BE IN RIGHT SUBTREE
      traversalptr -> right = remove(data,traversalptr -> right);
    else//IF DATA IS NOT FOUND AND CAN BE IN LEFT SUBTREE
      traversalptr -> left = remove(data,traversalptr -> left);
    
    //UPDATING HEIGHTS
    if(traversalptr != NULL){//IF NODE IS NOT 'NULL' THEN ONLY DO THIS BELOW STUFF
      traversalptr -> height = std::max(getHeight(traversalptr -> left),getHeight(traversalptr -> right))+1;
      //CHECKING BALANCE
      if(balanceFactor(traversalptr) > 1){//LEFT SIDE HAS MORE NODES
        if(balanceFactor(traversalptr -> left) >= 0)
          traversalptr = rightRotation(traversalptr);
        else
          traversalptr = leftRightRotation(traversalptr);
        }
      else if(balanceFactor(traversalptr) < -1){//RIGHT SIDE HAS MORE NODES
	if(balanceFactor(traversalptr -> right) < 0)
          traversalptr = leftRotation(traversalptr);
        else
          traversalptr = rightLeftRotation(traversalptr);
        }
      //AGAIN CHECKING AND UPDATING HEIGHT AFTER ROTATIONS
      //ALSO IF TRAVERSALPTR IS NODE ITSELF ON WHICH ROTATIONS ARE PERFORMED THEN THIS STEP CAN BE EXTRA FOR IT BECAUSE ROTATION
      //FUNCTION HAS ALREADY THE HEIGHT UPDATION STEP BUT AS HEIGHT UPDATION IS NOW CONSTANT SO IT DOESN'T MATTER TO DO EXTRA TIME
      traversalptr -> height = std::max(getHeight(traversalptr -> left),getHeight(traversalptr -> right))+1;
      }
    return traversalptr;
    }

  Node<X>* inorderSuccessor(Node<X> *ptr){
    ptr = ptr -> right;
    while(ptr -> left != NULL)
      ptr = ptr -> left;
    return ptr;
    }

  //ROTATIONS
  Node<X>* rightRotation(Node<X> *grandparent){
    cout<<"RIGHT ROTATION FOR "<<grandparent -> data<<endl;
    auto parent = grandparent -> left;
    grandparent -> left = parent -> right;
    //HEIGHT UPDATION FOR GRANDPARENT(NO OTHER NODE WILL HAVE ANY CHANGE IN HEIGHT)
    grandparent -> height = std::max(getHeight(grandparent -> left),getHeight(grandparent -> right))+1;
    parent -> right = grandparent;
    //HEIGHT UPDATION FOR PARENT(NO OTHER NODE WILL HAVE ANY CHANCE IN HEIGHT)
    parent -> height = std::max(getHeight(parent -> left),getHeight(parent -> right))+1;
    return parent;
    }
  Node<X>* leftRotation(Node<X> *grandparent){
    cout<<"LEFT ROTATION FOR "<<grandparent -> data<<endl;
    auto parent = grandparent -> right;
    grandparent -> right = parent -> left;
    //HEIGHT UPDATION FOR GRANDPARENT(NO OTHER NODE WILL HAVE ANY CHANGE IN HEIGHT)
    grandparent -> height = std::max(getHeight(grandparent -> left),getHeight(grandparent -> right))+1;
    parent -> left = grandparent;
    //HEIGHT UPDATION FOR PARENT(NO OTHER NODE WILL HAVE ANY CHANCE IN HEIGHT)
    parent -> height = std::max(getHeight(parent -> left),getHeight(parent -> right))+1;
    return parent;
    }
  Node<X>* leftRightRotation(Node<X> *grandparent){
    grandparent -> left = leftRotation(grandparent -> left);
    //HEIGHT UPDATION FOR GRANDPARENT(NO OTHER NODE WILL HAVE ANY CHANGE IN HEIGHT)
    grandparent -> height = std::max(getHeight(grandparent -> left),getHeight(grandparent -> right))+1;
    return (rightRotation(grandparent)); 
    }
  Node<X> *rightLeftRotation(Node<X> *grandparent){
    grandparent -> right = rightRotation(grandparent -> right);
    //HEIGHT UPDATION FOR GRANDPARENT(NO OTHER NODE WILL HAVE ANY CHANGE IN HEIGHT)
    grandparent -> height = std::max(getHeight(grandparent -> left),getHeight(grandparent -> right))+1;
    return (leftRotation(grandparent));
    }
  public:
  BinarySearchTree(){
    root = NULL;
    }
  void insert(X data){
    this -> root = this -> insert(data,this -> root);
    } 
  int getHeight(){//ACCESS TO PUBLIC FOR HEIGHT OF TREE ONLY
    return getHeight(this -> root);
    }
  void printPreorder(){
    printPreorder(this -> root);
    }
  void printInorder(){
    printInorder(this -> root);
    }
  void printPostorder(){
    printPostorder(this -> root);
    }
  void printBreadthFirst(){
    printBreadthFirst(this -> root);
    }
  void remove(X data){
    this -> root = remove(data,this -> root);
    }
 };

int main(){
BinarySearchTree<int> tree;
int n,r;
cout<<"ENTER THE NUMBER OF ELEMENT YOU WANT IN TREE: ";
cin>>n;
timer t;
for(int i = 0;i < n;i++){
  //r = rand()%n;
  cin>>r;
  tree.insert(r);
  }
t.stop();
cout<<"HEIGHT : "<<tree.getHeight()<<endl;
//getch();
cout<<endl;
//cout<<"PREORDER :";tree.printPreorder();cout<<endl;
cout<<"INORDER: ";tree.printInorder();cout<<endl;
/*cout<<"POSTORDER: ";tree.printPostorder();cout<<endl;
cout<<"BREADTH FIRST PRINT: ";tree.printBreadthFirst();cout<<endl;
cout<<"INORDER: ";tree.printInorder();cout<<endl;
tree.remove(56);
cout<<"INORDER: ";tree.printInorder();cout<<endl;
tree.remove(56);
cout<<"INORDER: ";tree.printInorder();cout<<endl;*/
/*tree.remove(6);
tree.remove(78);
cout<<"INORDER: ";tree.printInorder();cout<<endl;
cout<<"HEIGHT : "<<tree.getHeight()<<endl;
cout<<"INORDER: ";tree.printInorder();cout<<endl;*/
tree.remove(3);
tree.remove(10);
tree.remove(7);
tree.remove(8);
tree.remove(6);
cout<<"HEIGHT: "<<tree.getHeight()<<endl;
cout<<"INORDER: ";tree.printInorder();cout<<endl;
return 0; 
}

