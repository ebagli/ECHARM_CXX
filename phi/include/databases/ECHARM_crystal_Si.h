//
//  ECHARM_crystal_Si.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

///
///   This class has to be filled with atomic parameters only.
///   Thermal vibration amplitude is automatically evaluated.
///   No input from standard databases are implemented right now.
///

#ifndef _ECHARM_crystal_Si_h
#define _ECHARM_crystal_Si_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <iomanip>

#ifndef _ECHARM_crystal_h
#include "ECHARM_crystal.h"
#endif

class ECHARM_crystal_Si:public ECHARM_crystal
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_crystal_Si(int vMillerPl[3],int vMillerAx[3]);
    virtual ~ECHARM_crystal_Si();
    
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_Si*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_Si&);    
    
public:
    
    int operator==(const ECHARM_crystal_Si&) const;
    int operator!=(const ECHARM_crystal_Si&) const;
    
public:
    
    ECHARM_crystal_Si(ECHARM_crystal_Si&);
    ECHARM_crystal_Si(const ECHARM_crystal_Si&);
    const ECHARM_crystal_Si & operator=(const ECHARM_crystal_Si&);
    
private:
};

#endif
