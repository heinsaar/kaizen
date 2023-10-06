#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_stack_of_strings()
{
    BEGIN_SUBTEST;
    zen::deque<zen::string> d = { "1", "2", "3", "4" };
    zen::stack<zen::string> x(d); // stack is not directly contructible from an initializer list
    x.push("0");

    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_stack_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::deque<zen::string> d = { "1", "2", "3", "4" };
    zen::stack<zen::string> v{ d };

    std::stack sv{ v };
    zen::stack zv{ sv };

    ZEN_EXPECT(sv == zv);
}

void main_test_stack()
{
    BEGIN_TEST;

    zen::stack<int> x;
    x.push(1);
    x.push(2);
    x.push(3);

    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_stack_zen_std_interchangeability();
    test_stack_of_strings();
}