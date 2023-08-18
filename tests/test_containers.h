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
}