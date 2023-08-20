#pragma once

#include <cassert>
#include "../algorithms.h"
#include "../containers/vector.h"

void sanitest_vector() {
    zen::vector<int> v;
    zen::populate_random(v);
    zen::print(v);

    v.push_back(777);
    assert(v.contains(777));

    std::cout << "TEST PASS: zen::vector<T>" << std::endl;
}