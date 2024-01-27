#include "lattice.hpp"

class observable
{
protected:
    std::vector<double> collected_data;
    std::vector<double> local_data;

public:
    observable(/* args */);
    virtual ~observable() = default;
    // Define when to collect data
    virtual bool shouldCollect(int step) const = 0;

    // Collect data
    virtual void collectData(const lattice &lat) = 0;
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

private:
    static const int thermalizationSteps = 1000;
};