//
//  ECHARM_lattice_zincblend_a.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_lattice_zincblend_a_h

#include "ECHARM_lattice_zincblend_a.hh"

ECHARM_lattice_zincblend_a::ECHARM_lattice_zincblend_a():ECHARM_lattice(){
    for(unsigned int i=0;i<1;i++){
        Add(0.0+0.25*i,0.0+0.25*i,0.0+0.25*i);
        Add(0.5+0.25*i,0.5+0.25*i,0.0+0.25*i);
        Add(0.0+0.25*i,0.5+0.25*i,0.5+0.25*i);
        Add(0.5+0.25*i,0.0+0.25*i,0.5+0.25*i);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice_zincblend_a::~ECHARM_lattice_zincblend_a(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif