#include<iostream>
#include<vector>
#include<map>
#include<string>
#define string std::string
#define map std::map
#define cin std::cin
#define vector std::vector
#define cout std::cout
#define endl '\n'

/**
 * AS MOST GRAPHS IN REAL WORLD ARE SPARSE SO ADJACENCY MATRIX WAS BAD IN TERMS OF STORAGE HENCE THE MOST OPTIMAL 
 * CHOICE WOULD BE ADJACENCY LIST
 * NOW REFERRING TO 'MYCODESCHOOL' VIDEO WHERE SIR HAS SAID THAT LINKED OR ANY OTHER EFFICIENT DATA STRUCTURE 
 * SHOULD BE USED TO STORE THE NEIGHBOURS AND SO PRESENTING YOU THE GRAPH WHICH HAS ARRAY OF AVL TREES FOR STORING
 * NEIGHBOURS OF A VERTEX
 * HERE INSERTING A EGDE TAKES O(LOGN) TIME AS IN AVL TREE AND ALSO SEARCHING ADJACENT VERTEX TAKES SAME TIME
 */


template<class X>
class BinaryTree;

template<class X>
class Node{
  int first;
  X second;
  int height;
  Node<X> *left,*right;

  Node(int key,X& data){
    this -> first = key;
    this -> second = data;
    this -> height = 0;
    this -> left = NULL;
    this -> right = NULL;
  }
  
  void operator =(Node& node){
    this -> first = node.first;
    this -> second = node.second;
  }
  ~Node(){
    this -> first = 0;
  }

  friend class BinaryTree<X>;
};

//speciaziled AVL TREE TO STORE ADJACENT VERTICES
template<class X>
class BinaryTree{
  
  Node<X> *root;//tree to store adjacent vertices
  X mainVertex;//name of main vertex of which neighbours are stored
  public:
  void setMainVertex(X& data){
    this -> mainVertex = data;
  }

  X getMainVertex(){
    return mainVertex;
  }

  private:
  //insertion
  Node<X>* insert(Node<X> *_root_,int key,X& data){
    if(_root_ == NULL)
      return (new Node<X>(key,data));
    
    if(_root_ -> first > key)
      _root_ -> left = insert(_root_ -> left,key,data);
    
    else if(_root_ -> first < key)
      _root_ -> right = insert(_root_ -> right,key,data);
    
    _root_ -> height = std::max(getHeight(_root_ -> left),getHeight(_root_ -> right)) + 1;
    
    int balanceFactor = getHeight(_root_ -> left) - getHeight(_root_ -> right);
    
    //it's time to rotate
    if(balanceFactor > 1 || balanceFactor < -1){
      if(balanceFactor > 1){//either right or left right rotation
        auto balanceFactorOfChild = getHeight(_root_ -> left -> left) - getHeight(_root_ -> left -> right);
	if(balanceFactorOfChild < 0)//left rotation first
	  _root_ -> left = leftRotate(_root_ -> left);
	_root_ = rightRotate(_root_);
      }

      else{//either left or right left rotation
        auto balanceFactorOfChild = getHeight(_root_ -> right -> left) - getHeight(_root_ -> right -> right);
	if(balanceFactorOfChild > 0)//right rotation first
	  _root_ -> right = rightRotate(_root_ -> right);
	_root_ = leftRotate(_root_);
      }
    }
    
    return _root_;
  }
  
