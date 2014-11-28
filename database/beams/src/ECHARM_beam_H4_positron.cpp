//
//  ECHARM_beam_H4_positron.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_beam_H4_positron_h

#include "ECHARM_beam_H4_positron.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_H4_positron::ECHARM_beam_H4_positron(double angx_zero,double angx_sigma = 0.,double vBeamEnergy = 120.E9){

    ECHARM_particle* positron = new ECHARM_particle(+1,cElectronMass);
        
    AddParticle(positron,1.);
    
    if(angx_sigma != 0.){
        fDistrMomentumX = new ECHARM_distribution_gauss(angx_zero*vBeamEnergy,angx_sigma*vBeamEnergy);
    }
    else{
        fDistrMomentumX = new ECHARM_distribution_const(angx_zero*vBeamEnergy);
    }
    
    fDistrMomentumY = new ECHARM_distribution_const(0.);
    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_H4_positron::~ECHARM_beam_H4_positron(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif