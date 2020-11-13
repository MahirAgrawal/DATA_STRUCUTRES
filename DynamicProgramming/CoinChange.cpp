#include<iostream>
#include<queue>
#define queue std::queue
#include<vector>
#define vector std::vector
#define cout std::cout
#define cin std::cin
#define endl '\n'
/** RECURSION ON THIS PROBLEM MAKES S^A CALL WHERE S = TOTAL COINS AND A = TOTAL AMOUNT SO THIS TIME COMPLEXITY IS
*   VERY COSTLY HENCE WE MEMOIZE TO REDUCE THE NUMBER OF CALLS TO FUNCTIONS BY AVOIDING DUPLICATION OF CALLS OF SAME
*   FUNCTIONS FOR EVERY AMOUNT THERE IS ONLY ONE CALL MADE AND THEN ANSWER IS SAVED TO PROVIDE THE ANSWER IN O(1) IF
*   AGAIN FUNCTION WITH SAME AMOUNT IS CALLED SO,
*   THE TOTAL COMPUTATIONS MADE IS UNIQUE FOR EACH AMOUNT AND ANY REPITITION WOULD BE SERVED BY MAP OR LOOKUP TABLE
*   SO THE TOTAL TIME REDUCES TO O(S*A) WHERE A = AMOUNT AND S = NUMBER OF COINS.
*   BECAUSE FOR EVERY AMOUNT I.E. A,A-1,A-2,...,1 THERE WILL BE S PATHS FOR EACH SO TOTAL CALLS ARE O(S*N)
*/

//TOP DOWN APPROACH WITH MEMOIZATION
/**LOOKUP TABLE CAN BE ONE DIMENSIONAL ARRAY OF LENGTH = AMOUNT WHERE EACH CELL REPRESENTS A AMOUNT AND STORES THE
 * MINIMUM COINS TO HAVE THE AMOUNT AND FOR EVERY CELL YOU CHOOSE FROM S PATHS THE BEST PATH i.e. THE MINIMUM ONE
 * SO IN THIS WAY WE STORE THE CALCULATION IN CELL AFTER EACH COMPUTATION
 * 
 * FOR AMOUNT WE GO 'S' RECURSIVE CALLS WHERE WE FIND MINIMUM COINS AMONG {A-S1,A-S2,A-S3,..,} AMOUNTS AND STORE
 * THE VALUE FOR FURTHER USE
 */

int count = 0;
int minimumCoin(vector<int>& coinValue,int sum,int *minimumCoinMap){
  if(sum == 0)//sum has been achieved by coins
   return 0;
  if(minimumCoinMap[sum])
    return minimumCoinMap[sum];
  
  int minCoin = INT_MAX;
  count++;
  for(auto& i : coinValue)
    if(i && sum-i >= 0)//coin value is not zero
      minCoin = std::min(minimumCoin(coinValue,sum-i,minimumCoinMap),minCoin);
  if(minCoin != INT_MAX){
    minCoin++;
    minimumCoinMap[sum] = minCoin;//if reaching from this sum to the 0 is possible so the minStep and 1 for using
                                  //this coin also
  }
  else
    minimumCoinMap[sum] = minCoin;//INT_MAX if reaching to the 0 from this sum is not possible so storing it also
  return minCoin;
}

/**
 * THIS IS ONE OF THE DYNAMIC PROGRAMMING PROBLEMS WHERE WE CAN PERFORM BFS FOR EACH AMOUNT THERE ARE S PATHS
 * WHERE THE ADJACENT NODES WILL BE {A-S1,A-S2,A-S3,..,} AND WHERE EACH EDGE REPRESENTS ONE COIN 
 * USED SO IT BECOMES A UNDIRECTED GRAPH WITH ALL WEIGHTS = 1 AND THE NODE WE WANT TO REACH IS 0. 
 * SO THE BFS WILL GIVE SHORTEST EDGE PATH FROM START NODE WHICH IS GIVEN AMOUNT AND LAST NODE = ZERO AND AS 
 * EACH EDGE REPRESENTS ONE COIN SO THE SHORTEST EDGE LENGTH PATH WOULD MEAN MINIMUM COINS USED
 * ALSO HERE AS WE ONLY VISIT UNIQUE VERTEX AND NOT TRAVERSE THE VERTEX WHICH IS ALREADY TRAVELLED SO THIS PROPERTY
 * HELPS US TO AVOID DUPLICATIONS OF CALLS AND THUS GIVES SHORTEST COIN PATH TO ZERO
 */
