//
//  ECHARM_crystal_SiGe.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#include <cfloat>
#include <limits>
#include "ECHARM_crystal_SiGe.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_SiGe::ECHARM_crystal_SiGe(double x){
    
    SetAtomName("SiGe");
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
    
    ECHARM_atom_xray *atomSi = new ECHARM_atom_xray("Si",14.,28.086 * amu,640.,173.,vSiExperimentalCoefficients);
    ECHARM_lattice_diamond *latticeSi = new ECHARM_lattice_diamond();
    AddBase(atomSi,latticeSi,1.-x);
    
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
    
    ECHARM_atom_xray *atomGe = new ECHARM_atom_xray("Ge",32.,72.61 * amu,360.0,350.0,vGeExperimentalCoefficients);
    ECHARM_lattice_diamond *latticeGe = new ECHARM_lattice_diamond();
    AddBase(atomGe,latticeGe,x);

    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    double cell_par = (5.431 + 0.20*x + 0.027*x*x)*AA;
    fCell = new ECHARM_cell(cell_par,cell_par,cell_par);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_SiGe::~ECHARM_crystal_SiGe(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......