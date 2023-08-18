#pragma once

#include "../algorithms.h"
#include "../masis.h"

void test_vector() {
    mas::vector<int> v;
    v.populate_random(20);
    mas::print(v);
}