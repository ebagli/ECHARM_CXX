//
//  ECHARM_distribution_const.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_distribution_const.hh"

ECHARM_distribution_const::ECHARM_distribution_const(double mean):
ECHARM_distribution(){
    fPar.push_back(mean);
    fParNames.push_back("Mean");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_distribution_const::~ECHARM_distribution_const(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution_const::GenerateNumber(){
    return fPar.at(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution_const::GetProbability(double x){
    if(x == fPar.at(0)){
        return 1.;
    }
    return 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


