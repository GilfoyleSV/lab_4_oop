#pragma once
#include "figure.h"

template <typename T>
class Octagon : public Figure<T> {
public:
    Octagon() = default;
    Octagon(const Point<T>& center, T radius);

    const std::string who_am_i() const override { return "Octagon"; }
    size_t vertex_count() const override { return 8; }

    ~Octagon() override = default;
};

template <typename T>
Octagon<T>::Octagon(const Point<T>& center, T radius)
    : Figure<T>(center, radius) {
    this->generate_points();
}