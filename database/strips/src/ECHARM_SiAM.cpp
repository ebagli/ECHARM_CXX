//
//  ECHARM_SiAM.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_SiAM.hh"
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_EC_const.hh"
#include "ECHARM_3vec.hh"

ECHARM_SiAM::ECHARM_SiAM(double length){
    
    fCrystal = new ECHARM_crystal_Si();
    
    ECHARM_EC_const* pot = new ECHARM_EC_const("pot",fCrystal,0.);
    ECHARM_EC_const* atd = new ECHARM_EC_const("atd",fCrystal,1.);
    ECHARM_EC_const* eld = new ECHARM_EC_const("eld",fCrystal,1.);
    ECHARM_EC_const* efx = new ECHARM_EC_const("efx",fCrystal,0.);
    ECHARM_EC_const* efy = new ECHARM_EC_const("efy",fCrystal,0.);
    ECHARM_EC_const* efz = new ECHARM_EC_const("efz",fCrystal,0.);
    
    SetPot(pot);
    SetAtD(atd);
    SetElD(eld);
    SetEFX(efx);
    SetEFY(efy);
    SetEFZ(efz);

    fPot->ComputeMax();
    fPot->ComputeMin();
    fEFX->ComputeMax();
    fEFX->ComputeMin();
    fEFY->ComputeMax();
    fEFY->ComputeMin();
    fEFZ->ComputeMax();
    fEFZ->ComputeMin();
    fAtD->ComputeMax();
    fAtD->ComputeMin();
    fElD->ComputeMax();
    fElD->ComputeMin();
    
    fDim = new ECHARM_3vec(1. * millimeter,1. * millimeter,length);;
    fBRconst = new ECHARM_3vec(0.,0.,0.);

    SetName("SiAM");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_SiAM::~ECHARM_SiAM(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
