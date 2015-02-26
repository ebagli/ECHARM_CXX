//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_LiNbO3_cubic_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_LiNbO3_cubic.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_LiNbO3_cubic::ECHARM_crystal_LiNbO3_cubic(){
    
    SetAtomName("LiNbO3");

    ECHARM_atom_moliere *atomLiNbO3 = new ECHARM_atom_moliere("LiNbO3",13.6,29.56904 * amu,575.0,149.44);
    ECHARM_lattice *latticeLiNbO3 = new ECHARM_lattice();
    latticeLiNbO3->Add(0.5,0.5,0.5);

    AddBase(atomLiNbO3,latticeLiNbO3);
    
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

ECHARM_crystal_LiNbO3_cubic::~ECHARM_crystal_LiNbO3_cubic(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
