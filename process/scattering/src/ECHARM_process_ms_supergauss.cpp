//
//  ECHARM_process_ms_supergauss.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_process_ms_supergauss_h

#include "ECHARM_process_ms_supergauss.hh"
#include "ECHARM_distribution_gauss.hh"

ECHARM_process_ms_supergauss::ECHARM_process_ms_supergauss():
ECHARM_process_ms(){
    fR = 2.3;
    fA = 0.89;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_ms_supergauss::~ECHARM_process_ms_supergauss(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_ms_supergauss::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    double vLength = part->GetStepLength();
    ComputeStdDev(strip,part,vLength);
    fStdDev *= ComputeAvgDen(strip,part);
    
    if(drand48() < fA){
        return ComputeThetaMS(strip,part);
    }
    else{
        fStdDev *= fR;
        return ComputeThetaMS(strip,part);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
