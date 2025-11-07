#ifndef ARRAY_H
#define ARRAY_H
#include "figure.h"
#include <string>
#include <memory>

template <typename T>
class Array{
    public:
    Array();
    Array(const Array& other);
    Array(Array&& other) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    void print_info() const;
    double total_area() const;
    void remove_figure(size_t i);
    void add_figure(std::shared_ptr<Figure<T>> fig);
    ~Array() noexcept = default;

    private:
    size_t length;
    std::unique_ptr<std::shared_ptr<Figure<T>>[]> array_of_figures;
    size_t capacity;

    void grow();
};

#endif