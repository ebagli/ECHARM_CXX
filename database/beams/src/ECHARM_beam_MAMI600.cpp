//
//  ECHARM_beam_MAMI600.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_MAMI600.hh"
#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_MAMI600::ECHARM_beam_MAMI600(double thetaxin,double thetaxyin_sigma = 30. * microrad){

    ECHARM_particle* electron = new ECHARM_particle(-1,cElectronMass);
    
    AddParticle(electron,1.);
    
    double vBeamEnergy = 600.*MeV;
    fDistrMomentumX = new ECHARM_distribution_gauss(thetaxin*vBeamEnergy,thetaxyin_sigma*vBeamEnergy);
    fDistrMomentumY = new ECHARM_distribution_gauss(0.,thetaxyin_sigma*vBeamEnergy);
    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_MAMI600::~ECHARM_beam_MAMI600(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
