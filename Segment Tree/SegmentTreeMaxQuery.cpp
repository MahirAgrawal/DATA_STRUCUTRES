#include<iostream>
#define cout std::cout
#define cin std::cin
#define endl '\n'

class SegmentTree{
  
  class Segment{
    public:
    long int queryAns;
    long int lazyUpdate;
    
    Segment(){
      this -> queryAns = INT_MIN;
      this -> lazyUpdate = 0;
    }
  };

   public:

   int tree_size,arr_size;
   Segment *tree = NULL;
   SegmentTree(int n){
     int size_n = 1;
     while(size_n < n)
       size_n = size_n << 1;
     size_n = size_n * 2 - 1;
     this -> tree_size = size_n;
     this -> arr_size = n;
     this -> tree = new Segment[tree_size];
     makeSegTree(0,0,n-1);
   }

   void makeSegTree(int index,int low,int high){
      
     if(low == high)
       tree[index].queryAns = 0;
      
     else{
       makeSegTree(2*index+1,low,(low+high)/2);
       makeSegTree(2*index+2,(low+high)/2 + 1,high);
       tree[index].queryAns = std::max(tree[2*index+1].queryAns,tree[2*index+2].queryAns);
     }
   }
    
    void propogateUpdate(int parent_index,long int update){
      if(2*parent_index+1 < tree_size)
        tree[parent_index*2+1].lazyUpdate += update;
      if(2*parent_index+2 < tree_size)
        tree[parent_index*2+2].lazyUpdate += update;
    }

    long int maxQuery(int index,int low,int high,int g_low,int g_high){
      
      if(tree[index].lazyUpdate != 0){
        tree[index].queryAns += tree[index].lazyUpdate;
        propogateUpdate(index,tree[index].lazyUpdate);
        tree[index].lazyUpdate = 0;
      }

      if(g_low <= low && high <= g_high)
        return tree[index].queryAns;

      else if(g_low > high || g_high < low){
        return INT_MIN;
      }

      else{
        auto left_ans = maxQuery(2*index+1,low,(low+high)/2,g_low,g_high);
        auto right_ans = maxQuery(2*index+2,(low+high)/2+1,high,g_low,g_high);
        tree[index].queryAns = std::max(tree[2*index+1].queryAns,tree[2*index+2].queryAns);//updating max value as lazy updates has been done in its both of its child
        return (std::max(left_ans,right_ans)); 
      }
    } 

    //INTERFACE TO USE MAXQUERY
    long int maxQuery(int g_low,int g_high){
      return maxQuery(0,0,arr_size-1,g_low,g_high);
    }

    void updateQuery(int index,int low,int high,int g_low,int g_high,long int g_update){
      
      cout<<low<<" "<<high<<" "<<g_low<<" "<<g_high<<endl;
      if(tree[index].lazyUpdate != 0){
        cout<<"LAZY PRO: "<<tree[index].lazyUpdate<<endl;
	tree[index].queryAns += tree[index].lazyUpdate;
        propogateUpdate(index,tree[index].lazyUpdate);
        tree[index].lazyUpdate = 0;
      }

      if(g_low <= low && high <= g_high){
        tree[index].queryAns += g_update;
        propogateUpdate(index,g_update);
      }

      else if(g_low > high || g_high < low){
        //lazyUpdate but no update is done on this range because it is non overlapping with g_low:g_high
      }

      else{
        //partial overlap so going both left and right to find required range in which update has to be done
        updateQuery(2*index+1,low,(low+high)/2,g_low,g_high,g_update);
        updateQuery(2*index+2,(low+high)/2+1,high,g_low,g_high,g_update);
        tree[index].queryAns = std::max(tree[2*index+1].queryAns,tree[2*index+2].queryAns);//updating max value as lazy updates has been done in its both of its child and Update in the child with range overlapping with the given range g_low:g_high
      }
      
    }

    //INTERFACE TO USE UPDATE
    void updateQuery(int g_low,int g_high,long int update){
      updateQuery(0,0,this -> arr_size - 1,g_low,g_high,update);
    }

    void printTree(){
      for(int i = 0;i < this -> tree_size;i++)
       cout<<tree[i].queryAns<<":"<<tree[i].lazyUpdate<<" ";
      cout<<endl;
    }
};

int main(){
  SegmentTree tree(5);
  tree.updateQuery(0,1,100);
  tree.printTree();
  tree.updateQuery(1,4,100);
  tree.printTree();
  tree.updateQuery(2,3,100);
  tree.printTree();
  cout<<tree.maxQuery(0,4)<<endl;
}
