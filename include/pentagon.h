#pragma once

#include "figure.h"
#include <vector>
#include <memory>

template <typename T>
class Pentagon : public Figure<T> {
    public:
    Pentagon();
    Pentagon(std::vector<std::unique_ptr<Point<T>>>& coords); 

    const std::string who_am_i() const override;
    bool is_valid() const override; 
    ~Pentagon() override = default;
};

template <typename T>
Pentagon<T>::Pentagon(std::vector<std::unique_ptr<Point<T>>>& coords){
    if (coords.size() != 5){
        throw std::invalid_argument("Некорректные координаты для пятиугольника: фигура не является пятиугольником или имеет не 5 точек.");
    }
    this->number_of_coords = 5;
    this->coords = std::move(coords);
}

template <typename T>
Pentagon<T>::Pentagon(){
    this->number_of_coords = 5;
    for (size_t i = 0; i < this->number_of_coords; ++i){
        this->coords.push_back(std::make_unique<Point<T>>(0, 0));
    }
}

template <typename T>
const std::string Pentagon<T>::who_am_i() const {
    return "Pentagon";
}

template <typename T>
bool Pentagon<T>::is_valid() const {
    const size_t REQUIRED_POINTS = 5;

    return this->number_of_coords == REQUIRED_POINTS; 
}