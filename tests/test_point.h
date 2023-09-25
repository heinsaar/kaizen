#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_point_copy_assignment()
{
    BEGIN_SUBTEST;
    std::pair<double, double> p1 = { 1.0, 2.0 };
    zen::point2d p2;
    p2 = p1; // test copy assignment
    ZEN_EXPECT(
        p2.x() == 1.0 &&
        p2.y() == 2.0
    );
}

void test_point_std_map_interoperability()
{
    BEGIN_SUBTEST;
    std::map<zen::point2d, int> mp;
    mp.insert({ {1.0, 2.0}, 3 });
    mp[{4.0, 5.0}] = 6;
    ZEN_EXPECT(mp.find({ 1.0, 2.0 }) != mp.end());

    // std::map functions using std::pair

    // Test insert
    auto r1 = mp.insert({ {7.0, 8.0}, 9 });
    ZEN_EXPECT(
        r1.first->first.x() == 7.0 &&
        r1.first->first.y() == 8.0 &&
        r1.second == true
    );

    // Test emplace
    auto r2 = mp.emplace(zen::point2d(10.0, 11.0), 12);
    ZEN_EXPECT(
        r2.first->first.x() == 10.0 &&
        r2.first->first.y() == 11.0 &&
        r2.second == true
    );

    // Test equal_range
    mp[{2.0, 3.0}] = 4;
    mp[{3.0, 4.0}] = 5;
    auto r3 = mp.equal_range(zen::point2d(2.0, 3.0));
    ZEN_EXPECT(
        r3.first->first.x()  == 2.0 &&
        r3.first->first.y()  == 3.0 &&
        r3.second->first.x() == 3.0 &&
        r3.second->first.y() == 4.0
    );
}

void test_point_std_vector_of_pairs()
{
    BEGIN_SUBTEST;
    std::vector<std::pair<double, double>> v1 = { {1.0, 2.0}, {3.0, 4.0} };
    zen::points v2(v1.begin(), v1.end()); // copy construct from std::pair vector

    ZEN_EXPECT(
        v2[0].x() == 1.0 &&
        v2[0].y() == 2.0 &&
        v2[1].x() == 3.0 &&
        v2[1].y() == 4.0
    );
}

void test_std_algorithms()
{
    BEGIN_SUBTEST;
    zen::points v = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
    std::sort(v.begin(), v.end()); // sort using pair's comparison

    ZEN_EXPECT(
        v[0].x() == 1.0 &&
        v[0].y() == 2.0 &&
        v[2].x() == 5.0 &&
        v[2].y() == 6.0
    );
}

void test_point_stdpair_interchangability()
{
    test_point_std_map_interoperability();
    test_point_std_vector_of_pairs();
    test_point_copy_assignment();
    test_std_algorithms();
}

void main_test_point()
{
    BEGIN_TEST;

    zen::point   p2(1.0, 2.0);
    zen::point3d p3(1.0, 2.0, 3.0);

    zen::point3d q3 = p2;

    ZEN_EXPECT(
        p2.x() == p3.x() &&
        p2.y() == q3.y()
    );

    test_point_stdpair_interchangability();
}