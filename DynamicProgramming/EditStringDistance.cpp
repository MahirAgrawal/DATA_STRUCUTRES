#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#define vector std::vector
#define string std::string
#define cout std::cout
#define cin std::cin
#define endl '\n'

/**
 * THE DYNAMIC APPROACH BUILDS A TABLE OF SIZE M*N WHERE M,N IS LENGTH OF TWO GIVEN STRINGS
 * AND SO TIME AND SPACE COMPLEXITY IS O(N*M) WHICH IS FAR BETTER THAN EXPONENTIAL RUN TIME
 */

vector<vector<int>> lookupTable;//to store calculated subproblems
//moves to convert a into b
int editDistance(string& a,string& b,int i,int j){
  if(lookupTable[i][j] != -1)
    return lookupTable[i][j];
  int minStep;
  if(i == a.size() && j == b.size())
    minStep = 0;
  else if(i == a.size())//not sufficient characters in first string to convert into second string so insert all
	                //characters of remaining second string into first string
    minStep = b.size()-j;
  else if(j == b.size())//no more characters in second string to be matched in first string so delete all character
	                //of first string after i to get second string
    minStep = a.size()-i;
  else if(a[i] == b[j])//both characters of first and second characters matched so no operations of replace
	               //or delete is needed so just to convert string a from i+1 to string b from j+1 
    minStep = editDistance(a,b,i+1,j+1);
  else{
    auto tryDelete =  1 + editDistance(a,b,i+1,j);//try converting string a into string b by deleting i'th character
                                                  //from string a and converting that into string b and so deleting
						  //adds 1 into steps
    auto tryReplace = 1 + editDistance(a,b,i+1,j+1);//try converting string a into string b by replacing the non
                                                    //matching i'th character of string a into j'th character of
						    //string b
    auto tryInsert = 1 + editDistance(a,b,i,j+1);//try inserting mismatched character of string b into string a
                                                 //and hence now remaining characters from i needs to be check
						 //against j+1 because j'th position character is inserted
    minStep = std::min(std::min(tryDelete,tryReplace),tryInsert);
  }
  lookupTable[i][j] = minStep;
  return minStep;
}

int editDistanceBottomUpApproach(string& a,string& b){
  vector<vector<int>> lookupTable;
  for(int i = 0;i <= a.size();i++)
    lookupTable.push_back(*(new vector<int>(b.size()+1,-1)));
  
  //in case of string1 = "" and some string2 or some string1 and string2 = "" and 
  //hence insertions or deletions is equal to size of non empty strings
  for(int i = a.size();i >= 0;i--)
    lookupTable[i][b.size()] = a.size()-i;
  for(int j = b.size();j >= 0;j--)
    lookupTable[a.size()][j] = b.size()-j;
 
  for(int i = a.size()-1;i >= 0;i--){
    for(int j = b.size()-1;j >= 0;j--){
      if(a[i] == b[j])//doesn't need any operation as both characters are same
        lookupTable[i][j] = lookupTable[i+1][j+1];
      else//not same character so try insert,deletion and replace which can be done by fetching three cells of
	   //lookup table which are given in min() function
        lookupTable[i][j] = std::min(std::min(lookupTable[i+1][j+1],lookupTable[i+1][j]),lookupTable[i][j+1])+1;//added one as all three operations has 1 cost value
    }
  }

  return lookupTable[0][0];
}

int editDistance(string& a,string& b){
  for(int i = 0;i < a.size()+1;i++)
    lookupTable.push_back(*(new vector<int>(b.size()+1,-1)));
  return (editDistance(a,b,0,0));
}

int main(){
  string a,b;
  cout<<"ENTER STRING TO CONVERT: ";
  getline(cin,a);
  cout<<"ENTER THE STRING TO CONVERT INTO: ";
  getline(cin,b);
  cout<<"size: "<<a.size()<<" "<<b.size()<<endl;
  cout<<"STEPS TO CONVERT "<<a<<" INTO "<<b<<" IS: "<<editDistance(a,b)<<endl; 
  cout<<"BOTTOM UP APPROACH: "<<editDistanceBottomUpApproach(a,b)<<endl;
  return 0;
}

