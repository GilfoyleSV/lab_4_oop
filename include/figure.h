#pragma once

#include <initializer_list>
#include <utility>
#include <iostream>
#include <vector>
#include "point.h"
#include <memory>
#include <stdexcept>
#include <cmath>


template <typename T>
class Figure {
public:
    Figure() = default;
    Figure(const Point<T>& center, T radius);
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    virtual ~Figure() = default;

    virtual size_t vertex_count() const = 0;

    virtual const std::string who_am_i() const = 0;

    virtual void generate_points();

    std::pair<T, T> geom_centre() const;
    operator double() const; // площадь

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;
    bool operator==(const Figure& other) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Figure<U>& fig);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Figure<U>& fig);

protected:
    Point<T> center;
    T radius = 0;
    std::vector<Point<T>> coords;
};

template <typename T>
Figure<T>::Figure(const Point<T>& center, T radius)
    : center(center), radius(radius) {
    generate_points();
}

template <typename T>
Figure<T>::Figure(const Figure<T>& other)
    : center(other.center), radius(other.radius), coords(other.coords) {}

template <typename T>
Figure<T>::Figure(Figure<T>&& other) noexcept
    : center(other.center), radius(other.radius), coords(std::move(other.coords)) {}

template <typename T>
Figure<T>& Figure<T>::operator=(const Figure<T>& other) {
    if (this != &other) {
        center = other.center;
        radius = other.radius;
        coords = other.coords;
    }
    return *this;
}

template <typename T>
Figure<T>& Figure<T>::operator=(Figure<T>&& other) noexcept {
    if (this != &other) {
        center = other.center;
        radius = other.radius;
        coords = std::move(other.coords);
    }
    return *this;
}

template <typename T>
bool Figure<T>::operator==(const Figure<T>& other) const {
    if (coords.size() != other.coords.size()) return false;
    for (size_t i = 0; i < coords.size(); i++) {
        if (!(coords[i] == other.coords[i])) return false;
    }
    return true;
}


template <typename T>
void Figure<T>::generate_points() {
    coords.clear();
    size_t n = vertex_count();
    coords.reserve(n);

    for (size_t i = 0; i < n; i++) {
        T angle = 2 * M_PI * i / n;
        T x = center.get_x() + radius * std::cos(angle);
        T y = center.get_y() + radius * std::sin(angle);
        coords.emplace_back(x, y);
    }
}

template <typename T>
std::pair<T, T> Figure<T>::geom_centre() const {
    return {center.get_x(), center.get_y()};
}


template <typename T>
Figure<T>::operator double() const {
    size_t n = coords.size();
    if (n < 3) return 0.0;

    double s = 0;
    for (size_t i = 0; i < n; i++) {
        const auto& p1 = coords[i];
        const auto& p2 = coords[(i + 1) % n];
        s += p1.get_x() * p2.get_y() - p2.get_x() * p1.get_y();
    }
    return std::abs(s) / 2.0;
}


template <typename T>
std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    T x, y, r;
    is >> x >> y >> r;
    fig.center = Point<T>(x, y);
    fig.radius = r;
    fig.generate_points();
    return is;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    os << fig.who_am_i() << " with center (" << fig.center.get_x()
       << ", " << fig.center.get_y() << ") and radius " << fig.radius << "\n";
    os << "Points:" << "\n";
    for (const auto& p : fig.coords) {
        os << "(" << p.get_x() << ", " << p.get_y() << ")\n";
    }
    return os;
}
