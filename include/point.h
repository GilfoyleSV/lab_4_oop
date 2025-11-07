#pragma once
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T> 
class Point {
public:
    Point(T x, T y) : x(x), y(y) {}
    ~Point() = default;
    
    T get_x() const { return x; }
    T get_y() const { return y; }

private:
    T x;
    T y;
};