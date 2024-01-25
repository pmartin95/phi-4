#include <vector>

#pragma once
class lattice
{
private:
    /* data */
    std::vector<int> latticeDimensions;
    std::vector<double> sites;
    std::vector<double> momenta; // This will act as auxilliary momenta for hybrid monte carlo
    int numSites;

    void calculateNumSites();

public:
    lattice(/* args */);
    lattice(const std::vector<int> &dimensions);
    // Copy constructor
    lattice(const lattice &other)
        : latticeDimensions(other.latticeDimensions), sites(other.sites),
          momenta(other.momenta), numSites(other.numSites) {}
    // Move constructor
    lattice(lattice &&other) noexcept
        : latticeDimensions(std::move(other.latticeDimensions)), sites(std::move(other.sites)),
          momenta(std::move(other.momenta)), numSites(other.numSites) {}

    ~lattice();
    // Copy assignment operator
    lattice &operator=(const lattice &other)
    {
        if (this != &other)
        {
            lattice temp(other);
            std::swap(*this, temp);
        }
        return *this;
    }
    // Move assignment operator
    lattice &operator=(lattice &&other) noexcept
    {
        if (this != &other)
        {
            latticeDimensions = std::move(other.latticeDimensions);
            sites = std::move(other.sites);
            momenta = std::move(other.momenta);
            numSites = other.numSites;
        }
        return *this;
    }

    // Overloaded [] operator to access elements of 'sites'
    double &operator[](int index) { return sites.at(index); }             // For non-const objects
    const double &operator[](int index) const { return sites.at(index); } // For const objects

    int getLinearIndex(const std::vector<int> &coords) const;
    std::vector<int> getCoordinates(int linearIndex) const;

    // Getters
    const std::vector<int> &getLatticeDimensions() const { return latticeDimensions; }
    double getSiteValue(int index) const { return sites.at(index); }       // throws std::out_of_range for invalid index
    double getMomentumValue(int index) const { return momenta.at(index); } // throws std::out_of_range for invalid index
    int getNumSites() const { return numSites; }

    // Setters
    void setLatticeDimensions(const std::vector<int> &newDimensions);
    void setSiteValue(int index, double value);
    void setMomentumValue(int index, double value);

    // Calculations
    double calcAvePhiSquare() const;
};
