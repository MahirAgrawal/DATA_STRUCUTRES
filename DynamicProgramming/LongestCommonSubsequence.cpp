#include<iostream>
#include<string>
#include<vector>
#include<string.h>
#define vector std::vector
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl '\n'

/*
 * FOLLOW UP VIDEOS: BACK TO BACK SWE AND ABDUL BARI VIDEO
 */

/**
 * recursive method to find longest common subsequence of two given strings
 * but as recursive code itself is easy but we know from factorial or fibonacci method that repetitive calls are 
 * made and hence the time complexity is O(2^n) exponential and hence we use a matrix,array or hash table for
 * storing the calclated subproblems so that any repetitive call to same subproblem would be completed in O(1) time
 */


/*TOP DOWN APPROACH WITH MEMOIZATION BUT AS CODE WORKS RECURSIVELY THERE CAN BE A STACK OVERFLOW IN THE PROBLEMS WITH LARGE STRINGS LIKE A DOCUMENT OR LARGE FILE
 *SO THE RECURSIVE APPROACH IS EASY TO BUILD AND THINK BUT ITERATIVE CODE IS MUST FOR LARGE PROBLEMS
 */
char one[10000],two[10000];
short int *lookupTable;//for storing answers to subproblems
int size1,size2;
long long int count = 0;

//recursive piece of code for LARGEST COMMON SUBSEQUENCE
int LCS(int i = 0,int j = 0){
  count++;
  if(i == size1 || j == size2)
    return 0;
 if(lookupTable[i*size2+j] != -1)//if subproblem is already solved then return the answer in lookupTable
    return lookupTable[i*size2+j];
  int maxLCS = 0;
  //_a_bcd --first character matched for both strings
  //_a_ded
  if(one[i] == two[j])
    maxLCS = 1+LCS(i+1,j+1);
  else//if first letters not matched then try finding string1 in the substring of string2 which doesn't have first 
      //letter and vice versa
      //_a_bdefg -> lcs(abdefg in cdgef) 
      //_b_cdgef -> lcs(bcdgef in bdefg)
      //and return max of both of them
    maxLCS = std::max(LCS(i,j+1),LCS(i+1,j));
  lookupTable[i*size2+j] = maxLCS;//answer to this subproblem is stored for future use
  return maxLCS;
}

/*BOTTOM UP ITERATIVE 
 * IN THIS THE MATRIX IS NOT FILLED AFTER FINDING SOLUTIONS OF SUBPROBLEMS BUT INSTEAD THE SUBPROBLEMS' ANSWERS ARE FOUND FIRST AND SO THE SUBPROBLEMS ARE SOLVED 
 * FIRST AND THEN THE LARGER PROBLEMS ARE FILLED SO IT STARTS WITH THE SMALLEST PROBLEM AND THEN START TO FILL MATRIX WITH LARGER AND LARGER SUBPROBLEMS
 */
int LCS(char *a,char *b){
  auto size1 = strlen(a);
  auto size2 = strlen(b);  
  vector<vector<int>> lookupTable;//extra 1 for easing the empty string LCS call
  for(int i = 0;i < size1+1;i++)
    lookupTable.push_back(*(new vector<int>(size2+1)));//extra 1 for easing the empty string LCS call
  for(int i = 0;i < lookupTable.size();i++){
    for(int j = 0;j < lookupTable[i].size();j++)
      cout<<lookupTable[i][j]<<" ";
    cout<<endl;
  }

  for(int i = size1-1;i >= 0;i--){
    for(int j = size2-1;j >= 0;j--){
      if(a[i] == b[j])
        lookupTable[i][j] = 1+lookupTable[i+1][j+1]; 
      else
        lookupTable[i][j] = std::max(lookupTable[i][j+1],lookupTable[i+1][j]);
    }
  }
 
  for(int i = 0;i < lookupTable.size();i++){
    for(int j = 0;j < lookupTable[i].size();j++)
      cout<<lookupTable[i][j]<<" ";
    cout<<endl;
  }
 
  auto answer = lookupTable[0][0];
  lookupTable.clear();
  return answer;//lookupTable[0][0]
}

int main(){
  cout<<"ENTER THE FIRST STRING: ";
  cin>>one;
  cout<<"ENTER THE SECOND STRING: ";
  cin>>two;
  size1 = strlen(one);
  size2 = strlen(two);
  cout<<"size: "<<size1<<" "<<size2<<endl;
  lookupTable = new short int[size1*size2];
  for(int i = 0;i < size1*size2;i++)
    lookupTable[i] = -1;
  cout<<"RECURSIVE APPROACH: "<<LCS(0,0)<<endl;
  cout<<"ITERATIVE APPROACH: "<<LCS(one,two)<<endl;
  cout<<"Count: "<<count<<endl;
  delete []lookupTable;
  return 0;
}

