#include <iostream>
#include <boost/timer.hpp>
#include <vector>

using namespace std;

// generic function template
template<int P>
int pow(int val) {
    int res = 1;
    for (int i = 0; i < P; i++) {
        res *= val;
    }
    return res;
}

// 'fast' specializations
template<>
int pow<1>(int val) { return val; }
template<>
int pow<2>(int val) { return val*val; }
template<>
int pow<3>(int val) { return val*val*val; }
template<>
int pow<4>(int val) { return val*val*val*val; }

// old-fashioned implementation
int old_pow(int val, int P) {
    int res = 1;
    for (int i = 0; i < P; i++) {
        res *= val;
    }
    return res;
}

std::vector<int> generate_large_vector() {
    const size_t S = 100000000;
    std::vector<int> v;
    v.resize(S+1);
    v.at(S) = 1;
    int tmp = 0;
    for (auto& x: v) {
        x = tmp++;
    }
    return v;
}

int main()
{
    boost::timer tm;
    std::vector<int> v1 = generate_large_vector();
    {
        int res = 0;
        tm.restart();
        for (auto x: v1) {
            res ^= pow<4>(x);
        }
        cout << tm.elapsed() << "s " << res << endl;
    }
    std::vector<int> v2 = generate_large_vector();
    {
        int res = 0;
        tm.restart();
        const int POW = 4;
        for (auto x: v2) {
            res ^= old_pow(x, POW);
        }
        cout << tm.elapsed() << "s " << res << endl;
    }
    return 0;
}

