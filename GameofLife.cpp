#include<iostream>
#include<conio.h>
#include<cstdio>
#include<windows.h>
#include<stdlib.h>
#include<vector>
#define black 0
#define blue 1
#define light_gray 7
#define white 15
#define yellow 14
#define green 2
#define light_green 10
#define red 4
#define light_red 12
#define cout std::cout
#define cin std::cin
#define endl std::endl
#define fsream std::fstream
#define cerr std::cerr

void HighlightText(int front_color = 12,int back_color = 14)
{
WORD wCOLOR = ((back_color & 0x0F) << 4) + (front_color & 0x0F);
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hStdOut,wCOLOR);
return;
}

class GameofLife{
  
  short int *Cell,*Celltemp;
  int cols,rows;
  std::vector<std::vector<short int>> neighbours;
  public:
  GameofLife(int rows){
    Cell = new short int[rows*rows];
    this -> rows = rows;
    this -> cols = rows;
    randomize();
    Celltemp = NULL;
  }
  
  //0 for dead and 1 for live
  void randomize(){
    srand((unsigned int)Cell);
    for(int i = 0;i < rows;i++)
      for(int j = 0;j < cols;j++){
        Cell[i*cols+j] = rand()%2;
	//PRECALCULATING NEIGHBOURS' POSITION
	std::vector<short int> v;
        v.push_back(((i-1+cols)%cols)*cols+((j+cols)%cols));
        v.push_back(((i+1+cols)%cols)*cols+((j+cols)%cols));
        v.push_back(((i+cols)%cols)*cols+((j+1+cols)%cols));
        v.push_back(((i+cols)%cols)*cols+((j-1+cols)%cols));
        v.push_back(((i-1+cols)%cols)*cols+((j-1+cols)%cols));
        v.push_back(((i-1+cols)%cols)*cols+((j+1+cols)%cols));
        v.push_back(((i+1+cols)%cols)*cols+((j-1+cols)%cols));
        v.push_back(((i+1+cols)%cols)*cols+((j+1+cols)%cols));
	neighbours.push_back(v);
      }
  }
  
  void changeGeneration(){
    if(!Celltemp)
      Celltemp = new short int[rows*cols];
    int location = 0,sumofLife = 0;
    for(int i = 0;i < rows;i++){
      for(int j = 0;j < cols;j++){
        location = i*cols+j;
	sumofLife = getNeighbours(i,j);
	if(sumofLife == 2 || sumofLife == 3){
          if(!Cell[location] && sumofLife == 3)
	    Celltemp[location] = 1;
	  else
	    Celltemp[location] = Cell[location];
	}
	else{
          if(Cell[location] && sumofLife > 3 || sumofLife < 2) 
            Celltemp[location] = 0;
	  else
	    Celltemp[location] = Cell[location];
	}
      }
    }
    auto temp = Cell;
    Cell = Celltemp;//NEXT GENERATION
    Celltemp = temp;//FOR FURTHER USE
  }

  int getNeighbours(int i,int j){
    int sum = 0;
    for(int k = 0;k < 8;k++)
      sum += Cell[neighbours[i*cols+j][k]];
    return sum;
  }

  void printGeneration(){
    for(int i = 0;i < rows;i++){
      for(int j = 0;j < cols;j++){
        if(Cell[i*cols+j]){
	  HighlightText(white,white);
          cout<<"  ";
	  HighlightText(black,black);
       	}
	else
          cout<<"  ";
      }
      cout<<'\n';
    }
    HighlightText(light_gray,black);
  }
  
  void simulate(int generation){
    printGeneration();
    for(int i = 0;i < generation;i++){
       changeGeneration();
       printGeneration();
       system("cls");
    }  
  }
  
};

int main(){
  int rows = 0,generation;
  cout<<"ENTER THE ROWS: ";
  cin>>rows;
  cout<<"ENTER THE GENERATION: ";
  cin>>generation;
  system("cls");
  GameofLife& g = *(new GameofLife(rows));
  g.simulate(generation);
  HighlightText(light_gray,black);
}
