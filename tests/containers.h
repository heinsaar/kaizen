// ...

#include "../masis.h"

void test_vector() {
    mas::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    std::cout << v.front();
}