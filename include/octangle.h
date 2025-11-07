#pragma once
#include "figure.h"
#include <vector>

template <typename T>
class Octangle : public Figure<T> {
    public:
    Octangle(); 
    Octangle(std::vector<std::unique_ptr<Point<T>>>& coords); 

    const std::string who_am_i() const override;
    bool is_valid() const override; 
    ~Octangle() override = default;
};

template <typename T>
Octangle<T>::Octangle(std::vector<std::unique_ptr<Point<T>>>& coords){
    if (coords.size() != 8){
        throw std::invalid_argument("Некорректные координаты для восьмиугольника: фигура не является восьмиугольником или имеет не 8 точек.");
    }
    this->number_of_coords = 8;
    this->coords = std::move(coords);
}

template <typename T>
Octangle<T>::Octangle(){
    this->number_of_coords = 8;
    for (size_t i = 0; i < this->number_of_coords; ++i){
        this->coords.push_back(std::make_unique<Point<T>>(0, 0));
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
