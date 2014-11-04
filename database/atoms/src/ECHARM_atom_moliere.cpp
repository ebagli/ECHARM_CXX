//
//  ECHARM_atom_moliere.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_atom_moliere_h

#include "ECHARM_atom_moliere.hh"

ECHARM_atom_moliere::ECHARM_atom_moliere(std::string  AtomName,
                                         double Z,
                                         double A,
                                         double DebyeTemperature,
                                         double AverageIonizationConstant):
ECHARM_atom(AtomName,Z,A,DebyeTemperature,AverageIonizationConstant){
    fMoliereCoefficientsAlfa[0] = 0.1;
    fMoliereCoefficientsAlfa[1] = 0.55;
    fMoliereCoefficientsAlfa[2] = 0.35;

    fMoliereCoefficientsBeta[0] = 6.0;
    fMoliereCoefficientsBeta[1] = 1.2;
    fMoliereCoefficientsBeta[2] = 0.3;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom_moliere::~ECHARM_atom_moliere(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_moliere::ComputeRecFF(double RecVec2){
    double vResult = 0.0;
    
    double vTF = GetThomasFermiRadius();
    double vTemp = 0.;
    for(unsigned int i=0;i<3;i++){
        vTemp = RecVec2 * vTF * vTF / fSquare(fMoliereCoefficientsBeta[i]);
        vResult += (fMoliereCoefficientsAlfa[i] / (1. +  vTemp));
    }
    
    vResult = 1.0 - vResult;
    
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_moliere::ComputeFF(double Vec){
    
    double vResult = 0.0;
    
    for(unsigned int i=0;i<3;i++){
        vResult += (fMoliereCoefficientsAlfa[i] * exp( -fMoliereCoefficientsBeta[i] * fabs(Vec)/GetThomasFermiRadius() ) );
    }
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_moliere::ComputeFFDerivate(double Vec){
    
    double vResult = 0.0;
    
    for(unsigned int i=0;i<3;i++){
        vResult -= (fMoliereCoefficientsAlfa[i]  * fMoliereCoefficientsBeta[i] * exp( - fMoliereCoefficientsBeta[i] * fabs(Vec) / GetThomasFermiRadius() ) / GetThomasFermiRadius());
    }
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif