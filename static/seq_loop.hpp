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
  /// @brief execute the function f multiple times with different
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
    int tlsToUse = 0;
    int count = 0;
    int iterations = (end)/nThreads;
    int breakPoint = 0;
    //each thread owns a tls so thread 0 has tls 0, iterate that thread its amount of times then
    //move to next thread at the end add them together
    TLS tls[nThreads];
    //std::thread myThread(before, std::ref(tls[tlsToUse]));
    //before(tls[tlsToUse]);   
    for(int x = 0; x < nThreads; x++){
      std::thread myThread(before, std::ref(tls[tlsToUse]));
      //leftover iteration case
      if (x == nThreads - 1){
        iterations == end;
      }
      //mythreads.push_back(std::thread(f(i,tls));
    //iterations = (n - count)/nThreads;
      for (size_t i=count; i<end; i+= increment) {
      //f(i,tls);
      //std::thread myThread(helperAddToArray, tls, results, i);
      //std::thread myThread(inte)
      
      //std::thread mythread(f(i, tls));
      std::thread myThread(f, i, std::ref(tls[tlsToUse]));
      count++;
      breakPoint++;
      if(breakPoint + 1 == iterations){
        breakPoint = 0;
        // mythreads.push_back(std::move(myThread));
        break;

      }
     /* if(count > end / nThreads){
        count = 0;
        mythreads.push_back(std::move(myThread));

      }*/
      }
      std::thread(after, std::ref(tls[tlsToUse]));
      mythreads.push_back(std::move(myThread));
      tlsToUse++;
    }
    
    for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }
  // std::thread myThread(after, std::ref(tls[tlsToUse]));
    //mythreads.push_back(std::move(myThread));
   //after(tls[tlsToUse]);
  }


};



#endif
