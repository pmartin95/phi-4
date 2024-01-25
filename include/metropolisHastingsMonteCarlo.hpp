#pragma once
#include <cmath>
#include "action.hpp"
#include "lattice.hpp"
#include "randomUtils.hpp"

template <typename RNG, typename Distribution>
int updateSite(lattice &Lattice, lagrangian_function L_func, RNG &rng, Distribution &dist, const double max_step, const double m2, const double g, int site_index)
{
    double holder = Lattice[site_index];
    double Lagrangian_initial = L_func(Lattice, m2, g, site_index);
    Lattice[site_index] += std::min(max_step, dist(rng));
    double Lagrangian_new = L_func(Lattice, m2, g, site_index);
    std::uniform_real_distribution<double> real_dist(0.0, 1.0);
    if (std::min(std::exp(-(Lagrangian_new - Lagrangian_initial)), 1.0) < real_dist(rng))
    {
        Lattice[site_index] = holder;
        return 0;
    }
    else
    {
        return 1;
    }
}

class metropolisHastingsMonteCarlo
{
private:
    int nAccepts, nRejects;
    lagrangian_function lagrangian = phi4LangrangianDensityPeriodicBC;
    action_function action = phi4ActionPeriodicBC;
    double g, m2;

public:
    metropolisHastingsMonteCarlo(/* args */);
    ~metropolisHastingsMonteCarlo();
};
