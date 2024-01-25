#include "action.hpp"

double phi4ActionPeriodicBC(const lattice &Lattice, const double m2, const double g)
{
    double action = 0.0;
    int numSites = Lattice.getNumSites();
    for (int i = 0; i < numSites; ++i)
    {
        action += phi4LangrangianDensityPeriodicBC(Lattice, m2, g, i);
    }
    return action;
}
double phi4LangrangianDensityPeriodicBC(const lattice &Lattice, const double m2, const double g, const int index)
{
    double langrangian = 0.0;
    std::vector<int> shift(Lattice.getLatticeDimensions().size(), 0);
    double phiMain = periodicBCAccessor(Lattice, index, shift);
    double gFactor = g / 24.0;
    int dimensions = Lattice.getLatticeDimensions().size();

    for (int i = 0; i < dimensions; ++i)
    {
        shift[i] = 1;
        double phiTmp = periodicBCAccessor(Lattice, index, shift);
        double deltaPhi = phiTmp - phiMain;
        langrangian += 0.5 * deltaPhi * deltaPhi;
        shift[i] = 0;

        langrangian += 0.5 * m2 * phiMain * phiMain;
        langrangian += gFactor * phiMain * phiMain * phiMain * phiMain;
    }
    return langrangian;
}
double periodicBCAccessor(const lattice &Lattice, int ref_index, std::vector<int> shift)
{
    std::vector<int> referenceCoordinates = Lattice.getCoordinates(ref_index);
    std::vector<int> finalCoordinates(referenceCoordinates.size());
    int dimensions = Lattice.getLatticeDimensions().size();

    for (int i = 0; i < dimensions; ++i)
    {
        finalCoordinates[i] = (referenceCoordinates[i] + shift[i] + Lattice.getLatticeDimensions()[i]) % Lattice.getLatticeDimensions()[i];
    }

    int finalLinearIndex = Lattice.getLinearIndex(finalCoordinates);
    return Lattice[finalLinearIndex];
}