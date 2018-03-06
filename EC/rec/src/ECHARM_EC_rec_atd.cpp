//
//  ECHARM_EC_rec_atd.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_rec_atd_h

#include "ECHARM_EC_rec_atd.hh"

ECHARM_EC_rec_atd::ECHARM_EC_rec_atd(ECHARM_crystal* crystal,
                                     int recX,
                                     int recY,
                                     int recZ):
ECHARM_EC_rec("atd",
              crystal,
              recX,
              recY,
              recZ){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_atd::~ECHARM_EC_rec_atd(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_EC_rec_atd::ComputeRecFF(int vIndex[3],
                                                    double vIndexEC[3])
{
    std::vector<double> FC;
    std::vector<double> SF = fCrystal->ComputeSF(vIndex);
    
    double ThermalVibration = 0.0;
    double RecVec2 = fCrystal->GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<fCrystal->GetNumBases();i++){
        ThermalVibration = exp( - fSquare(fCrystal->GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back(GetFactorRe(vIndexEC) * SF[2*i] * ThermalVibration);
        FC.push_back(GetFactorIm(vIndexEC) * SF[2*i+1] * ThermalVibration);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_atd::Get(double x, double y, double z){
    if(fFFC.size() == 0){
        StoreRecFF();
        StoreValues();

    }
    double vAtD = GetFT(x,y,z,fFFC);
    vAtD += (fCrystal->GetNumCoord()); //eV*m on charge evaluated in unit of electron charge
    vAtD /= (fCrystal->GetNumCoord());
    
    return vAtD;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_atd::GetIndexesSF(int* vIndex,int i0,int i1,int i2){
    vIndex[0] = i0 * fCrystal->GetMiller()->GetX(0) + i1 * fCrystal->GetMiller()->GetY(0) + i2 * fCrystal->GetMiller()->GetZ(0);
    vIndex[1] = i0 * fCrystal->GetMiller()->GetX(1) + i1 * fCrystal->GetMiller()->GetY(1) + i2 * fCrystal->GetMiller()->GetZ(1);
    vIndex[2] = i0 * fCrystal->GetMiller()->GetX(2) + i1 * fCrystal->GetMiller()->GetY(2) + i2 * fCrystal->GetMiller()->GetZ(2);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_atd::GetIndexesEC(double* vIndexEC,int* vIndexSF,int i0,int i1,int i2){
    vIndexEC[0] = i0;
    vIndexEC[1] = i1;
    vIndexEC[2] = i2;
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
