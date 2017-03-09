//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Langasite_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Langasite.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Langasite::ECHARM_crystal_Langasite(){
    
    SetAtomName("Langasite");
    
    ECHARM_atom_xray *atomSi = new ECHARM_atom_xray("Si",14.,28.086 * amu,640.,173.);
    ECHARM_atom_xray *atomO = new ECHARM_atom_xray("O",8.,15.9994 * amu,575.0,96.0);
    ECHARM_atom_xray *atomGa = new ECHARM_atom_xray("Ga",31.,69.723 * amu,240.,334.);
    ECHARM_atom_moliere *atomLa = new ECHARM_atom_moliere("La",57.,138.90547 * amu,135,472.);

    ECHARM_lattice *latticeO = new ECHARM_lattice();
    ECHARM_lattice *latticeSi = new ECHARM_lattice();
    ECHARM_lattice *latticeGa = new ECHARM_lattice();
    ECHARM_lattice *latticeLa = new ECHARM_lattice();

    latticeGa->Add(0.0,0.0,0.0);
    latticeGa->Add(0.0,0.33333,0.46821);
    latticeGa->Add(0.7653,0.0,0.5);
    latticeGa->Add(0.500005,0.166665,0.53179);
    latticeGa->Add(0.61736,0.38265,0.5);
    latticeGa->Add(0.0,0.66667,0.53179);
    latticeGa->Add(0.11735,0.11735,0.5);
    latticeGa->Add(0.5,0.5,0.0);
    latticeGa->Add(0.2653,0.5,0.5);
    latticeGa->Add(0.61736,0.38265,0.5);
    latticeGa->Add(0.500005,0.166665,0.53179);
    latticeGa->Add(0.2653,0.5,0.5);
    latticeGa->Add(0.0,0.666665,0.53179);
    latticeGa->Add(0.5,0.5,0.0);
    latticeGa->Add(0.0,0.333325,0.46821);
    latticeGa->Add(0.11736,0.88265,0.5);
    latticeGa->Add(0.5,0.83333,0.46821);
    latticeGa->Add(0.5,0.5,0.0);
    latticeGa->Add(0.5,0.83333,0.46821);
    latticeGa->Add(0.11736,0.88265,0.5);
    latticeGa->Add(0.61735,0.61735,0.5);
    latticeGa->Add(0.0,0.666665,0.53179);

    latticeLa->Add(0.41874,0.0,0.0);
    latticeLa->Add(0.790635,0.209365,0.0);
    latticeLa->Add(0.29063,0.29063,0.0);
    latticeLa->Add(0.290635,0.709365,0.0);
    latticeLa->Add(0.91874,0.5,0.0);
    latticeLa->Add(0.79063,0.79063,0.0);

    latticeO->Add(0.0,0.33333,0.803);
    latticeO->Add(0.3094,0.1558,0.68401);
    latticeO->Add(0.181055,0.040055,0.237);
    latticeO->Add(0.500005,0.166665,0.197);
    latticeO->Add(0.079,0.2326,0.31599);
    latticeO->Add(0.6116,0.0768,0.68401);
    latticeO->Add(0.8494,0.0705,0.237);
    latticeO->Add(0.0,0.66667,0.197);
    latticeO->Add(0.111595,0.423195,0.31599);
    latticeO->Add(0.349395,0.429505,0.763);
    latticeO->Add(0.579,0.2674,0.68401);
    latticeO->Add(0.46955,0.38945,0.237);
    latticeO->Add(0.96954,0.11055,0.763);
    latticeO->Add(0.500005,0.166665,0.197);
    latticeO->Add(0.80941,0.3442,0.31599);
    latticeO->Add(0.681055,0.459955,0.763);
    latticeO->Add(0.0,0.666665,0.197);
    latticeO->Add(0.0,0.333325,0.803);
    latticeO->Add(0.1116,0.5768,0.68401);
    latticeO->Add(0.3494,0.5705,0.237);
    latticeO->Add(0.5,0.83333,0.803);
    latticeO->Add(0.079,0.7674,0.68401);
    latticeO->Add(0.5,0.83333,0.803);
    latticeO->Add(0.8094,0.6558,0.68401);
    latticeO->Add(0.681055,0.540055,0.237);
    latticeO->Add(0.579,0.7326,0.31599);
    latticeO->Add(0.46954,0.61055,0.763);
    latticeO->Add(0.611595,0.923195,0.31599);
    latticeO->Add(0.849395,0.929505,0.763);
    latticeO->Add(0.96955,0.88945,0.237);
    latticeO->Add(0.0,0.666665,0.197);
    latticeO->Add(0.30941,0.8442,0.31599);
    latticeO->Add(0.181055,0.959955,0.763);

    latticeSi->Add(0.0,0.33333,0.46821);
    latticeSi->Add(0.500005,0.166665,0.53179);
    latticeSi->Add(0.0,0.66667,0.53179);
    latticeSi->Add(0.500005,0.166665,0.53179);
    latticeSi->Add(0.0,0.666665,0.53179);
    latticeSi->Add(0.0,0.333325,0.46821);
    latticeSi->Add(0.5,0.83333,0.46821);
    latticeSi->Add(0.5,0.83333,0.46821);
    latticeSi->Add(0.0,0.666665,0.53179);
    
    
    AddBase(atomO,latticeO);
    AddBase(atomSi,latticeSi);
    AddBase(atomGa,latticeGa);
    AddBase(atomLa,latticeLa);
    
    fCell = new ECHARM_cell(8.176E-10, 14.1612474027E-10, 5.108E-10,90.,90.,90.);
    
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

ECHARM_crystal_Langasite::~ECHARM_crystal_Langasite(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
