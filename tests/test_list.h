#pragma once

#include <cassert>
#include "../algorithms.h"
#include "../containers/list.h"

void sanitest_list()
{
    zen::list<int> x;
    zen::populate_random(x);

    x.push_back(777);
    assert(x.contains(777));

    std::cout << "TEST PASS: " << __func__ << "() CONTENT " << zen::to_string(x) << std::endl;
}