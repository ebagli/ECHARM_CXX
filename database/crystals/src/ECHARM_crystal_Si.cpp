//
//  ECHARM_crystal_Si.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Si_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Si::ECHARM_crystal_Si(){
    
    SetAtomName("Si");

    ECHARM_atom_xray *atom_xray = new ECHARM_atom_xray("Si",14.,28.086 * amu,640.,173.);
    atom_xray->SetThermalVibrationConstant(0.075 * AA);
    ECHARM_lattice_diamond *lattice_diamond = new ECHARM_lattice_diamond();
    AddBase(atom_xray,lattice_diamond);
    
    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    fCell = new ECHARM_cell(5.43*AA,5.43*AA,5.43*AA);

    ComputeParameters();

    SetThermalVibrationConstant(0.075 * AA);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Si::~ECHARM_crystal_Si(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
