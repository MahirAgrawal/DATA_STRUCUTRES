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

//Prioriy Class
template<class X>
class Priority_Queue{
//SLOT CLASS which is the BUILDING BLOCK OF PRIORITY QUEUE
template<class Y>
class Slot{
  public:
  int priority;
  Y data;
  Slot(){}
  //adds by copy constructor
  Slot(Slot& t){
    this -> data = t.data;
    priority = t.priority;
    }
  //adds the given data and it's priority
  void add(Y& t,int p){ 
    this -> data = t;
    priority = p;
    }
  //Overloaded assignment operator for deep copying
  void operator =(Slot& t){
    this -> data = t.data;
    priority = t.priority;
    }
  ~Slot(){
    priority = 326878;
    }
  };

//Variable to hold the entire array of 'SLOTS' and slots have data and priority
Slot<X> *start;
int current_index;//Take note where should the new element should be added
int max_index;//Max size of Priority Queue or broadly speaking size of 'MIN HEAP'
void swap_by_reference(Slot<X>& a,Slot<X>& b){
  Slot<X> temp = a;
  a = b;
  b = temp;
  }
public:
Priority_Queue(int n){
  max_index = n;
  current_index = 0;
  start = new Slot<X>[max_index];
  }
//Pushes data of any class/datatype at current_index and then the data bubble-up in O(logn) time as per it's priority
void push(X d,int priority){
  if(current_index == max_index){
    cout<<"HEAP OVERFLOW!!"<<endl;
  return; 
  }
  start[current_index].add(d,priority);
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
//Recursive method used when the minimum element in heap is deleted ,last elements(at current_index - 1) takes place at index '0'
//That element needs to bubble down to its correct position (based on priority value) in O(logn) time and is carried out by this      function
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

//Deletes array's zeroth position which happens to be have the maximum priority and then calls above function
void pop(){
  if(current_index == 0)
    cout<<"HEAP UNDERFLOW!!";
  else{
    swap_by_reference(start[0],start[current_index-1]);
    current_index--;
    get_appropriate_place();
    }
  }

//Returns the element/data's address which have the highest priority
X* peek(){
  return (&(start[0].data));
  }
void display(){
  for(int i = 0;i < current_index;i++)
    cout<<start[i].data<<" ";
  cout<<endl;
  }
~Priority_Queue(){
  current_index = 0;
  max_index = 0;
  delete []start;
  }
};

//Sample class to test Priority_Queue by heap
class Dog{
  string name;
  int age;
  public:
  Dog(){}
  //Copy constructor to have deep copy
  Dog(Dog& d){
    this -> name.assign(d.name);
    this -> age = d.age;
    }
  //Overloaded assignment operator for copying two Dog variables
  void operator =(Dog& d){
    this -> name.assign(d.name);
    this -> age = d.age;
    }
  //Overloaded friend function to directly use '<<'  '>>' for output and input
  friend std::istream& operator >>(std::istream&,Dog&);
  friend std::ostream& operator <<(std::ostream&,Dog&);
  };
std::ostream& operator <<(std::ostream& out,Dog& d){
  out<<d.name<<" "<<d.age;
  return out;
  }
std::istream& operator >>(std::istream& in,Dog& d){
  cout<<"ENTER NAME OF DOG: ";
  std::getline(in,d.name);
  cout<<"ENTER AGE OF DOG: ";
  in>>d.age;
  return in;
  }
int main(){
int  n = 0,p;
Dog data;
//char data;
//string name;
cout<<"ENTER THE NUMBER OF ELEMENTS IN QUEUE: ";
cin>>n;
fflush(stdin);
Priority_Queue<Dog> p_queue(n);
for(int i = 0;i < n;i++){
  //cout<<"ENTER THE DATA: ";
  //std::getline(cin,name);
  cin>>data;
  cout<<"ENTER THE PRIORITY: ";
  cin>>p;
  fflush(stdin);
  p_queue.push(data,p);
  }
p_queue.display();
cout<<"PATIENT AS PER THE PRIORITY: "<<endl;
for(int i = 0;i < n;i++){
  cout<<*(p_queue.peek())<<endl;
  p_queue.pop();
  }
return 0;
}
