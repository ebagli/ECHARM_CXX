//
//  ECHARM_strip.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_strip.hh"

ECHARM_strip::ECHARM_strip(){
    fBR = new ECHARM_3vec(0.,0.,0.);
    fPos = new ECHARM_3vec(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_strip::~ECHARM_strip(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_strip::IsIn(ECHARM_3vec* vPoint){
    if(fabs(vPoint->GetX()) <= (fPos->GetX() + fDim->GetX() * 0.5)){
        if(fabs(vPoint->GetY()) <= (fPos->GetY() + fDim->GetY() * 0.5)){
            if(fabs(vPoint->GetZ()) <= (fPos->GetZ() + fDim->GetZ() * 0.5)){
                return true;
            }
        }
    }
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::Print(){
    std::cout << "ECHARM_strip - Strip Properties" << std::endl;
    PrintGeometry();
    fCrystal->Print();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::PrintGeometry(){
    std::cout << "ECHARM_strip - Geometrical Properties" << std::endl;
    std::cout << "Position  X  [mm]   Y  [mm]   Z  [mm] "<< std::endl;
    fPos->Print(1.0/millimeter);
    std::cout << "Size      X  [mm]   Y  [mm]   Z  [mm] "<< std::endl;
    fDim->Print(1.0/millimeter);
    std::cout << "Bend. Rad.R_X [m]   R_Y [m]   R_Z [m]" << std::endl;
    fBR->Print();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_strip::IsBent(int vIndex){
    return ( (fBR->Get(vIndex) != 0.) ? true : false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_strip::PrintECtoTH(){
#ifdef ROOT_
    fPot->PrintToTH1("pot");
    fAtD->PrintToTH1("atd");
    fElD->PrintToTH1("eld");
    fEFX->PrintToTH1("efx");
    fEFY->PrintToTH1("efy");
    fEFZ->PrintToTH1("efz");
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC* ECHARM_strip::GetEF(int vIndex){
    switch (vIndex) {
        case 0:
            return fEFX;
            break;
        case 1:
            return fEFY;
            break;
        case 2:
            return fEFZ;
            break;
        default:
            break;
    }
    return fEFX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
