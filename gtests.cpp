#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "figure.h"
#include "array.h"
#include "octangle.h"
#include "point.h"


TEST(OctangleTest, ConstructorValid) {
    std::vector<std::unique_ptr<Point<double>>> coords;
    for (int i = 0; i < 8; ++i)
        coords.push_back(std::make_unique<Point<double>>(i, i+1));

    EXPECT_NO_THROW({
        Octangle<double> oct(coords);
    });
}

TEST(OctangleTest, ConstructorInvalidThrows) {
    std::vector<std::unique_ptr<Point<double>>> coords;
    for (int i = 0; i < 5; ++i)
        coords.push_back(std::make_unique<Point<double>>(i, i+1));

    EXPECT_THROW({
        Octangle<double> oct(coords);
    }, std::invalid_argument);
}

TEST(OctangleTest, WhoAmI) {
    std::vector<std::unique_ptr<Point<double>>> coords;
    for (int i = 0; i < 8; ++i)
        coords.push_back(std::make_unique<Point<double>>(i, i+1));

    Octangle<double> oct(coords);
    EXPECT_EQ(oct.who_am_i(), "Octangle");
}

TEST(OctangleTest, GeometricCentreWorks) {
    std::vector<std::unique_ptr<Point<double>>> coords;
    coords.push_back(std::make_unique<Point<double>>(0, 0));
    coords.push_back(std::make_unique<Point<double>>(1, 0));
    coords.push_back(std::make_unique<Point<double>>(1, 1));
    coords.push_back(std::make_unique<Point<double>>(0, 1));
    coords.push_back(std::make_unique<Point<double>>(2, 1));
    coords.push_back(std::make_unique<Point<double>>(2, 2));
    coords.push_back(std::make_unique<Point<double>>(1, 2));
    coords.push_back(std::make_unique<Point<double>>(0, 2));

    Octangle<double> oct(coords);
    auto c = oct.geom_centre();

    EXPECT_NEAR(c.first, 0.875, 1e-6);
    EXPECT_NEAR(c.second, 1.125, 1e-6);
}

TEST(OctangleTest, OutputStream) {
    std::vector<std::unique_ptr<Point<double>>> coords;
    for (int i = 0; i < 8; ++i)
        coords.push_back(std::make_unique<Point<double>>(i, i));

    Octangle<double> oct(coords);
    std::ostringstream oss;
    oss << oct;
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Octangle") != std::string::npos);
    EXPECT_TRUE(output.find("points") != std::string::npos);
}


TEST(ArrayTest, AddAndTotalAreaWithOctangles) {
    Array<Figure<double>> arr;

    std::vector<std::unique_ptr<Point<double>>> coords1;
    for (int i = 0; i < 8; ++i)
        coords1.push_back(std::make_unique<Point<double>>(i, i+1));
    auto oct1 = std::make_shared<Octangle<double>>(coords1);

    std::vector<std::unique_ptr<Point<double>>> coords2;
    for (int i = 0; i < 8; ++i)
        coords2.push_back(std::make_unique<Point<double>>(i*2, i*2+1));
    auto oct2 = std::make_shared<Octangle<double>>(coords2);

    arr.add_figure(oct1);
    arr.add_figure(oct2);

    EXPECT_GE(arr.total_area(), 0.0);
    EXPECT_NO_THROW(arr.print_info());
}

TEST(ArrayTest, RemoveFigureAndGrow) {
    Array<Figure<double>> arr;

    for (int n = 0; n < 12; ++n) {
        std::vector<std::unique_ptr<Point<double>>> coords;
        for (int i = 0; i < 8; ++i)
            coords.push_back(std::make_unique<Point<double>>(i, i+1));
        arr.add_figure(std::make_shared<Octangle<double>>(coords));
    }

    EXPECT_NO_THROW(arr.remove_figure(5));
    EXPECT_THROW(arr.remove_figure(100), std::out_of_range);
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