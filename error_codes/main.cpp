#include <iostream>
#include <stdexcept>
#include <boost/timer.hpp>

volatile int K = 1000000000l - 1;

void check_value(int x) {
    if (x == K)
        throw std::runtime_error("invalid value");
}

bool check_value_ret(int x) {
    return x == K;
}

int main()
{
    boost::timer tm;
    size_t value = 0u;
    try {
        while(true) {
            check_value(value);
            value++;
        }
    }
    catch(const std::runtime_error& err) {
        double secs = tm.elapsed();
        std::cout << value <<  ", With exception: " << secs << std::endl;
    }
    value = 0u;
    tm.restart();
    while(true) {
        if (check_value_ret(value))
            break;
        value++;
    }
    double secs = tm.elapsed();
    std::cout << value << ", Without exception: " << secs << std::endl;
    return 0;
}

