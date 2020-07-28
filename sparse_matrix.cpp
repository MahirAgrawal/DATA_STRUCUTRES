#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#include<vector>
class Coordinate{
public:
short int x;
short int y;
int data;
Coordinate *next;
Coordinate(short int& x_co,short int& y_co,int& d){
  x = x_co;y = y_co;data = d;
  next = NULL;
  }
~Coordinate(){
  x = 0;
  y = 0;
  data = 0;
  next = NULL;
  }
};

//WHY WE USE LINKED LIST AND SIMPLE ARRAY TO STORE POINTER TO COORDINATE DATA ELEMENTS ?
//->) BEACAUSE THE WHOLE IDEA TO USE MINIMUM SPACE FOR SPARSE MATRIX. NOW IF FOR MxN MATRIX YOU USE THE MxN SIZED ARRAY FOR STROING  POINTERS THEN IT IS AS BAD AS YOU ARE WASTING A MxN ARRAY FOR SPARSE MATRIX ITSELF. SO WE NEED DYNAMIC ARRAYS FOR STORING WHICH    TAKE SPACE AS PER THE DEMAND. NOW WE HAVE TWO OPTIONS :
//1) FIRST STORE THE ELEMENTS TEMPORARY IN A MxN ARRAY WHILE TAKING INPUT AND THEN SCAN THROUGH THE MxN MATRIX TO FIND THE ACTUAL   NUMBER OF ELEMENTS AND ALLOCATE MEMORY FOR ARRAY OF SIZE AS PER SCAN RESULT. 
//2) SECOND TAKE INPUT -- IF 0 continue -- ELSE STORE IT IN LINK LIST NODES RIGHT AT THE MOMENT

//FOR 1) THERE IS DISADVANTAGE THAT WE HAVE TO SCAN WHOLE MxN MATRIX TWO TIMES
//FOR 2) THERE IS DISADVANTAGE OF EXTRA SPACE OF 'next' POINTER OF HAVING COORDINATES OF NEXT NON-ZERO ELEMENT

class Sparse_Matrix{
Coordinate *start;
Coordinate *end;
int count;
int rows,columns;
public:
Sparse_Matrix(int r,int c){
  start = NULL;
  end = NULL;
  count = 0;
  rows = r;
  columns = c;
  }
void add(short int& i,short int& j,int& data){
  Coordinate *temp = new Coordinate(i,j,data);
  if(start == NULL){
    start = temp;
    end = temp;
    }
  else{
    end -> next = temp;
    end = end -> next;
    }
  count++;
  }
void print(){
  Coordinate *ptr = start;
  while(ptr != NULL){
    cout<<ptr -> x<<" "<<ptr -> y<<" "<<ptr -> data<<endl;
    ptr = ptr -> next;
    }
  cout<<"YOU HAVE USED "<<(((double)count)/(rows*columns))*100<<"%"<<endl;
  }  
~Sparse_Matrix(){
  Coordinate *ptr = start;
  while(ptr != NULL){
    start = start -> next;
    delete ptr;
    ptr = start;
    }
  start = NULL;
  end = NULL;
  count = 0;
  rows = 0;
  columns = 0;
  }
};
int main(){
int rows,columns;
cout<<"ENTER THE NUMBER OF ROWS: ";
cin>>rows;
cout<<"ENTER THE NUMBER OF COLUMNS: ";
cin>>columns;
Sparse_Matrix s(rows,columns);
int d = 0;
for(short int i = 0;i < rows;i++){
  for(short int j = 0;j < columns;j++){
    cout<<"ENTER ELEMENT: "<<"["<<i<<"]"<<"["<<j<<"]:";
    cin>>d;
    if(d == 0);
    else
      s.add(i,j,d); 
    }  
  }
s.print();
return 0;
}
