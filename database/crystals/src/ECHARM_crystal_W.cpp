//
//  ECHARM_crystal_W.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_W_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_W.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_orto.hh"
#include "ECHARM_lattice_bcc.hh"

ECHARM_crystal_W::ECHARM_crystal_W(){
    
    SetAtomName("W");
    
    ECHARM_atom_moliere *atomW = new ECHARM_atom_moliere("W",74.,183.84 * amu,735.,417.0);
    ECHARM_lattice_bcc *latticeW = new ECHARM_lattice_bcc();
    AddBase(atomW,latticeW);
 

    int vMillerX[3] = {1,-1,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY,vMillerZ);
    fCell = new ECHARM_cell(3.1652*AA,3.1652*AA,3.1652*AA);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_W::~ECHARM_crystal_W(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
