//
//  ECHARM_process_cpc141_2001_semigauss.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//

#include "ECHARM_process_cpc141_2001_semigauss.hh"

ECHARM_process_cpc141_2001_semigauss::ECHARM_process_cpc141_2001_semigauss(){
    fName = "cpc141_2001_semigauss";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_cpc141_2001_semigauss::~ECHARM_process_cpc141_2001_semigauss(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001_semigauss::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
   
    double vV = drand48();
        
    if(vV < fE){
        return ComputeThetaSS(strip,part);
    }
    else{
        double vLength = part->GetStepLength() * ComputeLengthMod(strip,part);
        ComputeStdDev(strip,part,vLength);
        return ComputeThetaMS(strip,part);
    }

    return 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


