//
//  ECHARM_EC_Rec_Coeff.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_Rec_Coeff_h

#include "ECHARM_EC_Rec_Coeff.hh"

ECHARM_EC_Rec_Coeff::ECHARM_EC_Rec_Coeff(ECHARM_crystal* fCrystal,bool planeOn,int millerX, int millerY, int millerZ,int fft_n = 256,std::string type){
    
    fType = type;
    
    int fft_nx = fft_n;
    int fft_ny = fft_n;
    
    fDim = new ECHARM_3vec(0.,0.,0.);
    fBRconst = new ECHARM_3vec(0.,0.,0.);
    
    SetName("ECHARM_EC_Rec_Coeff");
    
    if(planeOn == true){
        int vMiller[3] = {millerX,millerY,millerZ};
        fCrystal->GetMiller()->SetX(vMiller);
        fCrystal->ComputeParameters();
        char filename[128];
        
        if(fType == "" or fType == "pot"){
            sprintf(filename,"%s%d%d%dpl_pot",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
            ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_pl(fCrystal,fft_n);
            pot->PrintCoeffToFile(filename,false,"pot");
        }
        
        if(fType == "" or fType == "atd"){
            sprintf(filename,"%s%d%d%dpl_atd",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
            ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_pl(fCrystal,fft_n);
            atd->PrintCoeffToFile(filename,false,"atd");
       }
        
        if(fType == "" or fType == "eld"){
            sprintf(filename,"%s%d%d%dpl_eld",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
            ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_pl(fCrystal,fft_n);
            eld->PrintCoeffToFile(filename,false,"eld");
        }
        
        if(fType == "" or fType == "efx"){
            sprintf(filename,"%s%d%d%dpl_efx",fCrystal->GetAtomName().c_str(),millerX,millerY,millerZ);
            ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_pl(fCrystal,fft_n);
            efx->PrintCoeffToFile(filename,true,"pot");
        }
    }
    else{
        int vMillerZ[3] = {millerX,millerY,millerZ};
        
        std::ifstream fileIn;
        char filename[128];
        
        if(fType == "" or fType == "pot"){
            sprintf(filename,"%s%d%d%dax_pot",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
            ECHARM_EC_rec* pot = new ECHARM_EC_rec_pot_ax(fCrystal,fft_nx,fft_ny);
            pot->PrintCoeffToFile(filename,false,"pot");
        }
        
        if(fType == "" or fType == "atd"){
            
            sprintf(filename,"%s%d%d%dax_atd",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
            ECHARM_EC_rec* atd = new ECHARM_EC_rec_atd_ax(fCrystal,fft_nx,fft_ny);
            atd->PrintCoeffToFile(filename,false,"atd");
        }
        
        if(fType == "" or fType == "eld"){
            
            sprintf(filename,"%s%d%d%dax_eld",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
            ECHARM_EC_rec* eld = new ECHARM_EC_rec_eld_ax(fCrystal,fft_nx,fft_ny);
            eld->PrintCoeffToFile(filename,false,"eld");

        }
        
        if(fType == "" or fType == "efx"){
            
            sprintf(filename,"%s%d%d%dax_efx",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
            ECHARM_EC_rec* efx = new ECHARM_EC_rec_efx_ax(fCrystal,fft_nx,fft_ny);
            efx->PrintCoeffToFile(filename,true,"efy");

        }
        
        if(fType == "" or fType == "efy"){
            sprintf(filename,"%s%d%d%dax_efy",fCrystal->GetAtomName().c_str(),vMillerZ[0],vMillerZ[1],vMillerZ[2]);
            ECHARM_EC_rec* efy = new ECHARM_EC_rec_efy_ax(fCrystal,fft_nx,fft_ny);
            efy->PrintCoeffToFile(filename,true,"efy");

        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_Rec_Coeff::~ECHARM_EC_Rec_Coeff(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
