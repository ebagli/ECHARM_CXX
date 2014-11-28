//
//  ECHARM_crystal_Si_Defect.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Si_Defect_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Si_Defect.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Si_Defect::ECHARM_crystal_Si_Defect(double defect_density){
    
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
    
    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    fCell = new ECHARM_cell(5.43*AA,5.43*AA,5.43*AA);

    ECHARM_lattice_diamond *lattice_diamond = new ECHARM_lattice_diamond();
    
    double percentage = defect_density / (lattice_diamond->GetCoordinatesNumber() / fCell->GetVolume());
        
    ECHARM_atom_xray *atom_xray = new ECHARM_atom_xray("Si",14.,28.086 * amu,640.,173.,vSiExperimentalCoefficients);
    ECHARM_atom_moliere *vacuum = new ECHARM_atom_moliere("vacuum",0.,0. * amu,640.,173.);
    
    AddBase(atom_xray,lattice_diamond,1.-percentage);
    AddBase(vacuum,lattice_diamond,percentage);
    
    //atoms per cm3 is = (1 cm3 * #atoms_in_the_cell / #cell_volume[cm^3])

    
    ComputeParameters();
    
    SetThermalVibrationConstant(0.075);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_Si_Defect::~ECHARM_crystal_Si_Defect(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif