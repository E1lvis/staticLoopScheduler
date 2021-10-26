#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>

void printHello(){
std::cout<< "hello" << " ";

}

int main (int argc, char* argv[]) {
std::vector<std::thread> mythreads;

  for(int x = 0; x < 10; x++){
      mythreads.push_back(std::thread ());

  }
 for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }

}