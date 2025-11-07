#include "five_side.h"

template <typename T>
Five_Side<T>::Five_Side(std::vector<std::unique_ptr<Point<T>>>& coords): Figure(coords) {
    if (!this->is_valid()){
        throw std::invalid_argument("Некорректные координаты для пятиугольника: фигура не является пятиугольником или имеет не 5 точек.");
    }
}


template <typename T>
const std::string Five_Side<T>::who_am_i() const {
    return "Five_Side";
}

template <typename T>
bool Five_Side<T>::is_valid() const {
    const size_t REQUIRED_POINTS = 5;

    return this->number_of_coords == REQUIRED_POINTS; 
}