//
//  ECHARM_torsion.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifdef _ECHARM_torsion_h

#include "ECHARM_torsion.hh"

ECHARM_torsion::ECHARM_torsion(double torsiony,double sigmay,double torsionx = 0.,double sigmax = 0.):
ECHARM_process("torsion"){
    
    fTorsionX = torsionx;
    fTorsionY = torsiony;
    
    fDistrX = new ECHARM_distribution_gauss(0.,sigmax);
    fDistrY = new ECHARM_distribution_gauss(0.,sigmay);

    fX = 0.;
    fY = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_torsion::~ECHARM_torsion(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_torsion::DoBeforeInteraction(ECHARM_strip*,ECHARM_particle* part,ECHARM_info_save*){
    if(fDistrX->GetPar(1)!=0.){
        fX = fDistrX->GenerateNumber();
    }
    if(fDistrY->GetPar(1)!=0.){
        fY = fDistrY->GenerateNumber();
    }
    
    double vMom = part->GetMomMod();
    
    double vThetaX = fX * fTorsionX;
    double vThetaY = fY * fTorsionY;
        
    part->GetMom()->AddX( vMom * vThetaX );
    part->GetMom()->AddY( vMom * vThetaY );
    part->GetMom()->SubtractZ( vMom * vThetaX + vMom * vThetaY);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_torsion::DoAfterInteraction(ECHARM_strip*,ECHARM_particle* part,ECHARM_info_save*){
    double vMom = part->GetMomMod();
    
    double vThetaX = fX * fTorsionX;
    double vThetaY = fY * fTorsionY;
    
    part->GetMom()->SubtractX( vMom * vThetaX );
    part->GetMom()->SubtractY( vMom * vThetaY );
    part->GetMom()->AddZ( vMom * vThetaX + vMom * vThetaY);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif