#include "metropolisHastingsMonteCarlo.hpp"

metropolisHastingsMonteCarlo::metropolisHastingsMonteCarlo(/* args */)
{
}
metropolisHastingsMonteCarlo::metropolisHastingsMonteCarlo(double g_in, double m2_in, double max_step_in, int therm_steps_in, int sim_steps_in, std::vector<int> &lattice_dims_in) : g(g_in), m2(m2_in), max_step(max_step_in), stepDistribution(-max_step_in, max_step), nAccepts(0), nRejects(0), simulationSteps(sim_steps_in), thermalizationSteps(therm_steps_in), latticeDims(lattice_dims_in)
{
    std::random_device r;
    rng.seed(r());
    SimulationLattice = std::unique_ptr<lattice>(new lattice(latticeDims));
    fillLatticeWithRandom(*SimulationLattice, rng, stepDistribution);
    lattice_created = true;
}
metropolisHastingsMonteCarlo::~metropolisHastingsMonteCarlo()
{
}
void metropolisHastingsMonteCarlo::printObservableAverages()
{
    for (auto &x : observables)
    {
        std::cout << x->averageData() << std::endl;
    }
}
void metropolisHastingsMonteCarlo::runSimulation()
{
    int totalSteps = thermalizationSteps + simulationSteps;
    int step = 0;
    if (!lattice_created)
    {
        SimulationLattice = std::unique_ptr<lattice>(new lattice(latticeDims));
        fillLatticeWithRandom(*SimulationLattice, rng, stepDistribution);
    }
    if (!lattice_thermalized)
    {
        for (; step < thermalizationSteps; step++)
        {
            for (int i = 0; i < SimulationLattice->getNumSites(); i++)
                updateSite(*SimulationLattice, lagrangian, rng, stepDistribution, max_step, m2, g, i);
            for (auto &obs : observables)
            {
                if (obs->shouldCollect(step))
                {
                    obs->collectData(*SimulationLattice);
                }
            }
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
        for (auto &obs : observables)
        {
            if (obs->shouldCollect(step))
            {
                obs->collectData(*SimulationLattice);
            }
        }
    }
}