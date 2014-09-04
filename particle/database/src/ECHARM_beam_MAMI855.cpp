//
//  ECHARM_beam_MAMI855.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_MAMI855.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_gauss.hh"

ECHARM_beam_MAMI855::ECHARM_beam_MAMI855(double thetaxin){

    ECHARM_particle* electron = new ECHARM_particle(-1,cElectronMass);
    
    AddParticle(electron,1.);
    
    ECHARM_distribution *distr_mom_x = new ECHARM_distribution_gauss(thetaxin*855.*MeV,30.*microrad*855.*MeV);
    ECHARM_distribution *distr_mom_y = new ECHARM_distribution_gauss(0.,30.*microrad*855.*MeV);
    ECHARM_distribution *distr_mom_z = new ECHARM_distribution_box(855.*MeV,0.);

    fDistrMomentumX = distr_mom_x;
    fDistrMomentumY = distr_mom_y;
    fDistrMomentumZ = distr_mom_z;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_MAMI855::~ECHARM_beam_MAMI855(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
