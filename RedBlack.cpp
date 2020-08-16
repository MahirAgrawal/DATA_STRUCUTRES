#include<iostream>
#include<vector>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define vector std::vector
#define GRANDPARENT(x) (x->parent->parent)
#define PARENT(x) (x->parent)
 //1 for RED and 0 for BLACK
class Node{
  Node *parent;//STORES POINTER TO PARENT ALSO
  Node *left;
  int data;
  Node *right;
  bool color;
  Node(int data,Node *parent = NULL){
    this -> parent = parent;
    this -> left = NULL;
    this -> data = data;
    this -> right = NULL;
    this -> color = 1;
    }
  friend class RedBlack;
  };
class RedBlack{
  Node *root = NULL;
  public:
  RedBlack(){
    root = NULL;
    }
  private:
  Node* recolor(Node *child){ 
    GRANDPARENT(child) -> left -> color = 0;
    GRANDPARENT(child) -> right -> color = 0;
    GRANDPARENT(child) -> color = 1;
    return (GRANDPARENT(child));
    }
   
  Node* leftRotation(Node *ptr){
    auto to_preserve = GRANDPARENT(ptr);
    GRANDPARENT(ptr) = ptr;
    if(ptr -> left != NULL)
      ptr -> left -> parent = PARENT(ptr);
    PARENT(ptr) -> right = ptr -> left;
    ptr -> left = PARENT(ptr);
    PARENT(ptr) = to_preserve;
    if(PARENT(ptr) != NULL){
      if(ptr -> data < PARENT(ptr) -> data)//SETTING PTR AS GRANDPARENT CHILD HERE ONLY AS RECURSIVE SOLUTION LIKE IN AVL WON'T WORK
        PARENT(ptr) -> left = ptr;
      else
        PARENT(ptr) -> right = ptr;
      }
    else
      this -> root = ptr;
    return ptr;
    }

