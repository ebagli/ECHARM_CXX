//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_Bi4Ge3O12_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_Bi4Ge3O12.hh"
#include "ECHARM_miller.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_Bi4Ge3O12::ECHARM_crystal_Bi4Ge3O12(){
    
    SetAtomName("Bi4Ge3O12");

    ECHARM_atom_moliere *atomBi4Ge3O12 = new ECHARM_atom_moliere("Bi4Ge3O12",13.6,29.56904 * amu,575.0,149.44);
    ECHARM_lattice *latticeBi4Ge3O12 = new ECHARM_lattice();
    latticeBi4Ge3O12->Add(0.5,0.5,0.5);

    AddBase(atomBi4Ge3O12,latticeBi4Ge3O12);
    
    fCell = new ECHARM_cell(1.485984E-10,1.485984E-10,1.485984E-10,90.,90.,90.);
    
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

ECHARM_crystal_Bi4Ge3O12::~ECHARM_crystal_Bi4Ge3O12(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
