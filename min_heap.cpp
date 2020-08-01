#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) ((i-1)/2)
class Min_Heap{
int *array;
int max_size;
int current_index;
void swap_by_reference(int& a,int& b){
  int temp = a;
  a = b;
  b = temp;
  }
void swap_by_address(int index1,int index2){
  if(index1 < 0 || index2 < 0){
    cout<<"Illegal Use Of Swap Function"<<endl;
    return;
    }
  int temp = array[index1];
  array[index1] = array[index2];
  array[index2] = temp;
  }
public:
Min_Heap(){
  max_size = 100;
  array = new int[max_size];
  current_index = 0;
  }
void push(int d){
  if(current_index == max_size){
    cout<<"Heap Overflow!!";
    return;
    }
  array[current_index] = d;
  int temp_current_index = current_index;
  current_index++;
  while(temp_current_index > 0){
    if(array[PARENT(temp_current_index)] > array[temp_current_index]){
      swap_by_reference(array[PARENT(temp_current_index)],array[temp_current_index]);
      temp_current_index = PARENT(temp_current_index);
      }
    else
      break;  
    }
  }
void find_appropriate_place(int index = 0){
  int left = LEFT(index);
  int right = RIGHT(index);
  int min = index;
  if(left < current_index && array[left] < array[min])
    min = left;
  if(right < current_index && array[right] < array[min])
    min = right;
  if(min != index){
    swap_by_reference(array[index],array[min]);
    find_appropriate_place(min);
    }
  }
int pop(){
  int ans = -43509e4;
  if(current_index == 0){
    cout<<"OUT_OF_BOUNDS_EXCEPTON!!"<<endl;
    return ans;
    }
  ans = array[0];
  swap_by_reference(array[0],array[current_index-1]);
  current_index--;
  find_appropriate_place();
  return ans;
  }
friend std::ostream& operator <<(std::ostream&,Min_Heap&);
};
std::ostream& operator <<(std::ostream& out,Min_Heap& m){
  for(int i = 0;i < m.current_index;i++)
    out<<m.array[i]<<" ";
  return out;
  }
int main(){
Min_Heap m;
int n,d;
cout<<"size of:"<<sizeof(m)<<endl;
cout<<"ENTER THE NUMBER OF ELEMENTS: ";
cin>>n;
for(int i = 0;i < n;i++)
  m.push(rand()%500);
/*for(int i = 0;i < n;i++){
  cin>>d;
  m.push(d);
  }*/
//cout<<m<<endl;
for(int i = 0;i < n;i++)
  cout<<m.pop()<<" ";
cout<<endl;
return 0;
}
