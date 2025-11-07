#include "array.h"

#define START_CAPACITY 10

template <typename T>
Array<T>::Array(){
    this->length = 0;
    this->capacity = START_CAPACITY;
    this->array_of_figures = std::make_unique<std::shared_ptr<Figure<T>>[]>(START_CAPACITY);
}

template <typename T>
Array<T>::Array(const Array& other){   
    this->length = other.length;
    this->capacity = other.capacity;
    this->array_of_figures = std::make_unique<std::shared_ptr<Figure<T>>[]>(other.capacity);
    for (size_t i = 0; i < length; ++i)
        array_of_figures[i] = other.array_of_figures[i];
}

template <typename T>
Array<T>::Array(Array&& other) noexcept{   
    this->length = other.length;
    this->capacity = other.capacity;
    this->array_of_figures = std::move(other.array_of_figures);
    other.length = 0;
    other.capacity = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        capacity = other.capacity;
        length = other.length;
        array_of_figures = std::make_unique<std::shared_ptr<Figure<T>>[]>(capacity);
        for (size_t i = 0; i < length; ++i)
            array_of_figures[i] = other.array_of_figures[i];
    }
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        capacity = other.capacity;
        length = other.length;
        array_of_figures = std::move(other.array_of_figures);
        other.length = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename T>
void Array<T>::grow() {
    size_t new_capacity = capacity * 2;

    auto new_array = std::make_unique<std::shared_ptr<Figure<T>>[]>(new_capacity);

    for (size_t i = 0; i < length; ++i)
        new_array[i] = std::move(array_of_figures[i]);
    array_of_figures = std::move(new_array);
    capacity = new_capacity;
}

template <typename T>
void Array<T>::add_figure(std::shared_ptr<Figure<T>> fig) {
    if (length >= capacity)
        grow();
    array_of_figures[length++] = std::move(fig);
}

template <typename T>
void Array<T>::remove_figure(size_t i) {
    if (i >= length)
        throw std::out_of_range("Индекс вне диапазона");

    for (size_t j = i; j < length - 1; ++j)
        array_of_figures[j] = std::move(array_of_figures[j + 1]);

    --length;
}

template <typename T>
void Array<T>::print_info() const {
    for (size_t i = 0; i < length; ++i) {
        std::cout << "Figure " << i + 1 << ":\n";
        std::cout << array_of_figures[i]->who_am_i() << '\n';
        auto centre = array_of_figures[i]->geom_centre();
        std::cout << "Geom centre: (" << centre.first << ", " << centre.second << ")\n";
        std::cout << "Square: " << double(*array_of_figures[i]) << "\n\n";
    }
}

template <typename T>
double Array<T>::total_area() const {
    double total = 0.0;
    for (size_t i = 0; i < length; ++i)
        total += double(*array_of_figures[i]);
    return total;
}
