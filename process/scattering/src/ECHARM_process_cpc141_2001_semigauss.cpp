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

#ifdef _ECHARM_process_cpc141_2001_semigauss_h

#include "ECHARM_process_cpc141_2001_semigauss.hh"

ECHARM_process_cpc141_2001_semigauss::ECHARM_process_cpc141_2001_semigauss(){
    fName = "cpc141_2001_semigauss";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process_cpc141_2001_semigauss::~ECHARM_process_cpc141_2001_semigauss(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001_semigauss::ComputeThetaScattering(ECHARM_strip* strip,ECHARM_particle* part){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (6)

    double vTheta = 0.;
    double vLength = part->GetStepLength();
    fStdDev = ComputeStdDev(strip,part,vLength);
    fStdDev *= ComputeAvgDen(strip,part);
    fE = ComputeE(strip,part,vLength);
    
    fE = 0.0;
    
    if(drand48() < fE){
        vTheta = ComputeThetaSS(strip,part);
    }
    else{
        vTheta = ComputeThetaMS(strip,part);
    }
    return vTheta;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process_cpc141_2001_semigauss::ComputeE(ECHARM_strip* strip,ECHARM_particle* part,double length){
    //  Computer Physics Communications 141 (2001) 230–246
    //  Eq. (7)

    double vE = (1. - fSquare(fStdDev)) / (fSquare(fA)*(log(fB/fA) - 0.5) - fSquare(fStdDev));
    
    if(vE < 0.) {
        vE = 0.;
    }
    
    return vE;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
