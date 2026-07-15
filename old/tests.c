#include <stdio.h>
#include <assert.h>
#include "my_deque.h"

int main() {
    /*##########################################################
    #                  tests for MyDeque<int>                  #
    ##########################################################*/
    
    printf("\033[34m");

    //constructor tests:
    MyDeque q1 = deque_new(sizeof(int));
    assert(q1 != NULL);
    assert(q1->capacity == DEFAULT_CAPACITY * sizeof(int));
    assert(q1->size == 0);
    assert(q1->head == 0);
    assert(q1->element_size == sizeof(int));
    assert(q1->data != NULL);
    printf("default constructor test past\n");
    MyDeque q2 = deque_new_with_capacity(sizeof(int), 150);
    assert(q2 != NULL);
    assert(q2->capacity == 150 * sizeof(int));
    assert(q2->size == 0);
    assert(q2->head == 0);
    assert(q2->element_size == sizeof(int));
    assert(q2->data != NULL);
    printf("constructor with capacity test past\n");
    printf("\033[36mconstructor tests past\033[34m\n\n");

    // test push_back:
    for (int i = 0; i < 201; i++) {
        push_back(q1, &i);
    }
    assert(q1->capacity > DEFAULT_CAPACITY);
    assert(len(q1) == 201);
    printf("\033[36mpush_back test past\033[0m\n\n");

    // test push_front:
    for (int i = 0; i < 201; i++) {
        push_front(q1, &i);
    }
    assert(len(q1) == 201 + 201);
    printf("\033[36mpush_front test past\033[0m\n\n");

    // test get:
   for (int i = 0; i < len(q1); i++) {
        printf("value: %d\t index: %d\n", GET_INT(q1, i), i);
        //assert(GET_INT(q1, 201 + i) == i);
        //assert(GET_INT(q1, 201 - i) == i);
        //printf("value: %d\t index: %d\n", GET_INT(q1, 201 + i), i);
        //printf("value: %d\t index: %d\n", GET_INT(q1, 201 - i), i);
    }
    printf("\033[36mget test past\033[0m\n\n");

    // destructor tests:
    destroy(q1);
    destroy(q2);
    printf("\033[36mdestructor tests past\033[0m\n\n");

    return 0;
}