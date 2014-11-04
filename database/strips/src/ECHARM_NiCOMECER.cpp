//
//  ECHARM_NiCOMECER.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_NiCOMECER_h

#include "ECHARM_NiCOMECER.hh"
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

ECHARM_NiCOMECER::ECHARM_NiCOMECER(double length){
    
    fCrystal = new ECHARM_crystal_Ni();
    
    int vMillerX[3] = {1,-1,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};
    
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
    
    fileIn.open("Ni111pot.txt");
    std::cout << "Ni111pot.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        pot_intrp->ReadVecFromFile("Ni111pot.txt");
    }
    else{
        ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_ax(fCrystal,128,128);
        pot_intrp->Store(pot);
        pot_intrp->PrintVecToFile("Ni111pot.txt");
    }
    
    
    fileIn.open("Ni111atd.txt");
    std::cout << "Ni111atd.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        atd_intrp->ReadVecFromFile("Ni111atd.txt");
    }
    else{
        ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_ax(fCrystal,128,128);
        atd_intrp->Store(atd);
        atd_intrp->PrintVecToFile("Ni111atd.txt");
    }
    
    
    fileIn.open("Ni111eld.txt");
    std::cout << "Ni111eld.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        eld_intrp->ReadVecFromFile("Ni111eld.txt");
    }
    else{
        ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_ax(fCrystal,128,128);
        eld_intrp->Store(eld);
        eld_intrp->PrintVecToFile("Ni111eld.txt");
    }
    
    
    fileIn.open("Ni111efx.txt");
    std::cout << "Ni111efx.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        efx_intrp->ReadVecFromFile("Ni111efx.txt");
    }
    else{
        ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_ax(fCrystal,128,128);
        efx_intrp->Store(efx);
        efx_intrp->PrintVecToFile("Ni111efx.txt");
    }
    
    fileIn.open("Ni111efy.txt");
    std::cout << "Ni111efy.txt" << std::endl;
    if (fileIn.good()){
        fileIn.close();
        efy_intrp->ReadVecFromFile("Ni111efy.txt");
    }
    else{
        ECHARM_EC_rec* efy = new ECHARM_EC_rec_efy_ax(fCrystal,128,128);
        efy_intrp->Store(efy);
        efy_intrp->PrintVecToFile("Ni111efy.txt");
    }
    
    
    ECHARM_EC_direct* pot_direct = new ECHARM_EC_direct("pot",fCrystal,3);

    SetPot(pot_direct);
    SetAtD(atd_intrp);
    SetElD(eld_intrp);
    SetEFX(efx_intrp);
    SetEFY(efy_intrp);
    SetEFZ(efz);
    
    fDim = new ECHARM_3vec(1. * millimeter,1. * millimeter,length);;
    fBRconst = new ECHARM_3vec(0.,0.,0.);
    
    SetName("STtest");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_NiCOMECER::~ECHARM_NiCOMECER(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif