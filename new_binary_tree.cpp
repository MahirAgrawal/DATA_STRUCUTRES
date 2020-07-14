#include<iostream>
#include<cstdio>
#include"simple_queue.h"
#include"simple_stack.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl
template<class X>
class binary_tree;
template<class X>
class node{
X data;
node *left = NULL;
node *right = NULL;
public:
node()
  {
  left = NULL;
  right = NULL;
  }
node(X d)
  {
  left = NULL;
  this -> data = d;
  right = NULL;
  }
~node()
  {
  //cout<<"DELETED "<<this -> data<<endl;
  X garbage;
  data = garbage;
  left = NULL;
  right = NULL;
  }
friend class binary_tree<X>;
};
template<class X>
class binary_tree{
node<X> *root = NULL;
public:
binary_tree()
  {
  root = NULL;	
  }
private:
//FUNCTION OVERLOADING WITHIN CLASS
//THIS IS PRIVATE AND OTHER PROTOTYPE OF SAME NAME FUNCTION TAKES ONLY ONE ARGUMENT : DATA_TO_BE_INSERTED
node<X>* insert_recursively(X data,node<X> *temp_root)
  {
  if(temp_root == NULL)
    temp_root = new node<X>(data);
  else if(data <= temp_root -> data)
    temp_root -> left = insert_recursively(data,temp_root -> left);
  else
    temp_root -> right = insert_recursively(data,temp_root -> right);
  int balance = height(temp_root -> left) - height(temp_root -> right);
  if(balance > 1)
    {
    if(data < (temp_root -> left) -> data)
     temp_root =  right_rotation(temp_root);
    else
      temp_root = left_right_rotation(temp_root);
    }
  else if(balance < -1)
    {
    if(data > (temp_root -> right) -> data)
     temp_root =  left_rotation(temp_root);
    else
      temp_root = right_left_rotation(temp_root);
    }
  balance = height(temp_root -> left) - height(temp_root -> right);
  if(balance > 1 || balance < -1)
   cout<<"UNBALANCED "<<balance<<" AT: "<<temp_root -> data<<"WHEN ADDED:"<<data<<endl;
  return temp_root;
  }
public:
void insert_recursively(X data)
  {
  root = insert_recursively(data,root);
  }
private:
//BREADTH-FIRST TRAVERSAL
my_queue::queue<node<X>*> q;
void print_breadth_first(node<X> *temp_root)
{
if(temp_root == NULL)
  return;
else
  {
  cout<<temp_root -> data<<" ";
  if(temp_root -> left != NULL)
    q.enqueue(temp_root -> left);
  if(temp_root -> right != NULL)
    q.enqueue(temp_root -> right);
  if(q.empty());
  else
    print_breadth_first(q.dequeue());
  }
}
public:
void print_breadth_first()
  {
  print_breadth_first(this -> root);
  }

//INSERT BY ITERATIONS
void insert(X data)
  {
  node<X> *ptr = new node<X>(data);
  if(root == NULL)
    root = ptr;
  else
    {
    node<X> *temp = root;
    bool flag = true;
    while(flag)
      {
      if(data <= temp -> data)
        {
	if(temp -> left == NULL)
	  {
	  temp -> left = ptr;
	  flag = false;
	  }
	else
	  temp = temp -> left;
	}
      else
        {
	if(temp -> right == NULL)
	  {
	  temp -> right = ptr;
	  flag = false;
	  }
	else
	  temp = temp -> right;
	}
      }
    }
  }
private:
//DEPTH-FIRST TRAVERSAL
void print_preorder(node<X> *temp_root)
  {
  if(temp_root == root)
    cout<<"DATA: ";
  if(temp_root == NULL)
    return;
  cout<<temp_root -> data<<" ";
  print_preorder(temp_root -> left);
  print_preorder(temp_root -> right);
  if(temp_root == root)
    cout<<endl;
  }
public:
void print_preorder()
  {
  print_preorder(this -> root);
  }
private:
void print_inorder(node<X> *temp_root)
  {
  if(temp_root == NULL)
    return;
  if(temp_root == root)
    cout<<"DATA: ";
  print_inorder(temp_root -> left);
  cout<<temp_root -> data<<" ";
  print_inorder(temp_root -> right);
  if(temp_root == root)
    cout<<endl;
  }
public:
void print_inorder()
  {
  print_inorder(this -> root);
  }
private:
void print_postorder(node<X> *temp_root)
  {
  if(temp_root == NULL)
    return;
  if(temp_root == root)
    cout<<"DATA: ";
  print_postorder(temp_root -> left);
  print_postorder(temp_root -> right);   
  cout<<temp_root -> data<<" ";
  if(temp_root == root)
    cout<<endl;
  }
public:
void print_postorder()
  {
  print_postorder(this -> root);
  }
private:
bool search(X d,node<X> *ptr)
  {
  if(ptr == NULL)
    ptr = root;
  if(ptr -> data == d)
    return true;
  else if(d < ptr -> data && ptr -> left != NULL)
    return  search(d,ptr -> left);
  else if(d > ptr -> data && ptr -> right != NULL)
    return search(d,ptr -> right);
  else
    return false;
  }
public:
bool search(X d)
  {
  return (search(d,root));
  }
//TO GET HEIGHT OF ROOT OR ANY OTHER NODE BUT IT IS PRIVATE
//BELOW THIS, A PUBLIC FUNCTION OF HEIGHT IS PRESENT WHICH IS ONLY TO GET HEIGHT OF ROOT i.e. OF TREE
private:
int height(node<X> *temp_root)
  {
  if(temp_root == NULL)
    return -1;
  else if((temp_root -> left == NULL) && (temp_root -> right == NULL))
    return 0;
  else
    {
    int height_left_subtree = height(temp_root -> left);
    int height_right_subtree = height(temp_root -> right);
    height_left_subtree++;height_right_subtree++;
    int max_height = (height_left_subtree >= height_right_subtree)? height_left_subtree:height_right_subtree;
    return max_height;	  
    }
  }
public:
int height()
{ 
return (height(this -> root));
}
private:
void search_address(X d,node<X> *temp_root,my_stack::stack<node<X>*>& s)
  {
  if(temp_root == NULL)
    s.pop();
  else if(d == temp_root -> data)
    {
    s.push(temp_root);
    return;
    }
  else if(d < temp_root -> data)
    {
    if(!s.empty())
      s.pop();
    s.push(temp_root);
    search_address(d,temp_root -> left,s);
    }
  else if(d > temp_root -> data)
    {
    if(!s.empty())
      s.pop();
    s.push(temp_root);
    search_address(d,temp_root -> right,s);
    }
  }
//FINDING INORDER WISE DATA BEFORE ROOT DATA
X largest_data_smaller_than_root(node<X> *temp_root)
  {
  if(temp_root -> right == NULL)
    return temp_root -> data;
  else
    return (largest_data_smaller_than_root(temp_root -> right));
  }
//FINDING INORDER WISE DATA AFTER ROOT DATA
X smallest_data_larger_than_root(node<X> *temp_root)
  {
  if(temp_root -> left == NULL)
    return temp_root -> data;
  else
    return (smallest_data_larger_than_root(temp_root -> left));
  }
public:
//BY RECURSION BUT USING STACK
void delete_node(X d)
  {
  my_stack::stack<node<X>*> s;
  search_address(d,root,s);
  if(s.empty())
    return;
  if(s.peek() -> left == NULL && s.peek() -> right == NULL)
    {
    if(s.peek() == root)
      {
      root = NULL;
      delete s.pop();
      }
    else
      {
      delete s.pop();
      if(d < s.peek() -> data)
        s.pop() -> left = NULL;
      else
        s.pop() -> right = NULL;
      }
    }
  else if(s.peek() -> left != NULL && s.peek() -> right != NULL)
    {
    node<X> *temp = s.pop();
    X to_replace_with = largest_data_smaller_than_root(temp->left);
    if(to_replace_with == d)
      to_replace_with = smallest_data_larger_than_root(temp->right);
    delete_node(to_replace_with);
    temp -> data = to_replace_with;
    }
  else
    {
    node<X> *node_to_be_restored = NULL;
    if(s.peek() -> right == NULL)
      node_to_be_restored = s.peek() -> left;
    else if(s.peek() -> left == NULL)
      node_to_be_restored = s.peek() -> right;
    delete (s.peek());
    if(s.peek() == root)
      {
      s.pop();
      root = node_to_be_restored;
      }
    else
      {
      s.pop();
      if(d > s.peek() -> data)
        s.peek() -> right = node_to_be_restored;
      else
        s.peek() -> left = node_to_be_restored;
      s.pop();
      }
    }
  }
//DELETING NODE OR ELEMENT BY RECURSION BUT THIS IS PRIVATE 
//BELOW THIS FUNCTION, A PUBLIC VERSION IS THERE WHICH DELETES A NODE FROM ROOT ONLY
private:
node<X>* delete_recursively(X d,node<X> *temp_root)
  {
  bool flag = true;
  if(temp_root == NULL)
    {
    std::cerr<<d<<" NOT FOUND...."<<endl;
    flag = false;
    }
  else if(temp_root -> data == d)
    {  
    flag = false;
    node<X> *node_to_be_restored = NULL;
    if(temp_root -> left == NULL && temp_root -> right == NULL)
      {
      delete temp_root;
      temp_root = NULL;
      }
    else if(temp_root->left != NULL && temp_root->right != NULL)
      {
      int to_replace_with = largest_data_smaller_than_root(temp_root -> left);
      if(to_replace_with == d)
        {
        to_replace_with = smallest_data_larger_than_root(temp_root -> right);
	temp_root -> right = delete_recursively(to_replace_with,temp_root -> right);
	temp_root -> data = to_replace_with;
	}
      else
        {
        temp_root -> left = delete_recursively(to_replace_with,temp_root -> left);
        temp_root -> data = to_replace_with;
	}
      }
    else
      {
      if(temp_root -> left == NULL)
        {
	node_to_be_restored = temp_root -> right;
	delete temp_root;
	temp_root = node_to_be_restored;
	}
      else if(temp_root -> right == NULL)
        {
	node_to_be_restored = temp_root -> left;
	delete temp_root;
	temp_root = node_to_be_restored;
	}
      }
    }
  else if(d < temp_root -> data)
    temp_root -> left = delete_recursively(d,temp_root -> left);
  else if(d > temp_root -> data)
    temp_root -> right = delete_recursively(d,temp_root -> right);
  if(flag)
    {
    int balance = height(temp_root -> left) - height(temp_root -> right);
    if(balance > 1)
      {
      if(d < (temp_root -> left) -> data)
        temp_root =  right_rotation(temp_root);
      else
        temp_root = left_right_rotation(temp_root);
      }
    else if(balance < -1)
      {
      if(d > (temp_root -> right) -> data)
        temp_root =  left_rotation(temp_root);
      else
        temp_root = right_left_rotation(temp_root);
      }
    }
  return temp_root;
  }
public:
//BY RECURSION
void delete_recursively(X d)
  {
  root = delete_recursively(d,this -> root);
  }
//CLEARING THE TREE FROM GIVEN NODE
//THIS IS PRIVATE BUT PUBLIC VERSION IS AVAILABLE BELOW IT WHICH CLEARS THE TREE FROM ROOT
private:
void clear(node<X> *temp_root)
  {
  if(temp_root == NULL)
    return;
  clear(temp_root -> left);
  clear(temp_root -> right);
  delete temp_root;
  root = NULL;
  }
public:
void clear()
  {
  clear(this -> root);
  }
//ROTATIONS

//LEFT ROTATION
node<X>* left_rotation(node<X> *temp_root)
  {
  node<X> *node_to_be_returned = temp_root -> right;
  node<X> *temp = temp_root -> right -> left;
  temp_root -> right -> left = temp_root;
  temp_root -> right = temp;
  return node_to_be_returned;
  }

//RIGHT ROTATION
node<X>* right_rotation(node<X> *temp_root)
  {
  node<X> *node_to_be_returned = temp_root -> left;
  node<X> *temp = temp_root -> left -> right;
  temp_root -> left -> right = temp_root;
  temp_root -> left = temp;
  return node_to_be_returned;
  }

//RIGHT - LEFT ROTATION : 2 ROTATION
node<X>* right_left_rotation(node<X> *grandparent)
  {
  node<X> *parent = grandparent -> right;
  node<X> *temp = parent -> left -> right;
  grandparent -> right -> left -> right = parent;
  grandparent -> right = parent -> left;
  parent -> left = temp;
  return (left_rotation(grandparent));
  }

//LEFT - RIGHT ROTATION : 2 ROTATION
node<X>* left_right_rotation(node<X> *grandparent)
 {
 node<X> *parent = grandparent -> left;
 node<X> *temp = parent -> right -> left;
 grandparent -> left = parent -> right;
 grandparent -> left -> left = parent;
 parent -> right = temp;
 return (right_rotation(grandparent));
 }

~binary_tree()
  {
  clear(this -> root);
  }
};
int main()
{
binary_tree<char> t;
t.insert_recursively('a');
//t.print_inorder();
t.insert_recursively('b');
//t.print_inorder();
t.insert_recursively('c');
//t.print_inorder();
t.insert_recursively('d');
//t.print_inorder();
t.insert_recursively('e');
//t.print_inorder();
t.insert_recursively('f');
//t.print_inorder();
t.insert_recursively('g');
//t.print_inorder();
t.insert_recursively('h');
//t.print_inorder();
t.insert_recursively('i');
t.insert_recursively('j');
t.print_preorder();
t.print_inorder();
t.print_postorder();
t.print_breadth_first();
//cout<<"SEARCH RESULT: "<<t.search('l');
//cout<<"SEARCH RESULT: "<<t.search('z');
//cout<<"SEARCH RESULT: "<<t.search('x');
//cout<<"HEIGHT: "<<t.height()<<endl;
//t.print_breadth_first();
//t.print_inorder();
cout<<"HEIGHT: "<<t.height()<<endl;
//t.clear();
//cout<<t.get_root();
//cout<<"SEARCHING ADDRESSES:"<<endl;
//t.insert('b');
//t.insert('h');t.insert('i');
//t.delete_node_2('m');
//cout<<t.get_root();t.print_inorder(t.get_root());
//t.delete_node_2('x');
//t.print_inorder(t.get_root());
//t.delete_node_2('j');
//t.print_inorder(t.get_root());
//t.delete_node_2('a');
//t.delete_node_2('r');
//t.delete_node_2('x');
//t.print_inorder(t.get_root());
//cout<<"HEIGHT: "<<t.height()<<endl;
return 0;
}
