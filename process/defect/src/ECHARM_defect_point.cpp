//
//  ECHARM_defect_point.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//  Eq. (16) and (2)
//

#ifdef _ECHARM_defect_point_h

#include "ECHARM_defect_point.hh"

ECHARM_defect_point::ECHARM_defect_point(double defect_density){
    fTotalProbThetaSS = 0.3;
    fInitialProb = fTotalProbThetaSS;
    fDefectDensity = defect_density;
    fName = "defect_point";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect_point::~ECHARM_defect_point(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_point::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    UpdateConstants(strip,part);
    fTotalProbThetaSS = fInitialProb * fDefectDensity / strip->GetCrystal()->GetNucleiDensity();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_point::DoAfterInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    fTotalProbThetaSS = fInitialProb;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_defect_point::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    double vTheta = 0.;
    
    double vStep = GetStepLengthSinceLastProcess();
    vStep *= (0.5 * (strip->GetAtD()->ComputeMax() + strip->GetElD()->ComputeMax() - (GetAtDSinceLastProcess() + GetElDSinceLastProcess())));
    
    double vInvMFP = ComputeXS_SS(strip,part,fThetaMin);
    vInvMFP *= strip->GetCrystal()->GetNucleiDensity();
    
    double vZss = +DBL_MAX;
    if(vStep>0. && vInvMFP>0.){
        vZss = -log(drand48()) / vInvMFP / vStep;
    }
    else{
        std::cout << fName << " " << vStep << " " << vInvMFP << " " << strip->GetAtD()->ComputeMax() << " " << strip->GetElD()->ComputeMax() << " " << GetAtDSinceLastProcess() << " " << GetElDSinceLastProcess() << std::endl;
    }
    
    if(vZss < fTotalProbThetaSS){
        double vTheta2 = ComputeTheta2(strip,part,vStep);
        vTheta += ComputeThetaSS(strip,part,vTheta2);
        ResetSinceLastProcess();
    }
    
    return vTheta;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

