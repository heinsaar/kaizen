#pragma once

#include "../algorithms.h"
#include "../masis.h"
#include <cassert>

void test_vector() {
    mas::vector<int> v;
    mas::populate_random(v);
    mas::print(v);

    v.push_back(777);
    assert(v.contains(777));

    std::cout << "TEST PASS: mas::list<T>" << std::endl;
}

void test_list() {
    mas::list<int> x;
    mas::populate_random(x);
    mas::print(x);

    x.push_back(777);
    assert(x.contains(777));

    std::cout << "TEST PASS: mas::list<T>" << std::endl;
}