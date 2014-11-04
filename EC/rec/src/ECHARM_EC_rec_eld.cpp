//
//  ECHARM_EC_rec_eld.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_rec_eld_h

#include "ECHARM_EC_rec_eld.hh"

ECHARM_EC_rec_eld::ECHARM_EC_rec_eld(ECHARM_crystal* crystal,
                                     int recX,
                                     int recY,
                                     int recZ):
ECHARM_EC_rec("eld",
              crystal,
              recX,
              recY,
              recZ){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_eld::~ECHARM_EC_rec_eld(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_EC_rec_eld::ComputeRecFF(int vIndex[3])
{
    std::vector<double> FC;
    std::vector<double> SF = fCrystal->ComputeSF(vIndex);
    
    double FormFactor = 0.0;
    double ThermalVibration = 0.0;
    double RecVec2 = fCrystal->GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<fCrystal->GetNumBases();i++){
        FormFactor = fCrystal->GetAtom(i)->ComputeRecFF(RecVec2);
        ThermalVibration = exp( - fSquare(fCrystal->GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back((1 - FormFactor) * SF[2*i] * fCrystal->GetAtom(i)->GetZ() * ThermalVibration);
        FC.push_back((1 - FormFactor) * SF[2*i+1] * fCrystal->GetAtom(i)->GetZ() * ThermalVibration);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_eld::Get(double x, double y, double z){
    if(fFFC.size() == 0){
        StoreRecFF();
    }
    double vElD = GetFT(x,y,z,fFFC);
    vElD += (fCrystal->GetNumCoord() * fCrystal->GetZ()); //eV*m on charge evaluated in unit of electron charge
    vElD /= (fCrystal->GetNumCoord() * fCrystal->GetZ());
    
    return vElD;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif