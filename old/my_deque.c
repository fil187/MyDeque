#include "my_deque.h"

#define ABS(N) (N < 0 ? -N : N)

/*##########################################################
#                         functions                        #
##########################################################*/

MyDeque deque_new_with_capacity(size_t element_size, size_t capacity) {
    MyDeque self = malloc(sizeof(struct MyDeque));
    if (self == NULL) {
        return NULL;
    }

    self->data = malloc(capacity * element_size);
    if (self->data == NULL) {
        free(self);
        return NULL;
    }

    self->capacity = capacity * element_size;
    self->element_size = element_size;
    self->size = 0;
    self->head = 0;
    
    return self;
}

MyDeque deque_new(size_t element_size) {
    return deque_new_with_capacity(element_size, DEFAULT_CAPACITY);
}

size_t len(MyDeque self) {
    return self->size / self->element_size;
}

int resize(MyDeque self, size_t new_size) {
    uint8_t* resized = malloc(new_size);

    if (resized == NULL) {
        return 0;
    }

    size_t head_bytes = self->size - self->head;
    size_t tail_bytes = self->size - head_bytes;

    size_t head_large_chunks = head_bytes / LARGE_CHUNK_SIZE;
    size_t tail_large_chunks = tail_bytes / LARGE_CHUNK_SIZE;
    size_t head_small_chunks = head_bytes % LARGE_CHUNK_SIZE;
    size_t tail_small_chunks = tail_bytes % LARGE_CHUNK_SIZE;
    
    // head copy: 
    uint64_t* src_large_head = (uint64_t*)(self->data + self->head);
    uint64_t* dst_large_head = (uint64_t*)resized;

    for (int i = 0; i < head_large_chunks; i++) {
        dst_large_head[i] = src_large_head[i];
    }

    uint8_t* src_small_head = (uint8_t*)(src_large_head + head_large_chunks);
    uint8_t* dst_small_head = (uint8_t*)(dst_large_head + head_large_chunks);

    for (int i = 0; i < head_small_chunks; i++) {
        dst_small_head[i] = src_small_head[i];
    }

    // tail copy:
    uint64_t* src_large_tail = (uint64_t*)self->data;
    uint64_t* dst_large_tail = (uint64_t*)(dst_small_head + head_small_chunks);

    for (int i = 0; i < tail_large_chunks; i++) {
        dst_large_tail[i] = src_large_tail[i];
    }

    uint8_t* src_small_tail = (uint8_t*)(src_small_head + head_small_chunks);
    uint8_t* dst_small_tail = (uint8_t*)(dst_small_head + head_small_chunks);

    for (int i = 0; i < tail_small_chunks; i++) {
        dst_small_tail[i] = src_small_tail[i];
    }

    // modifications to self:

    self->capacity = new_size;
    free(self->data);
    self->data = resized;
    self->head = 0;

    return 1;
}

void push_back(MyDeque self, void* element) {
    if (self == NULL || element == NULL) {
        return;
    }
    
    if (self->size == self->capacity) {
        if (!resize(self, self->capacity * 2)) {
            return;
        }
    }

    uint8_t* bytes = (uint8_t*)element;
    for (int i = 0; i < self->element_size; i++) {
        self->data[(self->head + self->size++) % self->capacity] = *bytes++;
    }
}

void push_front(MyDeque self, void* element) {
    if (self == NULL || element == NULL) {
        return;
    }
    
    if (self->size == self->capacity) {
        if (!resize(self, self->capacity * 2)) {
            return;
        }
    }

    self->head = (self->head + self->capacity - self->element_size) % self->capacity;
    uint8_t* bytes = (uint8_t*)element;
    for (int i = 0; i < self->element_size; i++) {
        self->data[self->head + i] = *bytes++;
        self->size++;
    }
}

uint8_t* get(MyDeque self, size_t idx) {
    if (self == NULL || self->data == NULL || idx >= self->size || idx < 0) {
        return NULL;
    }

    return &self->data[(self->head + (idx * self->element_size)) % self->capacity];
}

uint8_t* pop_back(MyDeque self) {
    if (self == NULL || self->data == NULL || self->size == 0) {
        return NULL;
    }

    self->size -= self->element_size;
    return &self->data[(self->head + self->size) % self->capacity];
}

uint8_t* pop_front(MyDeque self) {
    if (self == NULL || self->data == NULL || self->size == 0) {
        return NULL;
    }

    self->size -= self->element_size;
    self->head += self->element_size;
    return &self->data[ABS((self->head - self->element_size) % self->capacity)];
}

int clear(MyDeque self) {

}

void destroy(MyDeque self) {
    if (self == NULL) {
        return;
    }

    if (self->data != NULL) {
        free(self->data);
        self->data = NULL;
    }

    free(self);
    self = NULL;
}