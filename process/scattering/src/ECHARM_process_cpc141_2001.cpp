//
//  ECHARM_process_cpc141_2001.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//  Eq. (16) and (2)
//

#include "ECHARM_process_cpc141_2001.hh"

ECHARM_process_cpc141_2001::ECHARM_process_cpc141_2001(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_cpc141_2001::~ECHARM_process_cpc141_2001(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    return ComputeThetaSS(strip,part);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001::ComputeThetaSS(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (16)
    double vU = drand48();
    double vThetaSS = fA * fB * fSquareRoot( (1.-vU) / (vU*fB*fB+fA*fA) ) ;
    return vThetaSS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_cpc141_2001::Init(ECHARM_strip* strip,ECHARM_particle* part){
    fA = ComputeThetaMin(strip,part);
    fB = ComputeThetaMax(strip,part);
    fE = ComputeE(strip,part,strip->GetDim()->GetZ());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001::ComputeE(ECHARM_strip* strip,ECHARM_particle* part,double length){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (13)
    // vLRT = Log(ReducedThickness)
    double vLRT = pow(strip->GetCrystal()->GetZ(),0.666666666666) * length;
    vLRT /= fSquare(part->GetBeta());
    vLRT /= strip->GetCrystal()->GetRadLength();
    vLRT = log(vLRT);
    
    double vE = 0.;

    if(vLRT<0.5){
        vE = 4.841E-2;
        vE += 6.348E-3*vLRT;
        vE += 6.096E-4*fSquare(vLRT);
    }
    else{
        vE = -1.908E-2;
        vE += 1.106E-1*vLRT;
        vE -= 5.729E-3*fSquare(vLRT);
    }
    
    if(vE<0.){vE = 0.;}
    
    return vE;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


