#include<iostream>
#include<cstdio>
#include"my_time.h"
#include<stdlib.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
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
public:
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
int height(node<X> *t_root = NULL,int i = 0)
{
int left,right;
if(t_root == NULL)
  return 0;
left = height(t_root -> left,i+1);
right = height(t_root -> right,i+1);
if(i != 0)
  {
  left++;
  right++;
  }
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
void print(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return;
print(ptr -> left);
cout<<ptr -> data<<" ";
print(ptr -> right);
}
node<X>* get_root()
{
return root;
}
/*void remove(X d){}*/
void clear_root(node<X> *ptr = NULL)
{
if(ptr == NULL)
  return;
node<X> *list[2] = {ptr -> left,ptr -> right};
clear_root(list[0]);
clear_root(list[1]);
delete ptr;
}
~binary_tree()
{
clear_root(this->root);
//cout<<"COMPLETED!!!"<<endl;
}
};
int main()
{
binary_tree<int> b;
int n = 0,t = 0;
cout<<"ENTER N:";
cin>>n;
fflush(stdin);
timer t2;
srand(n+2);
for(int i = 0;i < n;i++)
  {
  //cout<<"ENTER THE ELEMENT TO BE INSERTED IN BINARY TREE: ";
  cin>>t;
  b.insert(t);
  //b.insert_recursively(b.get_root(),rand()%100);
  }
t2.stop();
cout<<"DATA: ";
b.print(b.get_root());
if(b.search(12) == 0)
  cout<<"NOT FOUND...."<<endl;
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
tree.print(tree.get_root());
cout<<"max:"<<b.max(b.get_root())<<" MIN: "<<b.min(b.get_root());
cout<<"Height = "<<b.height(b.get_root())<<endl;
cout<<"Height = "<<tree.height(tree.get_root())<<endl;
return 0;
}

