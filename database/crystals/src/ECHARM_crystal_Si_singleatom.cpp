//
//  ECHARM_crystal_Si_singleatom.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Si_singleatom_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Si_singleatom.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_single.hh"

ECHARM_crystal_Si_singleatom::ECHARM_crystal_Si_singleatom(){
    
    SetAtomName("Si");
    double vSiExperimentalCoefficients[12];
    
    vSiExperimentalCoefficients[0] = 4.94976/14.;
    vSiExperimentalCoefficients[1] = 3.25403/14.;
    vSiExperimentalCoefficients[2] = 2.84957/14.;
    vSiExperimentalCoefficients[3] = 1.66053/14.;
    vSiExperimentalCoefficients[4] = 1.22949/14.;
    vSiExperimentalCoefficients[5] = 0.05611/14.;
    
    vSiExperimentalCoefficients[6] = 2.70254*AA*AA;
    vSiExperimentalCoefficients[7] = 34.45314*AA*AA;
    vSiExperimentalCoefficients[8] = 1.24059*AA*AA;
    vSiExperimentalCoefficients[9] = 0.07201*AA*AA;
    vSiExperimentalCoefficients[10] = 84.53648*AA*AA;
    vSiExperimentalCoefficients[11] = 56.34208*AA*AA;
    
    ECHARM_atom_xray *atom_xray = new ECHARM_atom_xray("Si",14.,28.086 * amu,640.,173.,vSiExperimentalCoefficients);
    ECHARM_lattice_single *lattice_single = new ECHARM_lattice_single();
    AddBase(atom_xray,lattice_single);
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    fCell = new ECHARM_cell(5.43*AA,5.43*AA,5.43*AA);

    ComputeParameters();
    
    SetThermalVibrationConstant(0.075 * AA);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Si_singleatom::~ECHARM_crystal_Si_singleatom(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif