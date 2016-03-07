//
//  ECHARM_crystal_PbWO4.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_PbWO4_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_PbWO4.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_orto.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_PbWO4::ECHARM_crystal_PbWO4(){
    
    SetAtomName("LiNbO3");
    
    ECHARM_atom_moliere *atomPb = new ECHARM_atom_moliere("Pb",82.,207.2 * amu,787.,42.2);
    ECHARM_atom_moliere *atomW = new ECHARM_atom_moliere("W",74.,183.84 * amu,735.,417.0);
    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,237.,96.0);

    ECHARM_lattice *latticePb = new ECHARM_lattice();
    latticePb->Add(0.0000,0.2500,0.6250);
    latticePb->Add(0.5000,0.7500,0.1250);
    latticePb->Add(0.5000,0.2500,0.8750);
    latticePb->Add(0.0000,0.7500,0.3750);
    
    AddBase(atomPb,latticePb);
    
    ECHARM_lattice *latticeW = new ECHARM_lattice();
    latticeW->Add(0.5000,0.7500,0.6250);
    latticeW->Add(0.5000,0.2500,0.3750);
    latticeW->Add(0.0000,0.2500,0.1250);
    latticeW->Add(0.0000,0.7500,0.8750);

    AddBase(atomW,latticeW);
    
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

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_PbWO4::~ECHARM_crystal_PbWO4(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif