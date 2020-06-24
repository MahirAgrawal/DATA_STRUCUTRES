#include<iostream>
#include<vector>
#include<cstdio>
#include"my_time.h"
#include<stdlib.h>
#include"stack.h"
#include"queue.h"
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define vector std::vector
template<class X>
class binary_tree;
template<class X>
class node{
node *left = NULL;
X data;
node *right = NULL;
public:
node()
{
left = NULL;
right = NULL;
}
~node()
{
left = NULL;
right = NULL;
X temp;
data = temp;
//cout<<"NODE IS DELETED.."<<endl;
}
friend class binary_tree<X>;
};
template<class X>
class binary_tree{
node<X> *root = NULL;
int nodes = 0;
stack::stack<X> my_stack;
stack::stack<node<X>*> address_buffer;
public:
//stack::stack<node<X>*> address_buffer;
binary_tree()
{
root = NULL;
}
void insert_recursively(node<X> *temp_root,X d)
{
if(temp_root == NULL)
  {
  root = new node<X>; 
  root -> data = d;
  }
else if(d <= (temp_root -> data))
  {
  if(temp_root -> left == NULL)
    {
    node<X> *temp = new node<X>; 
    temp -> data = d;
    temp_root -> left = temp;
    }
  else
    insert_recursively(temp_root->left,d);
  }
  else if(d > (temp_root -> data))
    {
    if(temp_root -> right == NULL)
      {
      node<X> *temp = new node<X>; 
      temp -> data = d;
      temp_root -> right = temp;
      }
    else
      insert_recursively(temp_root->right,d);
    }
}
void insert(X d)
{
//cout<<"D:"<<d<<(char)d<<endl;
node<X> *temp = new node<X>; 
temp -> data = d;
if(root == NULL)
  root = temp;
else
  {
  node<X> *temp_root = root;
  bool flag = true;
  while(flag)
    {
    //cout<<"IN WHILE..."<<endl;
    if(d <= (temp_root->data))
      {
      if(temp_root -> left == NULL)
        {
        temp_root -> left = temp;
        flag = false;
        }
      else
         temp_root = temp_root -> left;
      }
    else if(d > (temp_root -> data))
      {
      if(temp_root -> right == NULL)
        {
        temp_root -> right = temp;
        flag = false;
        }
      else
        temp_root = temp_root -> right;
      }
    }
  }
}
//BREADTH FIRST
void print_bf()
{
my_queue::queue<node<X>*> q;
if(root == NULL)
  return;
else
  {
  if(q.is_empty())
    {
    cout<<root -> data<<" ";
    if(root -> left != NULL)
      q.enqueue(root -> left);
    if(root -> right != NULL)
      q.enqueue(root -> right);
    }
  while(!q.is_empty())
    {
    cout<<q.peek() -> data<<" ";
    if(q.peek() -> left != NULL)
      q.enqueue(q.peek() -> left);
    if(q.peek() -> right != NULL)
      q.enqueue(q.peek() -> right);
    q.dequeue();
    }
  }
}
bool search(X d)
{
bool flag = true;
node<X> *temp_root = root;
while(flag)
  {
  if(temp_root -> data == d)
    {
    cout<<temp_root -> data<<endl;
      return true;
    }
  else if(d < (temp_root -> data))
    {
    if(temp_root -> left == NULL)
      return false;
    else
      temp_root = temp_root -> left;
    }
  else if(d > (temp_root -> data))
    {
    if(temp_root -> right == NULL)
      return false;
    else
      temp_root = temp_root -> right;
    }
  }
}
node<X>* search_address(node<X> *root_t,X d)
{
//cout<<"ROOTROOTROOT "<<(unsigned int)root_t<<endl;
node<X> *ptr = NULL;
if(root_t == NULL)
  ptr = NULL;
else if(root_t -> data == d)
  ptr = root_t;
else if(d <= root_t -> data)
  {
  if(address_buffer.is_empty())
    address_buffer.push(root_t);
  else
    {
    address_buffer.pop();
    address_buffer.push(root_t);
    }
  ptr = search_address(root_t -> left,d);
  }
else if(d > root_t -> data)
  {
  if(address_buffer.is_empty())
    address_buffer.push(root_t);
  else
    {
    address_buffer.pop();
    address_buffer.push(root_t);
    }
  ptr = search_address(root_t -> right,d);
  }
//cout<<"PTRPTRPTR: "<<(unsigned int)ptr<<endl;
return ptr;
}
int height(node<X> *t_root = NULL)
{
int left,right;
if(t_root == NULL)
  return -1;
left = height(t_root -> left);
right = height(t_root -> right);
left++;right++;
if(left >= right)
  return left;
else
  return right;
}
X max(node<X> *temp_root = NULL)
{
X t_data;
if(temp_root == NULL)
  return t_data;
else if(temp_root -> right == NULL)
  return temp_root -> data;
else
  return (max(temp_root -> right));
}
node<X>* max_address_from_left(node<X> *temp_root = NULL)
{
temp_root = temp_root -> left;
while(temp_root -> right != NULL)
  temp_root = temp_root -> right;
return temp_root;
}
node<X>* min_address_from_right(node<X> *temp_root = NULL)
{
temp_root = temp_root -> right;
while(temp_root -> left != NULL)
  temp_root = temp_root -> left;
return temp_root;
}
X min(node<X> *temp_root = NULL)
{
X t_data;
if(temp_root == NULL)
  return t_data;
else if(temp_root -> left == NULL)
  return temp_root -> data;
else
  return min(temp_root -> left);
}
//PRINT DEPTH FIRST
void print_inorder(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return;
print_inorder(ptr -> left);
cout<<ptr -> data<<" ";
print_inorder(ptr -> right);
}
void print_preorder(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return; 
cout<<ptr -> data<<" ";
print_preorder(ptr -> left);
print_preorder(ptr -> right);
}
void print_postorder(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return;
print_postorder(ptr -> left);
print_postorder(ptr -> right);
cout<<ptr -> data<<" ";
}
void is_binary_tree(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return;
is_binary_tree(ptr -> left);
if(!(my_stack.is_empty()))
  {
  if(my_stack.peek() >= ptr -> data)
    {
    cout<<"NOT A BINARY TREE!"<<endl;
    return;
    }
  else 
    my_stack.push(ptr -> data);
  }
else 
  my_stack.push(ptr -> data);
is_binary_tree(ptr -> right);
}
void remove(X d)
{
node<X> *ptr = NULL;
address_buffer.clear();
ptr = search_address(this -> root,d);
if(ptr == NULL)
  {
  cout<<"NO SUCH OBJECT EXIST!!"<<endl;
  address_buffer.clear();
  return;
  }
if((ptr -> left == NULL) && (ptr -> right == NULL))
  {
  if((address_buffer.peek()->data) < ptr -> data)
    address_buffer.peek() -> right = NULL;
  else
    address_buffer.peek()->left = NULL;
  delete ptr;
  }
else if((ptr -> left == NULL) || (ptr -> right == NULL))
  {
  if((address_buffer.peek()->data) < ptr -> data)
    {
    if(ptr -> right == NULL)
      address_buffer.peek() -> right = ptr -> left;
    else if(ptr -> left == NULL)
      address_buffer.peek() -> right = ptr -> right;
    }
  else
    {
    if(ptr -> right == NULL)
      address_buffer.peek() -> left = ptr -> left;
    else if(ptr -> left == NULL)
      address_buffer.peek() -> left = ptr -> right;
    }
  delete ptr;
  }
  else
  {
  node<X> *maximum = max_address_from_left(ptr);
  //cout<<"MINNIMUM ADDRESS:"<<(unsigned int)minimum<<"DATAMIN: "<<minimum->data<<endl;
  X temp_data = maximum -> data;
  remove(maximum -> data);
  ptr -> data = temp_data;
  }
//cout<<"STACKISEMPTY: "<<address_buffer.is_empty()<<endl;
address_buffer.clear();
}
void clear_root(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return	;
node<X> *list[2] = {ptr -> left,ptr -> right};
clear_root(list[0]);
clear_root(list[1]);
delete ptr;
}
node<X>* get_root()
{
return root;
}
~binary_tree()
{
clear_root(this->root);
}};

