#include <iostream>
#include "lattice.hpp"
#include "randomUtils.hpp"
#include "metropolisHastingsMonteCarlo.hpp"
int main()
{
    std::vector<int> dim{20, 20};
    metropolisHastingsMonteCarlo sim(1.0 /*g_in*/, 0.1 /*m2_in*/, 0.2 /*max_step_in*/, 3000 /*therm_steps_in*/, 10000 /*sim_steps_in*/, dim /*&lattice_dims_in*/);
    sim.addObservable(std::unique_ptr<observable>(new avePhiSquare));
    sim.runSimulation();
    sim.printObservableAverages();
    return 0;
}