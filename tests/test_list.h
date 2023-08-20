#pragma once

#include <cassert>
#include "../algorithms.h"
#include "../containers/list.h"

void sanitest_list() {
    zen::list<int> x;
    zen::populate_random(x);
    zen::print(x);

    x.push_back(777);
    assert(x.contains(777));

    std::cout << "TEST PASS: zen::list<T>" << __func__ << std::endl;
}