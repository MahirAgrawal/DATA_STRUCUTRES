#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
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
//1) FIRST STORE THE ELEMENTS TEMPORARY IN A MxN ARRAY WHILE TAKING INPUT AND THEN SCAN THROUGH THE MxN MATRIX TO FIND THE ACTUAL   NUMBER OF ELEMENTS AND ALLOCATE MEMORY FOR ARRAY OF SIZE AS PER SCAN RESULT. THAT IS TO USE DYNAMIC ARRAY LIKE VECTOR IN C++ BUT    LET'S ONLY USE DATA STRUCTURE WHICH I BUILD FROM STRATCH AND NOT THE IN-BUILT TEMPLATES	
//2) SECOND TAKE INPUT -- IF 0 IGNORE AND CONTINUE
//                     -- ELSE STORE IT IN LINK LIST NODES RIGHT AT THE MOMENT

//FOR 1) THERE IS DISADVANTAGE THAT WE HAVE TO SCAN WHOLE MxN MATRIX TWO TIMES. 
//FOR 2) THERE IS DISADVANTAGE OF EXTRA SPACE OF 'next' POINTER OF HAVING COORDINATES OF NEXT NON-ZERO ELEMENT
class Sparse_Matrix{
Coordinate *start;
Coordinate *end;
int count;
int rows,columns;
public:
Sparse_Matrix(int,int);
void add(short int&,short int&,int&);
void print();
void operator +(Sparse_Matrix&);
void operator -(Sparse_Matrix&);
void operator *(Sparse_Matrix&);
void operator /(Sparse_Matrix&);
~Sparse_Matrix();
static int* make_sparse_matrix(Sparse_Matrix& s);
};
//ALL DEFINIITONS AND FUNCTIONS ARE IN sparse_matrix.h FILE
#include"sparse_matrix.h"
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
cout<<"ENTER THE NUMBER OF ROWS: ";
cin>>rows;
cout<<"ENTER THE NUMBER OF COLUMNS: ";
cin>>columns;
Sparse_Matrix t(rows,columns);
for(short int i = 0;i < rows;i++){
  for(short int j = 0;j < columns;j++){
    cout<<"ENTER ELEMENT: "<<"["<<i<<"]"<<"["<<j<<"]:";
    cin>>d;
    if(d == 0);
    else
      t.add(i,j,d); 
    }  
  }
cout<<"YOU ENTERED SPARSE MATRIX: "<<endl;
s.print();
cout<<"YOU ENTERED SPARSE MATRIX: "<<endl;
t.print();
cout<<"\nADDITION: "<<endl;
s+t;
cout<<"\nSUBSTRACTION: "<<endl;
s-t;
cout<<"\nMULTIPLICATION: "<<endl;
s*t;
cout<<"\nDIVSION: "<<endl;
s/t;
return 0;
}
