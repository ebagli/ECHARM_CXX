//
//  ECHARM_process_ms_tikhomirov.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//  Eq. (16) and (2)
//

#include "ECHARM_process_ms_tikhomirov.hh"

ECHARM_process_ms_tikhomirov::ECHARM_process_ms_tikhomirov(){
    fTotalProbThetaSS = 0.2;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ms_tikhomirov::~ECHARM_process_ms_tikhomirov(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    
    double vLength = part->GetStepLength() * ComputeLengthMod(strip,part);
    
    ComputeStdDev(strip,part,vLength);

    double vThetaMS = ComputeThetaMS(strip,part);
    
    double vTheta = 0.;
    double vStep = vLength;

    bool bExit = true;

    do{
        bExit = true;
        double vRand = drand48();
        double vZss = -log(vRand) * vStep / fTotalProbThetaSS;
        
        if(vZss < vStep){
            double vTheta2 = ComputeTheta2(strip,part,vStep * ComputeLengthMod(strip,part));
            vTheta += ComputeThetaSS(strip,part,vTheta2);
            vStep -= vZss;
            bExit = false;
        }

    }while(bExit==false);
    
    vTheta += vThetaMS;
    
    return vTheta;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeThetaSS(ECHARM_strip* strip,ECHARM_particle* part,double theta2){
    double vInvThetaSS = fSquareRoot(1. + drand48() * (fSquare(fThetaMax/theta2) - 1.));
    return (fThetaMax / vInvThetaSS);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms_tikhomirov::Init(ECHARM_strip* strip,ECHARM_particle* part){
    fThetaMin = ComputeThetaMin(strip,part);
    fThetaMax = ComputeThetaMax(strip,part);
    fXS_SSconstant = ComputeXS_SSconstant(strip,part);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeTheta2(ECHARM_strip* strip,ECHARM_particle* part,double length){
    double vInvTheta2 = fTotalProbThetaSS / (length * fXS_SSconstant * strip->GetCrystal()->GetNucleiDensity());
    vInvTheta2 += 1./fSquare(fThetaMax);
    return fSquareRoot(1./vInvTheta2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeXS_SSconstant(ECHARM_strip* strip,ECHARM_particle* part){
    double vTotal = part->GetZ() * strip->GetCrystal()->GetZ() * cFineStructureConstant * cPlanckConstant;
    vTotal /= part->GetMomVel();
    return (cPi * fSquare(vTotal));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeXS_SS(ECHARM_strip* strip,ECHARM_particle* part,double theta2){
    double vTotal = 1./fSquare(theta2)-1./fSquare(fThetaMax);
    return (vTotal*fXS_SSconstant);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeThetaMin(ECHARM_strip* strip,ECHARM_particle* part){
    double vA = pow(strip->GetCrystal()->GetZ(),0.3333333333) / part->GetMomMod();
    vA *= cPlanckConstant;
    vA /= cBohrRadius;;
    return vA;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeThetaMax(ECHARM_strip* strip,ECHARM_particle* part){
    double vB = pow(strip->GetCrystal()->GetA()/amu,0.3333333333) / part->GetMomMod();
    vB *= cPlanckConstant;
    vB /= cElectronRadius;
    return vB;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


