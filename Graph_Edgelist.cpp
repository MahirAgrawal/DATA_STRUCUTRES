/**
 * EDGE LIST IS A LIST TYPE DATA STRUCTURE WHICH STORES ALL EDGES IN GRAPH IN A CONTINUOUS LIST AND NO ORDER IS
 * MAINTAINED 
 * 
 * SPACE COMPLEXITY: O(M+N),WHERE M IS NUMBER OF EDGES AND N IS NUMBER OF VERTICES BECAUSE WE STORE EVERY EDGE IN 
 * LIST(O(M)) AND ALSO MAINTAIN A HASH TABLE FOR MAPPING ACTUAL VERTEX TO A REFERENCE NUMBER FOR EASY SEARCHING O(N)
 * 
 * TIME COMPLEXITY:
 *1)SEARCHING ALL ADJACENT VERTICES: IT TAKES TO TRAVERSE THE WHOLE EDGE LIST AND DETERMINE THE EDGE HAVING ONE END
 *  AS THE GIVEN VERTEX AND THE OTHER BECOME ITS NEIGHBOUR BUT CLEARLY HERE WE ARE DOING A LOT OF EXTRA WORK 
 *  BECAUSE FOR A SINGLE VERTEX WE HAVE TO SCAN THROUGH THE WHOLE LIST OF EDGES SO THIS IS KIND OF BRUTE FORCE AND 
 *  HENCE NOT EFFICIENT O(M)
 *
 *2)FINDING IF EDGE EXIST BETWEEN TWO GIVEN VERTICES: THIS LIKE IN ABOVE IS HAVING A BRUTE FORCE APPROACH AND SO WE
 *  WE HAVE TO TRAVERSE THE WHOLE EDGE LIST FOR FINDING THE EDGE 
 *  THEREFORE THE TIME TO DELETE A EDGE IS O(M) AS IT REQUIRES SEARCHING THROUGH THE LIST
 *
 * SO OVERALL THE DATASTRUCTURE IS NOT EFFICIENT AS NO ORDERING OR ARRANGEMENT IS THERE AND WE HAVE TO ALWAYS TAKE
 * BRUTE FORCE APPROACH FOR FINDING QUERY ANSWER
 *
 */


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
    
    
    if(queryVertex == vertex.end()){//if vertex int code doesn't exist then it means no such vertex is ever added
      cout<<"VERTEX "<<a<<" DOESN'T EXISTS!!"<<endl;
      return;
    }
    
    vector<string> neighbours;//to collect neighbour vertices
 
    //vertex int code exist so the vertex was pushed/added in past
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

  bool edgeExist(string a,string b){//determines whether the edge between two given vertices exist or not
 
    auto queryVertex1 = vertex.find(a);//finds the int code for given string vertex
    auto queryVertex2 = vertex.find(b);//finds the int code for given string vertex
    if(queryVertex1 == vertex.end() || queryVertex2 == vertex.end()){
      cout<<"TWO GIVEN VERTEX SHOULD BE A PART OF GRAPH"<<endl;
      return false;
    }

    auto vertexCode1 = queryVertex1 -> second;
    auto vertexCode2 = queryVertex2 -> second;
    for(auto& i:edgeList){
      if(i.first == vertexCode1 && i.second == vertexCode2)
        return true;
      else if(i.first == vertexCode2 && i.second == vertexCode1)
        return true;
    }
    return false;
  }

  ~Graph(){
    edgeList.clear();
    vertex.clear();
  }
};

int Graph::vertexindex = 0;

int main(){
  
  Graph friendnetwork;
  string friend1,friend2;

  while(1){
    cout<<"ENTER PAIR OF FRIENDS(Enter 0 for exit): ";
    cin>>friend1;
    if(friend1 == "0")
      break;
    cin>>friend2;
    friendnetwork.addEdge(friend1,friend2);
  }


  while(1){
    cout<<"ENTER THE PERSON OF WHICH YOU WANT TO FIND FRIENDS(Enter 0 for exit): ";
    cin>>friend1;
    if(friend1 == "0")
      break;
    friendnetwork.printAdjacentVerticesTo(friend1);
  }

  while(1){
    cout<<"ENTER THE TWO NAMES OF WHICH YOU WANT TO FIND IF THEY ARE FRIEND(Enter 0 for exit): ";
    cin>>friend1;
    if(friend1 == "0")
      break;
    cin>>friend2;
    cout<<"FRIENDSHIP EXIST: "<<friendnetwork.edgeExist(friend1,friend2)<<endl;
  }

  return 0;
}
