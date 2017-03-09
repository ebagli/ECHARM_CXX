//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_SiO2_O_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_SiO2_O.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_SiO2_O::ECHARM_crystal_SiO2_O(){
    
    SetAtomName("SiO2_O");

    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,575.0,96.0);

    ECHARM_lattice *latticeO = new ECHARM_lattice();
    
    latticeO->Add(0.277995,0.138995,0.222);
    latticeO->Add(0.65249,0.0695,0.55533);
    latticeO->Add(0.569515,0.291495,0.88868);
    latticeO->Add(0.069505,0.208495,0.778);
    latticeO->Add(0.152495,0.430505,0.11132);
    latticeO->Add(0.777995,0.361005,0.44467);
    latticeO->Add(0.15249,0.5695,0.55533);
    latticeO->Add(0.069515,0.791495,0.88868);
    latticeO->Add(0.777995,0.638995,0.222);
    latticeO->Add(0.569505,0.708495,0.778);
    latticeO->Add(0.652495,0.930505,0.11132);
    latticeO->Add(0.277995,0.861005,0.44467);

    
    
    AddBase(atomO,latticeO);

    fCell = new ECHARM_cell(4.913E-10,17.0191312352E-10,5.405E-10,90.,90.,90.);
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_SiO2_O::~ECHARM_crystal_SiO2_O(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
