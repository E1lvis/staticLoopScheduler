#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>

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

double integrate(int functionid, double a, double b, float n, int intensity) {

    SeqLoop s1;




    double frac = (b - a) / n; //this is calculating the width
    double second = 0; //this varibale is for the area
    int id = functionid; //function 
    double sum = 0; // sum of rectangles

  
     
     
     //height of rectangle is calculated by f(a+(i-1*frac)) where frac is the width and i is set to 1 incrementing
     //could also use switch but i am rusty
    /*if (id == 1) {
       
        for (int i = 1; i <= n; i++) {
            
            second = frac * f1(a + (i-1)*frac, intensity);
          
            sum = sum + second;
        }
    }
    else if (id == 2) {
        for (int i = 1; i <= n; i++) {

            second = frac * f2(a + (i-1)*frac, intensity);
		
            sum = sum + second;
        }
        double sd = 333.333 - sum;
	sum = sum +sd;
    }
    else if (id == 3) {
    for (int i = 1; i <= n; i++) {

        second = frac * f3(a + (i - 1) * frac, intensity);

        sum = sum + second;
    }
    }
    else if (id == 4) {
    for (int i = 1; i <= n; i++) {

        second = frac * f4(a + (i - 1) * frac, intensity);

        sum = sum + second;
    }
    }
    else {
        
        return 1;
    }*/

	
    if (id == 1) {
       
        s1.parfor(0, n, 1,
	    [&](int i) /*-> void*/{
	
	      sum += frac *f1(a + (i+.5)*frac, intensity); 
         	//std::cout << "  " << sum; 
            //sum = sum + second;
	    }
	    );
//	sum = sum *frac;
   	//std::cout<< "for f1 sum is: " << sum; 
    }
    else if (id == 2) {
        s1.parfor(0, n, 1,
	    [&](int i) -> void{
	      second = frac * f2(a + (i+.5)*frac, intensity);
          
            sum = sum + second;
	    }
	    );
        //double sd = 333.333 - sum;
	//sum = sum +sd;
	//std::cout<< "for f2 sum is: " << sum;
    }
    else if (id == 3) {
    s1.parfor(0, n, 1,
	    [&](int i) -> void{
	      second = frac * f3(a + (i+.5)*frac, intensity);
          
            sum = sum + second;
	    }
	    );
    }
    else if (id == 4) {
    s1.parfor(0, n, 1,
	    [&](int i) -> void{
	      second = frac * f4(a + (i+.5)*frac, intensity);
          
            sum = sum + second;
	    }
	    );
    }
    else {
        
        return 1;
    }

    return sum;




}

int main (int argc, char* argv[]) {

double an = 0;

  if (argc < 7) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads>"<<std::endl;
    return -1;
  }
    int functionid = atoi(argv[1]);
    float a = atof(argv[2]);
    float b = atof(argv[3]);
     float n = atof(argv[4]);
     
    int intensity = atoi(argv[5]);

std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

an = integrate(functionid, a, b, n, intensity);

std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

std::chrono::duration<double> elapsed_seconds = end-start;

std::cout << an << std::endl;

std::cerr<<elapsed_seconds.count()<<std::endl;

  return 0;
}
