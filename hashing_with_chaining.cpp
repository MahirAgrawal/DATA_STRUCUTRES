#include<iostream>
#include<string>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define string std::string
#define MAX_SIZE 17
template<class X>
class chaining_hash;
template<class X>
class Node{
string name;
X data;
Node *next = NULL;
Node(string& str,X d,Node *next_node = NULL)
  {
  name.assign(str);
  data = d;
  next = next_node;
  }
~Node()
  {
  name.clear();
  X garbage;
  next = NULL;
  data = garbage;
  }
friend class chaining_hash<X>;
};
//HASHING WITH CHAINING TO RESOLVE COLLISION
//EACH SLOT IN HASH TABLE STORES LINKED LIST I.E. ADDRESS OF NODE<X>
//INSERTS TO THE HEAD POINTER OF SLOT IF SLOT IS TAKEN
//STILL INEFFICIENT AS BAD HASH FUNCTION LIKE MINE ABOVE, CAN MAP ALL KEYS TO A SINGLE SLOT THUS REDUCING OUR EFFORTS TO            SINGLY LINKED LIST
template<class X>
class chaining_hash{
Node<X> *hash_table[MAX_SIZE];
int hash(string s)
  {
  unsigned int h = 0;
  for(int i = 0;i < s.length();i++)
    h += (s.at(i)*i*i*s.at(0));
  return (h % MAX_SIZE);
  }
public:
chaining_hash()
  {
  for(int i = 0;i < MAX_SIZE;i++)
    hash_table[i] = NULL;
  }
bool add(string n,X data)
  {
  int index = hash(n);
  if(hash_table[index] == NULL)
    hash_table[index] = new Node<X>(n,data,NULL);
  else
    {
    Node<X> *ptr = hash_table[index];
    while(ptr != NULL)
      { 
      if((ptr -> name) == n)
        {
        cout<<"DUPLICATE FOUND OF "<<ptr -> name<<" ";
	cout<<"TRY UPDATING INSTEAD!!!"<<endl;
	return false;
	}
      ptr = ptr -> next;  
      }
    hash_table[index] = new Node<X>(n,data,hash_table[index]);
    }
    return true;
    }
bool update(string n,X d)
  {
  int index = hash(n);
  if(hash_table[index] == NULL);
  else
    {
    Node<X> *ptr = hash_table[index];
    while(ptr != NULL)
      { 
      if(ptr -> name == n)
        {
        ptr -> data = d;
	return true;
	}
      ptr = ptr -> next;  
      }
    }
  cout<<"CAN'T FIND GIVEN NAME!\n";
  return false;
  }
bool find(string n)
  {
  int index = hash(n);
  if(hash_table[index] == NULL);
  else
    {
    Node<X> *ptr = hash_table[index];
    while(ptr != NULL)
      { 
      if(ptr -> name == n)
        {
        cout<<"NAME : "<<n<<" = "<<ptr -> data<<endl;
	return true;
	}
      ptr = ptr -> next;  
      }
    }
  return false;
  }
void delete_key(string s)
  {
  Node<X> *ptr = NULL,*ptr_next = NULL;
  int index = hash(s);
  if(hash_table[index] == NULL);
  else
    {
    ptr = hash_table[index];
    if(ptr -> name == s)
      {
      hash_table[index] = hash_table[index] -> next;
      delete ptr;
      }
    else if(ptr -> next == NULL);
    else
      {
      while(ptr != NULL)
        {
       	ptr_next = ptr;
	ptr = ptr -> next;
	if(ptr && ptr -> name == s)
          {
          ptr_next -> next = ptr -> next;
          delete ptr;
          break;
	  }
        }
      }
    }
  } 
void print_table()
  {
  Node<X> *ptr = NULL;
  for(int i = 0;i < MAX_SIZE;i++)
    {
    ptr = hash_table[i];
    if(ptr == NULL)
      cout<<"--- ---";
    else
      {
      while(ptr != NULL)
        {
        cout<<ptr -> name<<":"<<ptr -> data<<" -> ";
        ptr = ptr -> next;
        }
      cout<<"|";
      }
    cout<<endl;
    }
  }
~chaining_hash()
  {
  Node<X> *ptr = NULL;
  Node<X> *temp = NULL;
  for(int i = 0;i < MAX_SIZE;i++)
    {
    ptr = hash_table[i];
    while(ptr != NULL)
      {
      temp = ptr;
      ptr = ptr -> next;
      delete temp;
      }
    }
  }
};
int main()
{
chaining_hash<float> h;
h.add("Mihir",90.6);
//h.print_table();
h.add("Hir",93.6);
//h.print_table();
h.add("Khushi",10.6);
//h.print_table();
h.add("Sushi",50.6);
//h.print_table();
h.add("ir",90.6);
h.add("s",22.33);
h.add("a",44.223);
h.add("g",23.75);
h.add("y",12.35);
h.add("o",21.2);
h.add("Urvashi",32.6);
h.add("Bhais",66);
h.add("Bais",0.6);
h.add("Khushi bai",9.6);
h.add("Khushi Bais",20.6);
h.add("Seer",54.4);
h.add("Sir",788.55);
h.print_table();
h.find("Bais");
h.find("Serr");
h.find("Mihir");
h.find("s");
h.find("Sushi");
h.find("sushi");
h.find("Bais");
h.find("Bais");
h.update("Mihir",20);
h.update("Suh",20);
h.update("g",20);
h.update("Hir",20);
cout<<"DELETING KEY"<<endl;
h.delete_key("Mihir");
cout<<"deleted first!!"<<endl;
h.delete_key("Sir");
cout<<"deleted second!!"<<endl;
h.delete_key("g");
cout<<"deleted third!!"<<endl;
h.print_table();
h.delete_key("Sir");
cout<<"deleted fourth!!"<<endl;
h.print_table();
return 0;
}
