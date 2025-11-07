#ifndef OCTANGLE_H
#define OCTANGLE_H

#include "figure.h"
#include <vector>

template <typename T>
class Octangle : public Figure<T> {
public:
    Octangle() : Figure(8) {} 
    Octangle(std::vector<std::unique_ptr<Point<T>>>& coords); 

    const std::string who_am_i() const override;
    bool is_valid() const override; 
    ~Octangle() override = default;
};


#endif