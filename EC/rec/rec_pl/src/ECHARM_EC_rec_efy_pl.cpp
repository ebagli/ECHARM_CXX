//
//  ECHARM_EC_rec_efy_pl.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_EC_rec_efy_pl_h

#include "ECHARM_EC_rec_efy_pl.hh"

ECHARM_EC_rec_efy_pl::ECHARM_EC_rec_efy_pl(ECHARM_crystal* crystal,
                                           int recX):
ECHARM_EC_rec_efy(crystal,
                  recX,
                  0,
                  0){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_rec_efy_pl::~ECHARM_EC_rec_efy_pl(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_EC_rec_efy_pl::GetIndexesSF(int* vIndex,int i0,int,int){
    vIndex[0] = fCrystal->GetMiller()->GetX(0) * i0;
    vIndex[1] = fCrystal->GetMiller()->GetX(1) * i0;
    vIndex[2] = fCrystal->GetMiller()->GetX(2) * i0;
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif