//
//  ECHARM_beam_SLAC.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_SLAC.hh"
#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_SLAC::ECHARM_beam_SLAC(double vBeamEnergy, double thetaxin=0.,double thetaxyin_sigma = 30. * microrad){

    ECHARM_particle* electron = new ECHARM_particle(-1,cElectronMass);
    
    AddParticle(electron,1.);
    
    if(vBeamEnergy > 10. * GeV){
        std::cout << "Max beam energy 10 GeV" << std::endl;
    }
    
    fDistrMomentumX = new ECHARM_distribution_gauss(thetaxin*vBeamEnergy,thetaxyin_sigma*vBeamEnergy);
    fDistrMomentumY = new ECHARM_distribution_const(0.);
    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_SLAC::~ECHARM_beam_SLAC(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
