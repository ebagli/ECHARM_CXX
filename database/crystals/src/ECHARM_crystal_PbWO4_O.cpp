//
//  ECHARM_crystal_PbWO4_O.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_PbWO4_O_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_PbWO4_O.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_orto.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_PbWO4_O::ECHARM_crystal_PbWO4_O(){
    
    SetAtomName("PbWO4_O");
    
    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,237.,96.0);
    atomO->SetThermalVibrationConstant(0.05 * AA);

    ECHARM_lattice *latticeO = new ECHARM_lattice();
    latticeO->Add(0.2342,0.1084,0.0408);
    latticeO->Add(0.7342,0.6084,0.5408);
    latticeO->Add(0.3584,0.5158,0.7092);
    latticeO->Add(0.6416,0.4842,0.2908);
    latticeO->Add(0.7342,0.1084,0.4592);
    latticeO->Add(0.2342,0.6084,0.9592);
    latticeO->Add(0.2658,0.8916,0.5408);
    latticeO->Add(0.7658,0.3916,0.0408);
    latticeO->Add(0.7658,0.8916,0.9592);
    latticeO->Add(0.2658,0.3916,0.4592);
    latticeO->Add(0.6416,0.9842,0.7092);
    latticeO->Add(0.1416,0.9842,0.7908);
    latticeO->Add(0.3584,0.0158,0.2908);
    latticeO->Add(0.1416,0.4842,0.2092);
    latticeO->Add(0.8584,0.0158,0.2092);
    latticeO->Add(0.8584,0.5158,0.7908);
    
    AddBase(atomO,latticeO);
    
    fCell = new ECHARM_cell(5.432E-10,5.432E-10,12.048E-10,90.,90.,90.);

    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller_orto(vMillerX,vMillerY,vMillerZ);

    SetThermalVibrationConstant(0.05 * AA);
    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_PbWO4_O::~ECHARM_crystal_PbWO4_O(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
