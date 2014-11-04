//
//  ECHARM_beam_H4_electron_120.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_beam_H4_electron_120_h

#include "ECHARM_beam_H4_electron_120.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_H4_electron_120::ECHARM_beam_H4_electron_120(double angx_zero,double angx_sigma = 0.){

    ECHARM_particle* electron = new ECHARM_particle(-1,cElectronMass);
    
    double vBeamEnergy = 120. * GeV;
    
    AddParticle(electron,1.);
    
    if(angx_sigma != 0.){
        fDistrMomentumX = new ECHARM_distribution_box(angx_zero*vBeamEnergy,angx_sigma*vBeamEnergy);
    }
    else{
        fDistrMomentumX = new ECHARM_distribution_const(angx_zero*vBeamEnergy);
    }
    
    fDistrMomentumY = new ECHARM_distribution_const(0.);
    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_H4_electron_120::~ECHARM_beam_H4_electron_120(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif