//
//  ECHARM_atom_spheric.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_atom_spheric.hh"

ECHARM_atom_spheric::ECHARM_atom_spheric(std::string  AtomName,
                         double Z,
                         double A,
                         double DebyeTemperature,
                         double AverageIonizationConstant):
ECHARM_atom(AtomName,Z,A,DebyeTemperature,AverageIonizationConstant){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_atom_spheric::~ECHARM_atom_spheric(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_spheric::ComputeRecFF(double RecVec2)
{
    double vResult = 0.0;
    vResult = 1 / (1+ RecVec2 * fSquare(GetThomasFermiRadius()));
    vResult = 1.0 - vResult;
    return vResult;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_spheric::ComputeFF(double Vec)
{
    double vResult = 0.0;
    vResult = exp( - Vec / GetThomasFermiRadius() );
    return vResult ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_atom_spheric::ComputeFFDerivate(double Vec)
{
     double vResult = 0.0;
    vResult = - exp( - Vec / GetThomasFermiRadius() ) / GetThomasFermiRadius();
    return vResult ;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
