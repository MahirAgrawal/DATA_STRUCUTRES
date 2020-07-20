#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<time.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define string std::string
#define MAX_SIZE 23
//SIMPLEST HASHING TECHNIQUE
//BUT IT DOES NOT DEAL WITH COLLISION AS IT DON'T ACCEPT INPUT IF THERE IS COLLISION SO NOT USEFUL BECAUSE DOESN'T STORE ALL INPUTS  GIVEN TO IT
//ALSO FIXED SIZE OF HASH TABLE SO CANNOT WORK IN CASE OF LARGER INPUT DATA THAN SIZE OF HASH TABLE

//BASIC FUNCTIONS:
//ADD_KEY()
//REMOVE_KEY()
//UPDATE_KEY()
//SEARCH_KEY()
//PRINT() : ENTIRE HASH TABLE
class hash;
struct hash_slot{
float marks;
string name;
hash_slot()
  {
  name = "";
  marks = -1;
  }
~hash_slot()
  {
  name.clear();
  marks = -1;
  }
friend class hash;
};
class hash{
hash_slot hash_table[MAX_SIZE];
int random = 0;
int hash_function(string s)
  {
  unsigned long int hash = 0;
  for(int i = 0;i < s.size();i++)
    hash += (i*s[i]*random);
  for(int i = s.length()-1;i >= 0;i--)
    hash += (i*s[i]*random);
  return (hash % MAX_SIZE);
  }
bool search(string s)
  {
  int index = hash_function(s);
  if(hash_table[index].name == s)
    return true;
  else
    return false;
  }
public:
hash()
  {
  srand(time(NULL));
  random = rand();
  }
void add(string s,float marks)
  {
  int index = hash_function(s);
  cout<<"STRING: "<<s<<" HASH: "<<index<<endl;
  if(hash_table[index].name.size() == 0)
    {
    hash_table[index].marks = marks;
    hash_table[index].name.assign(s);
    }
  else
    std::cerr<<"COULD NOT ADD "<<s<<" 's MARKS..."<<endl;
  }
void update(string s,float new_marks)
  {
   if(search(s))
     {
     hash_table[hash_function(s)].marks = new_marks;
     cout<<"UPDATED!!"<<endl;
     }
  else
    std::cerr<<"COULD NOT UPDATE "<<s<<" 's MARKS..."<<endl;
  }
float get(string s)
  {
  if(search(s))
    return (hash_table[hash_function(s)].marks);
  else 
    {
    std::cerr<<"VALUE DOESN'T EXIST!!"<<endl<<"RETURNING GARBAGE VALUE!!!\n";
    return -2322.33f;
    }
  }
void remove(string s)
  {
  if(search(s))
    {
    int index = hash_function(s);
    cout<<"DO YOU REALLY WANT TO REMOVE THE BELOW PAIR OF VALUES ?\n"                                                                       <<hash_table[index].name<<" : "<<hash_table[index].marks<<endl;
    cout<<"EXECUTE THE JOB ?(Y/N) : ";
    char response;
    cin>>response;
    fflush(stdin);
    switch(response)
      {
      case 'Y':
      case 'y':
      hash_table[index].name.clear();
      hash_table[index].marks = -1;
      break;
      case 'N':
      case 'n':
      std::cerr<<"DELETION TERMINATED!!"<<endl;
      break;
      default:
      std::cerr<<"NOT AN OPTION!!\n"<<endl;
      }
    }
  else
     return;
  }
void print_table()
  {
  cout<<"START:"<<endl;
  for(int i = 0;i < MAX_SIZE;i++)
    { 
    if(hash_table[i].name.size() != 0)
      cout<<hash_table[i].name<<" "<<hash_table[i].marks<<endl;
    else
      cout<<"------   -------"<<endl;
    }
  cout<<"END"<<endl;
  }
};
int main()
{
hash h;
h.add("mihir",20);
h.add("mihir",234.5);
cout<<"MARKS:"<<h.get("mihi")<<endl;
h.add("khushi",56);
h.remove("mihir");
h.update("mihir",1);
h.add("khushi",56);
h.add("mahir",23);
h.add("hir",2.125);
h.add("khu",532);
h.add("hi",2.20);
h.add("rara",324.5);
h.add("shi",67);
cout<<"MARKS:"<<h.get("mihi")<<endl;
cout<<"MARKS:"<<h.get("khushi")<<endl;
h.print_table();
return 0;
}
