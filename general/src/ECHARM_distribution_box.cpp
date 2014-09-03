//
//  ECHARM_distribution_box.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_distribution_box.hh"

ECHARM_distribution_box::ECHARM_distribution_box(double mean,double sigma):
ECHARM_distribution(){
    fPar.push_back(mean);
    fParNames.push_back("Mean");
    fPar.push_back(sigma);
    fParNames.push_back("HalfWidth");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_distribution_box::~ECHARM_distribution_box(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution_box::GenerateNumber(){
    return ( drand48() * 2.0 - 1.0 ) * fPar.at(1) + fPar.at(0);;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution_box::GetProbability(double x){
    return ((fabs(x-fPar.at(0))<fPar.at(1)) ? 0.5/fPar.at(1) : 0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


