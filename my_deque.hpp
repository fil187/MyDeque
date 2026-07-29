#include <cstddef>
#include <stdexcept>

/**
 * @brief A dynamically allocated mutable double-ended queue.
 * 
 * @invariant `capacity > 0`
 * @invariant `size <= capacity`
 * @invariant `head < capacity`
 * @invariant `data != nullptr`
 * @invariant `size` is always greater then 25% of capacity iff `capacity <= DEFAULT_CAPACITY`
 * @invariant For every `0 <= i < size`,
 *            `data[(head + i) % capacity]`
 *            stores the ith element of the deque.
 * @invariant data points to an allocated array of exactly `capacity` elements `T`.
 */
template <typename T>
class MyDeque {

private:

    T* data;
    size_t size;
    size_t head;
    size_t capacity;
    static constexpr size_t DEFAULT_CAPACITY = 100;

public:

    /**
     * @brief Construct an empty deque with the default capacity.
     * 
     * @throw std::bad_alloc if the allocation fails.
     */
    MyDeque() : MyDeque(DEFAULT_CAPACITY) {}

    /**
     * @brief Construct an empty deque with the specified capacity.
     * 
     * @param capacity The initial number of elements that can be stored without reallocation.
     * @throw std::invalid_argument if `capacity == 0`.
     * @throw std::bad_alloc if the allocation fails.
     */
    MyDeque(size_t capacity) : size(0), head(0), capacity(capacity) {
        if (capacity == 0)
            throw std::invalid_argument("capacity must be greater than 0");

        data = new T[capacity];
    }

    /**
     * @brief Constructs a deque containing copies of the elements in `source`.
     * 
     * @par Complexity
     *      O(m)
     * 
     * @throw std::invalid_argument if `source == nullptr`.
     * @throw std::bad_alloc if the allocation fails.
     * @param source The array whose contents are copied into this deque.
     * @param size The number of elements in `source`.
     */
    MyDeque(const T* source, size_t size) : size(size), head(0), capacity(std::max(size << 1, DEFAULT_CAPACITY)) {
        if (source == nullptr)
            throw std::invalid_argument("source can not be NULL");
        
        data = new T[std::max(size << 1, DEFAULT_CAPACITY)];
        std::copy(source, source + size, data);
    }

    /**
     * @brief Constructs a deque containing copies of the elements in `source`.
     * 
     * @par Complexity
     *      O(m)
     * 
     * @throw std::bad_alloc if the allocation fails.
     * @param source The deque whose contents are copied into this deque.
     */
    MyDeque(const MyDeque<T>& source) : size(source.size), head(0), capacity(source.capacity) {
        data = new T[source.capacity];
        for (size_t i = 0; i < source.size; i++) {
            size_t src_idx = (i + head) % source.capacity;
            data[i] = source.data[src_idx];
        }
    }

    /**
     * @note Move construction are disabled because this container's invariants do not permit a moved-from state.
     */
    MyDeque(const MyDeque<T>&&) = delete;

    /**
     * @note Move assignment are disabled because this container's invariants do not permit a moved-from state.
     */
    MyDeque& operator=(const MyDeque<T>&&) = delete;

    /**
     * @throw std::out_of_range if i greater than or equal to the length of this deque.
     * @return A reference to the element at index `i`.
     */
    T& operator[](size_t i) {
        if (i >= size)
            throw std::out_of_range("index out of range");
        
        return data[(head + i) % capacity];
    }

    /**
     * @brief Replaces the contents of this deque with those of `source`.
     * 
     * @par Complexity
     *      Worst case O(n)
     * 
     * @throw std::bad_alloc if the allocation fails
     * 
     * @post The contents of this deque are equal to `source`.
     * @post The length of this deque equals the length of `source`.
     */
    MyDeque& operator=(const MyDeque& source) {
        if (this == &source)
            return *this;
        
        delete[] data;
        data = new T[source.capacity];

        if (data == nullptr)
            throw std::bad_alloc();

        capacity = source.capacity;
        size = source.size;

        for (size_t i = head; i < source.size; i++)
            data[i % capacity] = source.data[i % capacity];
        
        return *this;
    }

