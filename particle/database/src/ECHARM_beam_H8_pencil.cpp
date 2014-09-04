//
//  ECHARM_beam_H8_pencil.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_H8_pencil.hh"
#include "ECHARM_distribution_box.hh"

ECHARM_beam_H8_pencil::ECHARM_beam_H8_pencil(double angx_zero,double angx_sigma = 0.){

    ECHARM_particle* proton = new ECHARM_particle(+1,cProtonMass);
    
    AddParticle(proton,1.);
    
    double beam_energy = 400.*GeV;
    
    ECHARM_distribution *distr_mom_x = new ECHARM_distribution_box(angx_zero*beam_energy,angx_sigma*beam_energy);
    ECHARM_distribution *distr_mom_y = new ECHARM_distribution_box(0.,0.);
    ECHARM_distribution *distr_mom_z = new ECHARM_distribution_box(beam_energy,0.);

    fDistrMomentumX = distr_mom_x;
    fDistrMomentumY = distr_mom_y;
    fDistrMomentumZ = distr_mom_z;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_H8_pencil::~ECHARM_beam_H8_pencil(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
