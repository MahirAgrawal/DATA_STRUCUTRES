//QUADRATIC PROBING
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
  ~slot()
    {
    name = "";
    //cout<<"DELETED!!"<<endl;
    }
  };
int MAX_LENGTH;
int keys;
slot *hash_slot;
int hash_function(string& name)
  {
  unsigned long int hash = 0;
  for(int i = 0;i < name.length();i++)
    hash += (pow(i,31)+name.at(i));
  return (hash%MAX_LENGTH);
  }
int next_index(int index,int counter)
  {
  return ((int)(index+pow(counter,2)))%MAX_LENGTH;
  }
public:
hash_table()
  {
  keys = 0;
  MAX_LENGTH = 11;
  hash_slot = new slot[MAX_LENGTH];  
  }
void resizing()
  {
  keys = 0;
  int TEMP_MAX_LENGTH = MAX_LENGTH;
  MAX_LENGTH = next_prime(MAX_LENGTH);
  slot *temp_hash_slot = hash_slot;
  hash_slot = new slot[MAX_LENGTH];
  for(int i = 0;i < TEMP_MAX_LENGTH;i++)
    {
    if(temp_hash_slot[i].name == "" || temp_hash_slot[i].name == "DELETED")
      continue;
    add(temp_hash_slot[i].name,temp_hash_slot[i].data);
    }
  delete []temp_hash_slot;
  }
void add(string s,X d)
  {
  int counter = 0;
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
    counter++;
    index = next_index(original_index,counter);
    }
  hash_slot[index].name.assign(s);
  hash_slot[index].data = d;
  keys++;
  double load_factor = ((double)keys)/MAX_LENGTH;
  if(load_factor > 0.5)
    resizing();
  }
int size_of_table()
  {
  return MAX_LENGTH;
  }
private:
int search(string& n)
  { 
  int counter = 0;
  auto index = hash_function(n);
  auto original_index = index;
  do{
  if(hash_slot[index].name == n)
    return index;
  counter++;
  index = next_index(original_index,counter);
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
    keys--;
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
      cout<<hash_slot[i].name<<" "<<hash_slot[i].data<<endl;
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
h.add("Ansh",54.3);
h.add("Raj",90.6);
h.add("Ans",89.55);
h.add("Anshul",103.3);
h.add("Ty",54.3);
h.add("Yk",90.6);
h.add("Oppo",89.55);
h.add("rara",103.3);
h.add("Vira",54.3);
h.add("Vihan",90.6);
h.add("Shreya",89.55);
h.add("Mahirra",103.3);
h.print_table();
h.delete_key("Mihir");
h.delete_key("Mihir");
h.update("Lalit",100);
h.update("Mihir",12);
cout<<"SEARCH:"<<endl;
cout<<h.search_key("Rupal")<<endl;
cout<<h.search_key("Lalit")<<endl;
cout<<"serach ends..."<<endl;
h.add("Rk",1763);
h.add("Uk",13.3);
h.add("Kk",1.33);
h.add("Lk",1.3);
h.add("Ghk",3);
h.print_table();
cout<<h.size_of_table();
return 0;
}
