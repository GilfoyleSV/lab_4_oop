#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "figure.h"
#include "array.h"
#include "octangle.h"
#include "point.h"
#include "hexagon.h"
#include "pentagon.h"

TEST(OctagonTest, ConstructorValid) {
    Point<double> center(0.0, 0.0);
    double radius = 5.0;

    EXPECT_NO_THROW({
        Octagon<double> oct(center, radius);
    });
}

TEST(OctagonTest, WhoAmI) {
    Point<double> center(0.0, 0.0);
    double radius = 5.0;

    Octagon<double> oct(center, radius);
    EXPECT_EQ(oct.who_am_i(), "Octagon");
}

TEST(OctagonTest, VertexCount) {
    Point<double> center(0.0, 0.0);
    double radius = 5.0;

    Octagon<double> oct(center, radius);
    EXPECT_EQ(oct.vertex_count(), 8);
}

TEST(OctagonTest, GeometricCentreWorks) {
    Point<double> center(2.0, 3.0);
    double radius = 4.0;

    Octagon<double> oct(center, radius);
    auto c = oct.geom_centre();

    EXPECT_NEAR(c.first, 2.0, 1e-6);
    EXPECT_NEAR(c.second, 3.0, 1e-6);
}

TEST(OctagonTest, AreaCalculation) {
    Point<double> center(0.0, 0.0);
    double radius = 1.0;

    Octagon<double> oct(center, radius);
    double area = double(oct);
    
    // Площадь правильного восьмиугольника с радиусом 1
    // Формула: 2 * √2 * R²
    double expected_area = 2 * std::sqrt(2) * 1.0 * 1.0;
    EXPECT_NEAR(area, expected_area, 1e-6);
}

TEST(OctagonTest, OutputStream) {
    Point<double> center(1.0, 2.0);
    double radius = 3.0;

    Octagon<double> oct(center, radius);
    std::ostringstream oss;
    oss << oct;
    std::string output = oss.str();
    
    EXPECT_TRUE(output.find("Octagon") != std::string::npos);
    EXPECT_TRUE(output.find("center") != std::string::npos);
    EXPECT_TRUE(output.find("radius") != std::string::npos);
}

TEST(OctagonTest, InputStream) {
    Octagon<double> oct;
    std::istringstream iss("1.5 2.5 3.5"); // center_x center_y radius
    
    EXPECT_NO_THROW({
        iss >> oct;
    });
}

TEST(ArrayTest, AddAndTotalAreaWithOctagons) {
    Array<Figure<double>> arr;

    auto oct1 = std::make_shared<Octagon<double>>(Point<double>(0.0, 0.0), 2.0);
    auto oct2 = std::make_shared<Octagon<double>>(Point<double>(1.0, 1.0), 3.0);

    arr.add_figure(oct1);
    arr.add_figure(oct2);

    double total_area = arr.total_area();
    EXPECT_GT(total_area, 0.0);
    
    // Проверяем, что площадь двух восьмиугольников больше площади одного
    double area1 = double(*oct1);
    double area2 = double(*oct2);
    EXPECT_NEAR(total_area, area1 + area2, 1e-6);
    
    EXPECT_NO_THROW(arr.print_info());
}

TEST(ArrayTest, RemoveFigureAndBounds) {
    Array<Figure<double>> arr;

    // Добавляем несколько восьмиугольников
    for (int i = 0; i < 5; ++i) {
        auto oct = std::make_shared<Octagon<double>>(
            Point<double>(i * 1.0, i * 1.0), i + 1.0
        );
        arr.add_figure(oct);
    }

    EXPECT_EQ(arr.size(), 5);
    
    // Удаляем фигуру по корректному индексу
    EXPECT_NO_THROW(arr.remove_figure(2));
    EXPECT_EQ(arr.size(), 4);
    
    // Пытаемся удалить по неверному индексу
    EXPECT_THROW(arr.remove_figure(10), std::out_of_range);
}

TEST(ArrayTest, MixedFigures) {
    Array<Figure<double>> arr;

    auto pent = std::make_shared<Pentagon<double>>(Point<double>(0.0, 0.0), 2.0);
    auto hex = std::make_shared<Hexagon<double>>(Point<double>(1.0, 1.0), 3.0);
    auto oct = std::make_shared<Octagon<double>>(Point<double>(2.0, 2.0), 4.0);

    arr.add_figure(pent);
    arr.add_figure(hex);
    arr.add_figure(oct);

    EXPECT_EQ(arr.size(), 3);
    
    double total_area = arr.total_area();
    EXPECT_GT(total_area, 0.0);
    
    // Проверяем, что все фигуры правильно идентифицируются
    EXPECT_NO_THROW(arr.print_info());
}

TEST(ScalarConceptTest, ArithmeticTypesAreScalar) {
    EXPECT_TRUE(Scalar<int>);
    EXPECT_TRUE(Scalar<float>);
    EXPECT_TRUE(Scalar<double>);
    EXPECT_TRUE(Scalar<long long>);
}

TEST(ScalarConceptTest, NonArithmeticTypesAreNotScalar) {
    EXPECT_FALSE(Scalar<std::string>);
    EXPECT_FALSE(Scalar<std::vector<int>>);
    EXPECT_FALSE(Scalar<Point<int>>);
}

TEST(OctagonTest, DefaultConstructor) {
    EXPECT_NO_THROW({
        Octagon<double> oct;
    });
    
    Octagon<double> oct;
    EXPECT_EQ(oct.who_am_i(), "Octagon");
    EXPECT_EQ(oct.vertex_count(), 8);
}

TEST(OctagonTest, CopyAndMoveSemantics) {
    Octagon<double> oct1(Point<double>(1.0, 2.0), 3.0);
    
    // Тест копирования
    Octagon<double> oct2 = oct1;
    EXPECT_EQ(oct2.who_am_i(), "Octagon");
    
    // Тест перемещения
    Octagon<double> oct3 = std::move(oct1);
    EXPECT_EQ(oct3.who_am_i(), "Octagon");
}