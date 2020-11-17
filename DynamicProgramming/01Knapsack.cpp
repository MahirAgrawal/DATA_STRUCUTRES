#include<iostream>
#include<vector>
#define vector std::vector
#define cout std::cout
#define cin std::cin
#define endl '\n'

/**
 * CLASSICAL HARD PROBLEM TO GRASP AT FIRST SIGHT
 * references : back to back swe TO UNDERSTAND PROBLEM AND WHY WE CAN'T PERFORM GREEDY APPROACH HERE
 * 
 * PROBLEM: In this problem a bag is given with limit of capacity of weight 'w' and we have a 'n' number of 
 * different items with their weights and cost price. In this we have to pick the number of items in such a way that
 * their collective weights is <= knapsack capacity. BUT IN THIS WE HAVE TO MAXIMIZE THE VALUE OR TOTAL PRICE GAIN
 *
 * E.g. IF THE KNAPSACK CAPACITY IS 4 AND THE ITEMS ARE {weight:cost} = {{1:2}{2:3}{4:1}}. NOW THERE ARE MANY WAYS 
 * TO SELECT THE ITEMS SUCH AS {1,2} = 2+3 TOTAL VALUE,{4} = 1,{2} = 3,{1} = 2 AND NOW ALL THESE ARRANGEMENTS CAN BE
 * ACCOMODATED IN KNAPSACK OF 4 WEIGHT BUT WE WANT THE ARRANGEMENT GIVING HIGHER GAIN OF COST WHICH IS THE
 * ARRANGEMENT {1,2} GIVING US 5
 *
 * ALSO KEEP IN MIND:
 * -WE CAN'T DIVIDE ITEMS i.e. WE CAN EITHER CHOOSE IT OR NOT BUT WE CAN'T BREAK IT INTO PARTS for e.g. in above
 *  eg f we choose item of 2 weight then knapsack now can have only 2 kg more to accomodate in which it cannot take
 *  the item having weight 4 and also we can't 2 kg out of 4 from item hence we cannot divide the items into pieces
 *  EITHER WE CHOOSE A ITEM i.e. 1 OR WE DISCARD IT 0 so THE NAME '0/1 KNAPSACK PROBLEM
 * -ALSO WE ONLY HAVE ONE COPY OF EACH ITEMS HENCE WE CAN'T SELECT A ITEM TWICE OR MORE NUMBER OF TIMES WE CAN ONLY
 *  SELECT EACH ITEM ONCE AND SO EACH THIS IS VERY DIFFERENT FROM COIN CHANGE PROBLEM WHERE WE HAD UNLIMITED NUMBER
 *  OF COIN OF EACH TYPE 
 * -ALSO WE HAVE TO SELECT ITEMS WHICH HAS COLLECTIVELY WEIGHT EQUAL TO OR LESS THAN KNAPSACK WEIGHT SO WE HAVE A
 *  CONSTRAINT OF MAX WEIGHT WE CAN FILL KNAPSACK WITH
 *
 */

//TOP DOWN APPROACH WITH MEMOZIATION 
//       READ ON GEEKS FOR GEEKS THE TOP DOWN APPROACH WHERE WE PASS THE 'i' INDEX ALSO WHICH INDICATES THE ITEM FOR
//       WHICH WE ARE DECIDING TO CHOOSE OR NOT. THIS IS EQUIVALENT TO THE ROW TRAVERSAL IN BOTTOM UP APPROACH

//weightList: the number of list of weights available to pick
//valueList: the corresponding list of values of weights available to pick
//maxWeight: the max weight which knapsack can hold
//item indicates the index of item for which we decide to include it or not

long long maxValue(vector<vector<long long>>& knapsack,vector<int>& weightList,vector<int>& valueList,int maxWeight,int itemIndex){
  cout<<"call for index: "<<itemIndex<<" maxWeight: "<<maxWeight<<endl;

  if(knapsack[itemIndex][maxWeight] != -1)
    return knapsack[itemIndex][maxWeight];
  if(maxWeight < weightList[itemIndex]){
    if(itemIndex > 0)
      return (knapsack[itemIndex][maxWeight] = maxValue(knapsack,weightList,valueList,maxWeight,itemIndex-1));
    else  
      return knapsack[itemIndex][maxWeight] = 0;
  }
  
  long long value = valueList[itemIndex];
  if(itemIndex > 0 && maxWeight - weightList[itemIndex] > 0)
    value += maxValue(knapsack,weightList,valueList,maxWeight - weightList[itemIndex],itemIndex-1);
     
  if(itemIndex > 0)
    knapsack[itemIndex][maxWeight] = std::max(value,maxValue(knapsack,weightList,valueList,maxWeight,itemIndex-1));
  else
    knapsack[itemIndex][maxWeight] = value;
  return knapsack[itemIndex][maxWeight];
}

