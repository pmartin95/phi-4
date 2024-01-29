
#include <cmath>
#include <memory>
#include "action.hpp"
#include "lattice.hpp"
#include "randomUtils.hpp"
#include "observable.hpp"
#pragma once
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
    std::unique_ptr<lattice> SimulationLattice;
    std::vector<std::unique_ptr<observable>> observables;
    std::vector<int> latticeDims;
    bool lattice_created = false;
    bool lattice_thermalized = false;
    lagrangian_function lagrangian = phi4LangrangianDensityPeriodicBC;
    action_function action = phi4ActionPeriodicBC;
    double g, m2;
    int thermalizationSteps = 3000, simulationSteps = 100000;
    double max_step = 0.2;
    std::mt19937 rng;
    std::uniform_real_distribution<double> stepDistribution;

public:
    metropolisHastingsMonteCarlo(/* args */);
    metropolisHastingsMonteCarlo(double g_in, double m2_in, double max_step_in, int therm_steps_in, int sim_steps_in, std::vector<int> &lattice_dims_in);
    ~metropolisHastingsMonteCarlo();
    void runSimulation();
    void printObservableAverages();
    void addObservable(std::unique_ptr<observable> observable)
    {
        observables.push_back(std::move(observable));
    }
};
