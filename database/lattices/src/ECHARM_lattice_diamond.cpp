//
//  ECHARM_lattice_diamond.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_lattice_diamond.hh"

ECHARM_lattice_diamond::ECHARM_lattice_diamond():ECHARM_lattice(){
    for(unsigned int i=0;i<2;i++){
        Add(0.0+0.25*i,0.0+0.25*i,0.0+0.25*i);
        Add(0.5+0.25*i,0.5+0.25*i,0.0+0.25*i);
        Add(0.0+0.25*i,0.5+0.25*i,0.5+0.25*i);
        Add(0.5+0.25*i,0.0+0.25*i,0.5+0.25*i);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice_diamond::~ECHARM_lattice_diamond(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


