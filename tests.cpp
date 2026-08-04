#include <gtest/gtest.h>
#include "my_deque.hpp"

using TestedTypes = ::testing::Types<int, double, std::string>;

/**
 * @invariant All array numbered `1` have length `40`
 * @invariant All array numbered `2` have length `60`
 */
template <typename T>
class MyDequeTest : public ::testing::Test {

protected:
    
    static inline const int i_array_1[40] = {73, 12, 98, 45, 21, 67, 34, 89, 5, 56,18, 92, 41, 77, 29, 63, 10, 84, 37, 50,96, 14, 58, 25, 71, 3, 88, 46, 19, 65,32, 81, 7, 54, 99, 27, 60, 39, 16, 75};
    static inline const int i_array_2[60] = {42, 17, 89, 3, 56, 91, 24, 68, 12, 77, 35, 8, 94, 51, 26, 73, 14, 60, 99, 31, 47, 5, 82, 19, 66, 38, 11, 97, 53, 28, 75, 9, 44, 86, 21, 63, 16, 90, 34, 58, 7, 80, 25, 49, 93, 13, 70, 36, 54, 2, 88, 41, 65, 18, 79, 30, 95, 57, 22, 84};
    static inline const double f_array_1[40] = {14.72, 83.19, 27.56, 91.04, 35.88, 62.41, 7.93, 48.15, 76.82, 19.67, 54.39, 88.01, 23.74, 69.58, 12.46, 95.30, 41.87, 58.22, 3.91, 81.65, 29.14, 66.78, 17.53, 99.42, 45.26, 72.90, 8.34, 57.11, 31.69, 84.05, 20.48, 63.97, 10.25, 93.56, 38.71, 51.84, 25.09, 79.33, 6.18, 87.60};
    static inline const double f_array_2[60] = {12.48, 93.15, 47.62, 8.39, 55.71, 21.04, 76.88, 3.56, 64.29, 18.91, 82.47, 39.75, 7.14, 91.63, 28.50, 54.87, 11.22, 68.94, 35.16, 79.08, 24.61, 97.35, 42.83, 6.19, 58.44, 13.77, 85.92, 31.58, 72.40, 49.06, 16.33, 94.71, 26.89, 61.25, 38.47, 9.82, 87.14, 44.53, 70.68, 19.37, 53.91, 5.28, 80.46, 33.72, 96.18, 14.95, 66.81, 27.39, 74.56, 41.03, 89.67, 22.14, 57.88, 10.49, 63.27, 36.75, 98.04, 29.61, 51.92, 17.86};
    static inline const std::string s_array_1[40] = {"alpha", "bravo", "charlie", "delta", "echo", "foxtrot", "golf", "hotel", "india", "juliet", "kilo", "lima", "mike", "november", "oscar", "papa", "quebec", "romeo", "sierra", "tango", "uniform", "victor", "whiskey", "xray", "yankee", "zulu", "crimson", "emerald", "sapphire", "amber", "violet", "silver", "gold", "bronze", "copper", "onyx", "pearl", "ruby", "topaz", "jade"};
    static inline const std::string s_array_2[60] = {"apple", "banana", "cherry", "dragonfruit", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon", "mango", "nectarine", "orange", "papaya", "quince", "raspberry", "strawberry", "tangerine", "ugli", "vanilla", "watermelon", "xigua", "yam", "zucchini", "apricot", "blackberry", "coconut", "date", "eggplant", "feijoa", "guava", "hazelnut", "iceberg", "jackfruit", "kumquat", "lime", "mulberry", "nutmeg", "olive", "peach", "pear", "pineapple", "plum", "pomegranate", "radish", "spinach", "tomato", "turnip", "walnut", "yambean", "artichoke", "broccoli", "cabbage", "carrot", "celery", "cucumber", "garlic", "lettuce", "onion", "pepper"};

    size_t get_len_1() { return 40; }
    size_t get_len_2() { return 60; }
    
    /**
     * @return The array number `1` of the corresponding type.
     * 
     * @note The returned array has length `40`.
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
     * @return The array number `2` of the corresponding type.
     * 
     * @note The returned array has length `60`.
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
    size_t len = this->get_len_1();
    TypeParam* array = this->get_arr_1();
    MyDeque<TypeParam> q1(array, len);
    MyDeque<TypeParam> q2(q1);
    EXPECT_EQ(q1.length(), q2.length());
    q1.pop_back();
    EXPECT_NE(q1.length(), q2.length());
    for (size_t i = 0; i < q2.length(); i++)
        EXPECT_EQ(array[i], q2[i]);
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

TYPED_TEST(MyDequeTest, PushBackTriggersSingleResize) {
    MyDeque<TypeParam> q(10);
    TypeParam* array = this->get_arr_1();
    for (int i = 0; i <= 10; i++)
        q.push_back(array[i]);
    EXPECT_EQ(11, q.length());
    for (int i = 0; i <= 10; i++)
        EXPECT_EQ(array[i], q[(size_t)i]);
}

TYPED_TEST(MyDequeTest, PushBackTriggersMultipleResizes) {
    MyDeque<TypeParam> q(4);
    TypeParam* array = this->get_arr_1();
    // first trigger
    for (int i = 0; i <= 4; i++)
        q.push_back(array[i]);
    EXPECT_EQ(5, q.length());
    for (int i = 0; i <= 4; i++)
        EXPECT_EQ(array[i], q[(size_t)i]);
    // second trigger
    for (int i = 5; i <= 8; i++)
        q.push_back(array[i]);
    EXPECT_EQ(9, q.length());
    for (int i = 0; i <= 8; i++)
        EXPECT_EQ(array[i], q[(size_t)i]);
    // third resize
    for (int i = 9; i <= 16; i++)
        q.push_back(array[i]);
    EXPECT_EQ(17, q.length());
    for (int i = 0; i <= 16; i++)
        EXPECT_EQ(array[i], q[(size_t)i]);
}

TYPED_TEST(MyDequeTest, PushFrontTriggersSingleResize) {
    MyDeque<TypeParam> q(10);
    TypeParam* array = this->get_arr_1();
    for (int i = 10; i >= 0; i--)
        q.push_front(array[i]);
    EXPECT_EQ(11, q.length());
    for (int i = 0; i <= 10; i++)
        EXPECT_EQ(array[i], q[(size_t)i]);
}

TYPED_TEST(MyDequeTest, PushFrontTriggersMultipleResizes) {
    MyDeque<TypeParam> q(4);
    TypeParam* array = this->get_arr_1();
    // first trigger
    for (int i = 0; i <= 4; i++)
        q.push_front(array[i]);
    EXPECT_EQ(5, q.length());
    for (int i = 0; i <= 4; i++)
        EXPECT_EQ(array[q.length() - i - 1], q[(size_t)i]);
    // second trigger
    for (int i = 5; i <= 8; i++)
        q.push_front(array[i]);
    EXPECT_EQ(9, q.length());
    for (int i = 0; i <= 8; i++)
        EXPECT_EQ(array[q.length() - i - 1], q[(size_t)i]);
    // third resize
    for (int i = 9; i <= 16; i++)
        q.push_front(array[i]);
    EXPECT_EQ(17, q.length());
    for (int i = 0; i <= 16; i++)
        EXPECT_EQ(array[q.length() - i - 1], q[(size_t)i]);
}

TYPED_TEST(MyDequeTest, BasicPopBack) {
    TypeParam* array = this->get_arr_1();
    size_t len = this->get_len_1();
    MyDeque<TypeParam> q(array, len);
    EXPECT_EQ(array[len - 1], q.pop_back());
    EXPECT_EQ(len - 1, q.length());
    EXPECT_EQ(array[len - 2], q.pop_back());
    EXPECT_EQ(len - 2, q.length());
    EXPECT_EQ(array[len - 3], q.pop_back());
    EXPECT_EQ(len - 3, q.length());
}

TYPED_TEST(MyDequeTest, BasicPopFront) {
    TypeParam* array = this->get_arr_1();
    size_t len = this->get_len_1();
    MyDeque<TypeParam> q(array, len);
    EXPECT_EQ(array[0], q.pop_front());
    EXPECT_EQ(len - 1, q.length());
    EXPECT_EQ(array[1], q.pop_front());
    EXPECT_EQ(len - 2, q.length());
    EXPECT_EQ(array[2], q.pop_front());
    EXPECT_EQ(len - 3, q.length());
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
    size_t len = this->get_len_1();
    TypeParam* array = this->get_arr_1();
    MyDeque<TypeParam> q1(array, len);
    MyDeque<TypeParam> q2;
    q2 = q1;
    EXPECT_EQ(q1.length(), q2.length());
    q1.pop_back();
    EXPECT_NE(q1.length(), q2.length());
    for (size_t i = 0; i < q2.length(); i++)
        EXPECT_EQ(array[i], q2[i]);
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

TYPED_TEST(MyDequeTest, BasicSort) {
    MyDeque<TypeParam> q(this->get_arr_2(), this->get_len_2());
    q.sort();
    EXPECT_EQ(this->get_len_2(), q.length());
    for (size_t i = 1; i < q.length(); i++)
        EXPECT_LE(q[i - 1], q[i]); 
}

TYPED_TEST(MyDequeTest, SortHeadNotNull) {
    MyDeque<TypeParam> q(this->get_arr_2(), this->get_len_2());
    for (size_t i = 0; i < this->get_len_1(); i++)
        q.push_front(this->get_arr_1()[i]);
    q.sort();
    EXPECT_EQ(this->get_len_2() + this->get_len_1(), q.length());
    for (size_t i = 1; i < q.length(); i++)
        EXPECT_LE(q[i - 1], q[i]); 
}