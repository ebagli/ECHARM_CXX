//
//  ECHARM_beam_H8_2012.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_beam_H8_2012.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_gauss.hh"

ECHARM_beam_H8_2012::ECHARM_beam_H8_2012(){

    ECHARM_particle* proton = new ECHARM_particle(+1,cProtonMass);
    
    AddParticle(proton,1.);
    
    ECHARM_distribution *distr_mom_x = new ECHARM_distribution_gauss(0.,10.67*microrad*400.*GeV);
    ECHARM_distribution *distr_mom_y = new ECHARM_distribution_gauss(0.,7.66*microrad*400.*GeV);
    ECHARM_distribution *distr_mom_z = new ECHARM_distribution_box(400.*GeV,0.);

    fDistrMomentumX = distr_mom_x;
    fDistrMomentumY = distr_mom_y;
    fDistrMomentumZ = distr_mom_z;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_H8_2012::~ECHARM_beam_H8_2012(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
