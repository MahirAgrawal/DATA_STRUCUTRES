#include<iostream>
#include<vector>
#define vector std::vector
#define cout std::cout
#define cin std::cin
#define endl '\n'
void printPartition(vector<vector<int>>& bracketTable,int start,int end);
//MCM MATRIX CHAIN MULTIPLICATION
vector<int> row;
vector<int> col;
vector<vector<int>> lookUpTable;

//has matrices stored in two seperate arrays one for row and other for column
int MCM(int start,int end){
  if(lookUpTable[start][end] != -1)
    return lookUpTable[start][end];
  int steps = 0;
  if(start == end)
    steps = 0;
  else{
    steps = INT_MAX;
    for(int i = start;i < end;i++){
      int stepForThisPartition = MCM(start,i);
      stepForThisPartition += MCM(i+1,end);
      stepForThisPartition += row[start]*col[end]*col[i];
      steps = std::min(steps,stepForThisPartition);
    }
  }
  cout<<"MINIMUM STEPS FOR: "<<start<<" "<<end<<" is: "<<steps<<endl;
  lookUpTable[start][end] = steps;
  return steps;
}

//has matrix in the merged form so has rows and columns in single array
//TOP DOWN APPROACH WITH MEMOIZATION
int MCM(vector<int>& matrix,int start,int end){
  //cout<<"call for: "<<start<<" "<<end<<endl;
  //cout<<"look: "<<lookUpTable[start][end]<<endl;
  if(lookUpTable[start][end] != -1)
    return lookUpTable[start][end];
  int steps = 0;
  if(start+1 == end)
    steps = 0;
  else{
    steps = INT_MAX;
    for(int i = start+1;i < end;i++){
      int stepForThisPartition = MCM(matrix,start,i);
      stepForThisPartition += MCM(matrix,i,end);
      stepForThisPartition += matrix[start]*matrix[end]*matrix[i];
      steps = std::min(steps,stepForThisPartition);
    }
  }
  //cout<<"MINIMUM STEPS FOR: "<<start<<" "<<end<<" is: "<<steps<<endl;
  lookUpTable[start][end] = steps;
  return steps;
}

/**REFERENCE ABDUL BARI YOUTUBE VIDEO
*  BOTTOM UP APPROACH WITH TABULATION
* ALSO IT STORES THE PARENTHESIZATION OF MATRICES TO GET THE MINIMUM OPERATIONS OF MATRICES. IT DOES THIS BY STORING
*  INDICES OF PARTITION INSTEAD OF MINIMUM OPERATION FOR SINGLE RANGE BUT THEN WE HAVE TO GO TO SMALLER RANGES' CELL
*  TO LOOK THE PARTITION OVER THERE
*  IT STORES THE PARTITION INDEX FOR EACH MATRICES RANGE(M(i+1),M2(i+2),M3(i+3),M4(i+4),...) SEE ABDUL BARI VIDEO ON
*  THIS
*/
int MCM(vector<int>& matrix){
  vector<vector<int>> lookUpTable;
  vector<vector<int>> bracketTable;//stores the paranthesization for the given vector of matrices 
  for(int i = 0;i < matrix.size();i++){
    lookUpTable.push_back(*(new vector<int>(matrix.size(),-1)));
    bracketTable.push_back(*(new vector<int>(matrix.size(),-1)));
  }
  for(int i = 1;i < matrix.size();i++){
    for(int j = 0;i+j < matrix.size();j++){
      if(i == 1)
        lookUpTable[j][i+j] = 0;
      else{
	int minOperation = INT_MAX;
	int index = -1;
        for(int k = j+1;k < i+j;k++){
	  minOperation = std::min(minOperation,lookUpTable[j][k]+lookUpTable[k][i+j]+matrix[j]*matrix[k]*matrix[i+j]); 
	  index = (minOperation<lookUpTable[j][k]+lookUpTable[k][i+j]+matrix[j]*matrix[k]*matrix[i+j])?index:k;
	}
        lookUpTable[j][i+j] = minOperation;
	bracketTable[j][i+j] = index;
      }
    }
  }
  for(auto& i:lookUpTable){
    for(auto& j:i)
      cout<<j<<" ";
    cout<<endl;
  }
  cout<<"PARTITION TABLE: "<<endl;
  for(auto& i:bracketTable){
    for(auto& j:i)
      cout<<j<<" ";
    cout<<endl;
  } 
  cout<<"BRACKETS PARTITION: "<<endl;
  printPartition(bracketTable,0,matrix.size()-1);
  return lookUpTable[0][matrix.size()-1];
}

void printPartition(vector<vector<int>>& bracketTable,int start,int end){
  if(start+1 == end)
    return;
  cout<<"FOR RANGE: "<<start<<":"<<end<<"is: "<<bracketTable[start][end]<<endl;
  printPartition(bracketTable,start,bracketTable[start][end]);
  printPartition(bracketTable,bracketTable[start][end],end);
}

int main(){
  int n,no;
  cout<<"ENTER NUMBER OF MATRIX: ";
  cin>>no;
  /*for(int i = 0;i < no;i++)
    lookUpTable.push_back(*(new vector<int>(no,-1)));
  for(int i = 0;i < no;i++){
    cin>>n;
    row.push_back(n); 
  }
  
  for(int i = 0;i < no;i++){
    cin>>n;
    col.push_back(n); 
  }*/
  
  //cout<<"THE MINIMUM STEPS TO DO MATRIX MULTIPLICATION IS: "<<MCM(0,no-1)<<endl;
 for(int i = 0;i <= no;i++)
   lookUpTable.push_back(*(new vector<int>(no+1,-1)));
 vector<int> matrix;
  for(int i = 0;i <= no;i++){
    cin>>n;
    matrix.push_back(n); 
  }
  cout<<"THE MINIMUM STEPS TO DO MATRIX MULTIPLICATION IS: "<<MCM(matrix,0,no)<<endl;
  for(auto& i:lookUpTable){
    for(auto& j:i)
      cout<<j<<" ";
    cout<<endl;
  }
  cout<<"THE MINIMUM STEPS TO DO MATRIX MULTIPLICATION BOTTOM UP: "<<MCM(matrix)<<endl;
  return 0;
}

