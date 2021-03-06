//
//  ECHARM_beam_SLAC.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_beam_SLAC_h

#include "ECHARM_beam_SLAC.hh"
#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_SLAC::ECHARM_beam_SLAC(double vBeamEnergy, double thetaxin=0.,double thetaxyin_sigma = 30. * microrad,int charge = -1,bool gauss = true){

    ECHARM_particle* electron = new ECHARM_particle(-1,cElectronMass);
    
    ECHARM_particle* positron = new ECHARM_particle(+1,cElectronMass);
    
    if(charge==-1){
        AddParticle(electron,1.);
    }
    
    if(charge==+1){
        AddParticle(positron,1.);
    }
    
    if(gauss){
    	fDistrMomentumX = new ECHARM_distribution_gauss(thetaxin*vBeamEnergy,thetaxyin_sigma*vBeamEnergy);
    	fDistrMomentumY = new ECHARM_distribution_gauss(0.,thetaxyin_sigma*vBeamEnergy);
    }
    else{
    	fDistrMomentumX = new ECHARM_distribution_box(thetaxin*vBeamEnergy,thetaxyin_sigma*vBeamEnergy);
    	fDistrMomentumY = new ECHARM_distribution_box(0.,thetaxyin_sigma*vBeamEnergy);
    }

    fDistrMomentumZ = new ECHARM_distribution_const(vBeamEnergy);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_SLAC::~ECHARM_beam_SLAC(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
