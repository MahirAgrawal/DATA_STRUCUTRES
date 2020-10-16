#include<iostream>
#include<vector>
#include<conio.h>
#define vector std::vector
#define cout std::cout
#define cin std::cin
#define endl std::endl

class Node{
  Node *parent = NULL;
  vector<int> key;
  vector<Node *> child;
  
  public:
  Node(){
    this -> parent = NULL;
  }

  void setParent(Node *parent){
    this -> parent = parent;
  }

  Node* getParent(){
    return (this -> parent);
  }
  
  Node* getChild(int i){
    return child[i];
  }

  int getKey(int i){
    return (this -> key[i]);
  }

  int insertKey(int k){//TO INSERT KEY DIRECTLY AS PER THE SORTED ORDER
    //***cout<<"kEY:"<<k<<":"<<key.size()<<endl;
    int i = 0;
    for(i = 0;i < key.size();i++)
      if(key[i] > k)
        break;
    //***cout<<"HEREINNODE"<<endl;
    key.insert(key.begin() + i,k);//INSERTION AS PER KEY VALUE BY INSERTION SORT SUBROUTINE
    return i;//RETURNS THE INDEX AT WHICH THE NEW KEY IS INSERTED
  }

  void insertChild(int i,Node *child){//TO INSERT CHILD AT PARTICULAR POSITION
    (this -> child).insert((this -> child).begin()+i,child);
  }

  void insertChild(Node *child){//TO INSERT CHILD AT END OF VECTOR
    (this -> child).push_back(child);
  }

  bool isKeyFound(int k){//TO AVOID STORING DUPLICATE KEY
    for(int i = 0;i < key.size();i++)
      if(key[i] == k)
        return true;
    return false;
  }

  void removeChild(int i){//TO REMOVE CHILD FROM GIVEN POSITION
    child.erase(child.begin() + i);
  }

  bool hasParent(){
    return (parent != NULL);
  }

  bool hasChild(){
    return (child.size() != 0);
  }

  int numberOfChild(){
    return child.size();
  }

  int numberOfKey(){
    return key.size();
  }

  int whichChildToGo(int k){//IF THE NODE HAS CHILDREN : RETURNS WHICH CHILD TO GO TO INSERT THE KEY
    int i = 0;
    for(i = 0;i < key.size();i++)
      if(key[i] > k)
        break;
    return i;
  }

  ~Node(){
    key.clear();
    child.clear();
    parent = NULL;
  }
};

class BTree{
  Node *root;
  int order;


  int split(Node *big,Node *a,Node *b){//SPLIT WILL ONLY OCCUR WHEN KEYS BECOME EQUAL TO ORDER

    int a_size = order/2;
  
    //CHILD DISTRIBUTION BETWEEN TWO SPLITS
    if(big -> hasChild()){
    //***cout<<"HAS CHILD"<<endl;
      for(int i = 0;i <= a_size;i++){
	big -> getChild(i) -> setParent(a); //SETTING NEW PARENT FOR EXISTING CHILD AS SPLIT CAUSES TWO NEW NODE FORMATION
        a -> insertChild(big -> getChild(i));
      }
      for(int i = a_size + 1;i <= order;i++){
        big -> getChild(i) -> setParent(b);
        b -> insertChild(big -> getChild(i));
      }
    }
 
      
    //KEY DISTRIBUTION BETWEEN TWO SPLITS
    for(int i = 0;i < a_size;i++)
      a -> insertKey(big -> getKey(i));
    for(int i = a_size + 1;i < order;i++)
      b -> insertKey(big -> getKey(i));
      
    return (big -> getKey(a_size));//KEY TO PROMOTE TO PARENT
  }

  void insert(Node *_root_,int key){
    //***if(_root_)
      //***cout<<"INSERT KEY: "<<key<<" NODE: "<<(unsigned int)_root_<<" SIZE: "<<_root_ -> numberOfKey()<<endl;
    if(_root_ == NULL){//BTree is empty
      _root_ = new Node;
      _root_ -> insertKey(key);
      this -> root = _root_;
      //***cout<<"INSERT KEY: "<<key<<endl;
      return;
    }
    
    if(_root_ -> isKeyFound(key)){//IF KEY IS ALREADY PRESENT THEN RETURN AS DUPLICATES ARE NOT ALLOWED
      std::cerr<<"KEY SHOULD BE UNIQUE!!"<<endl;
      return;
    }
    
    //IF _root_ IS NOT NULL AND KEY IS NOT NOT FOUND IN PRESENT NODE THEN WE HAVE TO INSERT KEY AS UNIQUE KEY
    if(_root_ -> hasChild())//IF CHILD IS PRESENT THEN GO TO THE CHILD BECAUSE INSERTION HAPPENS AT LEAF NODE ONLY
      insert(_root_ -> getChild(_root_ -> whichChildToGo(key)),key);

    else{//_root_ IS LEAF NODE AS NO CHILD IS PRESENT SO INSERTION HAPPENS HERE
       _root_ -> insertKey(key);
      //***cout<<"inserted: "<<_root_ -> insertKey(key)<<endl;
    }

    //KEY IS INSERTED BY ONE OF THE ABOVE FUNCTION AND NOW TO CHECK IF KEYS ARE m-1
    
    if(_root_ -> numberOfKey() > (this -> order-1)){//SPLIT SUBROUTINE WHEN KEYS BECOME LARGER THAN MAX KEYS
      //***cout<<"NEED OF SPLIT!"<<endl;
      //***getch();
      Node *a = new Node;
      Node *b = new Node;
      int keyToPromote = split(_root_,a,b);//split into a and b
      //***cout<<"KEY TO BE PROMOTED: "<<keyToPromote<<" "<<(unsigned int)(a)<<":"<<(unsigned int)b<<endl;
      
      if(_root_ -> hasParent()){//IF PARENT IS THERE THEN INSERT THE PROMOTED KEY TO PARENT TO COMPENSATE FOR THE EXTRA CHILD
        //***cout<<"HERE 0"<<endl;
	auto parent = _root_ -> getParent();
        //***cout<<"HERE 0.1"<<(unsigned int)parent<<endl;
	int keyindex = parent -> insertKey(keyToPromote);//RETURNS INDEX WHERE NEW KEY WAS INSERTED
        //***cout<<"HERE 0"<<endl;
	parent -> removeChild(keyindex);
	//***cout<<"HERE 1"<<endl;
	parent -> insertChild(keyindex,a);
	parent -> insertChild(keyindex+1,b);
	//***cout<<"HERE 2"<<endl;
	a -> setParent(parent);
	b -> setParent(parent);
	delete _root_;
	//***cout<<"HERE IN PARENT SETTING...";
      }
      
      else{//IF PARENT IS NULL THEN ITS TIME TO BUILD A NEW ROOT
	delete _root_;
        _root_ = new Node;
	//***cout<<"NEW ROOT: "<<(unsigned int)_root_<<endl;
	int keyindex = _root_ -> insertKey(keyToPromote);//RETURNS INDEX WHERE NEW KEY WAS INSERTED
	//cout<<"HERE.."<<endl;
	_root_ -> insertChild(keyindex,a);
        _root_ -> insertChild(keyindex+1,b);
	//cout<<"HERE2..."<<_root_ -> numberOfChild()<<" "<<_root_ -> numberOfKey()<<endl;
	a -> setParent(_root_);
	b -> setParent(_root_);
	this -> root = _root_;
      }

    }

  } 
  
 void heightOfTree(Node *_root_,int h,vector<Node *>& v){
    v.push_back(_root_);
    for(int i = 0;i < _root_ -> numberOfChild();i++)
      heightOfTree(_root_ -> getChild(i),h+1,v);
    
    if(_root_ -> numberOfChild() == 0){
      cout<<"height of tree: "<<h<<endl;
      for(int i = 0;i < v.size();i++)
        cout<<(unsigned int)v[i]<<":"<<v[i] -> numberOfKey()<<" Child: "<<v[i] -> numberOfChild()<<" ";
      cout<<endl;

    }
    v.pop_back();
   }

  void printInorder(Node *_root_){ 
    cout<<"ROOT: "<<(unsigned int)_root_<<endl;
    int i = 0;
    for(i = 0;i < _root_ -> numberOfKey();i++){
       if(_root_ -> hasChild())
         printInorder(_root_ -> getChild(i));
       cout<<_root_ -> getKey(i)<<" ";
       if(_root_ -> hasChild() && i == _root_ -> numberOfKey()-1)
         printInorder(_root_ -> getChild(i+1));
    }
  }
  
  public:
  
  //CONSTRUCTOR FOR B-TREE
  BTree(int m){
    if(m < 3){
      m = 3;
      std::cerr<<"ORDER CAN'T BE LESS THAN 3\n"\
	       <<"ASSIGNING DEFAULT VALUE OF ORDER 3"<<endl;
    }
    this -> order = m;
    this -> root = NULL;
  }
  
  //public functions to use private functions with root data hiding
  void printInorder(){
    printInorder(this -> root);
  }

  void insert(int key){
    insert(this -> root,key);
  }

  void height(){
    int h = 0;
    vector<Node *> v;
    this -> heightOfTree(this -> root,h,v);
  }
  
};

int main(){
  BTree tree(2);
  int a[] = {34,1,43,76,5,21,54,35,44,55,46,47};
  srand((unsigned int)&tree);
  for(int i = 0;i < 10;i++){
    //tree.insert(a[i]);
    tree.insert(rand()%1000);
    }
  tree.printInorder();
  cout<<endl;
  tree.height();
  return 0;
}
