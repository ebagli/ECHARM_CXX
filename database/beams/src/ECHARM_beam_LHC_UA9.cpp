//
//  ECHARM_beam_LHC_UA9.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_beam_LHC_UA9_h

#include "ECHARM_beam_LHC_UA9.hh"
#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_LHC_UA9::ECHARM_beam_LHC_UA9(){

    ECHARM_particle* proton = new ECHARM_particle(+1,cProtonMass);
    
    AddParticle(proton,1.);
    
    double vBeamEnergy = 7. * TeV;
    
    //fDistrMomentumX = new ECHARM_distribution_gauss(0.,5.*microrad*vBeamEnergy);
    //fDistrMomentumY = new ECHARM_distribution_gauss(0.,5.*microrad*vBeamEnergy);
    fDistrMomentumX = new ECHARM_distribution_const(0.);
    fDistrMomentumY = new ECHARM_distribution_const(0.);
    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_LHC_UA9::~ECHARM_beam_LHC_UA9(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
