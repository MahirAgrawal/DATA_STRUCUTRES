#include<iostream>
#include<conio.h>
#define cout std::cout
#define cin std::cin
#define endl '\n'
#define LEFT(X) (2*X+1)
#define RIGHT(X) (2*X+2)

class SegmentTree{

  public:
  class Segment{
    public:
    int queryAns; //STORE THE COMBINED QUERY ANSWER OF ITS CHILD RANGES
    int lazyUpdate;//STORES THE UPDATES (LAZY PROPOGATION)

    Segment(){
      this -> queryAns = INT_MAX;//BUILDING A MIN QUERY TREE SO USING INT_MAX
      this -> lazyUpdate = 0;
    }

    ~Segment(){
      this -> queryAns = 0;
      this -> lazyUpdate = 0;
    }
  };

  int arr_size,*arr;
  Segment *tree = NULL;
  int tree_size;

  SegmentTree(int *arr,int n){//PASSED THE SIZE OF ARRAY AROUND WHICH QUERY WILL BE ASKED
  
    int size_tree = 1;
    while(size_tree < n)//GETTING TO THE POWER OF 2 SO THAT THE SIZE OF SEGMENT TREE IS LARGE THAN SIZE OF ACTUAL ARRAY GIVEN FOR QUERIES
      size_tree = size_tree << 1;
   
    size_tree = (2 * size_tree -1);
    tree = new Segment[size_tree];//BUILDING A SEGMENT TREE OF SIZE (2*N - 1)(where the N is the lowest power of 2 greater than n) ON TOP OF ARRAY TO ANSWER QUERY IN O(LOGN)
    this -> arr_size = n;
    this -> arr = arr;
    this -> tree_size = size_tree;
    buildSegTree(0,0,n-1);
  }

  int buildSegTree(int index,int low,int high){
    //cout<<"index: "<<index<<" "<<low<<" "<<high<<endl;  
    if(low == high)//single index itself
      tree[index].queryAns = arr[low];
    
    else{
      int left_result = buildSegTree(LEFT(index),low,(low+high)/2);
      int right_result = buildSegTree(RIGHT(index),(low+high)/2+1,high);
      tree[index].queryAns = std::min(left_result,right_result);//BUILDING MINQUERY SEGMENT TREE
    }

    return tree[index].queryAns;
  }
 
  int minQuery(int index,int low,int high,int g_low,int g_high){//TO SEARCH MIN IN GIVEN RANGE OF g_low and g_high BOTH INCLUSIVE
    
    cout<<index<<" "<<low<<" "<<high<<" "<<g_low<<" "<<g_high<<endl;
    if(tree[index].lazyUpdate != 0){//UPDATING LAZY UPDATES
      cout<<"UPDATING LAZILY: "<<tree[index].lazyUpdate<<endl;
      tree[index].queryAns += tree[index].lazyUpdate;//UPDATING THE LAZY UPDATE WHEN WE TOUCH A NODE AND ALSO PROPOGATE LAZYUPDATE TO LEFT AND RIGHT
      propogateUpdate(index,tree[index].lazyUpdate);
      tree[index].lazyUpdate = 0;//SINCE THE UPDATE HAS BEEN DONE AND ALSO PROPOGATED SO REMOVING THE UPDATE
    }
    
    if(low >= g_low && high <= g_high){//RANGE MATCHED EXACTLY
      cout<<"matched: "<<low<<" "<<high<<endl;
      return tree[index].queryAns;
    }
    
    else if(g_low > high || g_high < low)//COMPLETELY DISJOINT RANGE
      return INT_MAX;
    
    else{//PARTIAL OVERLAP SO AGAIN SERCHING FOR THE RANGE IN BOTH LEFT AND RIGHT
      int left_result = minQuery(LEFT(index),low,(low+high)/2,g_low,g_high);//SEARCHING FOR QUERY IN LEFT SO DIVING QUERY ALSO
      int right_result = minQuery(RIGHT(index),(low+high)/2+1,high,g_low,g_high);//SEARCHING FOR QUERY IN RIGHT
      tree[index].queryAns = std::min(tree[LEFT(index)].queryAns,tree[RIGHT(index)].queryAns);
      return (std::min(left_result,right_result));
    }
  }

