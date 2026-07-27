#include "my_deque.hpp"
#include <assert.h>
#include <iostream>

void testDefaultConstructores() {
    MyDeque<int> q1;
    assert(q1.length() == 0);
    std::cout << "default constructor test passed!\n";
}

void testConstructorWithCapacity() {
    MyDeque<int> q(200);
    assert(q.length() == 0);
    std::cout << "constructor with capacity test passed!\n";
}

void testConstructorFromArray() {
    int array[3] = {1, 2, 3};
    MyDeque<int> q(array, 3);
    assert(q.length() == 3);
    for (size_t i = 0; i < 3; i++)
        assert(q[i] == (int)i + 1);
    std::cout << "constructor from array test passed!\n";
}

void testCopyConstructor() {
    int array[3] = {1, 2, 3};
    MyDeque<int> q1(array, 3);
    assert(q1.length() == 3);
    MyDeque<int> q2 = q1;
    assert(q2.length() == 3);
    
    for (size_t i = 0; i < 3; i++)
        assert(q1[i] == q2[i]);
    std::cout << "copy constructor test passed!\n";
}

void testPushBack() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_back(i);
    for (int i = 0; i <= 200; i++)
        assert(q[i] == i);
    std::cout << "push back test passed!\n";
}

void testPushFront() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_front(i);
    for (int i = 0; i <= 200; i++)
        assert(q[i] == 200 - i);
    std::cout << "push front test passed!\n";
}

void testPushBackPopBack() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_back(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_back() == 200 - i);
    std::cout << "push back pop back test passed!\n";
}

void testPushBackPopFront() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_back(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_front() == i);
    std::cout << "push back pop front test passed!\n";
}

void testPushFrontPopBack() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_front(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_back() == i);
    std::cout << "push front pop back test passed!\n";
}

void testPushFrontPopFront() {
    MyDeque<int> q;
    for (int i = 0; i <= 200; i++)
        q.push_front(i);
    for (int i = 0; i <= 200; i++)
        assert(q.pop_front() == 200 - i);
    std::cout << "push front pop front test passed!\n";
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
    std::cout << "sort test passed!\n";
}

int main() {
    testDefaultConstructores();
    testConstructorWithCapacity();
    testConstructorFromArray();
    testCopyConstructor();
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