#pragma once

#include <memory>

#include "kaizen.h" // test using generated header: jump with the parachute you folded

struct A {
    int f() { return 77; }
};

void test_deref_single_pointer()
{
    BEGIN_SUBTEST;
    A a;
    A* p = &a;
    zen::deref(p).f();
    ZEN_EXPECT(zen::deref(p).f() == 77);
}

void test_deref_double_pointer()
{
    BEGIN_SUBTEST;
    A a;
    A** p = new A*;
    *p = &a;
    ZEN_EXPECT(zen::deref(p).f() == 77);
    delete p;
}

void test_deref_iterator_to_pointer()
{
    BEGIN_SUBTEST;
    std::vector<A*> v;
    A a;
    v.push_back(&a);
    auto it = v.begin();
    ZEN_EXPECT(zen::deref(it).f() == 77);
}

void test_deref_verydeep_pointer_layers()
{
    BEGIN_SUBTEST;
    int  _1 = 11;
    auto _2 = &_1;
    auto _3 = &_2;
    auto _4 = &_3;
    auto _5 = &_4;
    auto _6 = &_5;
    auto _7 = &_6; // and so on

    ZEN_EXPECT(
        zen::deref(_1) == 11 &&
        zen::deref(_2) == 11 &&
        zen::deref(_3) == 11 &&
        zen::deref(_4) == 11 &&
        zen::deref(_5) == 11 &&
        zen::deref(_6) == 11 &&
        zen::deref(_7) == 11
    );
}

void test_deref_multiple_pointer_layers()
{
    BEGIN_SUBTEST;
    A a;
    A*** p = new A**;
    *p = new A*;
    **p = &a;

    A    _1;
    auto _2 = &_1;
    auto _3 = &_2;
    auto _4 = &_3;
    auto _5 = &_4;
    auto _6 = &_5;
    auto _7 = &_6; // and so on

    ZEN_EXPECT(
        zen::deref(_1).f() == 77 &&
        zen::deref(_2).f() == 77 &&
        zen::deref(_3).f() == 77 &&
        zen::deref(_4).f() == 77 &&
        zen::deref(_5).f() == 77 &&
        zen::deref(_6).f() == 77 &&
        zen::deref(_7).f() == 77
    );

    ZEN_EXPECT(zen::deref(p).f() == 77);
    delete *p;
    delete  p;
}

void test_deref_std_smart_pointer()
{
    BEGIN_SUBTEST;
    std::unique_ptr<A> p1(new A());

    ZEN_EXPECT(zen::deref(p1).f() == 77);
}

void main_test_deref()
{
    BEGIN_TEST;

    test_deref_verydeep_pointer_layers();
    test_deref_multiple_pointer_layers();
    test_deref_iterator_to_pointer();
    test_deref_std_smart_pointer();
    test_deref_single_pointer();
    test_deref_double_pointer();
}