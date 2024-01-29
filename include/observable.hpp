#include "lattice.hpp"
#include <string>
#pragma once
class observable
{
protected:
    std::vector<double> collected_data;
    std::vector<double> local_data;

public:
    inline observable(/* args */);
    virtual ~observable() = default;
    // Define when to collect data
    virtual bool shouldCollect(int step) const = 0;

    // Collect data
    virtual void collectData(const lattice &lat) = 0;
    // Return data
    virtual double averageData() = 0;
};

observable::observable(/* args */)
{
}

class avePhiSquare : public observable
{

public:
    bool shouldCollect(int step) const override
    {
        return (step > thermalizationSteps) && (step % 100 == 0);
    }

    void collectData(const lattice &lat) override
    {
        double phiSquare = 0.0;
        int numLatticeSites = lat.getNumSites();
        lat.forEachSite([&phiSquare](double x)
                        { phiSquare += x * x; });
        collected_data.push_back(phiSquare / numLatticeSites);
    }
    double averageData() override
    {
        double buffer = 0.0;
        for (auto &x : collected_data)
        {
            buffer += x;
        }
        return buffer / collected_data.size();
    }

private:
    static const int thermalizationSteps = 3000;
};