//
//  ECHARM_FIG5_PRE52_2045.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_FIG5_PRE52_2045.hh"
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_intrp.hh"
#include "ECHARM_3vec.hh"

ECHARM_FIG5_PRE52_2045::ECHARM_FIG5_PRE52_2045(){
    
    fCrystal = new ECHARM_crystal_Si();
    
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

    ECHARM_EC_rec* efy = new ECHARM_EC_rec_efy_pl(fCrystal,512);
    ECHARM_EC_intrp* efy_intrp = new ECHARM_EC_intrp("efy",fCrystal,2048);
    efy_intrp->Store(efy);

    ECHARM_EC_rec* efz = new ECHARM_EC_rec_efz_pl(fCrystal,512);
    ECHARM_EC_intrp* efz_intrp = new ECHARM_EC_intrp("efz",fCrystal,2048);
    efz_intrp->Store(efz);
        
    SetPot(pot_intrp);
    SetAtD(atd_intrp);
    SetElD(eld_intrp);
    SetEFX(efx_intrp);
    SetEFY(efy_intrp);
    SetEFZ(efz_intrp);
        
    fDim = new ECHARM_3vec(2. * millimeter,55. * millimeter,3. * centimeter);;
    fBRconst = new ECHARM_3vec(450. * centimeter,0.,0.);

    
    fBR = new ECHARM_3vec(0.,0.,0.);
    fPos = new ECHARM_3vec(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_FIG5_PRE52_2045::~ECHARM_FIG5_PRE52_2045(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
