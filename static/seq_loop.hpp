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
 
 
 static void helperFunction(void(*f)(int, float&),int end, int start, float tls){

        for(start; start < end; start++){
        f(start, std::ref(tls));
        }

  
 }

static void testFunction(int x, float& tls, void (*func)(int, float&)){
	std::cout<< "We work ";
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
	       std::function<void(int, TLS&)> func,
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
    
    //std::cout<<"|Checkpoint 1, TLS has been made tls0 =  "<< tls[0] << " |";
    
    for(int x = 0; x < nThreads; x++){
    	  
	    tlsToUse = x;

	    //std::cout<<"| x and tlsToUse " << x << " " << tlsToUse << " |";
  	  //mythreads.push_back(std::thread(before, std::ref(tls[tlsToUse])));
      
      before(tls[tlsToUse]);
      //need to call herlper function which will help with running the integrations, local start/local end was discussed
      
     // mythreads.push_back(std::thread(helperFunction, f,en, start, tls[tlsToUse]));
     mythreads.push_back(std::thread(testFunction, start, std::ref(tls[tlsToUse]), func));

      //mythreads.push_back(std::thread(f, beg, std::ref(tls[tlsToUse])));
      //std::cout << "|Before thread checkpoint, TLS = " << tls[tlsToUse] << " | ";
      
  //for (size_t i=beg; i<=end; i+= increment) {}
 
  //std::cout << "|tls = "<< tls[tlsToUse] << " I = " << i << " |";
     
      //std::cout << "|tls = "<< tls[tlsToUse] << " I = " << i << " |";
	 
      count++;
      breakPoint++;
      /*     if(breakPoint == iterations){
        breakPoint = 0;
      //	std::cout <<"break at: " << iterations << " ";
      //    mythreads.push_back(std::move(myThread));
        break;

      }
      */
     // std::cout<<"| x and tlsToUse " << x << " " << tlsToUse << " |";
    }
     
    for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }
    mythreads.push_back(std::thread(after, std::ref(tls[tlsToUse])));
  }



};



#endif