  //deletion
  Node<X>* erase(Node<X> *_root_,int key){
    if(_root_ == NULL){
      return _root_;
    }
    if(_root_ -> first > key)
      _root_ -> left = erase(_root_ -> left,key);
    
    else if(_root_ -> first < key)
      _root_ -> right = erase(_root_ -> right,key);

    else{//key is found
      if(_root_ -> left == NULL && _root_ -> right == NULL){
        delete _root_;
	_root_ = NULL;
      }

      else if(_root_ -> left && _root_ -> right){
        auto successor = _root_ -> right;
        while(successor -> left)
          successor = successor -> left;
	//_root_ -> first = successor -> first;//giving current node the value of successor node
	//_root_ -> second = successor -> second;
	(*_root_) = (*successor);
	_root_ -> right = erase(_root_ -> right,_root_ -> first);
      }

      else if(_root_ -> left || _root_ -> right){//any one child is present
	auto to_preserve = _root_ -> left;
        if(_root_ -> right)
          to_preserve = _root_ -> right;
	delete _root_;
	_root_ = to_preserve;
      }
    }

    if(_root_){
      _root_ -> height = std::max(getHeight(_root_ -> left),getHeight(_root_ -> right)) + 1;
      int balanceFactor = getHeight(_root_ -> left) - getHeight(_root_ -> right);
    
      //it's time to rotate
      if(balanceFactor > 1 || balanceFactor < -1){
        if(balanceFactor > 1){//either right or left right rotation
          auto balanceFactorOfChild = getHeight(_root_ -> left -> left) - getHeight(_root_ -> left -> right);
	  if(balanceFactorOfChild < 0)//left rotation first
	    _root_ -> left = leftRotate(_root_ -> left);
	  _root_ = rightRotate(_root_);
        }

        else{//either left or right left rotation
          auto balanceFactorOfChild = getHeight(_root_ -> right -> left) - getHeight(_root_ -> right -> right);
	  if(balanceFactorOfChild > 0)//right rotation first
	    _root_ -> right = rightRotate(_root_ -> right);
	  _root_ = leftRotate(_root_);
        }
      }

    }
    return _root_;
  }

  bool search(Node<X> *_root_,int key){
    if(_root_ == NULL)
      return false;
    if(_root_ -> first > key)
      return (search(_root_ -> left,key));
    else if(_root_ -> first < key)
      return (search(_root_ -> right,key));
    else 
      return true;
  }

  Node<X>* rightRotate(Node<X> *grandparent){
    auto parent = grandparent -> left;
    grandparent -> left = parent -> right;
    grandparent -> height = std::max(getHeight(grandparent -> left),getHeight(grandparent -> right)) + 1;
    parent -> right = grandparent;
    parent -> height = std::max(getHeight(parent -> left),getHeight(parent -> right)) + 1;
    //now parent has taken position of grandparent in rotation so parent becomes new grandparent
    return parent;
  }

  Node<X>* leftRotate(Node<X> *grandparent){
    auto parent = grandparent -> right;
    grandparent -> right = parent -> left;
    grandparent -> height = std::max(getHeight(grandparent -> left),getHeight(grandparent -> right)) + 1;
    parent -> left = grandparent;
    parent -> height = std::max(getHeight(parent -> left),getHeight(parent -> right)) + 1;
    //now parent has taken position of grandparent in rotation so parent becomes new grandparent
    return parent;
  }

  int getHeight(Node<X> *_root_){
    if(_root_)
      return _root_ -> height;
    return -1;
  }

  void inOrder(Node<X> *_root_){
    if(_root_ == NULL)
      return;
    inOrder(_root_ -> left);
    cout<<_root_ -> first<<" "<<_root_ -> second<<endl;
    inOrder(_root_ -> right);
  }

  public:
  //public methods to use above functions without knowing root of tree
  BinaryTree(){
    this -> root = NULL;  
  }
  
  void insert(int key,X data){
    this -> root = insert(this -> root,key,data);
  }
  
  void erase(int key){
    this -> root = erase(this -> root,key);
  }

  bool search(int key){
    return (search(this -> root,key));
  }

  void inOrder(){
    this -> inOrder(this -> root);
    cout<<endl;
  }
};

//will be undirected graph
template<class X>
class Graph{
  
  //assuming vertices are nothing but indices/numbers which are zero based
  map<X,int> m;//to map the actual type of vertices with integers to deal easily
  int vertexCounter;
  vector<BinaryTree<X>*> neighbourList;

  public:
  Graph(){
    vertexCounter = 0;
  }
  
  void insertEdge(X a,X b){

    auto v1 = m.find(a);
    auto v2 = m.find(b);
    int vindex1 = 0,vindex2 = 0;
    if(v1 == m.end()){
      vindex1 = vertexCounter++;
      neighbourList.push_back(new BinaryTree<X>);
      m[a] = vindex1;
      neighbourList[vindex1] -> setMainVertex(a);
    }
    else
      vindex1 = v1 -> second;
      
    if(v2 == m.end()){
      vindex2 = vertexCounter++;
      neighbourList.push_back(new BinaryTree<X>);
      m[b] = vindex2;
      neighbourList[vindex2] -> setMainVertex(b);
    }
    else
      vindex2 = v2 -> second;
    
    //undirected so bidirectional edges will be there
    neighbourList[vindex1] -> insert(vindex2,b);
    neighbourList[vindex2] -> insert(vindex1,a);
  }

