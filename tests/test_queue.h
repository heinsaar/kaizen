#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_queue_of_strings()
{
    BEGIN_SUBTEST;
    zen::deque<zen::string> d = { "1", "2", "3", "4" };
    zen::queue<zen::string> x(d); // queue is not directly contructible from an initializer list
    x.push("0");

    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void main_test_queue()
{
    BEGIN_TEST;

    zen::queue<int> x;
    x.push(1);
    x.push(2);
    x.push(3);

    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_queue_of_strings();
}