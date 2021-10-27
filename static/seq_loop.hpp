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
//    std::cout<< "|have started the construct| ";
  //  std::cout<< "end and nThreads = " << end << " " << nThreads << " ";
    int tlsToUse = 0;
    int count = 0;
    int iterations = (end)/nThreads;
    //std::cout << "|iterations = " << iterations << " |";
    int breakPoint = 1;
    TLS tls[nThreads];
    
    //std::cout<<"|Checkpoint 1, TLS has been made tls0 =  "<< tls[0] << " |";
    
    

    for(int x = 0; x < nThreads; x++){

    	    if(x == 0){
//	std::cout << "|first loop checkpoint| ";

	    }

	    tlsToUse = x;

	    //    std::cout<<"| x and tlsToUse " << x << " " << tlsToUse << " |";


  	mythreads.push_back(std::thread(before, std::ref(tls[tlsToUse])));
 for(std::thread &th: mythreads){
      if(th.joinable()){
      th.join();
      }
      }
	
	//std::thread join();
	     	
	//mythreads.push_back(std::thread(before, std::ref(tls[tlsToUse])));
	//std::thread th1(before, std::ref(tls[tlsToUse]));

	//th1.join();

  //	std::cout << "|Before thread checkpoint, TLS = " << tls[tlsToUse] << " | ";
      
      for (size_t i=beg; i<=end; i+= increment) {
 
 // std::cout << "|tls = "<< tls[tlsToUse] << " I = " << i << " |";
     
     
	

	      mythreads.push_back (std::thread(f, i, std::ref(tls[tlsToUse])));
 for(std::thread &th: mythreads){
      if(th.joinable()){
      th.join();
      }
      }

 std::cout << "|tls = "<< tls[tlsToUse] << " I = " << i << " |";
	 
      count++;
      breakPoint++;
/*     if(breakPoint == iterations){
        breakPoint = 0;
//	std::cout <<"break at: " << iterations << " ";
     //    mythreads.push_back(std::move(myThread));
        break;

      }
 */
    /* if(count > end / nThreads){
        count = 0;
        mythreads.push_back(std::move(myThread));

      }*/
      }
      
//	std::thread th3(after, std::ref(tls[tlsToUse]));
//	th3.join();

	/*for(int u = 0; u <nThreads; u++){
		std::thread tThread(after, std::ref(tls[tlsToUse]));
		 mythreads.push_back(std::move(tThread));

	}
*/
      mythreads.push_back(std::thread(after, std::ref(tls[tlsToUse])));
/*	 for(std::thread &th: mythreads){
      if(th.joinable()){
      th.join();
      }
      }
*/	
    //tlsToUse = x;
     // std::cout<<"| x and tlsToUse " << x << " " << tlsToUse << " |";
    }
    
  
    for(std::thread &t: mythreads){
      if(t.joinable()){
        t.join();
      }
    }
    
  }


};



#endif
