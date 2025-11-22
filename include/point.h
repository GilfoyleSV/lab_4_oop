#pragma once
#include <concepts>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T> 
class Point {
public:
    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
    ~Point() = default;
    
    T get_x() const { return x; }
    T get_y() const { return y; }

    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
private:
    T x;
    T y;
};