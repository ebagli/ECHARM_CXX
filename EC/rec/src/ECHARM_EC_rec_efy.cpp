//
//  ECHARM_EC_rec_efy.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_rec_efy_h

#include "ECHARM_EC_rec_efy.hh"

ECHARM_EC_rec_efy::ECHARM_EC_rec_efy(ECHARM_crystal* crystal,
                                     int recX,
                                     int recY,
                                     int recZ):
ECHARM_EC_rec("efy",
              crystal,
              recX,
              recY,
              recZ){
    fPhaseCos = +cPiHalf;
    fPhaseSin = -cPiHalf;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_efy::~ECHARM_EC_rec_efy(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_efy::GetFactorRe(double* vIndexEC){
    return (fCrystal->GetRecPeriod(1) * vIndexEC[1]);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_EC_rec_efy::ComputeRecFF(int vIndex[3],
                                                    double vIndexEC[3])
{
    std::vector<double> FC;
    std::vector<double> SF = fCrystal->ComputeSF(vIndex);

    double FormFactor = 0.0;
    double ThermalVibration = 0.0;
    double RecVec2 = fCrystal->GetCell()->ComputeRecVec2(vIndex);
    
    for(unsigned int i=0;i<fCrystal->GetNumBases();i++){
        FormFactor = fCrystal->GetAtom(i)->ComputeRecFF(RecVec2);
        ThermalVibration = exp( - fSquare(fCrystal->GetAtom(i)->GetThermalVibrationConstant()) * RecVec2 / 2);
        
        FC.push_back(GetFactorRe(vIndexEC) * FormFactor * SF[2*i] * fCrystal->GetAtom(i)->GetZ() * ThermalVibration / RecVec2);
        FC.push_back(GetFactorIm(vIndexEC) * FormFactor * SF[2*i+1] * fCrystal->GetAtom(i)->GetZ() * ThermalVibration / RecVec2);
    }
    return FC;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_efy::Get(double x, double y, double z){
    if(fFFC.size() == 0){
        StoreRecFF();
        StoreValues();
    }
    double vEFY = GetFT(x,y,z,fFFC);
    vEFY *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
    vEFY /= fCrystal->GetCell()->GetVolume();
    
    return -vEFY;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_efy::GetIndexesSF(int* vIndex,int i0,int i1,int i2){
    vIndex[0] = i0 * fCrystal->GetMiller()->GetX(0) + i1 * fCrystal->GetMiller()->GetY(0) + i2 * fCrystal->GetMiller()->GetZ(0);
    vIndex[1] = i0 * fCrystal->GetMiller()->GetX(1) + i1 * fCrystal->GetMiller()->GetY(1) + i2 * fCrystal->GetMiller()->GetZ(1);
    vIndex[2] = i0 * fCrystal->GetMiller()->GetX(2) + i1 * fCrystal->GetMiller()->GetY(2) + i2 * fCrystal->GetMiller()->GetZ(2);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_efy::GetIndexesEC(double* vIndexEC,int* vIndexSF,int i0,int i1,int i2){
    vIndexEC[0] = i0;
    vIndexEC[1] = i1;
    vIndexEC[2] = i2;
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
