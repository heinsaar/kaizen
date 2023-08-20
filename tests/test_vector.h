#pragma once

#include "../algorithms.h"
#include "../kaizen.h"
#include <cassert>

void test_vector() {
    zen::vector<int> v;
    zen::populate_random(v);
    zen::print(v);

    v.push_back(777);
    assert(v.contains(777));

    std::cout << "TEST PASS: mas::list<T>" << std::endl;
}