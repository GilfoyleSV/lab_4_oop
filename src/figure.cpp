#include "figure.h"
#include <stdexcept>
#include <math.h>

template <typename T> Figure<T>::Figure(){
    this->number_of_coords = 0;
    this->coords = {};
}

template <typename T> Figure<T>::Figure(size_t number_of_coords){
    this->number_of_coords = number_of_coords;
}

template <typename T> Figure<T>::Figure(std::vector<std::pair<T, T>>& coords){
    this->number_of_coords = coords.size();
    this->coords = coords;
}

template <typename T> Figure<T>::Figure(const Figure<T>& other){
    this->number_of_coords = other.number_of_coords;
    this->coords = other.coords;
}

template <typename T> Figure<T>::Figure(Figure<T>&& other) noexcept{
    this->number_of_coords = other.number_of_coords;
    this->coords = std::move(other.coords);
    other.number_of_coords = 0;
}

template <typename T> std::istream& operator>>(std::istream& is, Figure<T>& figure){
    size_t num_of_points;

    is >> num_of_points;

    if (!is){
        throw std::invalid_argument("Неправильный ввод: не удалось считать количество точек.");
    }
    figure.coords.clear();
    figure.number_of_coords = num_of_points;
    
    for (size_t i = 0; i != num_of_points; i++){
        T x, y;
        is >> x >> y;
        if (!is){
            throw std::invalid_argument("Неправильный ввод: не удалось считать координаты.");
        }
        figure.coords.push_back({x, y});
    }

    if (!is){
        throw std::invalid_argument("Неправильный ввод: ошибка после считывания данных.");
    }
    
    if (!figure.is_valid()){
        throw std::invalid_argument("Введенные данные не соответствуют требованиям фигуры.");
    }

    return is;
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Figure<T>& figure){
    for (size_t i = 0; i != figure.number_of_coords; i++){
        os << "(" << figure.coords[i].first << ", " << figure.coords[i].second << ")" << std::endl;
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
        x_sum += point.first;
        y_sum += point.second;
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
        double x1 = this->coords[i].first;
        double y1 = this->coords[i].second;
        double x2 = this->coords[(i + 1) % n].first;
        double y2 = this->coords[(i + 1) % n].second;
        s += x1 * y2 - x2 * y1;
    }

    return std::abs(s) / 2.0;
}

template <typename T> Figure<T>& Figure<T>::operator=(const Figure<T>& other){
    if (this != &other){
        this->coords = other.coords;
        this->number_of_coords = other.number_of_coords;
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

template <typename T> const std::string Figure<T>::who_am_i() const{
    return "Default figure";
}

template <typename T> bool Figure<T>::operator==(const Figure<T>& other) const{
    return this->coords == other.coords;
}

template <typename T> bool Figure<T>::is_valid() const{
    return this->number_of_coords >= 0;
}