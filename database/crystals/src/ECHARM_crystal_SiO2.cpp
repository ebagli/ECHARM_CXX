//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_SiO2_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_SiO2.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_SiO2::ECHARM_crystal_SiO2(){
    
    SetAtomName("SiO2");

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
    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,575.0,96.0);

    ECHARM_lattice *latticeSi = new ECHARM_lattice();
    ECHARM_lattice *latticeO = new ECHARM_lattice();
    
    latticeSi->Add(0.46499,0.0,0.33331);
    latticeSi->Add(0.26749,0.2675,0.0);
    latticeSi->Add(0.767495,0.232505,0.66669);
    latticeSi->Add(0.96499,0.5,0.33331);
    latticeSi->Add(0.267495,0.732505,0.66669);
    latticeSi->Add(0.76749,0.7675,0.0);

    latticeO->Add(0.277995,0.138995,0.222);
    latticeO->Add(0.65249,0.0695,0.55533);
    latticeO->Add(0.569515,0.291495,0.88868);
    latticeO->Add(0.069505,0.208495,0.778);
    latticeO->Add(0.152495,0.430505,0.11132);
    latticeO->Add(0.777995,0.361005,0.44467);
    latticeO->Add(0.15249,0.5695,0.55533);
    latticeO->Add(0.069515,0.791495,0.88868);
    latticeO->Add(0.777995,0.638995,0.222);
    latticeO->Add(0.569505,0.708495,0.778);
    latticeO->Add(0.652495,0.930505,0.11132);
    latticeO->Add(0.277995,0.861005,0.44467);

    
    
    AddBase(atomSi,latticeSi);
    AddBase(atomO,latticeO);

    fCell = new ECHARM_cell(4.913E-10,17.0191312352E-10,5.405E-10,90.,90.,90.);
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    ComputeParameters();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_SiO2::~ECHARM_crystal_SiO2(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
