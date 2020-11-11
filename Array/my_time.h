#include<iostream>
#include<chrono>
#include<windows.h>
class timer{
std::chrono::time_point<std::chrono::high_resolution_clock>start,end;
public:
timer()
{start = std::chrono::high_resolution_clock::now();}
void reset()
{start = std::chrono::high_resolution_clock::now();}
void stop()
{end = std::chrono::high_resolution_clock::now();
auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
std::cout<<"YOUR PROGRAM TOOK "<<dur.count()<<" MICROSECONDS"<<std::endl;}
};
/*int main()
{
timer t;
//for(int i = 0;i < 1000;i++);
Sleep(1000);
t.stop();
t.reset();
Sleep(2000);
//for(int i  =0;i < 100000000;i++);
t.stop();
return 0;
}*/
