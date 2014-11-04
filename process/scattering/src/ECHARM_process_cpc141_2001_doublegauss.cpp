//
//  ECHARM_process_cpc141_2001_doublegauss.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//

#include "ECHARM_process_cpc141_2001_doublegauss.hh"

ECHARM_process_cpc141_2001_doublegauss::ECHARM_process_cpc141_2001_doublegauss(){
    fName = "cpc141_2001_doublegauss";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_cpc141_2001_doublegauss::~ECHARM_process_cpc141_2001_doublegauss(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001_doublegauss::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    
    double vV = drand48();
    
    double vLength = part->GetStepLength();
    
    ComputeStdDev(strip,part,vLength);

    if(vV < fE){
        ComputeStdDevMod(strip,part);
    }
    else{
    }

    fStdDev *= ComputeAvgDen(strip,part);

    return ComputeThetaMS(strip,part);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001_doublegauss::ComputeStdDevMod(ECHARM_strip* strip,ECHARM_particle* part){
    double vE = ComputeE(strip,part,ComputeAvgDen(strip,part));
    fStdDev = fSquareRoot((1. - (1.-vE)*fStdDev*fStdDev) / vE);
    return fStdDev;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


