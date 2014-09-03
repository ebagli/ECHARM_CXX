//
//  ECHARM_atom_xray.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_atom_xray.hh"

ECHARM_atom_xray::ECHARM_atom_xray(std::string  AtomName,
                                   double Z,
                                   double A,
                                   double DebyeTemperature,
                                   double AverageIonizationConstant,
                                   double ExperimentalFormFactorParameters[12]):
ECHARM_atom(AtomName,Z,A,DebyeTemperature,AverageIonizationConstant){
    for(unsigned int i=0;i<12;i++){
        fExperimentalFormFactorParameters[i] = ExperimentalFormFactorParameters[i];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom_xray::~ECHARM_atom_xray()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_xray::ComputeRecFF(double RecVec2)
{
    double vResult = 0.0;
    
    for(unsigned int i=0;i<6;i++){
        vResult += (fExperimentalFormFactorParameters[i] * exp(- RecVec2 * fExperimentalFormFactorParameters[i+6] / 16. / (cPi * cPi)) );
    }
    
    vResult = 1.0 - vResult;
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_xray::ComputeFF(double Vec)
{
    double vResult = 0.0;
    
    for(unsigned int i=0;i<6;i++)
    {
        vResult += (fExperimentalFormFactorParameters[i]);
        vResult /= (1. + Vec / fExperimentalFormFactorParameters[i+6] / GetThomasFermiRadius());
    }
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_xray::ComputeFFDerivate(double Vec)
{
    double vResult = -1;
    return vResult ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
