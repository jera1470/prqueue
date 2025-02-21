#include "../prqueue.h"
//#include "prqueue.h"
#include <iostream>
#include <string>
#include <ostream>
#include <map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;


// Constructor
TEST(prqueue, constructor) {
    prqueue<int> pq;
    EXPECT_EQ(pq.getRoot(), nullptr);
    EXPECT_EQ(pq.size(), 0);
}

// Clear
TEST(prqueue, clear) {
    prqueue<int> pq1;
    pq1.enqueue(1, 1);
    pq1.enqueue(2, 2);
    pq1.enqueue(3, 3);
    EXPECT_EQ(pq1.size(), 3);
    pq1.clear();
    EXPECT_EQ(pq1.size(), 0);
    EXPECT_EQ(pq1.getRoot(), nullptr);
}

// Enqueue
TEST(prqueue, enqueue) {
    prqueue<int> pq1;
    pq1.enqueue(15, 2);
    pq1.enqueue(16, 2);
    pq1.enqueue(17, 3);
    pq1.enqueue(6, 2);
    pq1.enqueue(7, 1);
    pq1.enqueue(8, 1);
    pq1.enqueue(9, 2);
    pq1.enqueue(2, 3);
    pq1.enqueue(1, 3);

    EXPECT_EQ(pq1.size(), 9);
    EXPECT_EQ(pq1.peek(), 7);
}

// Peek
TEST(prqueue, peek) {
    prqueue<int> pq1;
    pq1.enqueue(2, 2);
    pq1.enqueue(3, 3);
    EXPECT_EQ(pq1.peek(), 2);
    pq1.enqueue(1, 1);
    EXPECT_EQ(pq1.peek(), 1);
}

// Dequeue
TEST(prqueue, dequeue) {
    prqueue<int> pq1;
    pq1.enqueue(1, 0);
    pq1.enqueue(2, -3);
    pq1.enqueue(3, -4);
    pq1.enqueue(4, -2);
    pq1.enqueue(5, -1);
    pq1.enqueue(6, 3);
    pq1.enqueue(7, 0);
    pq1.enqueue(8, -3);
    pq1.enqueue(9, -4);
    pq1.enqueue(10, -2);
    pq1.enqueue(11, -1);
    pq1.enqueue(12, 3);
    pq1.enqueue(13, 0);
    pq1.enqueue(14, -3);
    pq1.enqueue(15, -4);
    pq1.enqueue(16, -2);
    pq1.enqueue(17, -1);
    pq1.enqueue(18, 3);

    EXPECT_EQ(pq1.size(), 18);
    pq1.dequeue();
    pq1.dequeue();
}

// Copy constructor
TEST(prqueue, copy_constructor) {
    prqueue<int> pq1;
    pq1.enqueue(1, 0);
    pq1.enqueue(2, -3);
    pq1.enqueue(3, -4);
    pq1.enqueue(4, -2);
    pq1.enqueue(5, -1);
    pq1.enqueue(6, 3);
    pq1.enqueue(7, 0);
    pq1.enqueue(8, -3);
    pq1.enqueue(9, -4);
    pq1.enqueue(10, -2);
    pq1.enqueue(11, -1);
    pq1.enqueue(12, 3);
    pq1.enqueue(13, 0);
    pq1.enqueue(14, -3);
    pq1.enqueue(15, -4);
    pq1.enqueue(16, -2);
    pq1.enqueue(17, -1);
    pq1.enqueue(18, 3);

    prqueue<int> pq2(pq1);
    EXPECT_EQ(pq2.size(), 18);
    EXPECT_EQ(pq2.peek(), 3);
}

// operator=
TEST(prqueue, operator_equal) {
    prqueue<int> pq1;
    pq1.enqueue(1, 0);
    pq1.enqueue(2, -3);
    pq1.enqueue(3, -4);
    pq1.enqueue(4, -2);
    pq1.enqueue(5, -1);
    pq1.enqueue(6, 3);
    pq1.enqueue(7, 0);
    pq1.enqueue(8, -3);
    pq1.enqueue(9, -4);
    pq1.enqueue(10, -2);
    pq1.enqueue(11, -1);
    pq1.enqueue(12, 3);
    pq1.enqueue(13, 0);
    pq1.enqueue(14, -3);
    pq1.enqueue(15, -4);
    pq1.enqueue(16, -2);
    pq1.enqueue(17, -1);
    pq1.enqueue(18, 3);

    prqueue<int> pq2;
    pq2 = pq1;
    EXPECT_EQ(pq2.size(), 18);
    EXPECT_EQ(pq2.peek(), 3);
}

// operator== (returns true if the two prqueues are completely the same)
TEST(prqueue, operator_equal2) {
    prqueue<int> pq1;
    prqueue<int> pq2;
    EXPECT_EQ(pq1 == pq2, true);
    pq1.enqueue(1, 0);
    EXPECT_EQ(pq1 == pq2, false);
    pq2.enqueue(1, 0);
    EXPECT_EQ(pq1 == pq2, true);
    pq1.enqueue(2, -3);
    pq1.enqueue(3, -4);
    pq1.enqueue(4, -2);
    pq1.enqueue(5, -1);
    pq1.enqueue(6, 3);
    pq1.enqueue(7, 0);
    pq1.enqueue(8, -3);
    pq1.enqueue(9, -4);
    pq1.enqueue(10, -2);
    pq1.enqueue(11, -1);
    pq1.enqueue(12, 3);
    pq1.enqueue(13, 0);
    pq1.enqueue(14, -3);
    pq1.enqueue(15, -4);
    pq1.enqueue(16, -2);
    pq1.enqueue(17, -1);
    pq1.enqueue(18, 3);
    EXPECT_EQ(pq1 == pq2, false);
    pq2.enqueue(2, -3);
    pq2.enqueue(3, -4);
    pq2.enqueue(4, -2);
    pq2.enqueue(5, -1);
    pq2.enqueue(6, 3);
    pq2.enqueue(7, 0);
    pq2.enqueue(8, -3);
    pq2.enqueue(9, -4);
    pq2.enqueue(10, -2);
    pq2.enqueue(11, -1);
    pq2.enqueue(12, 3);
    pq2.enqueue(13, 0);
    pq2.enqueue(14, -3);
    pq2.enqueue(15, -4);
    pq2.enqueue(16, -2);
    pq2.enqueue(17, -1);
    pq2.enqueue(18, 3);
    EXPECT_EQ(pq1 == pq2, true);
    pq2.enqueue(19, 4);
    EXPECT_EQ(pq1 == pq2, false);
}

// begin and next
TEST(prqueue, next) {
    prqueue<int> pq1;
    pq1.begin();
    int value = pq1.peek();
    int priority = 0;
    EXPECT_EQ(value, 0);
    EXPECT_EQ(pq1.next(value, priority), false);

    pq1.enqueue(1, 0);
    pq1.enqueue(2, -3);
    pq1.enqueue(3, -4);
    pq1.enqueue(4, -2);
    pq1.enqueue(5, -1);
    pq1.enqueue(6, 3);
    pq1.enqueue(7, 0);
    pq1.enqueue(8, -3);
    pq1.enqueue(9, -4);
    pq1.enqueue(10, -2);
    pq1.enqueue(11, -1);
    pq1.enqueue(12, 3);
    pq1.enqueue(13, 0);
    pq1.enqueue(14, -3);
    pq1.enqueue(15, -4);
    pq1.enqueue(16, -2);
    pq1.enqueue(17, -1);
    pq1.enqueue(18, 3);
    EXPECT_EQ(pq1.peek(), 3);
    ASSERT_EQ(pq1.size(), 18);

    pq1.begin();
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(priority, -4);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 9);
    EXPECT_EQ(priority, -4);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 15);
    EXPECT_EQ(priority, -4);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 2);
    EXPECT_EQ(priority, -3);

    pq1.clear();
    pq1.enqueue(4, 4);
    pq1.enqueue(1, 1);
    pq1.enqueue(3, 3);
    pq1.enqueue(2, 2);
    pq1.enqueue(5, 5);
    EXPECT_EQ(pq1.peek(), 1);
    ASSERT_EQ(pq1.size(), 5);

    pq1.begin();
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(priority, 1);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 2);
    EXPECT_EQ(priority, 2);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(priority, 3);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 4);
    EXPECT_EQ(priority, 4);
    EXPECT_EQ(pq1.next(value, priority), true);
    EXPECT_EQ(value, 5);
    EXPECT_EQ(priority, 5);
    EXPECT_EQ(pq1.next(value, priority), false);
}