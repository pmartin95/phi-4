#include "metropolisHastingsMonteCarlo.hpp"

metropolisHastingsMonteCarlo::metropolisHastingsMonteCarlo(/* args */)
{
}
metropolisHastingsMonteCarlo::metropolisHastingsMonteCarlo(double g_in, double m2_in, double max_step_in) : g(g_in), m2(m2_in), max_step(max_step_in), stepDistribution(-max_step_in, max_step), nAccepts(0), nRejects(0)
{
}
metropolisHastingsMonteCarlo::~metropolisHastingsMonteCarlo()
{
}

void metropolisHastingsMonteCarlo::runSimulation()
{
    int totalSteps = thermalizationSteps + simulationSteps;
    int step = 0;
    if (!lattice_created)
        SimulationLattice = std::unique_ptr<lattice>(new lattice());
    if (!lattice_thermalized)
    {
        for (; step < thermalizationSteps; step++)
        {
            for (int i = 0; i < SimulationLattice->getNumSites(); i++)
                updateSite(*SimulationLattice, lagrangian, rng, stepDistribution, max_step, m2, g, i);
        }
    }
    else
    {
        step = thermalizationSteps;
    }

    for (; step < totalSteps; step++)
    {
        for (int i = 0; i < SimulationLattice->getNumSites(); i++)
            updateSite(*SimulationLattice, lagrangian, rng, stepDistribution, max_step, m2, g, i);
    }
}