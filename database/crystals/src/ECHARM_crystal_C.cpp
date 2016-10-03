//
//  ECHARM_crystal_C.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_C_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_C.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_C::ECHARM_crystal_C(){
    
    SetAtomName("C");
    
    ECHARM_atom_moliere *atom = new ECHARM_atom_moliere("C",6,12.011 * amu,1550.,81.);
    // mean ionization energy found at http://physics.nist.gov/cgi-bin/Star/compos.pl?matno=006
    
    ECHARM_lattice_diamond *lattice_diamond = new ECHARM_lattice_diamond();
    AddBase(atom,lattice_diamond);
    
    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    fCell = new ECHARM_cell(3.56682*AA,3.56682*AA,3.56682*AA);

    ComputeParameters();

    //SetThermalVibrationConstant(0.075 * AA);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_C::~ECHARM_crystal_C(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
