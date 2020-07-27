#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
class String{
static String *new_string;
int max_length = 100;
char *start = NULL;
char *end = NULL;
int index = 0;
public:
String(const char *s = NULL){
  start = new char[max_length];
  end = start+max_length-1;
  index = 0;
  if(s == NULL);
  else
    my_strcpy(s);
  }
String(String& s){
  start = new char[max_length];
  end = start+max_length-1;
  index = 0;
  for(int i = 0;i < s.length();i++)
    start[i] = s.start[i];
  index = s.index;
  }
void operator =(const char *to_copy_from){
  my_strcpy(to_copy_from);
  }
void operator =(String& s){
  for(int i = 0;i < s.length();i++)
    start[i] = s.start[i];
  index = s.index;
  }
String& operator +(const char *to_merge){
  if(new_string != NULL)  //this saves memory
    delete new_string;
  new_string = new String(*this);
  while(*to_merge != '\0'){
    new_string -> start[new_string -> index] = *to_merge;
    (new_string -> index)++;
    to_merge++; 
    }
  return *new_string; //Here it causes memory leak beacause this reference is of free store's object and then it is passed to string                      //Now whenever the String is passed to string then it makes a new copy(deep copy) and so this will be wasted!
                      //Can't delete because there is no way to delete once it's return and also once return there is no way to know                      //to know from which function it was created
		      //like e.g. if now i include code that will delete it when it is passed to string object by copy constructor                        //then all such string passed to copy constructor will be deleted(freed)
		      //So this function equivalent can be useful if there would be automatic garbage collector(like in java)
		      //I THINK IT CAN CAUSE A MAJOR MEMORY LEAK PROBLEM!!!!
		      //
		      //SOLVED THE PROBLEM WITH SIMPLY DECLARING STATIC MEMBER CALLED 'new_string'
		      //NOW WHENEVER THIS VARIABLE IS USED FIRST IT WILL BE CHECKED THAT IT IS NULL OR NOT
		      //IF(!NULL) -> IT WILL DELETE THE EARLIER ALLOCATED MEMORY THEN ONLY WILL GO AHEAD TO ALLOCATE NEW
		      //NOW IN WORST CASE IT CAN HAPPEN THAT 'operator +' IS USED ONCE THEN ONLY THE MEMORY REMAIN WASTED
		      //BUT AS SOON AS THE FUNCTION IS AGAIN CALLED THEN THE PREVIOUS MEMORY IS CLEARED
		      //
		      //SEE CODE WITH COMMENT 'SAVES MEMORY' FOR IMPLEMENTATION
  }
String& operator +(String& s){
  if(new_string != NULL)//this saves memory
    delete new_string;
  new_string = new String(*this);
  for(int i = 0;i < s.length();i++)
    new_string -> start[i+index] = s.start[i];
  new_string -> index;
  new_string -> index += s.index;
  return *new_string;
  }
void my_strcpy(const char *to_copy_from){
  clear();
  while(*to_copy_from != '\0'){
    start[index] = *to_copy_from;
    to_copy_from++;index++;
    }
  }
int size(){
  return index;
  }
int length(){
  return index;
  }
void clear(){
  index = 0;
  }
~String(){
  clear();
  delete []start;
  start = NULL;
  end = NULL;
  }
friend std::ostream& operator <<(std::ostream&,String&);
};
std::ostream& operator <<(std::ostream& out,String& s){
  for(int i = 0;i < s.length();i++)
    out<<s.start[i];
  return out;
  }
String* String::new_string = NULL;
int main(){
String s("Khushi ");
//s = "Agrawal";
String str = s + " Agrawal";//str = khushi agrawal
//str = s + " Agrawal"; 
String t;
t = s;//t = khushi
cout<<"Str:"<<str<<endl;
cout<<"T:"<<t<<endl;;
s = str + t;//khushi agrawalkhushi
cout<<"S:"<<s<<endl;
String father("Lalit");
String firstname("Mihir ");
String name = firstname + father;
cout<<name.length();
cout<<"Name:"<<name;//<<endl;
return 0;
}
