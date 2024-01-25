#include <random> // https://cplusplus.com/reference/random/
#include "lattice.hpp"
#include <iostream>

#pragma once

template <typename RNG, typename Distribution>
void fillLatticeWithRandom(lattice &lat, RNG &rng, Distribution &dist)
{
    for (int i = 0; i < lat.getNumSites(); ++i)
    {
        double randomValue = dist(rng);
        lat.setSiteValue(i, randomValue);
    }
}

template <typename RNG, typename Distribution>
void fillMomentaWithRandom(lattice &lat, RNG &rng, Distribution &dist)
{
    for (int i = 0; i < lat.getNumSites(); ++i)
    {
        double randomValue = dist(rng);
        lat.setMomentumValue(i, randomValue);
    }
}