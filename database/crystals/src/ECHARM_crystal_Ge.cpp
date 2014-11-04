//
//  ECHARM_crystal_Ge.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Ge_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Ge.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Ge::ECHARM_crystal_Ge(){
    
    SetAtomName("Ge");
    double vGeExperimentalCoefficients[12];
    
    vGeExperimentalCoefficients[0] = (9.56335/32.);
    vGeExperimentalCoefficients[1] = (7.86994/32.);
    vGeExperimentalCoefficients[2] = (7.64215/32.);
    vGeExperimentalCoefficients[3] = (3.31296/32.);
    vGeExperimentalCoefficients[4] = (2.13351/32.);
    vGeExperimentalCoefficients[5] = (1.47704/32.);
    
    vGeExperimentalCoefficients[6] = (2.21494*AA*AA);
    vGeExperimentalCoefficients[7] = (0.14284*AA*AA);
    vGeExperimentalCoefficients[8] = (3.86490*AA*AA);
    vGeExperimentalCoefficients[9] = (32.69417*AA*AA);
    vGeExperimentalCoefficients[10] = (8.94286*AA*AA);
    vGeExperimentalCoefficients[11] = (82.15827*AA*AA);
    
    ECHARM_atom_xray *atom = new ECHARM_atom_xray("Ge",32.,72.61 * amu,360.0,350.0,vGeExperimentalCoefficients);
    ECHARM_lattice_diamond *lattice = new ECHARM_lattice_diamond();
    AddBase(atom,lattice);
    
    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    fCell = new ECHARM_cell(5.6575*AA,5.6575*AA,5.6575*AA);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Ge::~ECHARM_crystal_Ge(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif