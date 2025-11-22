#pragma once
#include "figure.h"

template <typename T>
class Pentagon : public Figure<T> {
public:
    Pentagon() = default;
    Pentagon(const Point<T>& center, T radius);

    const std::string who_am_i() const override { return "Pentagon"; }
    size_t vertex_count() const override { return 5; }

    ~Pentagon() override = default;
};

template <typename T>
Pentagon<T>::Pentagon(const Point<T>& center, T radius)
    : Figure<T>(center, radius) {
    this->generate_points();
    }