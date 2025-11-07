#pragma once

#include <initializer_list>
#include <utility>
#include <iostream>
#include <vector>
#include "point.h"
#include <memory>
#include <stdexcept>
#include <cmath>

template <typename T> class Figure{
    public:
    Figure() = default;
    Figure(std::vector<std::unique_ptr<Point<T>>>& coords);
    Figure(const Figure& other);
    Figure(Figure&& other) noexcept;
    virtual ~Figure() = default;

    std::pair<T, T> geom_centre() const;
    operator double() const;

    virtual const std::string who_am_i() const = 0;

    Figure& operator =(const Figure& other);
    Figure& operator =(Figure&& other) noexcept;
    bool operator==(const Figure& other) const;

    template <typename U>
    friend std::ostream& operator<< (std::ostream& os, const Figure<U>& fig);
    template <typename U>
    friend std::istream& operator>> (std::istream& is, Figure<U>& fig);

    protected:
    virtual bool is_valid() const = 0;
    size_t number_of_coords;
    std::vector<std::unique_ptr<Point<T>>> coords;
};

template <typename T> Figure<T>::Figure(std::vector<std::unique_ptr<Point<T>>>& coords){
    if (coords.size() != this->number_of_coords){
        throw std::invalid_argument("Некорректное количество точек для фигуры.");
    }
    this->number_of_coords = coords.size();
    this->coords = std::move(coords);
}

template <typename T> Figure<T>::Figure(const Figure<T>& other){
    this->number_of_coords = other.number_of_coords;
    for (const auto& p : other.coords) {
            this->coords.push_back(std::make_unique<Point<T>>(*p));
    }
}

template <typename T> Figure<T>::Figure(Figure<T>&& other) noexcept{
    this->number_of_coords = other.number_of_coords;
    this->coords = std::move(other.coords);
    other.number_of_coords = 0;
}

template <typename T> Figure<T>& Figure<T>::operator=(const Figure<T>& other){
    if (this != &other) {
        this->number_of_coords = other.number_of_coords;

        this->coords.clear();
        this->coords.reserve(other.coords.size());

        for (const auto& p : other.coords) {
            this->coords.push_back(std::make_unique<Point<T>>(*p));
        }
    }
    return *this;
}

template <typename T> Figure<T>& Figure<T>::operator=(Figure<T>&& other) noexcept{
    if (this != &other){
        this->coords = std::move(other.coords);
        this->number_of_coords = other.number_of_coords;
        other.number_of_coords = 0; 
    }
    return *this;
}

template <typename T>
std::istream& operator>>(std::istream& is, Figure<T>& figure) {
    figure.coords.clear();

    for (size_t i = 0; i < figure.number_of_coords; i++) {
        T x, y;
        is >> x >> y;
        figure.coords.push_back(std::make_unique<Point<T>>(x, y));
    }

    if (!figure.is_valid()) {
        std::cerr << "Invalid figure input!\n";
    }

    return is;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
    os << figure.who_am_i() << " with " << figure.number_of_coords << " points:\n";
    for (size_t i = 0; i < figure.number_of_coords; i++) {
        os << "(" << figure.coords[i]->get_x() << ", "
           << figure.coords[i]->get_y() << ")\n";
    }
    return os;
}

template <typename T> std::pair<T, T> Figure<T>::geom_centre() const{
    if (this->number_of_coords == 0){
        throw std::runtime_error("Фигура не имеет точек, невозможно вычислить геометрический центр.");
    }

    T x_sum = 0;
    T y_sum = 0;

    for (const auto& point: this->coords){
        x_sum += point->get_x();
        y_sum += point->get_y();
    }

    x_sum /= this->number_of_coords;
    y_sum /= this->number_of_coords;

    return {x_sum, y_sum};
}

template <typename T> Figure<T>::operator double() const {
    size_t n = this->number_of_coords;
    if (n < 3)
        return 0.0;

    double s = 0;
    for (size_t i = 0; i < n; ++i) {
        double x1 = this->coords[i]->get_x();
        double y1 = this->coords[i]->get_y();
        double x2 = this->coords[(i + 1) % n]->get_x();
        double y2 = this->coords[(i + 1) % n]->get_y();
        s += x1 * y2 - x2 * y1;
    }

    return std::abs(s) / 2.0;
}

template <typename T> bool Figure<T>::operator==(const Figure<T>& other) const{
    if (this->number_of_coords != other.number_of_coords){
        return false;
    }

    for (size_t i = 0; i < this->number_of_coords; ++i){
        if (*(this->coords[i]) != *(other.coords[i])){
            return false;
        }
    }

    return true;
}