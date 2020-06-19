#include<iostream>
#include<chrono>
#include<string.h>
#define cout std::cout
#define cin std::cin
#define endl std::endl
class string{
char *str = NULL;
int length = 0;
public:
string()
{
length = 0;
str = NULL;
}
void operator =(char *s)
{
length = 0;
str = s;
while(*str != '\0')
  {
  length++;
  str++;
  }
str = new char[length+1];
strcpy(str,s);
}
void operator =(const string& s)
{
this -> str = new char[(s.length)+1];
strcpy(this -> str,s.str);
this -> length = s.length;
}
string operator +(string& s)
{
string temp;
temp.length = this -> length + s.length;
temp.str = new char[temp.length+1];
char *ptr = str;
char *iterator = temp.str;
while(*ptr != '\0')
  {
  *iterator = *ptr;
  iterator++;ptr++;
  }
ptr = s.str;
while(*ptr != '\0')
  {
  *iterator = *ptr;
  iterator++;ptr++;
  }
*iterator = '\0';
return temp;
}
int size()
{
return length;
}
~string()
{
delete []str;
length = 0;
}
friend std::ostream& operator <<(std::ostream& obj,string& s);
friend std::istream& operator >>(std::istream& obj,string& s);
};
std::ostream& operator <<(std::ostream& obj,string& s)
{
obj<<s.str;
return obj;
}
std::istream& operator >>(std::istream& obj,string& s)
{
char temp_arr[100];
obj.getline(temp_arr,100);
s = temp_arr;
return obj;
}
/*int main()
{
string s1,s2;
cin>>s1>>s2;
cout<<endl<<"SIZE:"<<s1.size()<<" "<<s2.size()<<endl;
string s3 = s1 + s2;
cout<<"Size s3:"<<s3.size()<<endl;
cout<<s3<<endl;
cin>>s1;
cout<<s1<<endl;
cout<<"size s1:"<<s1.size()<<endl;
return 0;
}*/
