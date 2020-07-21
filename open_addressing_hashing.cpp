#include<iostream>
#include<string>
#include<cmath>
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl std::endl
bool is_prime(int n)
  {
  int limit = sqrt(n);
  for(int i = 2;i <= limit;i++)
    if(n%i == 0)
      return false;
  return true;
  }
int next_prime(int current_prime)
  {
  current_prime *= 2;
  bool flag = false;
  while(!flag)
    {
    current_prime++;
    flag = is_prime(current_prime);
    }
  return current_prime;
  }
template<class X>
class hash_table{
struct slot{
  string name;
  X data;
  slot()
    {
    name = "";
    }
  };
int MAX_LENGTH;
slot *hash_slot;
int hash_function(string& name)
  {
  unsigned long int hash = 0;
  for(int i = 0;i < name.length();i++)
    hash += (pow(i,31)+name.at(i));
  return (hash%MAX_LENGTH);
  }
int next_index(int index)
  {
  return ((index+1)%MAX_LENGTH);
  }
public:
hash_table()
  {
  MAX_LENGTH = 31;
  hash_slot = new slot[MAX_LENGTH];  
  }
/*void resizing()
  {
  temp_hash_slot = new slot[next_prime(MAX_LENGTH)];
  for()
  }
*/
void add(string s,X d)
  {
  if(s.size() == 0)
    {
    cout<<"CAN'T ADD DATA WITHOUT NAME!"<<endl;
    return;
    }
  auto index = hash_function(s);
  auto original_index = index;
  while(hash_slot[index].name.size() != 0 && hash_slot[index].name != "DELETED")
    {
    if(hash_slot[index].name == s)
      {
      cout<<"ALREADY EXISTS!!"<<endl;
      cout<<"TRY UPDATING INSTEAD!!"<<endl;
      return;
      }
    index = next_index(index);
    if(index == original_index)
      {
      cout<<"THE TABLE IS FULL!";
      return;
      }
    }
    hash_slot[index].name.assign(s);
    hash_slot[index].data = d;
  } 
private:
int search(string& n)
  {
  auto index = hash_function(n);
  auto original_index = index;
  do{
  if(hash_slot[index].name == n)
    return index;
  else
    index = next_index(index);
  }while(hash_slot[index].name != "" && index != original_index);
  return -1;
  }
public:
X search_key(string n)
  {
  int index = search(n);
  if(index == -1)
    {
    cout<<"NOT FOUND AND RETURNING GARBAGE VALUE!!"<<endl;
    return -2122111;
    }
  else
    return hash_slot[index].data;
  }
void update(string n,X d)
  {
  int index = search(n);
  if(index == -1)
    {
    cout<<"CANNOT UPDATE NON-EXISTING VALUES!!"<<endl;
    cout<<"TRY ADDING INSTEAD!!"<<endl;
    }
  else
    hash_slot[index].data = d;
  }
void delete_key(string n)
  {
  int index = search(n);
  if(index == -1)
    {
    cout<<"NAME DOESN'T EXIST!"<<endl;
    return;
    }
  else
    {
    hash_slot[index].name = "DELETED";
    return;
    }
  }
void print_table()
  {
  cout<<"START:"<<endl;
  for(int i = 0;i < MAX_LENGTH;i++)
    {
    if(hash_slot[i].name == "" || hash_slot[i].name == "DELETED")
      cout<<"--- ---"<<endl;
    else
      cout<<"NAME: "<<hash_slot[i].name<<" "<<"MARKS: "<<hash_slot[i].data<<endl;
    }
  cout<<"END"<<endl;
  }
};
int main()
{
hash_table<float> h;
h.print_table();
h.add("Mihir",45);
h.add("Khushi",34);
h.add("Lalit",45.32);
h.add("Rupal",34.65);
h.add("Khush",34.4);
h.add("Rakesh",341);
h.add("Devansh",324);
h.add("Vansh",54.3);
h.add("Vihaan",90.6);
h.add("Shrey",89.55);
h.add("Mahir",103.3);
h.add("Mihi",43);
h.add("Kk",34);
h.add("Mk",133);
h.print_table();
h.delete_key("Mihir");
h.delete_key("Mihir");
h.update("Lalit",100);
h.update("Mihir",12);
cout<<h.search_key("Lalit")<<endl;
cout<<h.search_key("Llt")<<endl;
h.print_table();
cout<<next_prime(34);
return 0;
}