  Node* rightRotation(Node *ptr){
    auto to_preserve = GRANDPARENT(ptr);
    GRANDPARENT(ptr) = ptr;
    if(ptr -> right != NULL)
      ptr -> right -> parent = PARENT(ptr);
    PARENT(ptr) -> left = ptr -> right;
    ptr -> right = PARENT(ptr);
    PARENT(ptr) = to_preserve;
    if(PARENT(ptr) != NULL){
      if(ptr -> data < PARENT(ptr) -> data)//SETTING PTR AS GRANDPARENT CHILD HERE ONLY AS RECURSIVE SOLUTION LIKE IN AVL WON'T WORK
        PARENT(ptr) -> left = ptr;
      else
        PARENT(ptr) -> right = ptr;
      }
    else
      this -> root = ptr;
    return ptr;
    }
  public:
  void insert(int data){
    if(root == NULL){
      root = new Node(data);
      return;
      }
    auto traversalptr = this -> root;
    auto parentptr = PARENT(traversalptr);
    while(traversalptr){//GET TO THE APPROPRIATE LEAF NODE TO INSERT DATA
      if(data < traversalptr -> data){
	//cout<<"TO THE LEFT OF "<<traversalptr->data<<endl;
        parentptr = traversalptr;
        traversalptr = traversalptr -> left;
        }
      else{
	//cout<<"TO THE RIGHT OF "<<traversalptr->data<<endl;
	parentptr = traversalptr;
        traversalptr = traversalptr -> right;
        }
      }
    //traversalptr is NULL SO WE HAVE GET TO THE CORRECT LEAF NODE
    //NOW ONLY DECISION IS WHETHER THE DATA WILL BE LEFT OR RIGHT TO LEAF NODE
    if(data < parentptr -> data){
      parentptr -> left = new Node(data,parentptr);
      traversalptr = parentptr -> left;
      }
    else{
      parentptr -> right = new Node(data,parentptr);
      traversalptr = parentptr -> right;
      }
    while(PARENT(traversalptr) != NULL && PARENT(traversalptr) != root && traversalptr->color && PARENT(traversalptr) -> color){
    //LOOP CONDITIONS ABOVE: TO ENSURE THAT NODE IS NOT A ROOT OR ITS CHILDREN BECAUSE 
    //IF ROOT IS RED WE CAN MAKE IT BLACK DIRECTLY ALSO WE DO OPERATIONS IN CASE OF 'TWO RED CONFLICT i.e. BOTH NEWLY 
    //INSERTED NODE AND IT'S PARENT IS RED
    //cout<<"TRAVERSAL:"<<traversalptr->data<<" COLOR:"<<traversalptr->color<<" PARENT COLOR:"<<PARENT(traversalptr)->color<<endl;
      if(GRANDPARENT(traversalptr)->left == PARENT(traversalptr)){//PARENT OF POINTER IS LEFT CHILD OF GRANDPARENT
        if(GRANDPARENT(traversalptr)->right != NULL && GRANDPARENT(traversalptr)->right->color){//AUNT RIGHT TO GRANDPARENT IS RED
	  traversalptr = recolor(traversalptr);
	  //cout<<"RECOLORING.."<<endl;
	  }
	else{//AUNT RIGHT TO GRANDPARENT IS BLACK
          //cout<<"ROTATING.."<<endl;
	  if(PARENT(traversalptr)->left == traversalptr)//RIGHT ROTATION
	    traversalptr = rightRotation(traversalptr->parent);
	  else//DO LEFT-RIGHT ROTATION
	    traversalptr = rightRotation(leftRotation(traversalptr));
          traversalptr -> color = 0;//RECOLORING
	  traversalptr -> right -> color = 1;
	  } 
	}
      else{//PARENT IS RIGHT CHILD OF GRANDPARENT
        if(GRANDPARENT(traversalptr)->left != NULL && GRANDPARENT(traversalptr)->left->color){//AUNT LEFT TO GRANDPARENT IS RED
	  traversalptr = recolor(traversalptr);
	  //cout<<"RECOLORING.."<<endl;
	  }
	else{//AUNT LEFT TO GRANDPARENT IS BLACK
	  //cout<<"ROTATING.."<<endl;
	  if(PARENT(traversalptr)->right == traversalptr)//LEFT ROTATION
	    traversalptr = leftRotation(traversalptr->parent); 
	  else//DO RIGHT-LEFT ROTATION
	    traversalptr = leftRotation(rightRotation(traversalptr));
	  traversalptr -> color = 0;//RECOLORING
          traversalptr -> left -> color = 1;
	  }
        }
      }
    this -> root -> color = 0;//RECOLORING BLACK TO MAKE SURE THAT ROOT REMAINS BLACK
    }
  void blackHeight(FILE *fp,std::ofstream& file){
    vector<Node*> v;
    countPath(this -> root,v,fp,file);
    }
  void countPath(Node *ptr,vector<Node*>& v,FILE *fp,std::ofstream& file){
    if(ptr == NULL){
      for(int i = 0;i < v.size();i++){
        file<<"COLOR: "<<v[i] -> color<<" DATA: "<<v[i]->data<<endl;
        fprintf(fp,"COLOR: %d DATA: %d\n",(int)v[i]->color,v[i]->data);
        }
      file<<endl;
      fprintf(fp,"\n");
      return;
      }
    v.push_back(ptr);
    countPath(ptr->left,v,fp,file);
    countPath(ptr->right,v,fp,file);
    v.pop_back();
    }
  void printInorder(Node *ptr){ 
    if(ptr == NULL)
      return;
    printInorder(ptr -> left);
    cout<<ptr -> data<<" ";
    printInorder(ptr -> right);
    }
  public:
  void display(){
    printInorder(this -> root);
    }
  };
int main(){
RedBlack tree;
int n = 1000;
for(int i = 1;i <= n;i++){
  tree.insert(i);
  //cout<<endl;
  //getch();
  }
tree.display();
cout<<endl;

//BELOW CODE PRINT ALL PATHS FROM 'ROOT TO NULL' IN FILE NAMED  PathC and PathC++ IN SAME FOLDER AS THIS CPP FILE IS IN
//AND IT IS PRINTED BECAUSE WE CAN SEE AND PROVE THAT OUR ABOVE IMPLEMENTATION WORKS BECAUSE IT PRINTS 'COLOR' OF NODES IN A PATH     AND AS IT PRINTS ALL PATHS SO 'COUNT OF BLACK COLOR' SHOULD BE SAME FOR ALL PATHS
//BY WATCHING ALL PATHS FROM ROOT TO NULL ,BLACK COLOR COUNT IS SAME FOR ALL PATHS WE CAN SATISFY RedBlack PROPERTY!!

//C style
FILE *fp = fopen("PathC.txt","a");
//C++ style
std::ofstream file;
file.open("PathC++.txt",std::ios::app);
tree.blackHeight(fp,file);//giving file to write paths in it
file.close();
fclose(fp);
return 0;  
}
