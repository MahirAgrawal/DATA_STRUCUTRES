/**
 * EDGE LIST IS NOT TIME EFFICIENT AS IT USES BRUTE FORCE TO FIND ADJACENT VERTICES BUT HERE BY ADJACENCY MATRIX WE HAVE IMPROVED TIME COMPLEXITIES
 * 
 * TIME COMPLEXITIES:
 * 1) FINDING ADJACENCT VERTICES NOW JUST O(N), N = NUMBER OF VERTICES BECAUSE EACH ROW REPRESENT A VERTEX AND ALL THE VERTICES ADJACENT TO IT ARE PRESENT IN THAT
 *    ROW AND SO WE NEED NOT TO SCAN OTHER VERTICES' ROW
 * 2) FINDING IF THE EDGE EXIST BETWEEN TWO VERTICES NOW TAKES O(1) AS IF THERE IS A EDGE BETWEEN TWO VERTICES THEN IT WOULD MATRIX[VERTEX1][VERTEX2] WOULD HAVE 
 *    TRUE/1/WEIGHT TO INDICATE THE EDGE AND HENCE IT REQUIRES TO SEE THE MATRIX[VERTEX1][VERTEX2] CELL WHICH IS A CONSTANT OPERATION
 * 
 * SPACE COMPLEXITY:
 * THIS IS MAIN ISSUE AS SPACE IS TOO BIG FOR MATRIX IN ADJACENCY MATRIX AS IT IS O(N * N) SO IF THERE ARE 10^10 VERTICES THEN WE WOULD REQUIRES A MARTRIX HAVING
 * 10^20 CELLS WHICH IS ABOUT 10^8 TB AND THAT IS NOT A REALISTIC STORAGE WHICH IS AVAILABLE. ALSO MOST OF ROW CELLS MAY BE JUST ZERO(NO EDGE) BECAUSE REAL LIFE 
 * GRAPHS ARE SPARSE GRAPHS AND NOT DENSE GRAPHS SO MOST OF THE SPACE IS JUST ZERO
 * 
 *
 *
 */


#include<bits/stdc++.h>
#define cout std::cout
#define cin std::cin
#define endl '\n'
#define map std::map
#define string std::string

class Graph{

  int vertexN;
  int *adjacencyMatrix;//STORES THE ADJACENT EDGES INFO

  public:
  Graph(){
    cout<<"ENTER THE NUMBER OF VERTICES IN GRAPH: ";
    cin>>vertexN;
    adjacencyMatrix = (int *) calloc(vertexN*vertexN,sizeof(int));//STORES THE EDGE INFORMATION BETWEEN i and j BY STORING WEIGHT BETWEEN THEM SO USING INT
  }

  void addEdge(int a,int b,int weight = 1){

    if(a >= vertexN || b >= vertexN){
      cout<<"INDEX NOT IN RANGE"<<endl;
      return;
    }

    if(weight == 0){
      cout<<"MAKING WEIGHT AS DEFAULT WEIGHT BECAUSE IT CANNOT BE SMALLER THAN ONE"<<endl;
      weight = 1;
    }
    adjacencyMatrix[a*vertexN+b] = weight;//reaching out matrix(v1,v2) and putting weight in the cell to show connection
    adjacencyMatrix[a+vertexN*b] = weight;//undirected graph hence path(a,b) = path(b,a)
  }
  
  void adjacentVertex(int a){
    
    if(a >= vertexN){
      cout<<"INDEX NOT IN RANGE"<<endl;
      return;
    }

    cout<<"NEIGHBOURS: "<<endl;
    for(int i = 0;i < vertexN;i++)
      if(adjacencyMatrix[a*vertexN+i] != 0)
        cout<<i<<" WEIGHT: "<<adjacencyMatrix[a*vertexN+i]<<endl;
    
    cout<<endl;
  }

  bool isEgdePresent(int a,int b){
    if(a >= vertexN || b >= vertexN){
      cout<<"INDEX NOT IN RANGE"<<endl;
      return false;
    }

    if(adjacencyMatrix[a*vertexN+b])//not equal to zero
      return true;
    return false;
  }



  ~Graph(){
    delete []adjacencyMatrix;
  }

};

int main(){
  
  Graph graph;
  int node1,node2,weight;

  while(1){
    cout<<"ENTER TWO CITIES CONNECTED(Enter -1 for exit): ";
    cin>>node1;
    if(node1 == -1)
      break;
    cin>>node2;
    cout<<"ENTER THE PATH LENGTH BETWEEN THEM: ";
    cin>>weight;
    graph.addEdge(node1,node2,weight);
  }


  while(1){
    cout<<"ENTER THE CITY TO SHOW ITS CONNECTED CITIES(Enter -1 for exit): ";
    cin>>node1;
    if(node1 == -1)
      break;
    graph.adjacentVertex(node1);
  }

  while(1){
    cout<<"ENTER THE TWO CITIES TO KNOW IF PATH BETWEEN THEM EXIST(Enter -1 for exit): ";
    cin>>node1;
    if(node1 == -1)
      break;
    cin>>node2;
    cout<<"PATH EXIST: "<<graph.isEgdePresent(node1,node2)<<endl;
  }

  return 0;
}
