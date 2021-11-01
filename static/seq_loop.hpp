#ifndef __SEQ_LOOP_H
#define __SEQ_LOOP_H
#include <thread>
//#include "static_sched.cpp"

#include <functional>
//int start = 0;
//int finish = 0;
//int breakPoint =0;
class SeqLoop {
public:
  /// @brief execute the function f multiple times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel
  void parfor (size_t beg, size_t end, size_t inc,
	       std::function<void(int)> f) {
    for (size_t i=beg; i<end; i+= inc) {
      f(i);
    }
  }
static void helperAddToArray(float& Value, float *list, int i){
list[i] = Value;
}

 
 static float helperFunction(void(*f)(int, float&),int end, int start, float tls){

        for(start; start < end; start++){
        f(start, std::ref(tls));
        }

  return tls;
 }

static void testFunction(int x, int y, double& tls, std::function<void(int, double&)>f, int breakPoint ){
	int counterTo = 0;

	for(x; x < y; x++){
	f(x, tls);
  	
	counterTo++;		
	
	if(counterTo == breakPoint - 1){
	break;
	}
	  
  	}

}


  // @brief execute the function f multipl
  //
  //e times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel.
  ///
  /// Each thread that participate in the calculation will have its
  /// own TLS object.
  ///
  /// Each thread will execute function before prior to any
  /// calculation on a TLS object.
  ///
  /// Each thread will be passed the TLS object it executed before on.
  ///
  /// Once the iterations are complete, each thread will execute after
  /// on the TLS object. No two thread can execute after at the same time.
  //youre threading should be done in here 
  //tls will need to go into an array
  
  std::vector<std::thread> mythreads;
  template<typename TLS>
  void parfor (size_t beg, size_t end, size_t increment, int nThreads,
	       std::function<void(TLS&)> before,
	       std::function<void(int, TLS&)> f,
	       std::function<void(TLS&)> after
	       ) {
    
    int count = 0;
    int breakPoint = (end)/nThreads;

    TLS tls[nThreads];
    
    std::vector<int> localStart;
    localStart.push_back(1);
    
    for(int j = 1; j < end; j++){
     if(count == breakPoint - 1){
     count = 0;
     localStart.push_back(j+1);
     
     }
     count++;
     }

    for(int x = 0; x < nThreads; x++){
     
     

     mythreads.push_back(std::thread(before, std::ref(tls[x]))); 
     
     //partition work here
     
     if(x == nThreads - 1){
     breakPoint += end + (end%nThreads);
     }

     //partition work before here

     mythreads.push_back(std::thread(testFunction, localStart.at(x),end, std::ref(tls[x]), f, breakPoint  ));
    


    }
    //mythreads.push_back(std::thread(after, std::ref(tls[tlsToUse])));     

    for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }
  
    for(int x = 0; x < nThreads; x++) {
    mythreads.push_back(std::thread(after, std::ref(tls[x])));
    }
    
    for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }

  }



};



#endif
