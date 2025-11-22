#pragma once
#include "figure.h"

template <typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon();
    Hexagon(const Point<T>& center, T radius);

    const std::string who_am_i() const override;
    size_t vertex_count() const override { return 6; }

    ~Hexagon() override = default;
};

template <typename T>
Hexagon<T>::Hexagon() : Figure<T>(Point<T>(0, 0), 1) {} // центр (0,0), радиус 1

template <typename T>
Hexagon<T>::Hexagon(const Point<T>& center, T radius)
    : Figure<T>(center, radius) {}

template <typename T>
const std::string Hexagon<T>::who_am_i() const {
    return "Hexagon";
}
