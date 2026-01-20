#include "Case.hpp"
#include "Cercle.hpp"
#include <iostream>

Case::Case() = default;

bool Case::testerCercles(const Cercle& cercle){
    return !(std::find(cercles.begin(), cercles.end(), cercle) != cercles.end());
}

bool Case::ajouterCercle(const Cercle& cercle) {
    if (testerCercles(cercle)) {
        cercles.push_back(cercle);
    }
}
