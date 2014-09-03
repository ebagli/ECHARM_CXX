//
//  ECHARM_lattice_fcc.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_lattice_fcc.hh"

ECHARM_lattice_fcc::ECHARM_lattice_fcc():ECHARM_lattice(){
    Add(0.0,0.0,0.0);
    Add(0.5,0.5,0.0);
    Add(0.0,0.5,0.5);
    Add(0.5,0.0,0.5);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_lattice_fcc::~ECHARM_lattice_fcc(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