  void propogateUpdate(int parent_index,int update){
    if(LEFT(parent_index) < tree_size){//PROPAGATE THE UPDATE TO LEFT OF SEGMENT
      tree[LEFT(parent_index)].lazyUpdate +=  update;
      //cout<<tree[LEFT(parent_index)].lazyUpdate<<endl;
      //cout<<"PROPOGATE: "<<LEFT(parent_index)<<endl;
    }

    if(RIGHT(parent_index) < tree_size){//PROPOGATE THE UPDATE TO RIGHT OF SEGMENT
      tree[RIGHT(parent_index)].lazyUpdate += update;
      //cout<<"PROPOGATE: "<<RIGHT(parent_index)<<endl;
    }
  }


  int updateQuery(int index,int low,int high,int g_low,int g_high,int update_n){//TO UPDATE ALL NUMBERS FOR GIVEN RANGE G_LOW AND G_HIGH TO update_n
    
    if(tree[index].lazyUpdate != 0){
      cout<<"UPDATING LAZILY: "<<tree[index].lazyUpdate<<endl;
      tree[index].queryAns += tree[index].lazyUpdate;//UPDATING THE LAZY UPDATE WHEN WE TOUCH A NODE AND ALSO PROPOGATE LAZYUPDATE TO LEFT AND RIGHT
      propogateUpdate(index,tree[index].lazyUpdate);
      tree[index].lazyUpdate = 0;//SINCE THE UPDATE HAS BEEN DONE AND ALSO PROPOGATED SO REMOVING THE UPDATE
    }

    if(low >= g_low && high <= g_high){//RANGE MATCHED EXACTLY SO... 1)UPDATING THE QUERYANS IN THE NODE AND PROPOGATING UPDATE INTO LEFT AND RIGHT
      tree[index].queryAns += update_n;
      propogateUpdate(index,update_n); 
    }

    else if(g_high < low || g_low > high);//DISJOINT RANGE SO JUST RETURN THE tree[index].queryAns WHICH IS UPDATED VALUE AFTER LAZY PROPOGATION ADDITION

    else{//PARTIAL OVERLAP
      int left_result = updateQuery(LEFT(index),low,(low+high)/2,g_low,g_high,update_n);
      int right_result = updateQuery(RIGHT(index),(low+high)/2+1,high,g_low,g_high,update_n);
      tree[index].queryAns = std::min(left_result,right_result);
    }
    
    return tree[index].queryAns;
  }

  //INTERFACE TO USE minQuery
  int minQuery(int g_low,int g_high){
    return minQuery(0,0,this -> arr_size - 1,g_low,g_high);
  }

  //INTERFACE TO USE UPDATEQUERY
  void updateQuery(int g_low,int g_high,int update){
    updateQuery(0,0,arr_size-1,g_low,g_high,update);
  }

  void print(){
    for(int i = 0;i < tree_size;i++)
      cout<<tree[i].queryAns<<" ";//<<tree[i].lazyUpdate<<endl;
    cout<<endl;
  }

};

int main(){
  
  int arr[] = {23,5,-2,-5,5,0};
  SegmentTree T(arr,6);
  T.print();
  cout<<"QUERY: "<<T.minQuery(1,5)<<endl;//<<" "<<T.minQuery(3,4)<<" "<<T.minQuery(1,5)<<endl;
  T.updateQuery(0,2,2);
  T.print();
  cout<<"QUERY: "<<T.minQuery(1,5)<<endl;
  cout<<"QUERY: "<<T.minQuery(1,1)<<endl;
  T.print();
  return 0;
}
