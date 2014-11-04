//
//  ECHARM_beam_COMECER.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_COMECER.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_COMECER::ECHARM_beam_COMECER(double angx_zero,double angy_zero,double angx_sigma = 0.,double angy_sigma = 0.){

    ECHARM_particle* proton = new ECHARM_particle(+1,cProtonMass);
    
    AddParticle(proton,1.);
    
    double vBeamEnergy = 16.5 * MeV;
    
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

ECHARM_beam_COMECER::~ECHARM_beam_COMECER(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
