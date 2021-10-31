#ifndef __SEQ_LOOP_H
#define __SEQ_LOOP_H
#include <thread>
//#include "static_sched.cpp"

#include <functional>

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

static void testFunction(int x, int y, double& tls, std::function<void(int, double&)>f){

	//std::cout<< "We work ";

	for(x; x < y; x++){
        f(x, tls);
  	//std::cout<< "| tls = " << tls << " |";
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
//    std::cout<< "|have started the construct| ";
  //  std::cout<< "end and nThreads = " << end << " " << nThreads << " ";
    
    int start = beg;  
    int en = end;
 	  
	  
    int tlsToUse = 0;
    int count = 0;
    int iterations = (end)/nThreads;
    //std::cout << "|iterations = " << iterations << " |";
    int breakPoint = 1;

    TLS tls[nThreads];
    
    for(int x = 0; x < nThreads; x++){
    	  
	    tlsToUse = x;
      
      //before(tls[tlsToUse]);
     mythreads.push_back(std::thread(before, std::ref(tls[tlsToUse]))); 
     
     mythreads.push_back(std::thread(testFunction, start,end, std::ref(tls[tlsToUse]), f));
    



      count++;
      breakPoint++;
    }
    //mythreads.push_back(std::thread(after, std::ref(tls[tlsToUse])));     
    for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }
    mythreads.push_back(std::thread(after, std::ref(tls[tlsToUse])));
	  for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }

  }



};



#endif
