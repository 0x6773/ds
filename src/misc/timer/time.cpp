// time.cpp
#include <iostream>
#include <chrono>
#include <string>
#include <cstdio>
#include <thread>

using namespace std;
using namespace std::chrono;

inline string exec(string cmd)
{
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    return "ERROR";
  char buffer[128];
  string result = "";
  while(!feof(pipe))
    {
      if(fgets(buffer, 128, pipe) != NULL)
	result += buffer;
    }
  pclose(pipe);
  return result;
}

int main(int argv, char *argc[])
{
  std::chrono::duration<double> min = 10s;
  std::chrono::duration<double> max = 0s;

  string cmd;
  if(argv > 1)
    for(int i = 1; i < argv; ++i)
      cmd += string(argc[i]) + " "s;
  else
    cmd = "ls";
  
  double mean = 0.0;
  for(int i = 1; i < 11; ++i)
    {
      auto start = std::chrono::high_resolution_clock::now();
      exec(cmd);
      auto end = std::chrono::high_resolution_clock::now();
      auto tmr = end - start;
      auto tt = tmr.count()/1000000000.0;
      cout << tt << endl;
      if(tmr < min)
    	  min = tmr;
      if(tmr > max)
	      max = tmr;
      mean += tt;
      if(tt > 1.0)
        this_thread::sleep_for(1s);
    }
  cout<<"Command \t\t: "<<cmd<<endl;
  cout<<"Max Time Taken \t\t: "<<max.count()<<" s"<<endl;
  cout<<"Min Time Taken \t\t: "<<min.count()<<" s"<<endl;
  mean/=10;
  cout<<"Average Time Taken \t: "<<mean<<" s"<<endl;
  
  return 0;
}
