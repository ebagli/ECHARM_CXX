//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Al2O3_Al_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Al2O3_Al.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Al2O3_Al::ECHARM_crystal_Al2O3_Al(){
    
    SetAtomName("Al2O3");

    ECHARM_atom_moliere *atomAl = new ECHARM_atom_moliere("Al",13.,26.981539 * amu,980.0,145.2);

    ECHARM_lattice *latticeAl = new ECHARM_lattice();

    latticeAl->Add(0.0,0.0,0.352);
    latticeAl->Add(0.0,0.0,0.148);
    latticeAl->Add(0.0,0.0,0.648);
    latticeAl->Add(0.0,0.0,0.852);
    latticeAl->Add(0.500005,0.166665,0.68533);
    latticeAl->Add(0.500005,0.166665,0.48133);
    latticeAl->Add(0.500005,0.166665,0.98133);
    latticeAl->Add(0.500005,0.166665,0.18533);
    latticeAl->Add(1.0,0.333335,0.01867);
    latticeAl->Add(1.0,0.333335,0.81467);
    latticeAl->Add(1.0,0.333335,0.31467);
    latticeAl->Add(1.0,0.333335,0.51867);
    latticeAl->Add(0.0,0.666665,0.68533);
    latticeAl->Add(0.0,0.666665,0.48133);
    latticeAl->Add(0.0,0.666665,0.98133);
    latticeAl->Add(0.0,0.666665,0.18533);
    latticeAl->Add(0.5,0.5,0.352);
    latticeAl->Add(0.5,0.5,0.148);
    latticeAl->Add(0.5,0.5,0.648);
    latticeAl->Add(0.5,0.5,0.852);
    latticeAl->Add(0.499995,0.833335,0.01867);
    latticeAl->Add(0.499995,0.833335,0.81467);
    latticeAl->Add(0.499995,0.833335,0.31467);
    latticeAl->Add(0.499995,0.833335,0.51867);
  
    
    AddBase(atomAl,latticeAl);
    
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

ECHARM_crystal_Al2O3_Al::~ECHARM_crystal_Al2O3_Al(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
