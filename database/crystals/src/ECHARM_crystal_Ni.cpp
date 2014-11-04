//
//  ECHARM_crystal_Ni.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Ni_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Ni.hh"
#include "ECHARM_atom_moliere.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_fcc.hh"

ECHARM_crystal_Ni::ECHARM_crystal_Ni(){
    
    SetAtomName("Ni");
    
    ECHARM_atom_moliere *atom = new ECHARM_atom_moliere("Ni",28.,58.6934 * amu,375.,321.);

    ECHARM_lattice_fcc *lattice = new ECHARM_lattice_fcc();
    AddBase(atom,lattice);
    
    int vMillerX[3] = {2,0,0};
    int vMillerY[3] = {0,2,0};
    int vMillerZ[3] = {2,0,2};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    fCell = new ECHARM_cell(3.520*AA,3.520*AA,3.520*AA);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Ni::~ECHARM_crystal_Ni(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif