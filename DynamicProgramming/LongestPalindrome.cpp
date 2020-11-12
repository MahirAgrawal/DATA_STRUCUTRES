#include<iostream>
#include<vector>
#include<string>
#define string std::string
#define cout std::cout
#define vector std::vector
#define cin std::cin
#define endl '\n'
//REFERENCE LEETCODE EDITORIAL OF LONGEST PALINDROME PROBLEM ALSO READ ALL APPROACHES TO SOLVE THIS PROBLEM INCLUDING O(n)

/**gives the longest palindrome for the given string
*THE GENERAL IDEA IS THAT FOR A GIVEN STRING ISPALINDROME(str[first],str[last]) if(str[first] == str[last]) then check for ISPALINDROME(str[first+1],str[last-1]),
*ISPALINDROME(str[first],str[last-1]) and ISPALINDROME(str[first+1],str[last])
*E.G _a_abbaa_a_ (first and last == a) hence check for ISPALINDROME(abbaa), ISPALINDROME(aabbaa) and ISPALINDROME(abbaaa)
*
*ALSO INCASE str[first] != str[last] check for ISPALINDROME(str[first],str[last-1]) and ISPALINDROME(str[first+1],str[last])
*E.G _a_bba_d_ (a != d) so check ISPALINDROME(abba) and ISPALINDROME(bbad)
*
*/

//TOP DOWN APPROACH WITH MEMOIZATION
string longestPalindromeString = "";
vector<vector<int>> lookupTable;
int longestPalindrome(string& a,int start_i,int end_i){
  if(lookupTable[start_i][end_i] != -1)
    return lookupTable[start_i][end_i];
  int maxPalin = 0;
  
  if(start_i == end_i){
    maxPalin = 1;
    if(longestPalindromeString.size() < maxPalin)
      longestPalindromeString = a.substr(start_i,end_i-start_i+1);
  }
  
  else if(start_i+1 == end_i){//case when the length of string is 2 like 'ab' or 'aa'
    if(a[start_i] == a[end_i]){//when both letters are same like 'aa' or 'bb' hence returning length of 2
      maxPalin = 2;
    if(longestPalindromeString.size() < maxPalin)
      longestPalindromeString = a.substr(start_i,maxPalin);
    }
    else{//when both are different hence the max length can be 1 like for 'ab' the max length palindrome is a or b
      maxPalin = 1;
      if(longestPalindromeString.size() < maxPalin)
        longestPalindromeString = a.substr(start_i,maxPalin);
    }
  }
  
  else{
    bool checkVariants = true;
    if(a[start_i] == a[end_i]){//when for given length the first letter is equal to last letter
      maxPalin = longestPalindrome(a,start_i+1,end_i-1);
      if(maxPalin + 2 == end_i - start_i + 1){//when substring from index (start_i,end_i) is also palindrome then 
        maxPalin = end_i - start_i + 1;      //the given string must be palindrome itself and hence undoubtedly the 
                                             //largest palindrome we don't check other subproblems 
	        			     //i.e substring (start_i+1,end_i) and (start_i,end_i-1)
        checkVariants = false;//if passed string itself is palindromic then even if variant substrings are
	                      //palindromic they will be less length than this so need to check other substrings
	if(longestPalindromeString.size() < maxPalin)
          longestPalindromeString = a.substr(start_i,maxPalin);
      }
    }  
    
    if(checkVariants){
    //variantions to check palindrome property: e.g ...abbb... -> ....bbb... and ...abb....
      auto len1 = longestPalindrome(a,start_i,end_i-1);
      auto len2 = longestPalindrome(a,start_i+1,end_i);
      maxPalin = std::max(len1,len2);
    }
  }
  lookupTable[start_i][end_i] = maxPalin;
  return maxPalin;
}

int longestPalindrome(string& a){
  for(int i = 0;i < a.size();i++)
    lookupTable.push_back(*(new vector<int>(a.size(),-1)));
  return (longestPalindrome(a,0,a.size()-1));
}


//BOTTOM UP APPROACH
//FOR EASE OF TIME COMPLEXITY WE CAN USE ARRAYS INSTEAD OF VECTORS
string longestPalindromeBottomUp(string& a){
  
  vector<vector<int>> lookupTable;
  int start_i = 0,end_i = 0,maxlength = 1;
  for(int i = 0;i < a.size();i++)
    lookupTable.push_back(*(new vector<int>(a.size(),1)));
  for(int d = 1;d < a.size();d++){
    for(int i = 0,j = d;j < a.size();i++,j = i + d){
      if(a[i] == a[j]){
        if(i+1 <= j-1){//valid lookup cell
	  if(lookupTable[i+1][j-1] + 2 == j-i+1)
	    lookupTable[i][j] = j-i+1;
	  else
            lookupTable[i][j] = std::max(lookupTable[i][j-1],lookupTable[i+1][j]);
	}
	else
	  lookupTable[i][j] = 2;
      }
      else
        lookupTable[i][j] = std::max(lookupTable[i][j-1],lookupTable[i+1][j]);
      if(maxlength < lookupTable[i][j]){
        start_i = i;
	end_i = j;
	maxlength = lookupTable[i][j];
      }
    }
  }

  /*for(auto& i:lookupTable){
    for(auto& j:i)
      cout<<j<<" ";
    cout<<endl;
  }*/
  return a.substr(start_i,maxlength);
}

int main(){
  string a;
  cout<<"ENTER THE STRING TO GET IT'S LONGEST PALINDROME LENGTH: ";
  cin>>a;
  cout<<"LENGTH: "<<longestPalindrome(a)<<" FOR "<<longestPalindromeString<<endl;
  cout<<longestPalindromeBottomUp(a);
  return 0;
}

