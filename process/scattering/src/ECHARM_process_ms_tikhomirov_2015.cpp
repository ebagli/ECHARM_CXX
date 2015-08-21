//
//  ECHARM_process_ms_tikhomirov_2015.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//  Eq. (16) and (2)
//

#ifdef _ECHARM_process_ms_tikhomirov_2015_h
#include "ECHARM_process_ms_tikhomirov_2015.hh"

ECHARM_process_ms_tikhomirov_2015::ECHARM_process_ms_tikhomirov_2015(){
    fEnergyStored = 0.;
    fTotalProbThetaSS = 0.1;
    fName = "ms_tikhomirov_2015";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ms_tikhomirov_2015::~ECHARM_process_ms_tikhomirov_2015(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    
    double vLength = part->GetStepLength();
    double vMom = part->GetMomMod();
    double vTheta = 0.;
    double vStep = vLength / ComputeAvgDen(strip,part);
    
    bool bExit = true;
    double vThetaTemp = 0.;
    double vThetaTempTot = 0.;
    double vMomTV = vMom * strip->GetCrystal()->GetThermalVibrationConstant();

    UpdateConstants(strip,part,vLength);

    do{
        bExit = true;
        double vRand = drand48();
        double vStepSS = -log(vRand) * vStep / fXS_SS;
        
        if(vStepSS < vStep){
            double vTheta2 = ComputeTheta2(strip,part,vLength * ComputeAvgDen(strip,part));
            vThetaTemp = ComputeThetaSS(strip,part,vTheta2);
            vStep -= vStepSS;
            bExit = false;
            if(drand48() > exp(-fSquare(vThetaTemp*vMomTV))){
                vThetaTempTot += vThetaTemp;
            }
        }
        
    } while(bExit==false);
    
    vTheta += vThetaTempTot;
    
    //if(vTheta == 0.){
    {
        ComputeStdDev(strip,part,vLength);
        fStdDev *= ComputeAvgDen(strip,part);
        vTheta +=  ComputeThetaMS(strip,part);
    }
    
    fEnergyStored = part->GetMomMod();
    
    return vTheta;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeThetaSS(ECHARM_strip* strip,ECHARM_particle* part,double theta2){
    double vInvThetaSS = fSquareRoot(1. + drand48() * (fSquare(fThetaMax/theta2) - 1.));
    double random = drand48();
    vInvThetaSS *= ((random - 0.5)/fabs(random - 0.5));
    return (fThetaMax / vInvThetaSS);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms_tikhomirov_2015::UpdateConstants(ECHARM_strip* strip,ECHARM_particle* part,double length){
    if(fEnergyStored != part->GetMomMod()){
        fThetaMin = ComputeThetaMin(strip,part);
        fThetaMax = ComputeThetaMax(strip,part);
        fXS_SSconstant = ComputeXS_SSconstant(strip,part);
        fEnergyStored = part->GetMomMod();
    }

    fTheta1 = ComputeTheta1(strip,part);
    fTheta2 = ComputeTheta2(strip,part,length);
    fXS_SS = ComputeXS_SS(strip,part);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms_tikhomirov_2015::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeTheta1(ECHARM_strip* strip,ECHARM_particle* part){
    double vA = 0.;
    fSquareRoot(1.13 + 3.76 * fSquare( strip->GetCrystal()->GetZ() * cFineStructureConstant / part->GetBeta() ) );
    vA /= part->GetMomMod();
    vA *= cPlanckConstant;
    vA /= strip->GetCrystal()->GetThomasFermiRadius();;
    return vA;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeTheta2(ECHARM_strip* strip,ECHARM_particle* part,double length){
    double vInvTheta2 = fTotalProbThetaSS / (length * fXS_SSconstant * strip->GetCrystal()->GetNucleiDensity());
    vInvTheta2 += 1./fSquare(fThetaMax);
    return fSquareRoot(1./vInvTheta2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeXS_SSconstant(ECHARM_strip* strip,ECHARM_particle* part){
    double vTotal = part->GetZ() * strip->GetCrystal()->GetZ() * cFineStructureConstant * cPlanckConstant;
    vTotal /= part->GetMomVel();
    return (4. * cPi * fSquare(vTotal));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeXS_SS(ECHARM_strip* strip,ECHARM_particle* part){
    double vTotal = 1./(fSquare(fThetaMax) + fSquare(fTheta1)) - 1./(fSquare(fTheta2) + fSquare(fTheta1));
    return (vTotal*fXS_SSconstant);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeThetaMin(ECHARM_strip* strip,ECHARM_particle* part){
    double vA = pow(strip->GetCrystal()->GetZ(),0.3333333333) / part->GetMomMod();
    vA *= cPlanckConstant;
    vA /= cBohrRadius;;
    return vA;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_tikhomirov_2015::ComputeThetaMax(ECHARM_strip* strip,ECHARM_particle* part){
    double vB = pow(strip->GetCrystal()->GetA()/amu,0.3333333333) / part->GetMomMod();
    vB *= cPlanckConstant;
    vB /= cElectronRadius;
    return vB;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif
