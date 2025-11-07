#include "figure.h"

template <typename T>
class Five_Side : public Figure<T> {
    public:
    Five_Side() : Figure(5) {} 
    Five_Side(std::vector<std::unique_ptr<Point<T>>>& coords); 

    const std::string who_am_i() const override;
    bool is_valid() const override; 
    ~Five_Side() override = default;
};