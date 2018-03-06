//
//  ECHARM_crystal_LiNbO3_supercell.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_LiNbO3_supercell_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_LiNbO3_supercell.hh"
#include "ECHARM_atom_xray.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_LiNbO3_supercell::ECHARM_crystal_LiNbO3_supercell(){
    
    SetAtomName("LiNbO3_supercell");
    
    ECHARM_atom_moliere *atomLi = new ECHARM_atom_moliere("Li",3.,6.941 * amu,575.0,42.2);
    ECHARM_atom_moliere *atomNb = new ECHARM_atom_moliere("Nb",41.,92.906 * amu,575.0,417.0);
    ECHARM_atom_moliere *atomO = new ECHARM_atom_moliere("O",8.,15.9994 * amu,575.0,96.0);

    ECHARM_lattice *latticeLi = new ECHARM_lattice();
    latticeLi->Add(0.0,0.0,0.225);
    latticeLi->Add(0.499995,0.500005,0.225);
    latticeLi->Add(0.499995,0.499995,0.725);
    latticeLi->Add(0.0,0.0,0.725);
    latticeLi->Add(0.50001,0.16667,0.55833);
    latticeLi->Add(0.0,0.333335,0.89167);
    latticeLi->Add(0.0,0.333335,0.39167);
    latticeLi->Add(0.500005,0.500005,0.225);
    latticeLi->Add(0.500005,0.499995,0.725);
    latticeLi->Add(0.0,0.66667,0.55833);
    latticeLi->Add(0.5,0.5,0.225);
    latticeLi->Add(1.0,1.0,0.725);
    latticeLi->Add(0.0,1.0,0.725);
    latticeLi->Add(0.5,0.5,0.725);
    latticeLi->Add(0.500005,0.833335,0.89167);
    latticeLi->Add(0.500005,0.833335,0.39167);
    AddBase(atomLi,latticeLi);

    ECHARM_lattice *latticeNb = new ECHARM_lattice();
    latticeNb->Add(0.0,0.0,0.0);
    latticeNb->Add(0.499995,0.500005,0.0);
    latticeNb->Add(0.499995,0.500005,0.5);
    latticeNb->Add(0.0,0.0,0.5);
    latticeNb->Add(0.5,0.16666,0.33333);
    latticeNb->Add(0.5,0.16666,0.83333);
    latticeNb->Add(0.0,0.33333,0.66667);
    latticeNb->Add(0.0,0.33333,0.16667);
    latticeNb->Add(0.499995,0.500005,0.0);
    latticeNb->Add(0.499995,0.500005,0.5);
    latticeNb->Add(0.0,0.66666,0.33333);
    latticeNb->Add(0.0,0.66666,0.83333);
    latticeNb->Add(0.5,0.5,0.0);
    latticeNb->Add(0.5,0.5,0.5);
    latticeNb->Add(0.5,0.83333,0.66667);
    latticeNb->Add(0.5,0.83333,0.16667);
    AddBase(atomNb,latticeNb);

    ECHARM_lattice *latticeO = new ECHARM_lattice();
    latticeO->Add(0.31286,0.35385,0.0833);
    latticeO->Add(0.187205,0.479495,0.5833);
    latticeO->Add(0.12566,0.16665,0.5833);
    latticeO->Add(0.37436,0.33331,0.41663);
    latticeO->Add(0.31286,0.02052,0.41663);
    latticeO->Add(0.812795,0.146165,0.41663);
    latticeO->Add(0.187195,0.146165,0.91663);
    latticeO->Add(0.68716,0.02052,0.91663);
    latticeO->Add(0.62566,0.33331,0.91663);
    latticeO->Add(0.312795,0.312835,0.74997);
    latticeO->Add(0.18714,0.18718,0.24997);
    latticeO->Add(0.12564,0.49998,0.24997);
    latticeO->Add(0.87434,0.16665,0.0833);
    latticeO->Add(0.812805,0.479495,0.0833);
    latticeO->Add(0.68714,0.35385,0.5833);
    latticeO->Add(0.87434,0.49998,0.74997);
    latticeO->Add(0.81284,0.18718,0.74997);
    latticeO->Add(0.687205,0.312835,0.24997);
    latticeO->Add(0.312795,0.646165,0.41663);
    latticeO->Add(0.18716,0.52052,0.91663);
    latticeO->Add(0.12566,0.83331,0.91663);
    latticeO->Add(0.37434,0.66665,0.0833);
    latticeO->Add(0.81286,0.85385,0.0833);
    latticeO->Add(0.312805,0.979495,0.0833);
    latticeO->Add(0.687205,0.979495,0.5833);
    latticeO->Add(0.18714,0.85385,0.5833);
    latticeO->Add(0.62566,0.66665,0.5833);
    latticeO->Add(0.87436,0.83331,0.41663);
    latticeO->Add(0.81286,0.52052,0.41663);
    latticeO->Add(0.687195,0.646165,0.91663);
    latticeO->Add(0.37434,1.0,0.74997);
    latticeO->Add(0.31284,0.68718,0.74997);
    latticeO->Add(0.812795,0.812835,0.74997);
    latticeO->Add(0.187205,0.812835,0.24997);
    latticeO->Add(0.68714,0.68718,0.24997);
    latticeO->Add(0.62564,1.0,0.24997);

    AddBase(atomO,latticeO);
    fCell = new ECHARM_cell(5.185E-10,8.98068343724E-10,13.87E-10,90.,90.,90.);
    
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

ECHARM_crystal_LiNbO3_supercell::~ECHARM_crystal_LiNbO3_supercell(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
