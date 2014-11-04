//
//  ECHARM_distribution_gauss_cut.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_distribution_gauss_cut_h

#include "ECHARM_distribution_gauss_cut.hh"

ECHARM_distribution_gauss_cut::ECHARM_distribution_gauss_cut(double mean,double sigma,double cut):
ECHARM_distribution(){
    fPar.push_back(mean);
    fParNames.push_back("Mean");
    fPar.push_back(sigma);
    fParNames.push_back("Sigma");
    fPar.push_back(cut);
    fParNames.push_back("Cut");
    fSecondNumber = 0.;
    fUseSecond = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_distribution_gauss_cut::~ECHARM_distribution_gauss_cut(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution_gauss_cut::GenerateNumber(){
    double val = 0.;
    do{
        if(fUseSecond){
            
            fUseSecond = false;
            
            val = (fPar.at(0) + fSecondNumber * fPar.at(1));
        }
        else{
            double gaussTemp = 0.0;
            
            double gauss1 = 0.0;
            
            double gauss2 = 0.0;
            
            do{
                gauss1 = 2.0 * drand48() - 1.0;
                
                gauss2 = 2.0 * drand48() - 1.0;
                
                gaussTemp = gauss1 * gauss1 + gauss2 * gauss2;
            } while ( gaussTemp >= 1.0 );
            
            gaussTemp = fSquareRoot( (-2.0 * log(gaussTemp)) / gaussTemp);
            
            fSecondNumber = gauss2 * gaussTemp;
            
            fUseSecond = true;
            
            val = (fPar.at(0) + gaussTemp * gauss1 * fPar.at(1));
        }
    } while(fabs(val-fPar.at(0))>fabs(fPar.at(2)));
    return val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_distribution_gauss_cut::GetProbability(double x){
    if(fabs(x-fPar.at(0))>fabs(fPar.at(2))){
        return 0.;
    }
    else{
        return (exp(-0.5*fSquare((x-fPar.at(0))/fPar.at(1)))/(fSquareRoot(c2Pi)*fPar.at(1)));
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
