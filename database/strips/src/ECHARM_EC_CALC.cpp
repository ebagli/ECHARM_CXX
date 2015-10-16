//
//  ECHARM_EC_CALC.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_CALC_h

#include "ECHARM_EC_CALC.hh"

ECHARM_EC_CALC::ECHARM_EC_CALC(ECHARM_crystal* fCrystal,bool planeOn,int millerX, int millerY, int millerZ,bool fastON){


    int nPoints = 128;
    if(fastON==true) nPoints = 32;
    
    int vMillerX[3] = {1,-1,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);
    
    fCrystal->ComputeParameters();
    
    fDim = new ECHARM_3vec(0.,0.,0.);
    fBRconst = new ECHARM_3vec(0.,0.,0.);
    
    SetName("ECHARM_EC_CALC");
    
    if(planeOn == true){
        int vMiller[3] = {millerX,millerY,millerZ};
        fCrystal->GetMiller()->SetX(vMiller);

        char filename[128];
        sprintf(filename,"%s%d%d%dpot_pl.txt",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
        ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_pl(fCrystal,512);
        ECHARM_EC_intrp* pot_intrp = new ECHARM_EC_intrp("pot",fCrystal,2048);
        pot_intrp->Store(pot);
        pot_intrp->PrintVecToFile(filename);
        
        sprintf(filename,"%s%d%d%datd_pl.txt",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
        ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_pl(fCrystal,512);
        ECHARM_EC_intrp* atd_intrp = new ECHARM_EC_intrp("atd",fCrystal,2048);
        atd_intrp->Store(atd);
        atd_intrp->PrintVecToFile(filename);
        
        sprintf(filename,"%s%d%d%deld_pl.txt",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
        ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_pl(fCrystal,512);
        ECHARM_EC_intrp* eld_intrp = new ECHARM_EC_intrp("eld",fCrystal,2048);
        eld_intrp->Store(eld);
        eld_intrp->PrintVecToFile(filename);
        
        sprintf(filename,"%s%d%d%defx_pl.txt",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
        ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_pl(fCrystal,512);
        ECHARM_EC_intrp* efx_intrp = new ECHARM_EC_intrp("efx",fCrystal,2048);
        efx_intrp->Store(efx);
        efx_intrp->PrintVecToFile(filename);
        
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
        ECHARM_EC_intrp* pot_intrp = new ECHARM_EC_intrp("pot",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* atd_intrp = new ECHARM_EC_intrp("atd",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* eld_intrp = new ECHARM_EC_intrp("eld",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* efx_intrp = new ECHARM_EC_intrp("efx",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* efy_intrp = new ECHARM_EC_intrp("efy",fCrystal,nPoints,nPoints);
        ECHARM_EC_const* efz = new ECHARM_EC_const("efz",fCrystal,0.);
        
        
        std::ifstream fileIn;
        char filename[128];
        sprintf(filename,"%s111pot.txt",fCrystal->GetAtomName().c_str());
        fileIn.open(filename);
        std::cout << filename << std::endl;
        if (fileIn.good()){
            fileIn.close();
            pot_intrp->ReadVecFromFile(filename);
        }
        else{
            ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_ax(fCrystal,128,128);
            pot_intrp->Store(pot);
            pot_intrp->PrintVecToFile(filename);
        }
        
        sprintf(filename,"%s111atd.txt",fCrystal->GetAtomName().c_str());
        fileIn.open(filename);
        std::cout << filename << std::endl;
        if (fileIn.good()){
            fileIn.close();
            atd_intrp->ReadVecFromFile(filename);
        }
        else{
            ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_ax(fCrystal,128,128);
            atd_intrp->Store(atd);
            atd_intrp->PrintVecToFile(filename);
        }
        
        sprintf(filename,"%s111eld.txt",fCrystal->GetAtomName().c_str());
        fileIn.open(filename);
        std::cout << filename << std::endl;
        if (fileIn.good()){
            fileIn.close();
            eld_intrp->ReadVecFromFile(filename);
        }
        else{
            ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_ax(fCrystal,128,128);
            eld_intrp->Store(eld);
            eld_intrp->PrintVecToFile(filename);
        }
        
        sprintf(filename,"%s111efx.txt",fCrystal->GetAtomName().c_str());
        fileIn.open(filename);
        std::cout << filename << std::endl;
        if (fileIn.good()){
            fileIn.close();
            efx_intrp->ReadVecFromFile(filename);
        }
        else{
            ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_ax(fCrystal,128,128);
            efx_intrp->Store(efx);
            efx_intrp->PrintVecToFile(filename);
        }
        
        sprintf(filename,"%s111efy.txt",fCrystal->GetAtomName().c_str());
        fileIn.open(filename);
        std::cout << filename << std::endl;
        if (fileIn.good()){
            fileIn.close();
            efy_intrp->ReadVecFromFile(filename);
        }
        else{
            ECHARM_EC_rec* efy = new ECHARM_EC_rec_efy_ax(fCrystal,128,128);
            efy_intrp->Store(efy);
            efy_intrp->PrintVecToFile(filename);
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

ECHARM_EC_CALC::~ECHARM_EC_CALC(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
