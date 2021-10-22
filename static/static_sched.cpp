#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include <thread>

#include "seq_loop.hpp"
//this our maion file to turn in with so use this one to add and stuff
#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

void integrateFunction(float (*f)(float, int), double frac, double a, int i, int intensity, float& valueToChange ){
  valueToChange = frac *f(a + (i+.5)*frac, intensity);
}




int main (int argc, char* argv[]) {
SeqLoop s1;

double an = 0;

  if (argc < 7) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads>"<<std::endl;
    return -1;
  }
    int functionid = atoi(argv[1]);
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    int n = atoi(argv[4]);
    int nThreads = atoi(argv[6]);
     
    int intensity = atoi(argv[5]);

std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

//an = integrate(functionid, a, b, n, intensity);
//an = integrate2(functionid, a, b, n, intensity, nThreads);
  double testVariable = 0;
  int iterationCount = 0;
  int threadNumber = 0;
  bool extraThreadNeeded = false;
  //number of iterations each thread should do
    int numberOfIterations = n / nThreads;
  //if there are uneven iterations then we add those here
    int extraIterations = 0;
    int threadsToUse = nThreads;
    if( n % nThreads != 0){
     extraIterations = n % nThreads;
     extraThreadNeeded = true;

    }
    
    if (extraThreadNeeded){
      threadsToUse += 1;
    }
    std::vector<std::thread> mythreads (threadsToUse);
   // mythreads.at(0) = std::thread(integrateFunction, f1, ((b-a/n)), a, i, intensity);

    //aray to add all the results from iterations
    double results[100];

    double sum = 0;
     s1.parfor<int>(0, n, 1,
		 [&](int& tls) -> void{
		    tls = 0.0;
       
		 },
		 [&](int i, float tls) -> void{
		   //tls +=frac *functionInUse(a + (i+.5)*frac, intensity); 
       //tls += integrateFunction(*functionInUse, frac, a, i, intensity);
       //results[i] =  std::thread mythread(integrateFunction, f1, ((b-a)/n), a, i , intensity);
       std::thread mythreads(integrateFunction,f1, ((b-a)/n), a, i , intensity, tls );
       std::cout << "tls = " << tls << " ";
       //tls += 
      // double value = std::thread mythread(integrateFunction, *functionInUse, frac, a, i, intensity);
		  },
		 [&](int tls) -> void{
		   sum += tls;
		 }
		 );

std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

std::chrono::duration<double> elapsed_seconds = end-start;

std::cout << sum << std::endl;

std::cerr<<elapsed_seconds.count()<<std::endl;

  return 0;
}

