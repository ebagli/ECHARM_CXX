//
//  ECHARM_lattice_cubic.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifndef _ECHARM_lattice_cubic_h

#include "ECHARM_lattice_cubic.hh"

ECHARM_lattice_cubic::ECHARM_lattice_cubic():ECHARM_lattice(){
    Add(0.5,0.5,0.5);
    Add(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice_cubic::~ECHARM_lattice_cubic(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
