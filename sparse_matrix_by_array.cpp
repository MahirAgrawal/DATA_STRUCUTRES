//UNSUCCESSFUL TRY TO STORE SPARSE MATRIX IN ARRAY IN TERMS OF EFFICIENCY
//BECAUSE ONCE WE ALLOCATE A BLOCK OF SIZE MxN THEN DEALLOCATING A PART OF IT, IS NOT POSSIBLE SO WE CAN'T DO WHAT I HAVE DONE BELOW (SEE IN add(): I HAVE TRIED TO DEALLOCATE THE UNUSED COORDINATE POINTER BLOCK BY delete [](start+count))
//WHICH IS NOT GOOD PROGRAMMING PRACTICE

#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
class Coordinate{
public:
short int x;
short int y;
int data;
Coordinate(){
  x = 0;y = 0;data = 0;
  }
void add(short int& x_co,short int& y_co,int& d){
  x = x_co;y = y_co;data = d;
  }
void display(){
  cout<<"I: "<<x<<" J: "<<y<<" DATA: "<<data<<endl;
  }
~Coordinate(){
  x = 0;
  y = 0;
  data = 0;
  }
};

class Sparse_Matrix{
Coordinate *start;
int count;
int rows,columns;
public:
Sparse_Matrix(int r,int c,int *matrix){
  start = new Coordinate[r*c];
  cout<<"SIZE OF BLOCK : "<<sizeof(*start)<<endl;
  count = 0;
  rows = r;
  columns = c;
  add(matrix);
  }
void add(int *matrix){
  for(short int i = 0;i < rows;i++){
    for(short int j = 0;j < columns;j++){
    if(matrix[i*columns+j] == 0);
    else{
      start[count].add(i,j,matrix[i*columns+j]);
      count++;
      } 
    }  
  }
  cout<<"HERE I AM..\n";
  delete [](start+count);
  cout<<"SIZE OF BLOCK : "<<sizeof(start)<<endl;
  }
void print(){
  for(int i = 0;i < count;i++)
    start[i].display();
  cout<<"YOU HAVE USED "<<(((double)count)/(rows*columns))*100<<"%"<<endl;
  }  
~Sparse_Matrix(){
  //delete []start;
  start = NULL;
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
int *arr = new int[rows*columns];
for(short int i = 0;i < rows;i++){
    for(short int j = 0;j < columns;j++){
      cout<<"ENTER ELEMENT: "<<"["<<i<<"]"<<"["<<j<<"]:";
      cin>>arr[i*columns+j];
    }
  }
Sparse_Matrix s(rows,columns,arr);
delete []arr;
return 0;
}
