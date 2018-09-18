//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_InP_In_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_InP_In.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_InP_In::ECHARM_crystal_InP_In(){
    
    SetAtomName("InP");
//http://harker.chem.buffalo.edu/group/fit.html

    ECHARM_atom_xray *atomIn = new ECHARM_atom_xray("In",49.,114.818 * amu,301.,481.);

    ECHARM_lattice *latticeIn = new ECHARM_lattice_zincblend_a();

    AddBase(atomIn,latticeIn);
    
    fCell = new ECHARM_cell(5.8687*AA,5.8687*AA,5.8687*AA,90.,90.,90.);
    
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

ECHARM_crystal_InP_In::~ECHARM_crystal_InP_In(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
