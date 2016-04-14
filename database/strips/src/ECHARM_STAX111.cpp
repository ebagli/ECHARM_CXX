//
//  ECHARM_STAX111.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_STAX111_h

#include "ECHARM_STAX111.hh"
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

ECHARM_STAX111::ECHARM_STAX111(){
    //standard 420
    double Temp = 420.;
    
    fCrystal = new ECHARM_crystal_Si();
    
    int nPoints = 512;
    
    int vMillerX[3] = {2,-2,0};
    int vMillerY[3] = {1,1,-2};
    int vMillerZ[3] = {1,1,1};

    fCrystal->GetMiller()->SetX(vMillerX);
    fCrystal->GetMiller()->SetY(vMillerY);
    fCrystal->GetMiller()->SetZ(vMillerZ);
    
    fCrystal->SetTemperature(Temp);
    fCrystal->ComputeParameters();

    {
        ECHARM_EC_intrp* pot_intrp = new ECHARM_EC_intrp("pot",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* atd_intrp = new ECHARM_EC_intrp("atd",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* eld_intrp = new ECHARM_EC_intrp("eld",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* efx_intrp = new ECHARM_EC_intrp("efx",fCrystal,nPoints,nPoints);
        ECHARM_EC_intrp* efy_intrp = new ECHARM_EC_intrp("efy",fCrystal,nPoints,nPoints);
        ECHARM_EC_const* efz = new ECHARM_EC_const("efz",fCrystal,0.);
        
        
        std::ifstream fileIn;
        char filename[128];
        sprintf(filename,"%s%d%d%dax_pot.txt",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
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
            pot_intrp->PrintToTH(filename);
        }
        
        sprintf(filename,"%s%d%d%dax_atd.txt",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
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
        
        sprintf(filename,"%s%d%d%dax_eld.txt",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
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
        
        sprintf(filename,"%s%d%d%dax_efx.txt",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
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
        
        sprintf(filename,"%s%d%d%dax_efy.txt",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
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
        
    fDim = new ECHARM_3vec(1.02 * millimeter,55. * millimeter,1.95 * millimeter);;
    fBRconst = new ECHARM_3vec(31. * meter,0.,0.);
    
    SetName("STAX111");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_STAX111::~ECHARM_STAX111(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif