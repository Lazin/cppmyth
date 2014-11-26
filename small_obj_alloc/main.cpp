#include <iostream>
#include <vector>
#include <boost/pool/pool.hpp>
#include <boost/timer.hpp>
#include <jemalloc/jemalloc.h>

using namespace std;

const size_t COUNT = 1000000;
const size_t SMALL_OBJ_SIZE = sizeof(int);

struct Benchmark {
    std::vector<int*> data;

    // Initialize vector using malloc and then free resources
    void use_malloc() {
        double alloc_time, free_time;
        boost::timer tm;
        for (size_t i = COUNT; i --> 0;) {
            data.push_back((int*)malloc(SMALL_OBJ_SIZE));
        }
        alloc_time = tm.elapsed();
        malloc_stats_print(NULL, NULL, NULL);
        tm.restart();
        for (size_t i = COUNT; i --> 0;) {
            free(data[i]);
        }
        free_time = tm.elapsed();
        std::cout << "total: " << (free_time + alloc_time) << std::endl;
        std::cout << "allocation: " << alloc_time << std::endl;
        std::cout << "deallocation: " << free_time << std::endl;
        std::vector<int*> tmp;
        std::swap(data, tmp);
    }

    // Initialize vector using memory pool
    void use_pool() {
        double alloc_time, free_time;
        boost::timer tm;
        boost::pool<> pool(SMALL_OBJ_SIZE);
        for (size_t i = COUNT; i --> 0;) {
            data.push_back((int*)pool.malloc());
        }
        alloc_time = tm.elapsed();
        malloc_stats_print(NULL, NULL, NULL);
        tm.restart();
        pool.purge_memory();
        free_time = tm.elapsed();
        std::cout << "total: " << (free_time + alloc_time) << std::endl;
        std::cout << "allocation: " << alloc_time << std::endl;
        std::cout << "deallocation: " << free_time << std::endl;
        std::vector<int*> tmp;
        std::swap(data, tmp);
    }
};

int main()
{
    Benchmark b;
    b.use_pool();
    b.use_malloc();
    return 0;
}

