#include <cstddef>
#include <stdexcept>

template <typename T>
class MyDeque {

private:

    T* data;
    size_t size;
    size_t head;
    size_t capacity;
    static constexpr size_t DEFAULT_CAPACITY = 100;

public:

    MyDeque() : MyDeque(DEFAULT_CAPACITY) {
        // constructor with default capacity
    }

    MyDeque(size_t capacity) : size(0), head(0), capacity(capacity) {
        // constructor with defined capacity
        // thows illegal argument exception if capacity is null
        // @param capacity -> capcity for the vector
        if (capacity == 0)
            throw std::invalid_argument("capacity must be greater than 0");

        data = new T[capacity];
    }

    MyDeque(const T* source, size_t size) : size(size), head(0), capacity(max(size << 1, DEFAULT_CAPACITY)) {
        // constructor from array
        // @param source -> the array from wich to build the vector from
        // @param size -> the size of the array
        data = new T[max(size << 1, DEFAULT_CAPACITY)];
        for (size_t i = 0; i < size; i++)
            data[i] = source[i];
    }

    MyDeque(const MyDeque<T>& source) : size(source.size), head(0), capacity(source.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < source.size; i++) {
            size_t src_idx = (i + head) % source.capacity;
            data[i] = source.data[src_idx];
        }
    }

    T& operator[](size_t i) {
        if (i >= size)
            throw std::out_of_range("index out of range");
        
        return data[(head + i) % capacity];
    }

    MyDeque& operator=(const MyDeque& source) {
        if (this == &source)
            return *this;
        
        delete[] data;
        data = new T[source.capacity];
        capacity = source.capacity;
        size = source.size;

        for (size_t i = head; i < source.size; i++)
            data[i % capacity] = source.data[i % capacity];
        
        return *this;
    }

    size_t length() const {
        return size;
    }

    void push_back(const T& element) {
        if (size == capacity)
            resize(max(1, 2 * capacity));
        
        data[(head + size++) % capacity] = element;
    }

    void push_front(T element) {
        if (size == capacity)
            resize(max(1, 2 * capacity));
        if (head == 0)
            head = capacity;    
        
        size += 1;
        data[--head] = element;
    }

    T pop_back() {
        if (size == 0)
            throw std::out_of_range("can not pop() when deque is empty");
        if (size == capacity >> 2) // >> 2 -> 1/4
            resize(capacity >> 1); // >> 1 -> 1/2
    
        return data[(head + (--size)) % capacity];
    }

    T pop_front() {
        if (size == 0)
            throw std::out_of_range("can not pop() when deque is empty");
        if (size == capacity >> 2) // >> 2 -> 1/4
            resize(capacity >> 1); // >> 1 -> 1/2
        
        T result = data[head];
        head = (head + 1) % capacity;
        size -= 1;
        return result;
    }

    void clear() {
        size = 0;
        head = 0;
    }

    void sort() requires std::totally_ordered<T> {
        // calls private sort method for the whole array
        // rearrange data if head != 0
        if (head != 0)
            realligne();
        sort(0, size - 1);
    }

    ~MyDeque() {
        delete[] data;
    }

private:

    static inline size_t max(size_t a, size_t b) {
        return (a >= b) ? a : b;
    }

    void resize(size_t new_capacity) {
        T* destination = new T[new_capacity];
        for (size_t i = 0; i < size; i++)
            destination[i] = data[(i + head) % capacity];
        
        delete[] data;
        data = destination;
        capacity = new_capacity;
        head = 0;
    }

    void realligne() {
        for (size_t i = size; i > 0; i--)
            data[i] = data[(head + i) % capacity];
        head = 0;
    }

    void sort(size_t left, size_t right) {
        if (left >= right)
            return;

        size_t pivot_idx = left + ((right - left) >> 1);
        T pivot = data[pivot_idx];
        std::swap(data[pivot_idx], data[right]);
        
        size_t lower_bound = left;

        for (size_t i = left; i < right; i++)
            if (data[i] <= pivot)
                std::swap(data[i], data[lower_bound++]);
        
        std::swap(data[lower_bound], data[right]);
        sort(left, (lower_bound > 0) ? lower_bound - 1 : 0);
        sort(lower_bound + 1, right);
    }
};