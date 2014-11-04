//
//  ECHARM_EC_rec_efx.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_rec_efx_h

#include "ECHARM_EC_rec_efx.hh"

ECHARM_EC_rec_efx::ECHARM_EC_rec_efx(ECHARM_crystal* crystal,
                                     int recX,
                                     int recY,
                                     int recZ):
ECHARM_EC_rec("efx",
              crystal,
              recX,
              recY,
              recZ){
    fPhaseCos = +cPiHalf;
    fPhaseSin = -cPiHalf;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_efx::~ECHARM_EC_rec_efx(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_efx::GetFactorRe(double* vIndexEC){
    return (fCrystal->GetRecPeriodX() * vIndexEC[0]);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_EC_rec_efx::ComputeRecFF(int vIndex[3])
{
    std::vector<double> FC;
    std::vector<double> SF = fCrystal->ComputeSF(vIndex);
    
    double FormFactor = 0.0;
    double ThermalVibration = 0.0;
    double RecVec2 = fCrystal->GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<fCrystal->GetNumBases();i++){
        FormFactor = fCrystal->GetAtom(i)->ComputeRecFF(RecVec2);
        ThermalVibration = exp( - fSquare(fCrystal->GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back(FormFactor * SF[2*i] * fCrystal->GetAtom(i)->GetZ() * ThermalVibration / RecVec2);
        FC.push_back(FormFactor * SF[2*i+1] * fCrystal->GetAtom(i)->GetZ() * ThermalVibration / RecVec2);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_efx::Get(double x, double y, double z){
    if(fFFC.size() == 0){
        StoreRecFF();
    }
    double vEFX = GetFT(x,y,z,fFFC);
    vEFX *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
    vEFX /= fCrystal->GetCell()->GetVolume();
    
    return -vEFX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
