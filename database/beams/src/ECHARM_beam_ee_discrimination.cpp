//
//  ECHARM_beam_ee_discrimination.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_beam_ee_discrimination_h

#include "ECHARM_beam_ee_discrimination.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_ee_discrimination::ECHARM_beam_ee_discrimination(double vBeamEnergy,double fraction = 0.1,double angx_zero = 0.,double angx_sigma = 0.,double angy_zero = 0.,double angy_sigma = 0.){

    ECHARM_particle* electron = new ECHARM_particle(-1,cElectronMass);
    ECHARM_particle* positron = new ECHARM_particle(+1,cElectronMass);
    
    AddParticle(electron,1.-fraction);
    AddParticle(positron,fraction);
    
    if(angx_sigma != 0.){
        fDistrMomentumX = new ECHARM_distribution_box(angx_zero*vBeamEnergy,angx_sigma*vBeamEnergy);
    }
    else{
        fDistrMomentumX = new ECHARM_distribution_const(angx_zero*vBeamEnergy);
    }

    if(angy_sigma != 0.){
        fDistrMomentumY = new ECHARM_distribution_box(angy_zero*vBeamEnergy,angy_sigma*vBeamEnergy);
    }
    else{
        fDistrMomentumY = new ECHARM_distribution_const(angy_zero*vBeamEnergy);
    }

    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_ee_discrimination::~ECHARM_beam_ee_discrimination(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif