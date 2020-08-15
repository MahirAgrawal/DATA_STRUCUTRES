#include<stdio.h>
#include<stdlib.h>
//size_t is the return type of sizeof() operator basically means unsigned int

void quicksort(void *start,size_t size,size_t bytes,int (*comparator) (void *a,void *b),void (*swap)(void *a,void *b)){
if(size < 2)
  return;
unsigned int to_swap = 0;
for(int i = 0;i < size;i++){ 
  if(comparator(start+bytes*i,start+(size-1)*bytes)){  //LOOKING AT THIS CODE, 
    swap(start+bytes*i,start+to_swap*bytes);     //I THANKS TO C++ THAT TEMPLATES EXISTS FOR GENERIC PROGRAM!
    to_swap++;
    }
  }
swap(start+to_swap*bytes,start+(size-1)*bytes);
quicksort(start,to_swap,bytes,comparator,swap);
quicksort(start+(to_swap+1)*bytes,size-1-to_swap,bytes,comparator,swap);
}
int comparator(void *a,void *b){ //COMPARATOR TO BE PASSED FOR DECIDING WHETHER TO SWAP OR NOT
  if(*((int *)a) < *((int *)b))
    return 1;
  else
    return 0;
  }
void swap(void *a,void *b){//TO SWAP I NEED ADDRESS AND NUMBER OF BYTES BUT I FAILED IN COPYING BYTE BY BYTE DATA TO SWAP DATATYPE
	                   //IF IT WAS INT,CHAR OR ANY KNOWN THEN WE WOULD JUST TYPE CAST INTO THAT POINTER AND THEN SWAP EASILY BUT
			   //COPYING BYTE BY BYTE IS HARD FOR ME AS OF NOW SO INSTEAD I HAVE ALSO PASSED 'FUNCTION POINTER' TO 
	                   //SWAP THINGS AND IT SHOULD BE LIKE 'COMPARATOR', WRITTEN BY USER ONLY SO THIS WAS ONE EXTRA THING IN MY                            QUICK SORT
  int temp = (*((int *)a));
  *((int*)a) = *((int*)b);
  *((int*)b) = temp;
  }
int main(){
int n = 10;
int arr[10] = {4,3,5,43,1,55,3,5,3,24};
quicksort(arr,n,sizeof(int),comparator,swap);
printf("SORTED ARRAY: ");
for(int i = 0;i < n;i++)
  printf("%d ",arr[i]);
printf("\n");
return 0;
}