int main()
{
binary_tree<int> b;
int n = 0,t = 0;
cout<<"ENTER N:";
cin>>n;
fflush(stdin);
//timer t2;
//srand(n+2);
for(int i = 0;i < n;i++)
  {
  //cout<<"ENTER THE ELEMENT TO BE INSERTED IN BINARY TREE: ";
  cin>>t;
  b.insert(t);
  //b.insert_recursively(b.get_root(),rand()%100);
  }
//t2.stop();
cout<<"DATA: ";
//cout<<"BREADTH FIRST PRINTING:";
//b.print_bf();
cout<<endl;
b.print_inorder(b.get_root());cout<<endl;
//b.print_preorder(b.get_root());cout<<endl;
//b.print_postorder(b.get_root());cout<<endl;
for(int i = 0;i < 4;i++)
{
cout<<"ENTER THE ELEMENT TO BE DELETED: ";
cin>>t;
b.remove(t);
cout<<"DATA: ";
cout<<endl;
b.print_inorder(b.get_root());cout<<endl;
}
//if(b.search(12) == 0)
  //cout<<"NOT FOUND...."<<endl;
/*node<int> *ptr = b.search_address(b.get_root(),55);
if(ptr != NULL)
  {
  cout<<"PTR:"<<ptr -> data<<" "; 
  cout<<(b.address_buffer.peek())-> data<<" ";
  cout<<((b.address_buffer.peek()) -> left) -> data<<" ";
  cout<<"??????"<<endl;
  }
else
  b.address_buffer.clear();
ptr = b.search_address(b.get_root(),235);
if(ptr != NULL)
  {
  cout<<"PTR:"<<ptr<<endl; 
  b.address_buffer.display();
  cout<<"??????"<<endl;
  }
else
  b.address_buffer.clear();
  b.search(7);
binary_tree<char> tree;
cout<<"ENTER N:";
cin>>n;
fflush(stdin);
char ch;
t2.reset();
for(int i = 0;i < n;i++)
  {
  cout<<"ENTER THE ELEMENT TO BE INSERTED IN BINARY TREE: ";
  cin>>ch;
  tree.insert(ch);
  //b.insert('a'+(rand()%10));
  }
t2.stop();
cout<<"DATA: ";	
tree.print_preorder(tree.get_root());cout<<endl;
tree.print_postorder(tree.get_root());cout<<endl;*/
cout<<"max:"<<b.max(b.get_root())<<" MIN: "<<b.min(b.get_root());
cout<<"Height = "<<b.height(b.get_root())<<endl;
//cout<<"Height = "<<tree.height(tree.get_root())<<endl;
return 0;
}
