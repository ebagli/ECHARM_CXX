//
//  ECHARM_beam_H8_pencil.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_H8_pencil.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_H8_pencil::ECHARM_beam_H8_pencil(double angx_zero,double angx_sigma = 0.){

    ECHARM_particle* proton = new ECHARM_particle(+1,cProtonMass);
    
    AddParticle(proton,1.);
    
    if(angx_sigma != 0.){
        fDistrMomentumX = new ECHARM_distribution_box(angx_zero*400.*GeV,angx_sigma*400.*GeV);
    }
    else{
        fDistrMomentumX = new ECHARM_distribution_const(angx_zero*400.*GeV);
    }
    
    fDistrMomentumY = new ECHARM_distribution_const(0.);
    fDistrMomentumZ = new ECHARM_distribution_const(400.*GeV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_H8_pencil::~ECHARM_beam_H8_pencil(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
