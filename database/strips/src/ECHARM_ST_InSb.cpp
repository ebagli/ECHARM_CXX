//
//  ECHARM_ST_InSb.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_ST_InSb_h

#include "ECHARM_ST_InSb.hh"
#include "ECHARM_crystal_InSb.hh"
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

ECHARM_ST_InSb::ECHARM_ST_InSb(double length,bool planeOn,int millerX = 1,int millerY = 1,int millerZ = 1){
    
    fCrystal = new ECHARM_crystal_InSb();
    
    int vMillerX[3] = {1,-1,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);
    
    fCrystal->ComputeParameters();
    
    fDim = new ECHARM_3vec(1. * millimeter,1. * millimeter,length);;
    fBRconst = new ECHARM_3vec(0.,0.,0.);
    
    SetName("ST_InSb");
    
    if(planeOn == true){
        int vMiller[3] = {millerX,millerY,millerZ};
        fCrystal->GetMiller()->SetX(vMiller);

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
    }
    else{
        ECHARM_EC_intrp* pot_intrp = new ECHARM_EC_intrp("pot",fCrystal,64,64);
        ECHARM_EC_intrp* atd_intrp = new ECHARM_EC_intrp("atd",fCrystal,64,64);
        ECHARM_EC_intrp* eld_intrp = new ECHARM_EC_intrp("eld",fCrystal,64,64);
        ECHARM_EC_intrp* efx_intrp = new ECHARM_EC_intrp("efx",fCrystal,64,64);
        ECHARM_EC_intrp* efy_intrp = new ECHARM_EC_intrp("efy",fCrystal,64,64);
        ECHARM_EC_const* efz = new ECHARM_EC_const("efz",fCrystal,0.);
        
        
        std::ifstream fileIn;
        
        fileIn.open("InSb111pot.txt");
        std::cout << "InSb111pot.txt" << std::endl;
        if (fileIn.good()){
            fileIn.close();
            pot_intrp->ReadVecFromFile("InSb111pot.txt");
        }
        else{
            ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_ax(fCrystal,128,128);
            pot_intrp->Store(pot);
            pot_intrp->PrintVecToFile("InSb111pot.txt");
        }
        
        
        fileIn.open("InSb111atd.txt");
        std::cout << "InSb111atd.txt" << std::endl;
        if (fileIn.good()){
            fileIn.close();
            atd_intrp->ReadVecFromFile("InSb111atd.txt");
        }
        else{
            ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_ax(fCrystal,128,128);
            atd_intrp->Store(atd);
            atd_intrp->PrintVecToFile("InSb111atd.txt");
        }
        
        
        fileIn.open("InSb111eld.txt");
        std::cout << "InSb111eld.txt" << std::endl;
        if (fileIn.good()){
            fileIn.close();
            eld_intrp->ReadVecFromFile("InSb111eld.txt");
        }
        else{
            ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_ax(fCrystal,128,128);
            eld_intrp->Store(eld);
            eld_intrp->PrintVecToFile("InSb111eld.txt");
        }
        
        
        fileIn.open("InSb111efx.txt");
        std::cout << "InSb111efx.txt" << std::endl;
        if (fileIn.good()){
            fileIn.close();
            efx_intrp->ReadVecFromFile("InSb111efx.txt");
        }
        else{
            ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_ax(fCrystal,128,128);
            efx_intrp->Store(efx);
            efx_intrp->PrintVecToFile("InSb111efx.txt");
        }
        
        fileIn.open("InSb111efy.txt");
        std::cout << "InSb111efy.txt" << std::endl;
        if (fileIn.good()){
            fileIn.close();
            efy_intrp->ReadVecFromFile("InSb111efy.txt");
        }
        else{
            ECHARM_EC_rec* efy = new ECHARM_EC_rec_efy_ax(fCrystal,128,128);
            efy_intrp->Store(efy);
            efy_intrp->PrintVecToFile("InSb111efy.txt");
        }
        
        
        SetPot(pot_intrp);
        SetAtD(atd_intrp);
        SetElD(eld_intrp);
        SetEFX(efx_intrp);
        SetEFY(efy_intrp);
        SetEFZ(efz);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_ST_InSb::~ECHARM_ST_InSb(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif