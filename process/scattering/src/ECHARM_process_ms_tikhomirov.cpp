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
#ifdef _ECHARM_process_ms_tikhomirov_h

#include "ECHARM_process_ms_tikhomirov.hh"

ECHARM_process_ms_tikhomirov::ECHARM_process_ms_tikhomirov(){
    fEnergyStored = 0.;
    fTotalProbThetaSS = 0.3;
    fName = "ms_tikhomirov";
    fCorrectionElectron = 1.85;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ms_tikhomirov::~ECHARM_process_ms_tikhomirov(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    
    double vLength = part->GetStepLength();
    
    double vTheta = 0.;
    double vStep = vLength / ComputeAvgDen(strip,part);
    
    bool bExit = true;
    
    do{
        bExit = true;
        double vRand = drand48();
        double vZss = -log(vRand) * vStep / fTotalProbThetaSS;
        
        if(vZss < vStep){
            double vTheta2 = ComputeTheta2(strip,part,vLength * ComputeAvgDen(strip,part));
            vTheta += ComputeThetaSS(strip,part,vTheta2);
            vStep -= vZss;
            bExit = false;
        }
        
    }while(bExit==false);
    
    if(vTheta == 0.){
        ComputeStdDev(strip,part,vLength);
        fStdDev *= ComputeAvgDen(strip,part);
        vTheta +=  ComputeThetaMS(strip,part);
    }
    
    fEnergyStored = part->GetMomMod();
    
    return vTheta;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeThetaSS(ECHARM_strip* strip,ECHARM_particle* part,double theta2){
    double vInvThetaSS = fSquareRoot(1. + drand48() * (fSquare(fThetaMax/theta2) - 1.));
    return (fThetaMax / vInvThetaSS);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms_tikhomirov::UpdateConstants(ECHARM_strip* strip,ECHARM_particle* part){
    if(fEnergyStored != part->GetMomMod()){
        fThetaMin = ComputeThetaMin(strip,part);
        fThetaMax = ComputeThetaMax(strip,part);
        fXS_SSconstant = ComputeXS_SSconstant(strip,part);
        fEnergyStored = part->GetMomMod();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms_tikhomirov::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    UpdateConstants(strip,part);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeTheta2(ECHARM_strip* strip,ECHARM_particle* part,double length){
    UpdateConstants(strip,part);
    double vInvTheta2 = fTotalProbThetaSS / (length * fXS_SSconstant * strip->GetCrystal()->GetNucleiDensity());
    vInvTheta2 += 1./fSquare(fThetaMax);
    
    double correction = 1.;
    
    if(part->GetMass()==cElectronMass){
        correction = fCorrectionElectron;
    }

    return fSquareRoot(1./vInvTheta2*correction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeXS_SSconstant(ECHARM_strip* strip,ECHARM_particle* part){
    double vTotal = part->GetZ() * strip->GetCrystal()->GetZ() * cFineStructureConstant * cPlanckConstant;
    vTotal /= part->GetMomVel();
    return (cPi * fSquare(vTotal));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov::ComputeXS_SS(ECHARM_strip* strip,ECHARM_particle* part,double theta2){
    UpdateConstants(strip,part);
    double vTotal = (fSquare(fThetaMax) - fSquare(theta2))/(fSquare(theta2)*fSquare(fThetaMax));
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


#endif
