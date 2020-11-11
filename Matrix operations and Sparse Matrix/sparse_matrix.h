#include<cmath>
int determinant(int *,int);

//RETURNS THE DETERMINANT OF COFACTOR OF GIVEN SQUARE MATRIX IN FORM OF INTEGER LINEAR ARRAY POINTER WITH GIVEN ORDER AND GIVEN ROW AND COLUMN LOCATION OF ELEMENT WHOSE COFACTOR HAS TO BE FOUND!
int cofactor(int order,int *ptr,int row,int column){
int arr[(order-1)*(order-1)];
int counter_i = 0,counter_j = 0;
for(int i = 0;i  < order;i++){
  if(i == row)
    continue;
    counter_j = 0;
    for(int j = 0;j < order;j++){
    if(j == column)
      continue;
    else{
      arr[counter_i*(order-1)+counter_j] = *(ptr+i*order+j);
      counter_j++;
      }
    }
  counter_i++;
  }
return (determinant(arr,order-1));
}

//RETURNS DETERMINANT OF SQUARE MATRIX WITH GIVEN ORDER AND MATRIX IN FORM OF INTEGER LINEAR ARRAY
int determinant(int *arr,int order){
  int answer = 0;
  if(order == 1)
    answer = *arr;
  else if(order == 2){
    answer = (arr[0] * arr[3] - arr[1] * arr[2]);
    }
  else{
    for(int i = 0;i < order;i++){
      if(i%2 == 1)
        answer += (-1*arr[i]*cofactor(order,arr,0,i));
      else
        answer += (arr[i]*cofactor(order,arr,0,i));
      }
    }
  return answer;
  }

//RETURNS THE INVERSE OF SQUARE MATRIX IN FORM OF LINEAR ARRAY OF DOUBLE AND PARAMETERS GIVEN IS LINEAR ARRAY OF MATRIX WHOSE       INVERSE IS TO FOUND AND ORDER/RANK OF MATRIX

//AS DETERMINANT ONLY EXISTS FOR SQUARE MATRIX AND SO ONLY INVERSE EXISTS FOR SQUARE MATRIX
double* inverse(int *arr,int order){
  int ans = determinant(arr,order);
  if(ans == 0)
    return NULL;
  int *new_matrix = new int[order*order];
  for(int i = 0;i < order;i++){
    for(int j = 0;j < order;j++){
      if(pow(-1,i+j) == -1)
        new_matrix[i*order+j] = -1*cofactor(order,arr,i,j);
      else 
        new_matrix[i*order+j] = cofactor(order,arr,i,j);
      }
    }
  double *ptr = new double[order*order];
  for(int i = 0;i < order;i++){
    for(int j= 0;j < order;j++)
      ptr[i+order*j] = (double)new_matrix[i*order+j];
    }
  delete []new_matrix;
  for(int i = 0;i < order;i++){
    for(int j= 0;j < order;j++)
      ptr[i*order+j] /= ans;
    }
  return ptr;
  }

//PRINTS THE MULTIPLICATION OF TWO GIVEN MATRICES IF IT EXISTS
template<class X>
void matrix_multiplication(int r1,int c1,X *m1,int r2,int c2,X *m2){
  if(c1 != r2)
    cout<<"MATRIX MULTIPLICATION NOT POSSIBLE!!";
  else{
    X sum = 0;
    X answer_matrix[r1][c2];
    for(int k = 0;k < c2;k++){
      for(int i = 0;i < r1;i++){
        sum = 0;
        for(int j = 0;j < r2;j++)
          sum += m1[i*c1+j]*m2[j*c2+k];
        answer_matrix[i][k] = sum;
        }
      }
    cout<<"ANSWER: "<<endl;
    for(int i = 0;i < r1;i++){
      for(int j = 0;j < c2;j++) 
        cout<<answer_matrix[i][j]<<" ";
      cout<<endl;
      }
    }
  }