    /**
     * @return The number of elements currently stored in the deque.
     */
    size_t length() const {
        return size;
    }

    /**
     * @brief Adds the element at the end of the deque.
     * 
     * @par Complexity
     *      Worst case O(n)
     *      Average case O(1)
     * 
     * @throw std::bad_alloc if the allocation fails.
     * 
     * @post The length of this deque is increased by 1.
     * @post `element` is the last element of the deque.
     * @post The rest of the deque remains unchanged.
     */
    void push_back(const T& element) {
        if (size == capacity)
            resize(2 * capacity);
        
        data[(head + size++) % capacity] = element;
    }

    /**
     * @brief Adds the element at the start of the deque.
     * 
     * @par Complexity
     *      Worst case O(n)
     *      Average case O(1)
     * 
     * @post The length of this deque is increased by 1.
     * @post `element` is the first element of the deque.
     * @post The rest of the deque remains unchanged.
     */
    void push_front(T element) {
        if (size == capacity)
            resize(2 * capacity);
        if (head == 0)
            head = capacity;    
        
        size += 1;
        data[--head] = element;
    }

    /**
     * @brief Removes the last element of the deque.
     * 
     * @par Complexity
     *      Worst case O(n)
     *      Average case O(1)
     * 
     * @throw std::out_of_range if the deque is empty
     * @return The removed element.
     * 
     * @post The length of this deque is decreased by 1.
     * @post The rest of the deque remains unchanged.
     */
    T pop_back() {
        if (size == 0)
            throw std::out_of_range("can not pop() on an empty deque");
        if (capacity > DEFAULT_CAPACITY && size == capacity >> 2) // >> 2 -> 1/4
            resize(capacity >> 1); // >> 1 -> 1/2
    
        return data[(head + (--size)) % capacity];
    }

    /**
     * @brief Removes the first element of the deque.
     * 
     * @par Complexity
     *      Worst case O(n)
     *      Average case O(1)
     * 
     * @throw std::out_of_range if the deque is empty
     * @return The removed element.
     * 
     * @post The length of this deque is decreased by 1.
     * @post The rest of the deque remains unchanged.
     */
    T pop_front() {
        if (size == 0)
            throw std::out_of_range("can not pop() on an empty deque");
        if (capacity > DEFAULT_CAPACITY && size == capacity >> 2) // >> 2 -> 1/4
            resize(capacity >> 1); // >> 1 -> 1/2
        
        T result = data[head];
        head = (head + 1) % capacity;
        size -= 1;
        return result;
    }

    /**
     * @brief Sorts the deque in increasing order
     * @note This function is only available when `T` models `std::totally_ordered`.
     * @note The representation array is realligned if `head != 0`
     * 
     * @par Complexity
     *      Average case O(n * log(n))
     * 
     * @post The deque is sorted in increasing order.
     * @post All elements originally in data are present in the same number.
     */
    void sort() requires std::totally_ordered<T> {
        if (head != 0)
            realligne();
        sort(0, size - 1);
    }

    ~MyDeque() {
        delete[] data;
    }

private:

    /**
     * @par Complexity
     *      O(n)
     * 
     * @throw std::bad_alloc if the allocation fails.
     * 
     * @pre `new_capacity > 0`
     * @post The contents of this deque are unchanged.
     * @post The capacity of this deque is equal to new_capacity.
     */
    void resize(size_t new_capacity) {
        T* destination = new T[new_capacity];
        for (size_t i = 0; i < size; i++)
            destination[i] = data[(i + head) % capacity];
        
        delete[] data;
        data = destination;
        capacity = new_capacity;
        head = 0;
    }

    /**
     * @post `head == 0`
     * @post The first element is positioned at index 0
     *       and the last element is positioned at index `size - 1`.
     * @post All elements originally in data are present in the same number.
     * @post All elements originally in data are present in the same order.
     */
    void realligne() {
        for (size_t i = size; i > 0; i--)
            data[i] = data[(head + i) % capacity];
        head = 0;
    }

    /**
     * @par Complexity
     *      Average case O(n * log(n))
     * 
     * @post `data[left..right]` is sorted.
     * @post All elements originally in data are present in the same number.
     */
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