//
//  ECHARM_QM_CERN_H4_1mm.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_QM_CERN_H4_1mm_h

#include "ECHARM_QM_CERN_H4_1mm.hh"
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_direct.hh"
#include "ECHARM_EC_const.hh"
#include "ECHARM_3vec.hh"

ECHARM_QM_CERN_H4_1mm::ECHARM_QM_CERN_H4_1mm(double BR,double length = 1. * millimeter,std::string name = "Si"){
    
    if(name == "Si"){
        fCrystal = new ECHARM_crystal_Si();
    }
    else if(name == "Ge"){
        fCrystal = new ECHARM_crystal_Ge();
    }
    else{
        fCrystal = new ECHARM_crystal_Si();
    }
    
    
    
    int vMillerX[3] = {2,1,1};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,-1,0};
    
    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);
    
    fCrystal->SetTemperature(420.);
    fCrystal->ComputeParameters();
    std::cout << fCrystal->GetAtom(0)->GetThermalVibrationConstant() << std::endl;
    
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
    
    fDim = new ECHARM_3vec(10. * millimeter,10. * millimeter,length);;
    fBRconst = new ECHARM_3vec(BR,0.,0.);//standard 20 m

    SetName("ECHARM_QM_CERN_H4_1mms");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_QM_CERN_H4_1mm::~ECHARM_QM_CERN_H4_1mm(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif