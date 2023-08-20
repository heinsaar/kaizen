#pragma once

#include "../algorithms.h"
#include "../kaizen.h"
#include <cassert>

void test_list() {
    zen::list<int> x;
    zen::populate_random(x);
    zen::print(x);

    x.push_back(777);
    assert(x.contains(777));

    std::cout << "TEST PASS: mas::list<T>" << std::endl;
}