//BREADTH FIRST SEARCH APPROACH
int coinChange(vector<int>& coins, int amount) {
  if(amount == 0)
    return 0;
  auto minCoinCount = *(new vector<int>(amount+5,-1));
  queue<int> sum;
  minCoinCount[amount] = 1;
  sum.push(amount);
  int minStep = -1;
  while(!sum.empty()){
    auto currentCount = minCoinCount[sum.front()];
    for(int i = 0;i < coins.size();i++){
      if(sum.front()-coins[i] == 0)
        return currentCount;
      else if(sum.front()-coins[i] > 0 && minCoinCount[sum.front()-coins[i]] == -1){
        sum.push(sum.front()-coins[i]);
        minCoinCount[sum.front()-coins[i]] = currentCount+1;
      }
    }
  count++;
  sum.pop();
  }
  return -1;
}

//BOTTOM UP APPROACH ITERATIVE SOLUTION
//IN THIS WE FILL THE ARRAY FROM THE 1st INDEX UPTO ARR[AMOUNT] AND THEN RETURNS THE ARR[AMOUNT]
//THIS TAKES O(A*S) AS ARRAY IS OF SIZE A AND FOR EACH CELL WE TAKE MINIMUM OF (ARR[A-S1],ARR[A-S2],...,ARR[A-Sn])
//HENCE IT TAKES A*S CALLS AND SPACE IS O(A)

int minimumCoin(vector<int>& coins,int amount){
  vector<int> lookupTable(amount+1);
  lookupTable[0] = 0;//zero coins to get zero amount
  for(int i = 1;i < lookupTable.size();i++){
    int minCoinCount = INT_MAX;
    for(int j = 0;j < coins.size();j++)
      if(i-coins[j] >= 0)//index exist
        minCoinCount = std::min(minCoinCount,lookupTable[i-coins[j]]);
    if(minCoinCount != INT_MAX)
      minCoinCount++;
    lookupTable[i] = minCoinCount;
  }
  return lookupTable[amount];
}


int main(){
  vector<int> coin;
  int n,sum,value;
  cout<<"ENTER NUMBER OF COINS: ";
  cin>>n;
  for(int i = 0;i < n;i++){
    cout<<"ENTER THE VALUE OF COIN: ";
    cin>>value;
    coin.push_back(value);
  }
  cout<<"ENTER THE SUM YOU WANT: ";
  cin>>sum;
  int *minimumCoinMap = (int *)calloc(sum+1,sizeof(int));
  auto minCoin = minimumCoin(coin,sum,minimumCoinMap);
  //considering case when given coin value in vector is 0 so in that case also sum cannot be achieved so in for{}
  //loop 'if' condition will not be executed and then minCoin will remain INT_MAX only which indicates sum can't
  //be achieved so we return -1 to indicate it's not possible
  if(minCoin != INT_MAX)
    cout<<"MINIMUM COIN: "<<minCoin<<endl;
  else
    cout<<"MINIMUM COIN: "<<-1<<endl;
  cout<<"CALLS MADE IN DP: "<<count<<endl;
  count = 0;
  cout<<coinChange(coin,sum)<<endl;
  cout<<"CALLS MADE IN BFS: "<<count<<endl;
  cout<<"MIN COIN CHANGE ITERATIVE: "<<minimumCoin(coin,sum)<<endl;
  return 0;
}

