//
//  ECHARM_crystal_YVO4.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_YVO4_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_YVO4.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_orto.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_YVO4::ECHARM_crystal_YVO4(){
    
    SetAtomName("YVO4");
    
    ECHARM_atom_xray *atomY = new ECHARM_atom_xray("Y",39.,88.90585 * amu,375.,400.);
    ECHARM_atom_xray *atomV = new ECHARM_atom_xray("V",23.,50.9415 * amu,249.,400.);
    ECHARM_atom_xray *atomO = new ECHARM_atom_xray("O",8.,15.9994 * amu,237.,400.);

    ECHARM_lattice *latticeY = new ECHARM_lattice();
    latticeY->Add(0.75,0.0,0.125);
    latticeY->Add(0.25,0.0,0.875);
    latticeY->Add(0.25,0.5,0.625);
    latticeY->Add(0.75,0.5,0.375);
    AddBase(atomY,latticeY);
    
    ECHARM_lattice *latticeV = new ECHARM_lattice();
    latticeV->Add(0.75,0.0,0.625);
    latticeV->Add(0.25,0.0,0.375);
    latticeV->Add(0.25,0.5,0.125);
    latticeV->Add(0.75,0.5,0.875);
    AddBase(atomV,latticeV);
    
    ECHARM_lattice *latticeO = new ECHARM_lattice();
    latticeO->Add(0.75,0.18999,0.48);
    latticeO->Add(0.25,0.81001,0.52);
    latticeO->Add(0.75,0.81001,0.48);
    latticeO->Add(0.25,0.18999,0.52);
    latticeO->Add(0.06001,0.5,0.27);
    latticeO->Add(0.43999,0.5,0.27);
    latticeO->Add(0.43999,0.0,0.23);
    latticeO->Add(0.06001,0.0,0.23);
    latticeO->Add(0.25,0.68999,0.98);
    latticeO->Add(0.75,0.31001,0.02);
    latticeO->Add(0.25,0.31001,0.98);
    latticeO->Add(0.75,0.68999,0.02);
    latticeO->Add(0.93999,0.5,0.73);
    latticeO->Add(0.56001,0.0,0.77);
    latticeO->Add(0.56001,0.5,0.73);
    latticeO->Add(0.93999,0.0,0.77);
    AddBase(atomO,latticeO);

    fCell = new ECHARM_cell(7.126E-10*2,7.126E-10*2,6.1798E-10*2,90.,90.,90.);

    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller_orto(vMillerX,vMillerY,vMillerZ);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_YVO4::~ECHARM_crystal_YVO4(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
