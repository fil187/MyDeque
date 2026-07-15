#include "my_deque.hpp"
#include <assert.h>
#include <iostream>

void testConstructores() {
    MyDeque<int> q1;
    MyDeque<int> q2(200);
    int array[3] = {1, 2, 3};
    MyDeque<int> q3(array, 3);
    MyDeque<int> q4 = q3;

    assert(q1.length() == 0);
    assert(q2.length() == 0);
    assert(q3.length() == 3);
    assert(q4.length() == 3);
}

void testPushBack() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_back(i);
    for (int i = 0; i <= 200; i++)
        assert(q[i] == i);
}

void testPushFront() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_front(i);
    for (int i = 0; i <= 200; i++)
        assert(q[i] == 200 - i);
}

void testPushBackPopBack() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_back(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_back() == 200 - i);
}

void testPushBackPopFront() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_back(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_front() == i);
}

void testPushFrontPopBack() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_front(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_back() == i);
}

void testPushFrontPopFront() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_front(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_front() == 200 - i);
}

void testSort() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++) {
        q.push_front(i);
        q.push_back(i);
    }

    q.sort();
    for (size_t i = 1; i < q.length(); i++)
        assert(q[i - 1] <= q[i]);
}

int main() {
    testConstructores();
    testPushBack();
    testPushFront();
    testPushBackPopBack();
    testPushBackPopFront();
    testPushFrontPopBack();
    testPushFrontPopFront();
    testSort();
    std::cout << "all tests passed!";
    return 0;
}