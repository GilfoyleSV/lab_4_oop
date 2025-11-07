#include "figure.h"
#include "array.h"
#include "pentagon.h"
#include "hexagon.h"
#include "octangle.h"
#include "point.h"
#include <iostream>
#include <memory>
#include <sstream>

std::vector<std::unique_ptr<Point<double>>> create_points_vector(
    const std::vector<std::pair<double, double>>& coords) 
{
    std::vector<std::unique_ptr<Point<double>>> points;
    points.reserve(coords.size());
    for (const auto& [x, y] : coords) {
        points.push_back(std::make_unique<Point<double>>(x, y));
    }
    return points;
}

int main() {
    std::vector<std::pair<double, double>> pent_coords{
        {0.0, 4.0}, {-3.0, 1.0}, {-2.0, -3.0}, {2.0, -3.0}, {3.0, 1.0}
    };
    std::vector<std::pair<double, double>> hex_coords{
        {0.0, 2.0}, {-2.0, 1.0}, {-2.0, -1.0}, {0.0, -2.0}, {2.0, -1.0}, {2.0, 1.0}
    };
    std::vector<std::pair<double, double>> oct_coords{
        {1.0, 3.0}, {3.0, 1.0}, {3.0, -1.0}, {1.0, -3.0},
        {-1.0, -3.0}, {-3.0, -1.0}, {-3.0, 1.0}, {-1.0, 3.0}
    };

    auto pent_points = create_points_vector(pent_coords);
    auto hex_points  = create_points_vector(hex_coords);
    auto oct_points  = create_points_vector(oct_coords);

    std::shared_ptr<Pentagon<double>> pent_ptr = std::make_shared<Pentagon<double>>(pent_points);
    std::shared_ptr<Hexagon<double>>  hex_ptr  = std::make_shared<Hexagon<double>>(hex_points);
    std::shared_ptr<Octangle<double>> oct_ptr  = std::make_shared<Octangle<double>>(oct_points);

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

    std::istringstream iss("0 4 -3 1 -2 -3 2 -3 3 1");
    Pentagon<double> read_fig;

    iss >> read_fig;
    std::cout << "Read figure (from stream):\n";
    std::cout << read_fig;
    std::cout << "Area: " << double(read_fig) << "\n";

    return 0;
}
