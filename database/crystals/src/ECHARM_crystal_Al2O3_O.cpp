//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Al2O3_O_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Al2O3_O.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Al2O3_O::ECHARM_crystal_Al2O3_O(){
    
    SetAtomName("Al2O3_O");

    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,575.0,96.0);

    ECHARM_lattice *latticeO = new ECHARM_lattice();
    
    latticeO->Add(0.3063,0.0,0.25);
    latticeO->Add(0.34685,0.34685,0.25);
    latticeO->Add(0.6937,0.0,0.75);
    latticeO->Add(0.15315,0.15315,0.75);
    latticeO->Add(0.806305,0.166665,0.58333);
    latticeO->Add(0.346855,0.319815,0.58333);
    latticeO->Add(0.346855,0.013515,0.58333);
    latticeO->Add(0.193705,0.166665,0.08333);
    latticeO->Add(0.653155,0.013515,0.08333);
    latticeO->Add(0.653155,0.319815,0.08333);
    latticeO->Add(0.306295,0.333335,0.91667);
    latticeO->Add(0.153145,0.180185,0.41667);
    latticeO->Add(0.153145,0.486485,0.41667);
    latticeO->Add(0.84685,0.15315,0.25);
    latticeO->Add(0.65315,0.34685,0.75);
    latticeO->Add(0.846845,0.486485,0.91667);
    latticeO->Add(0.846845,0.180185,0.91667);
    latticeO->Add(0.693695,0.333335,0.41667);
    latticeO->Add(0.1937,0.5,0.75);
    latticeO->Add(0.306305,0.666665,0.58333);
    latticeO->Add(0.153155,0.513515,0.08333);
    latticeO->Add(0.153155,0.819815,0.08333);
    latticeO->Add(0.8063,0.5,0.25);
    latticeO->Add(0.34685,0.65315,0.25);
    latticeO->Add(0.84685,0.84685,0.25);
    latticeO->Add(0.15315,0.84685,0.75);
    latticeO->Add(0.65315,0.65315,0.75);
    latticeO->Add(0.846855,0.819815,0.58333);
    latticeO->Add(0.846855,0.513515,0.58333);
    latticeO->Add(0.693705,0.666665,0.08333);
    latticeO->Add(0.806295,0.833335,0.91667);
    latticeO->Add(0.346845,0.986485,0.91667);
    latticeO->Add(0.346845,0.680185,0.91667);
    latticeO->Add(0.193695,0.833335,0.41667);
    latticeO->Add(0.653145,0.680185,0.41667);
    latticeO->Add(0.653145,0.986485,0.41667);

    AddBase(atomO,latticeO);
    
    fCell = new ECHARM_cell(4.7554E-10,8.23659441031E-10,12.991E-10,90.,90.,90.);
    
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

ECHARM_crystal_Al2O3_O::~ECHARM_crystal_Al2O3_O(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
