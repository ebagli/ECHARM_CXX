//
//  ECHARM_EC_rec_efz.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_rec_efz_h

#include "ECHARM_EC_rec_efz.hh"

ECHARM_EC_rec_efz::ECHARM_EC_rec_efz(ECHARM_crystal* crystal,
                                     int recX,
                                     int recY,
                                     int recZ):
ECHARM_EC_rec("efz",
              crystal,
              recX,
              recY,
              recZ){
    fPhaseCos = +cPiHalf;
    fPhaseSin = -cPiHalf;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_efz::~ECHARM_EC_rec_efz(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_EC_rec_efz::GetFactorRe(double* vIndexEC){
    return (fCrystal->GetRecPeriod(2) * vIndexEC[2]);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_EC_rec_efz::ComputeRecFF(int vIndex[3],
                                                    double vIndexEC[3])
{
    std::vector<double> FC;
    std::vector<double> SF = fCrystal->ComputeSF(vIndex);
    std::complex<double> complexdouble;

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

double ECHARM_EC_rec_efz::Get(double x, double y, double z){
    if(fFFC.size() == 0){
        StoreRecFF();
        StoreValues();
    }
    double vEFZ = GetFT(x,y,z,fFFC);
    vEFZ *= cElectronLengthOnCharge; //eV*m on charge evaluated in unit of electron charge
    vEFZ /= fCrystal->GetCell()->GetVolume();
    
    return -vEFZ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_efz::GetIndexesSF(int* vIndex,int i0,int i1,int i2){
    vIndex[0] = i0 * fCrystal->GetMiller()->GetX(0) + i1 * fCrystal->GetMiller()->GetY(0) + i2 * fCrystal->GetMiller()->GetZ(0);
    vIndex[1] = i0 * fCrystal->GetMiller()->GetX(1) + i1 * fCrystal->GetMiller()->GetY(1) + i2 * fCrystal->GetMiller()->GetZ(1);
    vIndex[2] = i0 * fCrystal->GetMiller()->GetX(2) + i1 * fCrystal->GetMiller()->GetY(2) + i2 * fCrystal->GetMiller()->GetZ(2);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_efz::GetIndexesEC(double* vIndexEC,int* vIndexSF,int i0,int i1,int i2){
    vIndexEC[0] = i0;
    vIndexEC[1] = i1;
    vIndexEC[2] = i2;
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
