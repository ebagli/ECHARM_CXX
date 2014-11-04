//
//  ECHARM_Vacuum.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_Vacuum_h

#include "ECHARM_Vacuum.hh"
#include "ECHARM_crystal_Vacuum.hh"
#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_const.hh"
#include "ECHARM_3vec.hh"

ECHARM_Vacuum::ECHARM_Vacuum(double molecules_per_cm3,double x,double y, double z,double posx=0.,double posy=0., double posz=0.){
    
    fCrystal = new ECHARM_crystal_Vacuum(molecules_per_cm3);
    
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
    
    fDim = new ECHARM_3vec(x,y,z);;
    fPos = new ECHARM_3vec(x,y,z);;
    fBRconst = new ECHARM_3vec(0.,0.,0.);
    
    SetName("Vacuum");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_Vacuum::~ECHARM_Vacuum(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif