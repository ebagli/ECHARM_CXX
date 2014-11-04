//
//  ECHARM_beam_H8_2012.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_beam_H8_2012_h

#include "ECHARM_beam_H8_2012.hh"
#include "ECHARM_distribution_gauss.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam_H8_2012::ECHARM_beam_H8_2012(){

    ECHARM_particle* proton = new ECHARM_particle(+1,cProtonMass);
    
    AddParticle(proton,1.);
    
    fDistrMomentumX = new ECHARM_distribution_gauss(0.,10.67*microrad*400.*GeV);
    fDistrMomentumY = new ECHARM_distribution_gauss(0.,7.66*microrad*400.*GeV);
    fDistrMomentumZ = new ECHARM_distribution_const(400.*GeV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam_H8_2012::~ECHARM_beam_H8_2012(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif