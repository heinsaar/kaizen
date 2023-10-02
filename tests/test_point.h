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

    std::map<double, double> md = { {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0} };
    const zen::point p = *md.begin();
    md.insert(zen::point(4, 4));
    ZEN_EXPECT(p.x() == 1.0 && p.y() == 1.0);
    ZEN_EXPECT(md.size() == 4 && md[4.0] == 4.0);
}

void test_point_std_vector_of_pairs()
{
    BEGIN_SUBTEST;
    std::vector<std::pair<double, double>> v = { {1.0, 2.0}, {3.0, 4.0} };
    zen::points v2(v.begin(), v.end()); // copy construct from std::pair vector

    ZEN_EXPECT(
        v2[0].x() == 1.0 &&
        v2[0].y() == 2.0 &&
        v2[1].x() == 3.0 &&
        v2[1].y() == 4.0
    );
}

void test_point_std_algorithms()
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

void test_point_arithmetic()
{
    BEGIN_SUBTEST;

    zen::points2d v2d = { {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0} };
    zen::points3d v3d = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };

    // Addition
    zen::point2d sum2d = v2d[0] + v2d[1];
    zen::point3d sum3d = v3d[0] + v3d[1];

    ZEN_EXPECT(sum2d.x() == 4.0 && sum2d.y() == 6.0);
    ZEN_EXPECT(sum3d.x() == 5.0 && sum3d.y() == 7.0 && sum3d.z() == 9.0);

    // Subtraction
    zen::point2d diff2d = v2d[2] - v2d[0];
    zen::point3d diff3d = v3d[2] - v3d[0];

    ZEN_EXPECT(diff2d.x() == 4.0 && diff2d.y() == 4.0);
    ZEN_EXPECT(diff3d.x() == 6.0 && diff3d.y() == 6.0 && diff3d.z() == 6.0);

    // Multiplication
    zen::point2d prod2d = v2d[0] * 2.0;
    zen::point3d prod3d = v3d[0] * 2.0;

    ZEN_EXPECT(prod2d.x() == 2.0 && prod2d.y() == 4.0);
    ZEN_EXPECT(prod3d.x() == 2.0 && prod3d.y() == 4.0 && prod3d.z() == 6.0);

    // Division
    zen::point2d div2d = v2d[2] / 2.0;
    zen::point3d div3d = v3d[2] / 2.0;

    ZEN_EXPECT(div2d.x() == 2.5 && div2d.y() == 3.0);
    ZEN_EXPECT(div3d.x() == 3.5 && div3d.y() == 4.0 && div3d.z() == 4.5);

    // Equality and inequality
    ZEN_EXPECT(v2d[0] == zen::point2d(1.0, 2.0));
    ZEN_EXPECT(v2d[1] != zen::point2d(1.0, 2.0));

    ZEN_EXPECT(v3d[0] == zen::point3d(1.0, 2.0, 3.0));
    ZEN_EXPECT(v3d[1] != zen::point3d(1.0, 2.0, 3.0));
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

    zen::point a;
    a.x() = p2.x();
    a.y() = p2.y();

    ZEN_EXPECT(
        a.x() == p2.x() &&
        a.y() == p2.y()
    );

    std::tuple<int, float, double> tup = { 1, 2.0f, 3.0 };
    zen::point3d p3d(tup);
    ZEN_EXPECT(
        p3d.x() == 1 &&
        p3d.y() == 2 &&
        p3d.z() == 3
    );

    zen::point3d a3d{ 5, 5, 5 };
    a3d.x() = p3d.x();
    a3d.y() = p3d.y();
    a3d.z() = p3d.z();

    ZEN_EXPECT(
        a3d.x() == p3d.x() &&
        a3d.y() == p3d.y() &&
        a3d.z() == p3d.z()
    );

    test_point_std_map_interoperability();
    test_point_std_vector_of_pairs();
    test_point_copy_assignment();
    test_point_arithmetic();
    test_point_std_algorithms();
}