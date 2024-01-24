#include "lattice.hpp"
#include <gtest/gtest.h>

TEST(LatticeTest, LinearIndexAndCoordinatesConversion)
{
    std::vector<int> dimensions = {5, 5, 5}; // Example dimensions
    lattice testLattice(dimensions);

    std::vector<int> coords = {2, 3, 1}; // Test coordinates
    int linearIndex = testLattice.getLinearIndex(coords);
    std::vector<int> retrievedCoords = testLattice.getCoordinates(linearIndex);

    // Check if the original coordinates and retrieved coordinates match
    EXPECT_EQ(coords, retrievedCoords);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
