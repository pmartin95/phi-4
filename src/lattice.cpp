#include "lattice.hpp"

void lattice::calculateNumSites()
{
    numSites = 1;
    for (int size : latticeDimensions)
    {
        numSites *= size;
    }
}
lattice::lattice(/* args */)
{
}

lattice::~lattice()
{
}
lattice::lattice(const std::vector<int> &dimensions) : latticeDimensions(dimensions)
{
    calculateNumSites();
    sites.resize(numSites);
    momenta.resize(numSites);
}

int lattice::getLinearIndex(const std::vector<int> &coords) const
{
    int index = 0;
    int dimensionFactor = 1;

    for (int i = 0; i < coords.size(); ++i)
    {
        index += coords[i] * dimensionFactor;
        dimensionFactor *= latticeDimensions[i];
    }

    return index;
}
std::vector<int> lattice::getCoordinates(int linearIndex) const
{
    std::vector<int> coords(latticeDimensions.size(), 0);

    for (int i = 0; i < latticeDimensions.size(); ++i)
    {
        coords[i] = linearIndex % latticeDimensions[i];
        linearIndex /= latticeDimensions[i];
    }

    return coords;
}

// Definitions of setters
void lattice::setLatticeDimensions(const std::vector<int> &newDimensions)
{
    latticeDimensions = newDimensions;
    calculateNumSites();
    sites.resize(numSites);
    momenta.resize(numSites);
}

void lattice::setSiteValue(int index, double value)
{
    if (index >= 0 && index < sites.size())
    {
        sites[index] = value;
    }
    // Optionally handle out-of-range index
}

void lattice::setMomentumValue(int index, double value)
{
    if (index >= 0 && index < momenta.size())
    {
        momenta[index] = value;
    }
    // Optionally handle out-of-range index
}