//RETURNS 1 OR -1 BASED ON COMPARISON BETWEEN (X1,Y1) > (X2,Y2)
//RETURNS 0 IF SAME COORDINATE
int compare(int x1,int y1,int x2,int y2){
if(x1 > x2)
  return 1;
else if(x2 > x1)
  return -1;
else{
  if(y1 > y2)
    return 1;
  else if(y2 > y1)
    return -1;
  else
    return 0;
  }
}

//CLASS SPARSE_MATRIX_DEFINITIONS

//CONSTRUCTOR
Sparse_Matrix::Sparse_Matrix(int r,int c){
  start = NULL;
  end = NULL;
  count = 0;
  rows = r;
  columns = c;
  }

//ADD NON - ZERO ELEMENTS AS LINKED LIST'S NODE
void Sparse_Matrix::add(short int& i,short int& j,int& data){
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

//PRINTS PROPER MATRIX OF M*N
void Sparse_Matrix::print(){
  Coordinate *ptr = start;
  if(start == NULL)
    return;
  for(int i = 0;i < rows;i++){
    for(int j = 0;j < columns;j++){
      if(ptr != NULL){
	if(ptr -> x == i && ptr -> y == j){
          cout<<ptr -> data<<" ";
          ptr = ptr -> next;
	  }
	else
          cout<<0<<" ";
        }
      else
        cout<<0<<" ";
      }
    cout<<endl;
    } 
  }

//ADDS TWO SPARSE MATRICES IF POSSIBLE
void Sparse_Matrix::operator +(Sparse_Matrix& s){
  Coordinate *ptr1 = start;
  Coordinate *ptr2 = s.start;
  if(rows == s.rows && columns == s.columns){
  if(ptr2 == NULL){
    this -> print();
    return;
    }
  else if(ptr1 == NULL){
    s.print();
    return;
    }
  Sparse_Matrix temp(rows,columns);
  while(ptr1 && ptr2){
    if(compare(ptr1 -> x,ptr1 -> y,ptr2 -> x,ptr2 -> y) == -1){
      temp.add(ptr1->x,ptr1->y,ptr1->data);
      ptr1 = ptr1 -> next;
      }
    else if(compare(ptr1 -> x,ptr1 -> y,ptr2 -> x,ptr2 -> y) == 1){
      temp.add(ptr2->x,ptr2->y,ptr2->data);
      ptr2 = ptr2 -> next;
      }
    else{
      int spare = ptr1->data + ptr2->data;
      temp.add(ptr1->x,ptr1->y,spare);
      ptr1 = ptr1 -> next;
      ptr2 = ptr2 -> next;
      }
    }
  while(ptr1){
    temp.add(ptr1->x,ptr1->y,ptr1->data);
    ptr1 = ptr1 -> next;
    }
  while(ptr2){
    temp.add(ptr2->x,ptr2->y,ptr2->data);
    ptr2 = ptr2 -> next;
    }
  temp.print();
  }
  else
    cout<<"CAN'T ADD MATRICES WITH UNEQUAL NUMBER OF ROWS OR COLUMNS"<<endl;
  }

//SUBSTRACTS TWO SPARSE MATRICES IF POSSIBLE
void Sparse_Matrix::operator -(Sparse_Matrix& s){
  Coordinate *ptr1 = start;
  Coordinate *ptr2 = s.start;
  if(rows == s.rows && columns == s.columns){
  if(ptr2 == NULL){
    this -> print();
    return;
    }
  else if(ptr1 == NULL){
    s.print();
    return;
    }
  Sparse_Matrix temp(rows,columns);
  while(ptr1 && ptr2){
    if(compare(ptr1 -> x,ptr1 -> y,ptr2 -> x,ptr2 -> y) == -1){
      temp.add(ptr1->x,ptr1->y,ptr1->data);
      ptr1 = ptr1 -> next;
      }
    else if(compare(ptr1 -> x,ptr1 -> y,ptr2 -> x,ptr2 -> y) == 1){
      int spare = (ptr2 -> data)*(-1);
      temp.add(ptr2->x,ptr2->y,spare);
      ptr2 = ptr2 -> next;
      }
    else{
      int spare = ptr1->data - ptr2->data;
      temp.add(ptr1->x,ptr1->y,spare);
      ptr1 = ptr1 -> next;
      ptr2 = ptr2 -> next;
      }
    }
  while(ptr1){
    temp.add(ptr1->x,ptr1->y,ptr1->data);
    ptr1 = ptr1 -> next;
    }
  while(ptr2){
    int spare = (ptr2 -> data)*(-1);
    temp.add(ptr2->x,ptr2->y,spare);
    ptr2 = ptr2 -> next;
    }
  temp.print();
  }
  else
    cout<<"CAN'T SUBSTRACT MATRICES WITH UNEQUAL NUMBER OF ROWS OR COLUMNS"<<endl;
  }

//RETURNS A LINEAR ARRAY HAVING SPARSE MATRIX WHICH IS OBTAINED BY GIVEN PARAMETER SPARSE MATRIX: FILLING NON ZERO AND REST WITH    ZERO
int* Sparse_Matrix::make_sparse_matrix(Sparse_Matrix& s){
  int *matrix = new int[s.rows*s.columns];
  Coordinate *ptr = s.start;
  for(int i = 0;i < s.rows;i++){
    for(int j = 0;j < s.columns;j++){
      if(ptr != NULL){
	if(ptr -> x == i && ptr -> y == j){
          matrix[i*s.columns+j] = ptr -> data;
          ptr = ptr -> next;
	  }
	else
          matrix[i*s.columns+j] = 0;
        }
      else
         matrix[i*s.columns+j] = 0;      
      }
    } 
  return matrix;
  }

//PRINTS MULTIPLICATION OF TWO SPARSE MATRICES IF POSSIBLE
//FIRST CONVERTS THE SPARSE MATRIX INTO ACTUAL M*N ARRAY SIZE HAVING NON-ZERO AND ZERO ELEMENTS
//THEN DO MULTIPLICATION LIKE ANY OTHER NORMAL MATRICES MULTIPLICATION
void Sparse_Matrix::operator *(Sparse_Matrix& s){
  if(this -> columns != s.rows){
    cout<<"MATRIX MULTIPLICATION IS NOT POSSIBLE!!"<<endl;
    return;
    }
  int *matrix1 = make_sparse_matrix(*this);
  int *matrix2 = make_sparse_matrix(s);
  matrix_multiplication(rows,columns,matrix1,s.rows,s.columns,matrix2);
  delete []matrix2;
  delete []matrix1;
  }

//PRINTS DIVISION OF TWO SPARSE MATRICES IF POSSIBLE
//FIRST CONVERTS THE SPARSE MATRICS INTO ACTUAL ARRAY LIKE ABOVE IN MULTIPLICATION
//THEN FIND INVERSE OF MATRIX B WHICH IS INVERSE(B)
//THEN DO MULTIPLICATION OF INVERSE(B)*A
void Sparse_Matrix::operator /(Sparse_Matrix& s){
  if(s.rows != s.columns){
    cout<<"DIVISION NOT POSSIBLE BECAUSE 2ND MATRIX IS NOT A SQUARE MATRIX SO IT'S INVERSE DOESN'T EXIST\n";
    return;
    }
  int *matrix1 = make_sparse_matrix(*this);
  int *matrix2 = make_sparse_matrix(s);
  double *array2 = inverse(matrix2,s.rows);
  if(array2 == NULL)
    cout<<"DIVISION NOT POSSIBLE AS INVERSE IS NOT POSSIBLE OF MATRIX B BECAUSE DETERMINANT IS ZERO"<<endl;
  else{
    double *array1 = new double[rows*columns];
    for(int i = 0;i < rows;i++){
      for(int j = 0;j < columns;j++)
        array1[i*columns+j] = (double)matrix1[i*columns+j];
      }

    matrix_multiplication<double>(s.rows,s.columns,array2,rows,columns,array1);
    delete []array1;
    delete []array2;
    }
  delete []matrix1;
  delete []matrix2;
  }

//DESTRUCTOR
Sparse_Matrix::~Sparse_Matrix(){
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
