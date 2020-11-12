#include<iostream>
#include<map>
#define map std::map
#include<vector>
#define vector std::vector
#define cout std::cout
#define cin std::cin
#define endl '\n'
map<int,int> minimumCoinMap;

int minimumCoin(vector<int>& coinValue,int sum){
  if(sum == 0)//sum has been achieved by coins
   return 0;
  auto itr = minimumCoinMap.find(sum);
  if(itr != minimumCoinMap.end())
    return itr -> second;
  
  int minCoin = INT_MAX;
  
  for(auto& i : coinValue)
    if(i && sum-i >= 0)//coin value is not zero
      minCoin = std::min(minimumCoin(coinValue,sum-i),minCoin);
  if(minCoin != INT_MAX){
    minCoin++;
    cout<<"mapping: "<<sum<<":"<<minCoin<<endl;
    minimumCoinMap[sum] = minCoin;
  }
  return minCoin;
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
  auto minCoin = minimumCoin(coin,sum);
  //considering case when given coin value in vector is 0 so in that case also sum cannot be achieved so in for{}
  //loop 'if' condition will not be executed and then minCoin will remain INT_MAX only which indicates sum can't
  //be achieved so we return -1 to indicate it's not possible
  if(minCoin != INT_MAX)
    cout<<"MINIMUM COIN: "<<minCoin<<endl;
  else
    cout<<"MINIMUM COIN: "<<-1<<endl;
  return 0;
}

