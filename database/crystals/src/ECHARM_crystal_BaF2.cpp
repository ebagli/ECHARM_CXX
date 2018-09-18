//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_BaF2_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_BaF2.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_fcc.hh"
#include "ECHARM_lattice.hh"

ECHARM_crystal_BaF2::ECHARM_crystal_BaF2(){
    
    SetAtomName("BaF2");
//http://harker.chem.buffalo.edu/group/fit.html

    ECHARM_atom_xray *atomBa = new ECHARM_atom_xray("Ba",56.,137.327 * amu,282,491.);
    ECHARM_atom_xray *atomF = new ECHARM_atom_xray("F",9.,18.998 * amu,282,107);

    ECHARM_lattice *latticeBa = new ECHARM_lattice();
    latticeBa->Add(0.0,0.0,0.0);
    latticeBa->Add(0.5,0.5,0.0);
    latticeBa->Add(0.0,0.5,0.5);
    latticeBa->Add(0.5,0.0,0.5);

    ECHARM_lattice *latticeF = new ECHARM_lattice();
    latticeF->Add(0.25,0.25,0.25);
    latticeF->Add(0.25,0.75,0.25);
    latticeF->Add(0.75,0.25,0.25);
    latticeF->Add(0.75,0.75,0.25);

    latticeF->Add(0.25,0.25,0.75);
    latticeF->Add(0.25,0.75,0.75);
    latticeF->Add(0.75,0.25,0.75);
    latticeF->Add(0.75,0.75,0.75);

    AddBase(atomBa,latticeBa);
    AddBase(atomF,latticeF);
    
    fCell = new ECHARM_cell(6.2001*AA,6.2001*AA,6.2001*AA,90.,90.,90.);
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,0};
    int vMillerZ[3] = {0,0,1};
    
    fMiller = new ECHARM_miller_cubic(vMillerX,vMillerY);

    fMiller->SetX(vMillerX);
    fMiller->SetY(vMillerY);
    fMiller->SetZ(vMillerZ);

    ComputeParameters();
    

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_BaF2::~ECHARM_crystal_BaF2(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
