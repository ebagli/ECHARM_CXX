//
//  ECHARM_crystal_Vacuum.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_crystal_Vacuum_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Vacuum.hh"
#include "ECHARM_atom_moliere.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_single.hh"

ECHARM_crystal_Vacuum::ECHARM_crystal_Vacuum(double molecule_per_cm3){
    
    SetAtomName("Vacuum");
    
    // Air = Nitrogen 78% Oxygen 22%
    ECHARM_atom_moliere *atom_N = new ECHARM_atom_moliere("N",7.,14.007 * amu,0.,82.);
    ECHARM_lattice_single *lattice_N = new ECHARM_lattice_single();

    ECHARM_atom_moliere *atom_O = new ECHARM_atom_moliere("O",8.,15.9994 * amu,0.,95.);
    ECHARM_lattice_single *lattice_O = new ECHARM_lattice_single();
    
    AddBase(atom_N,lattice_N);
    AddBase(atom_O,lattice_O);
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    if(molecule_per_cm3 == 0.) molecule_per_cm3 = 1.E-6;
    
    fCell = new ECHARM_cell(1. * centimeter, 1. * centimeter, 0.5 * centimeter / molecule_per_cm3);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Vacuum::~ECHARM_crystal_Vacuum(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif