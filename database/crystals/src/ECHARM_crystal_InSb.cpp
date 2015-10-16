//
//  .cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_crystal_InSb_h

#include <cfloat>
#include <limits>
#include "ECHARM_crystal_InSb.hh"
#include "ECHARM_miller_cubic.hh"
#include "ECHARM_lattice_diamond.hh"

ECHARM_crystal_InSb::ECHARM_crystal_InSb(){
    
    SetAtomName("InSb");
//http://harker.chem.buffalo.edu/group/fit.html

    double vSbExperimentalCoefficients[12];
    
    vSbExperimentalCoefficients[0] = 19.04077/51.;
    vSbExperimentalCoefficients[1] = 13.05412/51.;
    vSbExperimentalCoefficients[2] = 6.63670/51.;
    vSbExperimentalCoefficients[3] = 4.95963/51.;
    vSbExperimentalCoefficients[4] = 4.60941/51.;
    vSbExperimentalCoefficients[5] = 2.69795/51.;
    
    vSbExperimentalCoefficients[6] = 0.46176*AA*AA;
    vSbExperimentalCoefficients[7] = 5.31900*AA*AA;
    vSbExperimentalCoefficients[8] = 5.31953*AA*AA;
    vSbExperimentalCoefficients[9] = 28.54198*AA*AA;
    vSbExperimentalCoefficients[10] = 0.00010*AA*AA;
    vSbExperimentalCoefficients[11] = 72.65174*AA*AA;

    double vInExperimentalCoefficients[12];
    
    vInExperimentalCoefficients[0] = 19.16300/49.;
    vInExperimentalCoefficients[1] = 18.59170/49.;
    vInExperimentalCoefficients[2] = 4.95237/49.;
    vInExperimentalCoefficients[3] = 4.27994/49.;
    vInExperimentalCoefficients[4] = 2.00969/49.;
    vInExperimentalCoefficients[5] = 0.00010/49.;
    
    vInExperimentalCoefficients[6] = 0.54868*AA*AA;
    vInExperimentalCoefficients[7] = 6.39500*AA*AA;
    vInExperimentalCoefficients[8] = 0.00010*AA*AA;
    vInExperimentalCoefficients[9] = 26.18224*AA*AA;
    vInExperimentalCoefficients[10] = 93.70112*AA*AA;
    vInExperimentalCoefficients[11] = 8.23922*AA*AA;
    
    ECHARM_atom_xray *atomIn = new ECHARM_atom_xray("In",49.,114.818 * amu,160.,481.,vInExperimentalCoefficients);
    ECHARM_atom_xray *atomSb = new ECHARM_atom_xray("Sb",51.,121.76 * amu,160.,472.,vSbExperimentalCoefficients);

    ECHARM_lattice *latticeIn = new ECHARM_lattice_zincblend_a();
    ECHARM_lattice *latticeSb = new ECHARM_lattice_zincblend_b();

    AddBase(atomIn,latticeIn);
    AddBase(atomSb,latticeSb);
    
    fCell = new ECHARM_cell(6.479*AA,6.479*AA,6.479*AA,90.,90.,90.);
    
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

ECHARM_crystal_InSb::~ECHARM_crystal_InSb(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
