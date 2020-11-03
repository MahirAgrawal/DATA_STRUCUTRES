#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<iterator>
#define string std::string
#define vector std::vector
#define pair std::pair
#define iterator std::iterator
#define map std::map
#define cout std::cout
#define cin std::cin
#define endl std::endl

class Graph{
  
  static int vertexindex;
  
  map<string,int> vertex;//for mapping given names to int to avoid variable size graph edgelist
  map<int,string> inttovertex;//for mapping the other way around so that we can get name by integer
  vector<pair<int,int>> edgeList;

  public:
  Graph(){
    cout<<"GRAPH IS CREATED!!"<<endl;
  }

  void addEdge(string& a,string& b){
    auto vertex1 = vertex.find(a);
    auto vertex2 = vertex.find(b);
    int vertexCode1,vertexCode2;
    
    if(vertex1 == vertex.end()){//vertex is not yet given code
      vertexCode1 = vertexindex++;
      vertex[a] = vertexCode1;
      inttovertex[vertexCode1] = a;
    }

    else//vertex is given int code already and hence retrieving that int only
      vertexCode1 = vertex1 -> second;

    //doing same for second vertex
    if(vertex2 == vertex.end()){//vertex is not yet given code
      vertexCode2 = vertexindex++;
      vertex[b] = vertexCode2;
      inttovertex[vertexCode2] = b;
    }
    else//vertex is given int code already and hence retrieving that int only
      vertexCode2 = vertex2 -> second;

    edgeList.push_back(std::make_pair(vertexCode1,vertexCode2));//pushing pair of integers representing unique edge
  }

  void printAdjacentVerticesTo(string& a){//gives adjacent vertices to a
    auto queryVertex = vertex.find(a);//finds the int code for given string vertex
    
    vector<string> neighbours;//to collect neighbour vertices

    if(queryVertex == vertex.end()){//if vertex int code doesn't exist then it means no such vertex is ever added
      cout<<"VERTEX "<<a<<" DOESN'T EXISTS!!"<<endl;
      return;
    }
     
    //vertex int code exist so the vertex must be pushed/added
    int vertexcode = queryVertex -> second;
    for(int i = 0;i < edgeList.size();i++){
      if(edgeList[i].first == vertexcode)
        neighbours.push_back(inttovertex.find(edgeList[i].second) -> second);

      else if(edgeList[i].second == vertexcode)
        neighbours.push_back(inttovertex.find(edgeList[i].first) -> second);
    }
     
    cout<<"FRIENDS: ";
    for(auto& i:neighbours)
      cout<<i<<" ";
    cout<<endl;

    neighbours.clear();

  }

  ~Graph(){
    edgeList.clear();
    vertex.clear();
  }
};

int Graph::vertexindex = 0;

int main(){
  
  Graph friendnetwork;
  int n;
  string friend1,friend2;
  cout<<"ENTER THE NUMBER OF CONNECTIONS YOU WANT TO ADD: ";
  cin>>n;

  for(int i = 0;i < n;i++){
    cout<<"ENTER PAIR OF FRIENDS: ";
    cin>>friend1>>friend2;
    friendnetwork.addEdge(friend1,friend2);
  }

  friend1 = "null";
  while(1){
    cout<<"ENTER THE PERSON OF WHICH YOU WANT TO FIND FRIENDS(Enter 0 for exit): ";
    cin>>friend1;
    if(friend1 == "0")
      break;
    friendnetwork.printAdjacentVerticesTo(friend1);
  }
  return 0;
}
