#include<bits/stdc++.h>
using namespace std;
/*           LIS LONGEST INCREASING SUBSEQUENCE 
 *
 *           REFERENCE: CODING NINJAS AND BACK TO BACK SWE YOUTUBE VIDEOS
 * 
 *  TIME COMPLEXITY: FOR EVERY ith INDEX WE CHECK ALL INDICES TO LEFT OF IT FOR POSSIBLE SUBSEQUENCES LENGHT AND 
 * HENCE WE DO 0,1,2,3,4,5,...,n-1 CHECKS FOR 0th,1st,2nd,3rd,... index AND HENCE THE TOTAL BECOMES O(N^2)
 * COMPARISONS SO THE TIME COMPLEXITY BECOMES O(N^2)
 * 
 *  SPACE COMPLEXITY: FOR EVERY ith INDEX WE STORE THE LONGEST INCREASING SUBSEQUENCE LENGTH WHICH TELLS US THE
 * LONGEST LENGTH OF INCREASING SUBSEQUENCE ASSUMING THE SEQUENCE ENDS AT THE ith INDEX HENCE THE SPACE COMPLEXITY
 * BECOMES O(N)
 *
 *  VARIATION IN THIS PROBLEM CAN BE TO FIND THE ACTUAL LIST OF LONGEST INCREASING SUBSEQUENCE WHICH IS NOT HARD
 *  TO FIND THE ACTUAL LIST OF ELEMENTS WE CAN TRAVERSE BACKWARDS FROM THE MAXIMUM LENGTH INDEX i HAVING LENGTH 'M'
 *  AND THEN INCLUDE EVERY ELEMENT IN OUR LIST WHICH HAS LENGTH 'M-1','M-2' UPTO 1 AND THATS ALL 
 *  IT WORKS BECAUSE THE LONGEST INCREASING SUBSEQUENCE LAST ELEMENT IS APPENDED TO LIST WHICH WAS GIVING MAXIMUM
 *  LENGTH AFTER INCLUDING THE LAST ELEMENT SO SURELY IT WOULD HAVE 'LIS' EXACTLY ONE LESS THAN LAST ELEMENT AND SO
 *  LIS WILL BE 'M-1' AND IT CAN CONCLUDED FOR EVERY ELEMENT IN LONGEST INCREASING SUBSEQUENCE AND SO WE CAN FIND
 *  THE ELEMENTS THEMSELVES
 */
int LIS(vector<int>& Array){
  vector<int> LongestSequence(Array.size(),1);//Initially the max length of longest increasing subsequence would be
                                              //one because every individual index can be thought as a subsequence 
					      //of length one
  for(int i = 1;i < Array.size();i++){
    for(int j = 0;j < i;j++)
      if(Array[j] <= Array[i])//if element at ith index is greater than its previous indices' element
        LongestSequence[i] = std::max(LongestSequence[i],LongestSequence[j]+1);//choosing between appending ith
      	//element after subsequence ending at jth index or the present length at ith index is greater
  }
  
  //FINDING THE MAX LENGTH OF SUBSEQUENCE
  int maxLength = INT_MIN;
  for(auto& i:LongestSequence){
    maxLength = std::max(maxLength,i);
    cout<<i<<" ";
  }
  cout<<endl;
  return maxLength;
}

int main(){
  int n;
  cout<<"ENTER THE LENGHT OF ARRAY: ";
  cin>>n;
  vector<int> arr(n);
  cout<<"ENTER THE ELEMENTS: "<<endl;
  for(int i = 0;i < n;i++)
    cin>>arr[i];
  cout<<"ENTER THE LENGTH OF LONGEST INCREASING SUBSEQUENCE(NON STRICT): "<<LIS(arr);
  return 0;
}

