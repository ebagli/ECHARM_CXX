//
//  ECHARM_process_bethe_bloch.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_process_bethe_bloch_h

#include "ECHARM_process_bethe_bloch.hh"
#include "ECHARM_distribution_gauss.hh"

ECHARM_process_bethe_bloch::ECHARM_process_bethe_bloch():
ECHARM_process("bethe_bloch"){
    fDistr = new ECHARM_distribution_gauss(0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_bethe_bloch::~ECHARM_process_bethe_bloch(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_bethe_bloch::ComputeElectronMaximumKineticTransfer(ECHARM_strip* strip,ECHARM_particle* part) //!<
{
    double KineticTransfer = 2 * fSquare(cElectronMass * part->GetBeta() * part->GetGamma());
    KineticTransfer /= (1 + 2 * part->GetGamma() * cElectronMass / part->GetMass() + fSquare(cElectronMass/part->GetMass()));
    return KineticTransfer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_bethe_bloch::ComputeLogarithmicTerm(ECHARM_strip* strip,ECHARM_particle* part) //!<
{
    double LogarithmicTerm = 2 * cElectronMass * fSquare(part->GetBeta() * part->GetGamma());
    LogarithmicTerm *= ComputeElectronMaximumKineticTransfer(strip,part);
    LogarithmicTerm /= (fSquare(strip->GetCrystal()->GetAverageIonizationConstant()));
    return (0.5 * log(LogarithmicTerm));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_bethe_bloch::ComputeDensityEffectTerm(ECHARM_strip* strip,ECHARM_particle* part) //!<
{
    double DensityTerm = 0.0;
    return DensityTerm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_bethe_bloch::ComputeMeanEnergyLoss(ECHARM_strip* strip,ECHARM_particle* part) //!<
{
    double EnergyLoss = (4 * cPi * fSquare(cElectronRadius) * cElectronMass);
    EnergyLoss *= (fSquare(fabs(part->GetZ()))*strip->GetCrystal()->GetZ());
    EnergyLoss *= (ComputeLogarithmicTerm(strip,part) + ComputeDensityEffectTerm(strip,part) - fSquare(part->GetBeta()));
    EnergyLoss /= (fSquare(part->GetBeta()) * strip->GetCrystal()->GetA());
    EnergyLoss *= strip->GetCrystal()->GetMassDensity();
    return EnergyLoss;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process_bethe_bloch::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    fStdDev = fSquareRoot(ComputeMeanEnergyLoss(strip,part) * part->GetStepLength() * cElectronMass) * ComputeAvgElD(strip,part);

    fDistr->SetPar(1,fStdDev);
    
    double vMomVar = part->GetMom()->GetModule() - fDistr->GenerateNumber();

    part->GetMom()->ScaleModule(vMomVar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif