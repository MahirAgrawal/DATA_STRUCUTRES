#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
class Max_Heap{
int *start;
int current_index;
unsigned int max = 10000;
public:
Max_Heap(){
  start = new int[max];
  current_index = 0;
  }
static void swap(int *a,int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
  }
void push(int data){
  if(current_index == max){
  cout<<"HEAP IS FULL!!"<<endl;
  return;
  }
  int i = current_index;
  start[i] = data;
  while(i > 0){
    if(start[((i-1)/2)] < start[i]){
      swap(start+((i-1)/2),start+i);
      i = ((i-1)/2);
      }
    else
      break;
    }
  current_index++;
  }
//RECURSIVE METHOD TO CHECK iTH POSITION IS SMALLER OR NOT THAN IT'S CHILD AND SWAP ACCORDINGLY
void compare_and_swap(int i){
  int left_child = 2*i+1;
  int right_child = 2*i+2;
  //checks if both child are invalid and if so then return
  if(left_child >= current_index && right_child >= current_index)
    return;
  int max = 0;
  //Above 'IF' condition is false then atleast there exist one child of 'i'
  //It can be left so checking for left
  if(left_child < current_index)
    max = start[i]>=start[left_child]?i:left_child;
  //checking for right child 
  if(right_child < current_index)
    max = start[max]>=start[right_child]?max:right_child;
  //if parent index 'i' itself is max index then also return SEE below:
  if(max == i)//if parent is larger than both it's child then have got suitable place for our element
    return;
  swap(start+i,start+max);//else swap the deserving maximum element in place of parent and then again search a new suitable place
                          //for this parent which now is shifted to another place because it is not maximum compared to it's child
  compare_and_swap(max);
  }
int pop(){
  if(current_index == 0){
    cout<<"NOTHING TO POP OUT!!\n";
    return -323222;
  }
  int ans = start[0];  
  swap(start+current_index-1,start);
  current_index--;
  compare_and_swap(0);
  return ans;
  }
void display(){
  for(int i = 0;i < current_index;i++)
    cout<<start[i]<<" ";
  cout<<endl;
  }
~Max_Heap(){
  delete []start;
  current_index = -1;
  }
};
int main(){
Max_Heap h;
int n,a;
cout<<"ENTER THE NUMBER OF ELEMENTS: ";
cin>>n;
srand(n*2);
for(int i = 0;i < n;i++){
  h.push(rand()%1000);
  }
cout<<"HEAP: ";h.display();
cout<<"SORTED ORDER: "<<endl;
for(int i = 0;i < n;i++)
  cout<<h.pop()<<" ";
return 0;
}
