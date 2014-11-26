#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

struct IFwdIter {
    virtual bool hasvalue() const = 0;
    virtual long next() = 0;
};

struct Foo {
    long acc;
    Foo() : acc(0) {}

    template<class FwdIter>
    void count(FwdIter begin, FwdIter end) {
        for (FwdIter it = begin; it != end; it++) {
            acc += *it;
        }
    }
};

struct Bar {
    long acc;
    Bar() : acc(0) {}

    void count(IFwdIter *iter) {
        while(iter->hasvalue()) {
            acc += iter->next();
        }
    }
};

std::vector<long> generate_large_vector() {
    const size_t S = 100000000;
    std::vector<long> v;
    v.resize(S+1);
    v.at(S) = 1;
    return v;
}

template<class Container>
struct Iter : IFwdIter {
    typename Container::const_iterator begin;
    typename Container::const_iterator end;

    Iter(Container const& c) : begin(c.begin()), end(c.end()) {}
    bool hasvalue() const {
        return begin < end;
    }
    long next() {
        return *begin++;
    }
};

template<class Cont>
Iter<Cont> make_iter(Cont const& c) {
    return Iter<Cont>(c);
}

int main()
{
    std::vector<long> v1 = generate_large_vector();
    Foo foo;
    boost::timer tm;
    {
        tm.restart();
        foo.count(v1.begin(), v1.end());
        double t = tm.elapsed();
        std::cout << "Templated count - " << t << "s, val - " << foo.acc << std::endl;
    }

    std::vector<long> v2 = generate_large_vector();
    Bar bar;
    {
        auto fwdit = make_iter(v2);
        tm.restart();
        bar.count(&fwdit);
        double t = tm.elapsed();
        std::cout << "Virtual count - " << t << "s, val - " << bar.acc << std::endl;
    }
    return 0;
}

