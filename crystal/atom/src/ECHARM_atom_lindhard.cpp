//
//  ECHARM_atom_lindhard.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_atom_lindhard.hh"


ECHARM_atom_lindhard::ECHARM_atom_lindhard(std::string  AtomName,
                                         double Z,
                                         double A,
                                         double DebyeTemperature,
                                         double AverageIonizationConstant):
ECHARM_atom(AtomName,Z,A,DebyeTemperature,AverageIonizationConstant){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom_lindhard::~ECHARM_atom_lindhard(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_lindhard::ComputeRecFF(double RecVec2)
{
    double vResult = -1.0;
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_lindhard::ComputeFF(double Vec)
{
    double vResult = 0.0;
    double vConstant = fSquareRoot(3) * GetThomasFermiRadius() ;
    vResult = fSquareRoot(Vec * Vec +  vConstant * vConstant);
    vResult -= Vec;
    vResult /= vConstant;
    return vResult ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_lindhard::ComputeFFDerivate(double Vec)
{
    double vResult = 0.0;
    double vConstant = fSquareRoot(3) * GetThomasFermiRadius() ;
    vResult = ( - 1.0 + Vec / fSquareRoot(Vec * Vec +  vConstant * vConstant) );
    vResult /= vConstant;
    return vResult ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
