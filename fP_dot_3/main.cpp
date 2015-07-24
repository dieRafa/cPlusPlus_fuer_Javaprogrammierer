#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <future>
#include"fix_point_oo.hpp"

const unsigned int vectorSize = 65536;
std::mutex m; //you can use std::lock_guard if you want to be exception safe
std::vector<fix_point> vecResults;


void dot_product(std::vector<fix_point>::iterator vec1FirstELement, std::vector<fix_point>::iterator vec1LastElement, std::vector<fix_point>::iterator vec2FirstElement){
    //using default inner product http://www.cplusplus.com/reference/numeric/inner_product/
   fix_point dotProduct = std::inner_product(vec1FirstELement, vec1LastElement, vec2FirstElement, fix_point(0.f));
    //Threads know that the region is locked, by Memory Fencing
    m.lock();
     // add thread results to global threadResults vector
    vecResults.push_back(dotProduct);
    m.unlock();
}

fix_point dot_product_threads(std::vector<fix_point>& vec1, std::vector<fix_point>& vec2){
    //store number of cores in a variable
    const int cores = std::thread::hardware_concurrency();
    const int elemPerThread = vectorSize/ cores;
    std::vector<std::thread> threadKeeper;

    for (int i = 0; i < cores; ++i){
        //open one thread per core
        threadKeeper.push_back(std::thread(
                     dot_product,
                     vec1.begin() + elemPerThread * i,
                     vec1.begin() + elemPerThread * (i + 1),
                     vec2.begin() + elemPerThread * i
             ));
    }

    // join() ensures that one thread is waiting for the other to be done
    for(auto& thread :  threadKeeper) {
        thread.join();
    }

    // calculate the sum of the thread results
    return std::accumulate(vecResults.begin(), vecResults.end(), fix_point(0.f));


}
fix_point dotProductAsync(std::vector<fix_point>::iterator vec1FirstELement, std::vector<fix_point>::iterator vec1LastElement, std::vector<fix_point>::iterator vec2FirstElement) {
    // default inner product
    return std::inner_product(vec1FirstELement, vec1LastElement, vec2FirstElement, fix_point(0.f));
}


fix_point dot_product_async(std::vector<fix_point> vec1, std::vector<fix_point> vec2) {
    const int numFutures = 4;
    const int elemPerFuture = vectorSize / numFutures;

    std::vector<std::future<fix_point>> futures;

    for (int i = 0; i < numFutures; ++i){
        //open one thread per core
        futures.push_back(std::async(
                     dotProductAsync,
                     vec1.begin() + elemPerFuture * i,
                     vec1.begin() + elemPerFuture * (i + 1),
                     vec2.begin() + elemPerFuture * i
             ));
    }
    fix_point result(0.f);
    for (auto& future : futures)
        result += future.get();

    return result;

}

int main(){
std::vector<fix_point> vec1( 65536, fix_point(0.5f) );
std::vector<fix_point> vec2;

//befüllen der Vektoren (geht auch mit insert: vec1.insert(vector1.begin(), vectorSize, fix_point(0.5f));
for (int i=0; i<vectorSize;++i){
    vec2.push_back(fix_point(0.25f));
}


auto threadsT1 = std::chrono::high_resolution_clock::now();
fix_point resultThreads = dot_product_threads(vec1, vec2);
auto threadsT2 = std::chrono::high_resolution_clock::now();
auto threadsDuration = std::chrono::duration_cast<std::chrono::microseconds>(threadsT2 - threadsT1).count();
std::cout << "THREADED dot product = " << float(resultThreads) << " (" << threadsDuration << "ms)" << std::endl;

auto asyncT1 = std::chrono::high_resolution_clock::now();
fix_point resultAsync = dot_product_async(vec1, vec2);
auto asyncT2 = std::chrono::high_resolution_clock::now();
auto asyncDuration = std::chrono::duration_cast<std::chrono::microseconds>(asyncT2 - asyncT1).count();
std::cout << "ASYNC dot product = " << float(resultAsync) << " (" << asyncDuration << "ms)" << std::endl;

std::cout<<"End of main!"<<std::endl;
return 0;
}
