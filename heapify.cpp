#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define LEFT(x) (2*x+1)
#define RIGHT(x) (2*x+2)
#define PARENT(x) ((x-1)/2)
//MAKING MAX HEAP BY HEAPIFY
class Heapify{
int *array;
int current_index;
int max_index;
bool full;
public:
Heapify(int n){
  max_index = n;
  array = new int[max_index];
  current_index = max_index-1;
  full = false;
  }
void swap_by_reference(int& a,int& b){
  int temp = a;
  a = b;
  b = temp;
  }
void find_appropriate_position(int i,int upper_limit){
  int left = LEFT(i);
  int right = RIGHT(i);
  int max = i;
  if(left < upper_limit && array[left] > array[max])
    max = left;
  if(right < upper_limit && array[right] > array[max])
    max = right;
  if(max != i){
    swap_by_reference(array[i],array[max]);
    find_appropriate_position(max,upper_limit);
    }
  }
void push(int d){
  if(!full){
    array[current_index] = d;
    find_appropriate_position(current_index,max_index);
    current_index--;
    if(current_index == -1){
      current_index = max_index;
      full = true;
      return;
      }
    }
  }
int pop(){
  int ans = -232e5;
  if(current_index == 0){
    current_index = max_index - 1;    
    cout<<"OUT_OF_BOUND_EXCEPTION!"<<endl;
    return ans;
    }
  ans = *array;
  swap_by_reference(*array,array[current_index-1]);
  current_index--;
  find_appropriate_position(0,current_index);
  return ans;
  }
void display(){
  for(int i = 0;i < max_index;i++)
    cout<<array[i]<<" ";
  cout<<endl;
  }
~Heapify(){
  delete []array;
  max_index = 0;
  current_index = 0;
  }
};
int main(){
int n;
cout<<"ENTER THE NUMBER OF ELEMENTS: ";
cin>>n;
Heapify h(n);
int d;
srand();
for(int i = 0;i < n;i++){
  //cin>>d;
  h.push(rand()%1000);
  }
h.display();
for(int i = 0;i < n;i++)
  cout<<h.pop()<<" ";
h.pop();
cout<<endl;
return 0; 
}
