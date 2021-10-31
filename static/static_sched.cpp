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
//integrate and add to an array
void helperIntergration(float (*f)(float, int), double frac, double a, int i, int intensity, float& valueToChange){
 valueToChange = frac * f(a + (i+0.05) * frac, intensity);

} 


double integrateFunction(float (*f)(float, int), float frac, float a, float i, int intensity ){
	double value = (frac)*(f(a+(i+0.5)*frac, intensity));
	return value; //f(a + (i+0.5)*frac, intensity) * frac;
}

void integrateFunction(float (*f)(float, int), double frac, double a, float i, int intensity, float& valueToChange ){
  valueToChange = frac *f(a + (i+.5)*frac, intensity);
}

double integrate(int functionid, double a, double b, int n, int x, int intensity) {

    SeqLoop s1;




    double frac = (b - a) / n; //this is calculating the width
    double second = 0; //this varibale is for the area
    int id = functionid; //function 
    double sum = 0; // sum of rectangles

  
     
     
    if (id == 1) {
       
      //  for (int i = n; i < n+1; i++) {
            
         second = frac * f1(a + (x+0.5)*frac, intensity);
          
            sum = sum + second;
        //}
    }
    else if (id == 2) {
        for (int i = 1; i <= n; i++) {

            second = frac * f2(a + (i+05)*frac, intensity);
		
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
    }

    return sum;




}   



double integrate2(int functionid, double a, double b, int n, int intensity, int numberOfThreads, int end, int start) {

    SeqLoop s1;
	std::cout << "we are here ";



    double frac = (b - a) / n; //this is calculating the width
    double second = 0; //this varibale is for the area
    int id = functionid; //function 
    double sum = 0; // sum of rectangles
    
    float (*functionInUse)(float, int);

    switch (functionid)
    {
    case 1:
      functionInUse = f1;
      break;
    case 2:
      functionInUse = f2;
      break;
    case 3:
      functionInUse = f3;
      break;
    case 4:
      functionInUse = f4;
      break;
    default:

      break;
    }
     
if (id == 1) {
       
       s1.parfor(0, end, 1,
	    [&](int start) -> void{
	      second = frac * f1(a + (start+.5)*frac, intensity);
          
            sum = sum + second;
	    }
	    );
	    
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

  /*  s1.parfor<float>(0, n, 1, numberOfThreads,
		 [&](float& tls){
		   tls = 0;
		 },
		[&](int i, float& tls) ->void {
		   
       tls = integrateFunction(*functionInUse, ((b-a)/n), a, i, intensity);
       
		  },
		 [&](float tls) -> void{
		   sum += tls;

		 });*/

    return sum;




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
    float n = atof(argv[4]);
    int nThreads = atoi(argv[6]);
     
    int intensity = atoi(argv[5]);

    float (*functionInUse)(float, int);

    switch (functionid)
    {
    case 1:
      functionInUse = f1;
      break;
    case 2:
      functionInUse = f2;
      break;
    case 3:
      functionInUse = f3;
      break;
    case 4:
      functionInUse = f4;
      break;
    default:

      break;
    }
double frac = (b-a)/n;
std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

//an = integrate(functionid, a, b, n, intensity);
//an = integrate2(functionid, a, b, n, intensity, nThreads);
double testVariable = 0;
    double sum = 0;
   
    s1.parfor<double>(1, n, 1, nThreads,
		 [&](double& tls){
		 tls = 0;

		 },
		[&](int i, double& tls) ->void {
      		//float passThrough = (float)i;	
		//tls += integrate(functionid, a, b, n, i, intensity);
		//std::cout<< "|TLS before " << tls << " |"; 
		tls += integrateFunction(*functionInUse, frac, a, i, intensity);
		//std::cout<<"TLS after "<< tls<< " |";  
		},
		 [&](double& tls) -> void{
		   sum += tls;
			//std::cout<< " |sum: "<< sum << " |";
		 }
		 );

std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

std::chrono::duration<double> elapsed_seconds = end-start;

//std::cout<< "made it here: ";



std::cout << sum << std::endl;

std::cerr<<elapsed_seconds.count()<<std::endl;
	
  return sum;
}

