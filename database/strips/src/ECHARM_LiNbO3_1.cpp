//
//  ECHARM_LiNbO3_1.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_LiNbO3_1_h

#include "ECHARM_LiNbO3_1.hh"
#include "ECHARM_crystal_LiNbO3.hh"
#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_const.hh"
#include "ECHARM_3vec.hh"

ECHARM_LiNbO3_1::ECHARM_LiNbO3_1(){
    
    fCrystal = new ECHARM_crystal_LiNbO3();

    int vMillerX[3] = {3,0,0};
    int vMillerY[3] = {0,3,0};
    int vMillerZ[3] = {0,0,1};
    
    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);
    
    fCrystal->ComputeParameters();
    
    ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_pl(fCrystal,512);
    ECHARM_EC_intrp* pot_intrp = new ECHARM_EC_intrp("pot",fCrystal,2048);
    pot_intrp->Store(pot);

    ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_pl(fCrystal,512);
    ECHARM_EC_intrp* atd_intrp = new ECHARM_EC_intrp("atd",fCrystal,2048);
    atd_intrp->Store(atd);

    ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_pl(fCrystal,512);
    ECHARM_EC_intrp* eld_intrp = new ECHARM_EC_intrp("eld",fCrystal,2048);
    eld_intrp->Store(eld);

    ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_pl(fCrystal,512);
    ECHARM_EC_intrp* efx_intrp = new ECHARM_EC_intrp("efx",fCrystal,2048);
    efx_intrp->Store(efx);

    ECHARM_EC_const* efy = new ECHARM_EC_const("efy",fCrystal,0.);
    ECHARM_EC_const* efz = new ECHARM_EC_const("efz",fCrystal,0.);
    
    SetPot(pot_intrp);
    SetAtD(atd_intrp);
    SetElD(eld_intrp);
    SetEFX(efx_intrp);
    SetEFY(efy);
    SetEFZ(efz);
    
    fDim = new ECHARM_3vec(0.9 * millimeter,70. * millimeter,1. * millimeter);;
    //fBRconst = new ECHARM_3vec(5.46 * meter,0.,0.);
    fBRconst = new ECHARM_3vec(5.241 * meter,0.,0.);
    
    SetName("LiNbO3_1");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_LiNbO3_1::~ECHARM_LiNbO3_1(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
