//
//  ECHARM_beam_general.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_beam_general_h

#include "ECHARM_beam_general.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_general::ECHARM_beam_general(ECHARM_particle* particle,double beam_energy,double angx_zero = 0.,double angx_sigma = 0.,double angy_zero = 0.,double angy_sigma = 0.){
    
    AddParticle(particle,1.);
    
    if(angx_sigma != 0.){
        fDistrMomentumX = new ECHARM_distribution_box(angx_zero*beam_energy,angx_sigma*beam_energy);
    }
    else{
        fDistrMomentumX = new ECHARM_distribution_const(angx_zero*beam_energy);
    }

    if(angy_sigma != 0.){
        fDistrMomentumY = new ECHARM_distribution_box(angy_zero*beam_energy,angy_sigma*beam_energy);
    }
    else{
        fDistrMomentumY = new ECHARM_distribution_const(angy_zero*beam_energy);
    }

    fDistrMomentumZ = new ECHARM_distribution_const(beam_energy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_general::~ECHARM_beam_general(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
