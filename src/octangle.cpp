#include "octangle.h"


template <typename T>
Octangle<T>::Octangle(std::vector<std::unique_ptr<Point<T>>>& coords): Figure(coords) {
    if (!this->is_valid()){
        throw std::invalid_argument("Некорректные координаты для восьмиугольника: фигура не является восьмиугольником или имеет не 8 точек.");
    }
}

template <typename T>
const std::string Octangle<T>::who_am_i() const {
    return "Octangle";
}

template <typename T>
bool Octangle<T>::is_valid() const {
    const size_t REQUIRED_POINTS = 8;

    return this->number_of_coords == REQUIRED_POINTS; 
}
