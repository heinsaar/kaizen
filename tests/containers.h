#pragma once

#include "../masis.h"

void test_vector() {
    mas::vector<int> v;
    v.populate_random(20);
    v.print();
}