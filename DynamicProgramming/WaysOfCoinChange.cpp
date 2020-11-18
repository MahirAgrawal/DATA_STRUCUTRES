#include<iostream>
#include<vector>
#define vector std::vector
#define cout std::cout
#define cin std::cin
#define endl '\n'
typedef long long ll;

//    REFER BACK TO BACK SWE FOR EXPLANATION

//IN THIS PROBLEM WE HAVE TO FIND THE NUMBER OF WAYS TO ACHIEVE A COIN PRICE FROM GIVEN COIN DENOMINATIONS
ll WaysToCoinChange(vector<int>& coin,int sum){
  ll coinWay[coin.size()][sum];
  
  for(int i = 0;i < sum;i++){
    if(coin[0] > i+1)
      coinWay[0][i] = 0;
    else{
      ll way = 0;
      if(i+1 - coin[0] == 0)
        way++;
      else
        way += coinWay[0][i-coin[0]];
      coinWay[0][i] = way;
    }
  }

  for(int i = 1;i < coin.size();i++){
    for(int j = 0;j < sum;j++){
      if(coin[i] > j+1)
        coinWay[i][j] = coinWay[i-1][j];
      else{
	ll way = 0;
        if(j+1 - coin[i] == 0)
          way++;
	else
	  way += coinWay[i][j-coin[i]];
	way += coinWay[i-1][j];
	coinWay[i][j] = way;
      }
    }  
  }
  
  for(int i = 0;i < coin.size();i++){
    for(int j = 0;j < sum;j++)
      cout<<coinWay[i][j]<<" ";
    cout<<endl;
  }
  return coinWay[coin.size()-1][sum-1];
}

int main(){
  int n;
  cout<<"ENTER THE NUMBER OF COIN DENOMINATIONS: ";
  cin>>n;
  cout<<"ENTER THE COIN VALUES: ";
  vector<int> coin(n);
  for(int i = 0;i < coin.size();i++)
    cin>>coin[i];
  cout<<"ENTER THE VALUE YOU WANT TO ACHIEVE: ";
  cin>>n;
  cout<<"WAYS TO CHANGE COINS: "<<WaysToCoinChange(coin,n)<<endl;
  return 0;
}

