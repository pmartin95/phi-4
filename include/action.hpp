#include "lattice.hpp"
#include <vector>

typedef double (*action_function)(const lattice &Lattice, const double m2, const double g);
typedef double (*lagrangian_function)(const lattice &Lattice, const double m2, const double g, const int index);

#pragma once
double phi4ActionPeriodicBC(const lattice &Lattice, const double m2, const double g);
double phi4LangrangianDensityPeriodicBC(const lattice &Lattice, const double m2, const double g, const int index);
double periodicBCAccessor(const lattice &Lattice, int ref_index, std::vector<int> shift);