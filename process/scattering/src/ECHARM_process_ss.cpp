//
//  ECHARM_process_ss.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//  Eq. (16) and (2)
//

#ifdef _ECHARM_process_ss_h

#include "ECHARM_process_ss.hh"

ECHARM_process_ss::ECHARM_process_ss(){
    fTotalProbThetaSS = 0.3;
    fName = "ss";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ss::~ECHARM_process_ss(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ss::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    
    double vTheta = 0.;
    double vStep = GetStepLengthSinceLastProcess();
    vStep *= (0.5 * (GetAtDSinceLastProcess() + GetElDSinceLastProcess()));

    double vInvMFP = ComputeXS_SS(strip,part,fThetaMin);
    vInvMFP *= strip->GetCrystal()->GetNucleiDensity();
    
    double vZss = +DBL_MAX;
    if(vStep>0. && vInvMFP>0.){
        vZss = -log(drand48()) / vInvMFP / vStep;
    }
    
    //if(vZss < fTotalProbThetaSS){
    if(true){

        double vTheta2 = ComputeTheta2(strip,part,vStep);
        vTheta += ComputeThetaSS(strip,part,vTheta2);
        ResetSinceLastProcess();
    }
    
    return vTheta;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

