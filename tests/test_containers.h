#pragma once

#include "../algorithms.h"
#include "../masis.h"

void test_vector() {
    mas::vector<int> v;
    mas::populate_random(v);
    mas::print(v);
}