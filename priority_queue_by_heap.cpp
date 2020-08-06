#include<iostream>
#include<string>
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define PARENT(i) ((i-1)/2)
#define LEFT_CHILD(i) (2*i+1)
#define RIGHT_CHILD(i) (2*i+2)
//THE SMALLER THE NUMBER, THE LARGER THE PRIORITY SO MAKING MIN HEAP

class Priority_Queue{
class Slot{
  public:
  int priority;
  string name;
  Slot(){}
  Slot(Slot& t){
    //cout<<"I AM CALLED!"<<endl;
    name.assign(t.name);
    priority = t.priority;
    }
  void add(string& t,int p){ 
    name.assign(t);
    priority = p; 
    }
  void operator =(Slot& t){
    //cout<<"I AM SO CALLED!"<<endl;
    name.assign(t.name);
    priority = t.priority;
    }
  ~Slot(){
    name = "";
    priority = 326878;
    }
  };
Slot *start;
int current_index;
int max_index;
void swap_by_reference(Slot& a,Slot& b){
  Slot temp = a;
  a = b;
  b = temp;
  }
public:
Priority_Queue(int n){
  max_index = n;
  current_index = 0;
  start = new Slot[max_index];
  }
void push(string name,int priority){
  if(current_index == max_index){
  cout<<"HEAP OVERFLOW!!"<<endl;
  return; 
  }
  start[current_index].add(name,priority);
  int index = current_index;
  current_index++;
  while(index > 0){
    if(start[index].priority < start[PARENT(index)].priority){
      swap_by_reference(start[index],start[PARENT(index)]);
      index = PARENT(index);
      }
    else
      break;
    }
  }
void get_appropriate_place(int index = 0){
  int left = LEFT_CHILD(index);
  int right = RIGHT_CHILD(index);
  int min = index;
  if(left < current_index && start[left].priority < start[min].priority)
    min = left;
  if(right < current_index && start[right].priority < start[min].priority)
    min = right;
  if(min != index){
    swap_by_reference(start[index],start[min]);
    get_appropriate_place(min);
    }
  }
string pop(){
  string answer = "";
  if(current_index == 0)
    cout<<"HEAP UNDERFLOW!!";
  else{
    answer = start[0].name;
    swap_by_reference(start[0],start[current_index-1]);
    current_index--;
    get_appropriate_place();
    }
  return answer;
  }
void display(){
  for(int i = 0;i < current_index;i++)
    cout<<start[i].name<<" ";
  cout<<endl;
  }
~Priority_Queue(){
  current_index = 0;
  max_index = 0;
  delete []start;
  }
};
int main(){
int  n = 0,p;string name;
cout<<"ENTER THE NUMBER OF ELEMENTS IN QUEUE: ";
cin>>n;
fflush(stdin);
Priority_Queue p_queue(n);
for(int i = 0;i < n;i++){
  cout<<"ENTER THE NAME OF PATIENT: ";
  std::getline(cin,name);
  cout<<"ENTER THE PRIORITY OF THIS PATIENT: ";
  cin>>p;
  fflush(stdin);
  p_queue.push(name,p);
  }
p_queue.display();
cout<<"PATIENT AS PER THE PRIORITY: "<<endl;
for(int i = 0;i < n;i++)
  cout<<p_queue.pop()<<endl;
return 0;
}
