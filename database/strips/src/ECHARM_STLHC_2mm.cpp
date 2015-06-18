//
//  ECHARM_STLHC_2mm.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_STLHC_2mm_h

#include "ECHARM_STLHC_2mm.hh"
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_const.hh"
#include "ECHARM_3vec.hh"

ECHARM_STLHC_2mm::ECHARM_STLHC_2mm(){
    
    fCrystal = new ECHARM_crystal_Si();
    
    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);

    fCrystal->SetTemperature(420.);
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
    
    fDim = new ECHARM_3vec(1. * millimeter,55. * millimeter,2. * millimeter);;
    fBRconst = new ECHARM_3vec(36.36 * meter,0.,0.);
    
    SetName("STLHC_2mm");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_STLHC_2mm::~ECHARM_STLHC_2mm(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
