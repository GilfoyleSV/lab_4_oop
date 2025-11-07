#include "six_side.h"

template <typename T>
Six_Side<T>::Six_Side(std::vector<std::unique_ptr<Point<T>>>& coords): Figure(coords) {
    if (!this->is_valid()){
        throw std::invalid_argument("Некорректные координаты для шестиугольника: фигура не является шестиугольником или имеет не 6 точек.");
    }
}

template <typename T>
const std::string Six_Side<T>::who_am_i() const {
    return "Six_Side";
}

template <typename T>
bool Six_Side<T>::is_valid() const {
    const size_t REQUIRED_POINTS = 6;

    return this->number_of_coords == REQUIRED_POINTS; 
}