  void removeEdge(X a,X b){//only removing the other vertex from neighbour list of a vertex
    auto v1 = m.find(a);
    auto v2 = m.find(b);
    int vindex1 = 0,vindex2 = 0;
    if(v1 == m.end() || v2 == m.end()){
      cout<<"SUCH VERTEX DOESN'T EXIST!!"<<endl;
      return;
    }

    vindex1 = v1 -> second;
    vindex2 = v2 -> second;
    //undirected so bidirectional edges will be there
    neighbourList[vindex1] -> erase(vindex2);
    neighbourList[vindex2] -> erase(vindex1);
  }
  
  //prints the whole graph i.e all vertices with their respective adjacent vertices list
  void printGraph(){
    for(auto i:neighbourList){
      cout<<i -> getMainVertex()<<":\n";
      i -> inOrder();
    }  
  }
  
  //print the adjacent vertices of given vertex
  void printAdjacentVertices(X a){
    auto v1 = m.find(a);
    if(v1 == m.end()){
      cout<<"SUCH VERTEX DOESN'T EXIST!!"<<endl;
      return;
    }
    int vindex1 = v1 -> second;
    cout<<neighbourList[vindex1] -> getMainVertex()<<":\n";
    neighbourList[vindex1] -> inOrder();
  }

  //prints true or false that if there is edge between two given vertices
  bool doesEdgeExist(X a,X b){
    auto v1 = m.find(a);
    auto v2 = m.find(b);
    int vindex1 = 0,vindex2 = 0;
    if(v1 == m.end() || v2 == m.end())
      return false;
     
    //undirected graph so if 'a' has adjacent vertex 'b' then 'b' would have 'a' so only to check a's row or b's
    vindex1 = v1 -> second;
    vindex2 = v2 -> second;
    return (neighbourList[vindex1] -> search(vindex2));
  }

};


int main(){
  
  Graph<string> friendNetwork;
  
  friendNetwork.insertEdge("mihir","khushi");
  friendNetwork.insertEdge("vansh","dev");
  friendNetwork.insertEdge("vansh","khushi");
  friendNetwork.insertEdge("dev","vihan");
  friendNetwork.insertEdge("mihir","shrey");
  friendNetwork.insertEdge("malav","mit");
  friendNetwork.insertEdge("mihir","tirth");
  friendNetwork.printGraph();
  friendNetwork.printAdjacentVertices("khusho");
  friendNetwork.printAdjacentVertices("khushi");
  cout<<"mihir and shrey: "<<friendNetwork.doesEdgeExist("mihir","shrey")<<endl;
  cout<<"mihir and khusho: "<<friendNetwork.doesEdgeExist("mihir","khusho")<<endl;
  cout<<"mihir and mit: "<<friendNetwork.doesEdgeExist("mihir","mit")<<endl;
  //friendNetwork.removeEdge("mihir","jk");
  //friendNetwork.removeEdge("mihir","dev");
  friendNetwork.removeEdge("mihir","shrey");
  cout<<"mihir and shrey: "<<friendNetwork.doesEdgeExist("mihir","shrey")<<endl;
  //friendNetwork.removeEdge("malav","mit");
  friendNetwork.printGraph();
  /*BinaryTree<float> tree;
  tree.insert(23,10.93);
  tree.insert(24,101.93); 
  tree.insert(25,1.93);  
  tree.insert(45,1.3);  
  tree.insert(40,.44);
  tree.insert(43,.4);
  tree.insert(10,33);
  tree.insert(5,23);
  tree.insert(15,1.32); 
  tree.insert(19,3.2);
  tree.inOrder();
  tree.erase(5);
  tree.inOrder();
  tree.erase(43);
  tree.erase(45);
  tree.inOrder();
  tree.erase(23);
  tree.inOrder();*/
  return 0;
}


