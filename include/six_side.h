#include "figure.h"

template <typename T>
class Six_Side : public Figure<T> {
    public:
    Six_Side() : Figure(6) {} 
    Six_Side(std::vector<std::unique_ptr<Point<T>>>& coords); 

    const std::string who_am_i() const override;
    bool is_valid() const override; 
    ~Six_Side() override = default;
};