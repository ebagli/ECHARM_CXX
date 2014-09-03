//
//  ECHARM_EC_rec_atd_ax.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_EC_rec_atd_ax.hh"

ECHARM_EC_rec_atd_ax::ECHARM_EC_rec_atd_ax(ECHARM_crystal* crystal,
                                           int recX,
                                           int recY):
ECHARM_EC_rec_atd(crystal,
                  recX,
                  recY,
                  0){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_atd_ax::~ECHARM_EC_rec_atd_ax(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_atd_ax::GetIndexesSF(int* vIndex,int i0,int i1,int){
    if(fCrystal->GetMiller()->IsMainAxis()){
        vIndex[0] = i0 * fCrystal->GetMiller()->GetX(0) + i1 * fCrystal->GetMiller()->GetY(0);
        vIndex[1] = i0 * fCrystal->GetMiller()->GetX(1) + i1 * fCrystal->GetMiller()->GetY(1);
        vIndex[2] = i0 * fCrystal->GetMiller()->GetX(2) + i1 * fCrystal->GetMiller()->GetY(2);
        return true;
    }
    else{
        vIndex[0]=i0;
        vIndex[1]=i1;
        vIndex[2]=0;
        if(fCrystal->GetMiller()->CheckOrthogonalityToAxis(vIndex)){
            fCrystal->GetMiller()->ReverseMillerOrder(vIndex);
            return true;
        }
        return false;
    }
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_atd_ax::GetIndexesEC(double* vIndexEC,int* vIndexSF,int i0,int i1,int){
    if(fCrystal->GetMiller()->IsMainAxis()){
        vIndexEC[0] = i0;
        vIndexEC[1] = i1;
        return true;
    }
    else{
        vIndexEC[0] = 0;
        vIndexEC[1] = 0;
        for(unsigned int k=0;k<3;k++){
            vIndexEC[0] += (vIndexSF[k] * fCrystal->GetMiller()->GetX(k) / fCrystal->GetMiller()->GetModuleSquaredX());
            vIndexEC[1] += (vIndexSF[k] * fCrystal->GetMiller()->GetY(k) / fCrystal->GetMiller()->GetModuleSquaredY());
        }
        return true;
    }
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

