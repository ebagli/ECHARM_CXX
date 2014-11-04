//
//  ECHARM_EC_const.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef _ECHARM_EC_const_h

#include "ECHARM_EC_const.hh"

ECHARM_EC_const::ECHARM_EC_const(std::string name,
                                 ECHARM_crystal *crystal,
                                 double val):
ECHARM_EC(name,
          crystal){
    fConst = val;
    fName = name;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_EC_const::~ECHARM_EC_const(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif