#pragma once
#include "figure.h"

template <typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon() = default;
    Hexagon(const Point<T>& center, T radius);

    const std::string who_am_i() const override { return "Hexagon"; }
    size_t vertex_count() const override { return 6; }

    ~Hexagon() override = default;
};

template <typename T>
Hexagon<T>::Hexagon(const Point<T>& center, T radius)
    : Figure<T>(center, radius) 
{
    this->generate_points();
}