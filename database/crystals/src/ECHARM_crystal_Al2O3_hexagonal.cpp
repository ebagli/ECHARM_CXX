//
//  ECHARM_crystal_Al2O3_hexagonal.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Al2O3_hexagonal_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Al2O3_hexagonal.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Al2O3_hexagonal::ECHARM_crystal_Al2O3_hexagonal(){
    
    SetAtomName("Al2O3_hex");
    
    ECHARM_atom_moliere *atomAl = new ECHARM_atom_moliere("Al",13.,26.981539 * amu,980.0,145.2);
    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,980.0,145.2);
    
    ECHARM_lattice *latticeAl = new ECHARM_lattice();
    ECHARM_lattice *latticeO = new ECHARM_lattice();

    latticeAl->Add(0.0000,0.0000,0.2829);
    latticeAl->Add(0.6667,0.3333,0.6162);
    latticeAl->Add(0.3333,0.6667,0.9496);
    latticeAl->Add(0.0000,0.0000,0.7829);
    latticeAl->Add(0.6667,0.3333,0.1162);
    latticeAl->Add(0.3333,0.6667,0.4496);
    latticeAl->Add(0.0000,0.0000,0.0000);
    latticeAl->Add(0.6667,0.3333,0.3333);
    latticeAl->Add(0.3333,0.6667,0.6667);
    latticeAl->Add(0.0000,0.0000,0.5000);
    latticeAl->Add(0.6667,0.3333,0.8333);
    latticeAl->Add(0.3333,0.6667,0.1667);
    AddBase(atomAl,latticeAl);
    
    latticeO->Add(0.0492,0.3446,0.0647);
    latticeO->Add(0.7159,0.6779,0.3980);
    latticeO->Add(0.3825,0.0113,0.7314);
    latticeO->Add(0.6554,0.7046,0.0647);
    latticeO->Add(0.3221,0.0379,0.3980);
    latticeO->Add(0.9887,0.3713,0.7314);
    latticeO->Add(0.2954,0.9508,0.0647);
    latticeO->Add(0.9621,0.2841,0.3980);
    latticeO->Add(0.6287,0.6175,0.7314);
    latticeO->Add(0.6554,0.9508,0.5647);
    latticeO->Add(0.3221,0.2841,0.8980);
    latticeO->Add(0.9887,0.6175,0.2314);
    latticeO->Add(0.2954,0.3446,0.5647);
    latticeO->Add(0.9621,0.6779,0.8980);
    latticeO->Add(0.6287,0.0113,0.2314);
    latticeO->Add(0.0492,0.7046,0.5647);
    latticeO->Add(0.7159,0.0379,0.8980);
    latticeO->Add(0.3825,0.3713,0.2314);
    AddBase(atomO,latticeO);
    
    fCell = new ECHARM_cell(4.7554E-10,4.7554E-10,12.991E-10,90.,90.,120.);
    
    int vMillerX[3] = {3,0,0};
    int vMillerY[3] = {0,3,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Al2O3_hexagonal::~ECHARM_crystal_Al2O3_hexagonal(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
