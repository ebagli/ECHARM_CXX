//
//  ECHARM_SiEnhancement.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_SiEnhancement_h

#include "ECHARM_SiEnhancement.hh"
#include "ECHARM_crystal_Si.hh"
#include "ECHARM_EC_rec_pot_pl.hh"
#include "ECHARM_EC_rec_atd_pl.hh"
#include "ECHARM_EC_rec_eld_pl.hh"
#include "ECHARM_EC_rec_efx_pl.hh"
#include "ECHARM_EC_rec_efy_pl.hh"
#include "ECHARM_EC_rec_efz_pl.hh"
#include "ECHARM_EC_intrp.hh"
#include "ECHARM_EC_const.hh"
#include "ECHARM_EC_direct.hh"
#include "ECHARM_3vec.hh"

ECHARM_SiEnhancement::ECHARM_SiEnhancement(double length){
    
    fCrystal = new ECHARM_crystal_Si();
    
    int vMillerX[3] = {1,0,0};
    int vMillerY[3] = {0,1,-1};
    int vMillerZ[3] = {0,1,1};

    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);
    
    fCrystal->ComputeParameters();
    
    ECHARM_EC_intrp* pot_intrp = new ECHARM_EC_intrp("pot",fCrystal,512,512);
    ECHARM_EC_intrp* atd_intrp = new ECHARM_EC_intrp("atd",fCrystal,512,512);
    ECHARM_EC_intrp* eld_intrp = new ECHARM_EC_intrp("eld",fCrystal,512,512);
    ECHARM_EC_intrp* efx_intrp = new ECHARM_EC_intrp("efx",fCrystal,512,512);
    ECHARM_EC_intrp* efy_intrp = new ECHARM_EC_intrp("efy",fCrystal,512,512);
    ECHARM_EC_const* efz = new ECHARM_EC_const("efz",fCrystal,0.);
    
    
    std::ifstream fileIn;
    
    fileIn.open("Si100pot.txt");
    std::cout << "Si100pot.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        pot_intrp->ReadVecFromFile("Si100pot.txt");
    }
    else{
        ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_ax(fCrystal,128,128);
        pot_intrp->Store(pot);
        pot_intrp->PrintVecToFile("Si100pot.txt");
    }
    

    fileIn.open("Si100atd.txt");
    std::cout << "Si100atd.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        atd_intrp->ReadVecFromFile("Si100atd.txt");
    }
    else{
        ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_ax(fCrystal,128,128);
        atd_intrp->Store(atd);
        atd_intrp->PrintVecToFile("Si100atd.txt");
    }
    
    
    fileIn.open("Si100eld.txt");
    std::cout << "Si100eld.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        eld_intrp->ReadVecFromFile("Si100eld.txt");
    }
    else{
        ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_ax(fCrystal,128,128);
        eld_intrp->Store(eld);
        eld_intrp->PrintVecToFile("Si100eld.txt");
    }
    
    
    fileIn.open("Si100efx.txt");
    std::cout << "Si100efx.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        efx_intrp->ReadVecFromFile("Si100efx.txt");
    }
    else{
        ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_ax(fCrystal,128,128);
        efx_intrp->Store(efx);
        efx_intrp->PrintVecToFile("Si100efx.txt");
    }
    
    fileIn.open("Si100efy.txt");
    std::cout << "Si100efy.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        efy_intrp->ReadVecFromFile("Si100efy.txt");
    }
    else{
        ECHARM_EC_rec* efy = new ECHARM_EC_rec_efy_ax(fCrystal,128,128);
        efy_intrp->Store(efy);
        efy_intrp->PrintVecToFile("Si100efy.txt");
    }
    
    SetPot(pot_intrp);
    SetAtD(atd_intrp);
    SetElD(eld_intrp);
    SetEFX(efx_intrp);
    SetEFY(efy_intrp);
    SetEFZ(efz);
    
    fDim = new ECHARM_3vec(1. * millimeter,1. * millimeter,length);;
    fBRconst = new ECHARM_3vec(0.,0.,0.);
    
    SetName("SiEnhancement");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_SiEnhancement::~ECHARM_SiEnhancement(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
