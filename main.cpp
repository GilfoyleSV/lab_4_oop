#include "figure.h"
#include "array.h"
#include "pentagon.h"
#include "hexagon.h"
#include "octangle.h"
#include "point.h"
#include <iostream>
#include <memory>
#include <sstream>

int main() {
    Point<double> center(0.0, 0.0);
    
    std::shared_ptr<Pentagon<double>> pent_ptr = std::make_shared<Pentagon<double>>(center, 4.0);
    std::shared_ptr<Hexagon<double>>  hex_ptr  = std::make_shared<Hexagon<double>>(center, 2.0);
    std::shared_ptr<Octagon<double>>  oct_ptr  = std::make_shared<Octagon<double>>(center, 3.0);

    Array<Figure<double>> arr;
    arr.add_figure(pent_ptr);
    arr.add_figure(hex_ptr);
    arr.add_figure(oct_ptr);

    std::cout << "Initial figures info:\n";
    arr.print_info();
    std::cout << "Total area: " << arr.total_area() << "\n\n";

    arr.remove_figure(1);
    std::cout << "After removing figure 2:\n";
    arr.print_info();
    std::cout << "Total area: " << arr.total_area() << "\n\n";

    std::istringstream iss("0.0 0.0 4.0");
    Pentagon<double> read_fig;

    iss >> read_fig;
    std::cout << "Read figure (from stream):\n";
    std::cout << read_fig;
    std::cout << "Area: " << double(read_fig) << "\n";

    return 0;
}