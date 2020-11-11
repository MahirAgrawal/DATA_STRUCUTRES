#include<iostream>
#include<exception>
#include<string>
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl std::endl
//Template to make it a GENERIC CLASS
template<class X>
class Vector{
X *head;
int current_index;
int max_size;
public:
Vector(){
  max_size = 2;
  head = new X[max_size];
  current_index = 0;
  }
//RESIZE() FUNCTION IS USED TO RESIZE THE MAX_SIZE WHEN ELEMENTS BECOMES MORE THAN AVAILABLE SPACE
void resize(){
  max_size *= 2;
  auto temp_head = new X[max_size];
  for(int i = 0;i < current_index;i++)
    temp_head[i] = head[i];
  delete []head;
  head = temp_head;
  }
//ADDS DATA TO BACK i.e. TO THE END OF ARRAY
void push_back(X d){
  insert(current_index,d);
  }
//ADDS DATA TO FRONT i.e. TO THE ZEROTH INDEX
void push_front(X d){
  insert(0,d);
  }
//INSERTS THE DATA AT THE GIVEN POSITION
//BY MAKING ONE SPACE EMPTY FOR NEW DATA. IT DOES THIS BY TRANSFERRRING EACH ELEMENT TO IT'S RIGHT
//SO OVERALL MOVEMENT IS FROM LEFT TOWARDS RIGHT TO INCREASE SPACE BY ONE
//INSERTION IN ARRAY: O(n)
void insert(int index,X d){
  if(index < 0 || index > current_index)
    throw std::out_of_range("Vector::insert(i,d), index is not in range!!");//throws error of out_of_range and prints message                                                                                    inside out_of_range('HERE THIS MESSAGE')
  if(current_index == max_size)
    resize();
  for(int i = current_index;i > index;i--)
    head[i] = head[i-1];
  head[index] = d;
  current_index++;
  }
//ERASES FIRST ELEMENT FROM ARRAY
void pop_front(){
  erase(0);
  }
//ERASES LAST ELEMENT FROM ARRAY
void pop_back(){
  erase(current_index-1);
  }
//MAIN erase(int index) FUNCTION WHICH IS EXECUTED IN WHICH EACH ELEMENT TAKES PLACE OF IT'S PREVIOUS ELEMENT AND SO OVERALL 
//MOVEMENT IS FROM RIGHT TOWARDS THE LEFT TO REDUCE ONE POSITION 
//DELETION IN ARRAY: O(n)
void erase(int index){
  if(index < 0 || index >= current_index)
    throw std::out_of_range("Vector::erase(index), index is not in range!!");//throws error of out_of_range and prints message                                                                                     inside out_of_range('HERE THIS MESSAGE')
  if(current_index == 0) 
    cout<<"VECTOR UNDERFLOW!!"<<endl;
  else{
    for(int i = index;i < current_index-1;i++)
      head[i] = head[i+1];
    current_index--;
    }
  }
//RETURNS DATA OF PARTICULAR ITEM
//IF YOU INSTEAD OF 'X', RETURN THE 'X&'(REFERENCE) THEN IT WILL BE A BIG BLUNDER AS ANYONE CAN CHANGE THE DATA OF VECTOR ARRAY       BECAUSE CHANGES TO THE REFERENCES CHANGES THE ACTUAL OBJECT
//THEREFORE WE ARE ONLY RETURNING THE OBJECT COPY ANDN NOT THE OBJECT ITSELF
X at(int index){
  if(index < 0 || index >= current_index)
    throw std::out_of_range("Vector::at(index) terminated due to OUT_OF_BOUND");//Trying throwing error for the first time
  return head[index];
  }

//BOTH size() and length() RETURNS NUMBER OF DATA ITEMS IN VECTOR ARRAY
int size(){
  return current_index;
  }
int length(){
  return current_index;
  }
//RETURNS MAXIMUM DATA THAN CAN BE ACCOMODATED IN ARRAY
int capacity(){
  return max_size; 
  }
//FORGETS THE DATA BY SETTING current_index AT 0 SO THAT CAN ADDITION OF DATA OCCURS FROM '0' AND OLD DATA IS OVERWRITTEN
void clear(){
  current_index = 0;
  }
//RETURNS THE POINTER TO THE START OF ARRAY
X* begin(){
  return head;
  }
//RETURNS THE POINTER TO THE END OF ARRAY
X* end(){
  return (head+current_index);
  }
//CHECKS WHETHER THE VECTOR ARRAY IS EMPTY
bool empty(){
  if(current_index == 0)
    return true;
  else
    return false;
  }
~Vector(){
  max_size = 0;
  delete []head;
  current_index = 0;
  }
};
//TIPS FOR MAKING BEST USE OF ABOVE VECTOR CLASS
//If Adding User-defined classes' object in vector then make sure to overload '=' assignment operator to have 'DEEP COPY' of          elements stored in vector array
/*int main(){
  Vector<int> v;
  v.insert(3,4);
  }*/
