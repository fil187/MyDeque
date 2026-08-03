#include <gtest/gtest.h>
#include "my_deque.hpp"

using TestedTypes = ::testing::Types<int, double, std::string>;

/**
 * @invariant `i_array_1` is of length `3`
 * @invariant `f_array_1` is of length `3`
 * @invariant `s_array_1` is of length `3`
 * @invariant `i_array_2` is of length `4`
 * @invariant `f_array_2` is of length `4`
 * @invariant `s_array_2` is of length `4`
 */
template <typename T>
class MyDequeTest : public ::testing::Test {
protected:
    static inline const int i_array_1[3] = {1, 2, 3};
    static inline const int i_array_2[4] = {4, 5, 6, 7};
    static inline const double f_array_1[3] = {1.1, 2.2, 3.3};
    static inline const double f_array_2[4] = {4.4, 5.5, 6.6, 7.7};
    static inline const std::string s_array_1[3] = {"hello", "world", "!"};
    static inline const std::string s_array_2[4] = {"hallo", "wereld", "?", "!"};

    size_t get_len_1() { return 3; }
    size_t get_len_2() { return 4; }
    
    /**
     * @return The array of the corresponding type.
     * 
     * @post The returned array has length `3`
     */
    T* get_arr_1() {
        if constexpr (std::is_same_v<T, int>) {
            return const_cast<int*>(i_array_1);
        } else if constexpr (std::is_same_v<T, double>) {
            return const_cast<double*>(f_array_1);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return const_cast<std::string*>(s_array_1);
        }
    } 

    /**
     * @return The array of the corresponding type.
     * @post The returned array has length `3`
     * 
     */
    T* get_arr_2() {
        if constexpr (std::is_same_v<T, int>) {
            return const_cast<int*>(i_array_2);
        } else if constexpr (std::is_same_v<T, double>) {
            return const_cast<double*>(f_array_2);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return const_cast<std::string*>(s_array_2);
        }
    }
};

TYPED_TEST_SUITE(MyDequeTest, TestedTypes);

TYPED_TEST(MyDequeTest, DefaultConstructor) {
    MyDeque<TypeParam> q;
    EXPECT_EQ(0, q.length());
}

TYPED_TEST(MyDequeTest, ConstructorWithCapacity) {
    MyDeque<TypeParam> q(10);
    EXPECT_EQ(0, q.length());
}

TYPED_TEST(MyDequeTest, ConstructorWithInvalidCpacity) {
    EXPECT_THROW(MyDeque<TypeParam>(0), std::invalid_argument);
}

TYPED_TEST(MyDequeTest, ConstructorFromArray) {
    MyDeque<TypeParam> q(this->get_arr_1(), this->get_len_1());
    EXPECT_EQ(this->get_len_1(), q.length());
}

TYPED_TEST(MyDequeTest, ConstructorFromEmptyArray) {
    TypeParam* array = new TypeParam[1];
    MyDeque<TypeParam> q(array, 0);
    EXPECT_EQ(0, q.length());
}

TYPED_TEST(MyDequeTest, ConstructorFromNullptrArray) {
    EXPECT_THROW(MyDeque<TypeParam>(nullptr, 0), std::invalid_argument);
}

TYPED_TEST(MyDequeTest, CopyConstructor) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    MyDeque<TypeParam> q2(q1);
    EXPECT_EQ(q1.length(), q2.length());
    for (size_t i = 0; i < q1.length(); i++)
        EXPECT_EQ(q1[i], q2[i]);
}

TYPED_TEST(MyDequeTest, CopyConstructorHeadNotNull) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    q1.push_front(this->get_arr_1()[1]);
    MyDeque<TypeParam> q2(q1);
    EXPECT_EQ(q1.length(), q2.length());
    for (size_t i = 0; i < q1.length(); i++)
        EXPECT_EQ(q1[i], q2[i]);
}

TYPED_TEST(MyDequeTest, CopyConstructorIndependent) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    MyDeque<TypeParam> q2(q1);
    EXPECT_EQ(q1.length(), q2.length());
    q1.pop_back();
    EXPECT_NE(q1.length(), q2.length());
    EXPECT_EQ(this->get_arr_1()[2], q2[2]);
}

TYPED_TEST(MyDequeTest, BasicPushBack) {
    MyDeque<TypeParam> q;
    q.push_back(this->get_arr_1()[0]);
    EXPECT_EQ(1, q.length());
    q.push_back(this->get_arr_1()[1]);
    EXPECT_EQ(2, q.length());
    EXPECT_EQ(this->get_arr_1()[0], q[0]);
    EXPECT_EQ(this->get_arr_1()[1], q[1]);
}

TYPED_TEST(MyDequeTest, BasicPushFront) {
    MyDeque<TypeParam> q;
    q.push_front(this->get_arr_1()[1]);
    EXPECT_EQ(1, q.length());
    q.push_front(this->get_arr_1()[0]);
    EXPECT_EQ(2, q.length());
    EXPECT_EQ(this->get_arr_1()[0], q[0]);
    EXPECT_EQ(this->get_arr_1()[1], q[1]);
}

TYPED_TEST(MyDequeTest, BasicPopBack) {
    MyDeque<TypeParam> q(this->get_arr_1(), this->get_len_1());
    EXPECT_EQ(this->get_arr_1()[2], q.pop_back());
    EXPECT_EQ(this->get_len_1() - 1, q.length());
    EXPECT_EQ(this->get_arr_1()[1], q.pop_back());
    EXPECT_EQ(this->get_len_1() - 2, q.length());
    EXPECT_EQ(this->get_arr_1()[0], q.pop_back());
    EXPECT_EQ(this->get_len_1() - 3, q.length());
}

TYPED_TEST(MyDequeTest, BasicPopFront) {
    MyDeque<TypeParam> q(this->get_arr_1(), this->get_len_1());
    EXPECT_EQ(this->get_arr_1()[0], q.pop_front());
    EXPECT_EQ(this->get_len_1() - 1, q.length());
    EXPECT_EQ(this->get_arr_1()[1], q.pop_front());
    EXPECT_EQ(this->get_len_1() - 2, q.length());
    EXPECT_EQ(this->get_arr_1()[2], q.pop_front());
    EXPECT_EQ(this->get_len_1() - 3, q.length());
}

TYPED_TEST(MyDequeTest, PopBackOnEmptyDeque) {
    MyDeque<TypeParam> q;
    EXPECT_THROW(q.pop_back(), std::out_of_range);
}

TYPED_TEST(MyDequeTest, PopFrontOnEmptyDeque) {
    MyDeque<TypeParam> q;
    EXPECT_THROW(q.pop_front(), std::out_of_range);
}

TYPED_TEST(MyDequeTest, MyDequeAssignment) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    MyDeque<TypeParam> q2;
    q2 = q1;
    EXPECT_EQ(q1.length(), q2.length());
    for (size_t i = 0; i < q1.length(); i++)
        EXPECT_EQ(q1[i], q2[i]);
}

TYPED_TEST(MyDequeTest, MyDequeAssignmentHead1NotNull) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    q1.push_front(this->get_arr_2()[2]);
    MyDeque<TypeParam> q2;
    q2 = q1;
    EXPECT_EQ(q1.length(), q2.length());
    for (size_t i = 0; i < q1.length(); i++)
        EXPECT_EQ(q1[i], q2[i]);
}

TYPED_TEST(MyDequeTest, MyDequeAssignmentHead2NotNull) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    MyDeque<TypeParam> q2;
    q2.push_front(this->get_arr_2()[2]);
    q2 = q1;
    EXPECT_EQ(q1.length(), q2.length());
    for (size_t i = 0; i < q1.length(); i++)
        EXPECT_EQ(q1[i], q2[i]);
}

TYPED_TEST(MyDequeTest, AssignmentHeadNotNull) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    q1.push_front(this->get_arr_1()[1]);
    MyDeque<TypeParam> q2;
    q2 = q1;
    EXPECT_EQ(q1.length(), q2.length());
    for (size_t i = 0; i < q1.length(); i++)
        EXPECT_EQ(q1[i], q2[i]);
}

TYPED_TEST(MyDequeTest, AssignmentIndependent) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    MyDeque<TypeParam> q2;
    q2 = q1;
    EXPECT_EQ(q1.length(), q2.length());
    q1.pop_back();
    EXPECT_NE(q1.length(), q2.length());
    EXPECT_EQ(this->get_arr_1()[2], q2[2]);
}

TYPED_TEST(MyDequeTest, SelfAssignment) {
    MyDeque<TypeParam> q1(this->get_arr_1(), this->get_len_1());
    q1 = q1;
    EXPECT_EQ(this->get_len_1(), q1.length());
    for (size_t i = 0; i < this->get_len_1(); i++)
        EXPECT_EQ(this->get_arr_1()[i], q1[i]);
}

TYPED_TEST(MyDequeTest, AtIndex) {
    MyDeque<TypeParam> q(this->get_arr_1(), this->get_len_1());
    for (size_t i = 0; i < q.length(); i++)
        EXPECT_EQ(this->get_arr_1()[i], q[i]);
}

TYPED_TEST(MyDequeTest, IndexOutOfBounds) {
    MyDeque<TypeParam> q(this->get_arr_1(), this->get_len_1());
    EXPECT_THROW(q[1000], std::out_of_range);
}


TYPED_TEST(MyDequeTest, IndexJustOutOfBounds) {
    MyDeque<TypeParam> q(this->get_arr_1(), this->get_len_1());
    EXPECT_THROW(q[this->get_len_1()], std::out_of_range);
}