long long maxValueTopDown(vector<int>& weightList,vector<int>& valueList,int maxWeight){
  vector<vector<long long>> knapsack;
  for(int i = 0;i < weightList.size();i++)
    knapsack.push_back(*(new vector<long long>(maxWeight+1,-1)));
  cout<<"TOP DOWN INTITAL TABLE: "<<endl;
  for(auto& i:knapsack){
    for(auto& j:i)
      cout<<j<<" ";
    cout<<endl;
  }

  cout<<"TOP DOWN AFTER OPERATION TABLE: "<<endl;
  auto mV = maxValue(knapsack,weightList,valueList,maxWeight,weightList.size()-1);
  for(auto& i:knapsack){
   for(auto& j:i)
     cout<<j<<" ";
   cout<<endl;
  }
  return mV;
}
/**
 * BOTTOM UP APPROACH
 * DYNAMIC PROGRAMMING GIVES OPTIMAL SOLUTION BY MAKING A MATRIX OF O(M*N) where M: NUMBER OF ITEMS TO CHOOSE
 * N: THE TOTAL WEIGHT TO MAKE
 * HENCE BOTH SPACE AND TIME COMPLEXITY WILL BE O(M*N)
 */
long long maxValue(vector<int>& weightList,vector<int>& valueList,int maxWeight){
  long long knapsack[weightList.size()][maxWeight];
  for(int i = 0;i < maxWeight;i++){
    if(i+1 < weightList[0])
      knapsack[0][i] = 0;
    else
      knapsack[0][i] = valueList[0];
  }

  for(int i = 1;i < weightList.size();i++){
    for(int j = 0;j < maxWeight;j++){
      if(j+1 < weightList[i])//the item is heavier than the whole capacity of knapsack itself
        knapsack[i][j] = knapsack[i-1][j];
      else{
        long long valueAfterIncludingItem = valueList[i];//try including item so it will contribute in the value
	if(j-weightList[i] >= 0)//also including the item will reduce the scope of weight we can add
	  valueAfterIncludingItem += knapsack[i-1][j-weightList[i]];//hence the remaining weight will be fulfilled by
	                                                        //other items
	knapsack[i][j] = std::max(valueAfterIncludingItem,knapsack[i-1][j]);// the current knapsack will be maximum
	                                                                    //of the two values: 1)after including
									    //the current item and 2)not
									    //including the current item
      }
    }
  }
  
  cout<<"BOTTOM UP AFTER TABLE: "<<endl;
  for(int i = 0;i < weightList.size();i++){
    for(int j = 0;j < maxWeight;j++)
      cout<<knapsack[i][j]<<" ";
    cout<<endl;
  }
  return knapsack[weightList.size()-1][maxWeight-1];
}

//OPTIMIZING SPACE COMPLEXITY
//THE DYNAMIC PROGRAMMING APPROACH WORKS FINE BUT THE SPACE COMPLEXITY IS A BIG ISSUE BUT AS WE MIGHT HAVE OBSERVED
//THAT FOR GIVEN ROW i.e. ith ITEM WE JUST NEED (i-1)TH ROW AND HENCE AT A GIVEN TIME WE NEED JUST 2 ROWS OF LENGTH
//EQUAL TO MAXWEIGHT

int main(){
  int n;
  cout<<"ENTER THE NUMBER OF ITEMS: ";
  cin>>n;
  vector<int> weightList(n),valueList(n);
  for(int i = 0;i < weightList.size();i++){
    cout<<"ENTER THE WEIGHT :";
    cin>>n;
    weightList[i] = n;
    cout<<"ENTER THE VALUE OF THIS WEIGHT: ";
    cin>>n;
    valueList[i] = n;
  }
  cout<<"ENTER THE MAXIMUM CAPACITY OF KNAPSACK: ";
  cin>>n;
  cout<<"THE MAX VALUE FOR GIVEN ITEMS WITH LIMITED KNAPSACK WEIGHT: "<<maxValue(weightList,valueList,n)<<endl;
  cout<<"THE MAX VALUE FOR GIVEN ITEMS WITH LIMITED KNAPSACK WEIGHT: "<<maxValueTopDown(weightList,valueList,n)<<endl;  
  return 0;
}

