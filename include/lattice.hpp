#include <vector>

#pragma once
class lattice
{
private:
    /* data */
    std::vector<int> latticeDimensions;
    std::vector<double> sites;
    std::vector<double> momenta;
    int numSites;

    void calculateNumSites();

public:
    lattice(/* args */);
    lattice(const std::vector<int> &dimensions);
    ~lattice();

    int getLinearIndex(const std::vector<int> &coords) const;
    std::vector<int> getCoordinates(int linearIndex) const;
};
