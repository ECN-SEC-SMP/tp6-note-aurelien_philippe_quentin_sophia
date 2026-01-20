#pragma once

#include <vector>
#include "Cercle.hpp"   

class Case {
public:
    Case();
    bool testerCercles(const Cercle& cercle);
    bool ajouterCercle(const Cercle& cercle);

private:
    std::vector<Cercle> cercles;
};
