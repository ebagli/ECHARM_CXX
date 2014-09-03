//
//  ECHARM_process_ms.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_process_ms.hh"
#include "ECHARM_distribution_gauss.hh"

ECHARM_process_ms::ECHARM_process_ms(){
    fDistr = new ECHARM_distribution_gauss(0.,0.);
    fConst = double(13.6) * MeV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ms::~ECHARM_process_ms(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::DoOnStrip(ECHARM_strip*,ECHARM_particle*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part){
    double vMom = part->GetMomMod();

    double vTheta = ComputeThetaScattering(strip,part);
    
    double VMomVar = vTheta * vMom;
    double vPhi = c2Pi * drand48();
    
    part->GetMom()->AddX( VMomVar * cos(vPhi) );
    part->GetMom()->AddY( VMomVar * sin(vPhi) );

    part->GetMom()->ScaleModule(vMom);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    double vLength = part->GetStepLength() * ComputeLengthMod(strip,part);
    ComputeStdDev(strip,part,vLength);
    return ComputeThetaMS(strip,part);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaMin(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (2)
    double vA = 0.;
    vA = pow(strip->GetCrystal()->GetZ(),0.3333333333) / part->GetMomMod();
    vA *= cFineStructureConstant / 1.4 * cElectronMass;
    return vA;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaMax(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (2)
    double vB = 0.;
    vB = pow(strip->GetCrystal()->GetA()/amu,-0.3333333333) / part->GetMomMod();
    vB *= 274. * cElectronMass;
    return vB;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeThetaMS(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (16)
    fDistr->SetPar(1,fStdDev);
    return fDistr->GenerateNumber();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeStdDev(ECHARM_strip* strip,ECHARM_particle* part,double length){
    fStdDev = fConst * fabs(part->GetZ()) / part->GetMomVel();
    fStdDev *= fSquareRoot(length / strip->GetCrystal()->GetRadLength());
    return fStdDev;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_ms::Init(ECHARM_strip* strip,ECHARM_particle* part){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms::ComputeLengthMod(ECHARM_strip* strip,ECHARM_particle* part){
    double vLengthMod = (strip->GetAtD()->Get(part->GetPos()) + strip->GetAtD()->Get(part->GetPosPre()))*0.5;
    return vLengthMod;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
