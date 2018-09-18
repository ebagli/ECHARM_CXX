//
//  ECHARM_crystal_Y.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Y_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Y.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_orto.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Y::ECHARM_crystal_Y(){
    
    SetAtomName("Y");
    
    ECHARM_atom_xray *atomY = new ECHARM_atom_xray("Y",39.,88.90585 * amu,375.,214.);

    ECHARM_lattice *latticeY = new ECHARM_lattice();
    latticeY->Add(0.5,1./6.,0.75);
    latticeY->Add(1.0,1./3.,0.25);
    latticeY->Add(0.5,5./6.,0.25);
    latticeY->Add(1.0,2./3.,0.75);
    latticeY->Add(1.0,1./3.,0.25);
    latticeY->Add(0.5,1./6.,0.75);
    latticeY->Add(0.5,5./6.,0.25);
    latticeY->Add(1.0,2./3.,0.75);
    latticeY->Add(0.5,1./6.,0.75);
    latticeY->Add(1.0,1./3.,0.25);
    latticeY->Add(0.5,5./6.,0.25);
    latticeY->Add(1.0,2./3.,0.75);
    latticeY->Add(0.5,5./6.,0.25);
    latticeY->Add(1.0,2./3.,0.75);
    latticeY->Add(0.5,1./6.,0.75);
    latticeY->Add(1.0,1./3.,0.25);
    AddBase(atomY,latticeY);

    fCell = new ECHARM_cell(3.663E-10,6.34450210812E-10,5.815E-10,90.,90.,90.);

    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller_orto(vMillerX,vMillerY,vMillerZ);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Y::~ECHARM_crystal_Y(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
