//
//  ECHARM_crystal_LiNbO3.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#include <cfloat>
#include <limits>
#include "ECHARM_crystal_LiNbO3.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_LiNbO3::ECHARM_crystal_LiNbO3(){
    
    SetAtomName("LiNbO3");
    
    ECHARM_atom_moliere *atomLi = new ECHARM_atom_moliere("Li",3.,6.941 * amu,575.0,42.2);
    ECHARM_atom_moliere *atomNb = new ECHARM_atom_moliere("Nb",41.,92.906 * amu,575.0,96.0);
    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",32.,72.61 * amu,575.0,255.417);

    ECHARM_lattice *latticeLi = new ECHARM_lattice();
    latticeLi->Add(0.0000,0.0000,0.2829);
    latticeLi->Add(0.6667,0.3333,0.6162);
    latticeLi->Add(0.3333,0.6667,0.9496);
    
    latticeLi->Add(0.0000,0.0000,0.7829);
    latticeLi->Add(0.6667,0.3333,0.1162);
    latticeLi->Add(0.3333,0.6667,0.4496);
    AddBase(atomLi,latticeLi);
    
    ECHARM_lattice *latticeNb = new ECHARM_lattice();
    latticeNb->Add(0.0000,0.0000,0.0000);
    latticeNb->Add(0.6667,0.3333,0.3333);
    latticeNb->Add(0.3333,0.6667,0.6667);
    
    latticeNb->Add(0.0000,0.0000,0.5000);
    latticeNb->Add(0.6667,0.3333,0.8333);
    latticeNb->Add(0.3333,0.6667,0.1667);
    AddBase(atomNb,latticeNb);
    
    ECHARM_lattice *latticeO = new ECHARM_lattice();
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
    
    fCell = new ECHARM_cell(5.1476E-10,5.1476E-10,13.8631E-10,90.,90.,120.);
    
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

ECHARM_crystal_LiNbO3::~ECHARM_crystal_LiNbO3(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......