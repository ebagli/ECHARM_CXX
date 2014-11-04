//
//  ECHARM_beam_FACET.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_FACET.hh"
#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_FACET::ECHARM_beam_FACET(double thetaxin,double thetaxyin_sigma = 30. * microrad){

    ECHARM_particle* positron = new ECHARM_particle(+1,cElectronMass);
    
    AddParticle(positron,1.);
    double vBeamEnergy = 15. * GeV;
    
    fDistrMomentumX = new ECHARM_distribution_box(thetaxin*vBeamEnergy,thetaxyin_sigma*vBeamEnergy);
    fDistrMomentumY = new ECHARM_distribution_const(0.);
    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_FACET::~ECHARM_beam_FACET(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
