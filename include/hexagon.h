#pragma once
#include "figure.h"

template <typename T>
class Hexagon : public Figure<T> {
    public:
    Hexagon();
    Hexagon(std::vector<std::unique_ptr<Point<T>>>& coords); 

    const std::string who_am_i() const override;
    bool is_valid() const override; 
    ~Hexagon() override = default;
};

template <typename T>
Hexagon<T>::Hexagon(std::vector<std::unique_ptr<Point<T>>>& coords){
    if (coords.size() != 6){
        throw std::invalid_argument("Некорректные координаты для шестиугольника: фигура не является шестиугольником или имеет не 6 точек.");
    }
    this->number_of_coords = 6;
    this->coords = std::move(coords);
}

template <typename T>
Hexagon<T>::Hexagon(){
    this->number_of_coords = 6;
    for (size_t i = 0; i < this->number_of_coords; ++i){
        this->coords.push_back(std::make_unique<Point<T>>(0, 0));
    }
}


template <typename T>
const std::string Hexagon<T>::who_am_i() const {
    return "Hexagon";
}

template <typename T>
bool Hexagon<T>::is_valid() const {
    const size_t REQUIRED_POINTS = 6;

    return this->number_of_coords == REQUIRED_POINTS; 
}