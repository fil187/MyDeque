#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef MY_DEQUE_H
#define MY_DEQUE_H

struct MyDeque {
    size_t capacity;            // in bytes (real capacity is 2 * capacity)
    size_t element_size;        // size of the elemnts stored, needed to retrive the data and store it

    size_t size;                // in bytes
    size_t head;                // idx of first element

    uint8_t* data;              // data stored as bytes
};

typedef struct MyDeque* MyDeque;

#define DEFAULT_CAPACITY 100
#define LARGE_CHUNK_SIZE 8

/*##########################################################
#                         functions                        #
##########################################################*/
MyDeque deque_new_with_capacity(size_t element_size, size_t capacity); // constructor with specified capacity (capacity * element_size)
MyDeque deque_new(size_t element_size);                                // constructor with default capacity (100 * element_size)
size_t len(MyDeque self);                                              // returns the number of items in the vec
void push_back(MyDeque self, void* element);                           // add element to the end of the vector
void push_front(MyDeque self, void* element);                          // add element to the front of the vector
uint8_t* get(MyDeque self, size_t idx);                                // get elemnt at index (byte pointer | needs casting)
uint8_t* pop_back(MyDeque self);                                       // pops the last element of the vector, returns the element that was removed (byte pointer | needs casting)
uint8_t* pop_front(MyDeque self);                                      // pops the first element of the vector, returns the element that was removed (byte pointer | needs casting)
int clear(MyDeque _self);                                              // *empty the vec (size is set back to 0) data is still present in memory returns 1 on success
void destroy(MyDeque self);                                            // destroyer

/*##########################################################
#               basic casting and referencing              #
##########################################################*/ 
// casting for get (cleaner code)
#define GET_INT(SELF, IDX) *(int*)get(SELF, IDX)
#define GET_FLOAT(SELF, IDX) *(float*)get(SELF, IDX)
#define GET_CHAR(SELF, IDX) *(char*)get(SELF, IDX)
#define GET_U8(SELF, IDX) *(uint8_t*)get(SELF, IDX)
#define GET_U16(SELF, IDX) *(uint16_t*)get(SELF, IDX)
#define GET_U32(SELF, IDX) *(uint32_t*)get(SELF, IDX)
#define GET_U64(SELF, IDX) *(uint64_t*)get(SELF, IDX)
#define GET_I8(SELF, IDX) *(int8_t*)get(SELF, IDX)
#define GET_I16(SELF, IDX) *(int16_t*)get(SELF, IDX)
#define GET_I32(SELF, IDX) *(int32_t*)get(SELF, IDX)
#define GET_I64(SELF, IDX) *(int64_t*)get(SELF, IDX)
#define GET_SIZE(SELF, IDX) *(size_t*)get(SELF, IDX)
// casting for pop_back (cleaner code)
#define POP_BACK_INT(SELF) *(int*)pop_back(SELF)
#define POP_BACK_FLOAT(SELF) *(float*)pop_back(SELF)
#define POP_BACK_CHAR(SELF) *(char*)pop_back(SELF)
#define POP_BACK_U8(SELF) *(uint8_t*)pop_back(SELF)
#define POP_BACK_U16(SELF) *(uint16_t*)pop_back(SELF)
#define POP_BACK_U32(SELF) *(uint32_t*)pop_back(SELF, IDX)
#define POP_BACK_U64(SELF) *(uint64_t*)pop_back(SELF, IDX)
#define POP_BACK_I8(SELF) *(int8_t*)pop_back(SELF, IDX)
#define POP_BACK_I16(SELF) *(int16_t*)pop_back(SELF, IDX)
#define POP_BACK_I32(SELF) *(int32_t*)pop_back(SELF, IDX)
#define POP_BACK_I64(SELF) *(int64_t*)pop_back(SELF, IDX)
#define POP_BACK_SIZE(SELF) *(size_t*)pop_back(SELF, IDX)
// casting for pop_front (cleaner code)
#define POP_FRONT_INT(SELF) *(int*)pop_front(SELF)
#define POP_FRONT_FLOAT(SELF) *(float*)pop_front(SELF)
#define POP_FRONT_CHAR(SELF) *(char*)pop_front(SELF)
#define POP_FRONT_U8(SELF) *(uint8_t*)pop_front(SELF)
#define POP_FRONT_U16(SELF) *(uint16_t*)pop_front(SELF)
#define POP_FRONT_U32(SELF) *(uint32_t*)pop_front(SELF, IDX)
#define POP_FRONT_U64(SELF) *(uint64_t*)pop_front(SELF, IDX)
#define POP_FRONT_I8(SELF) *(int8_t*)pop_front(SELF, IDX)
#define POP_FRONT_I16(SELF) *(int16_t*)pop_front(SELF, IDX)
#define POP_FRONT_I32(SELF) *(int32_t*)pop_front(SELF, IDX)
#define POP_FRONT_I64(SELF) *(int64_t*)pop_front(SELF, IDX)
#define POP_FRONT_SIZE(SELF) *(size_t*)pop_front(SELF, IDX)

#endif