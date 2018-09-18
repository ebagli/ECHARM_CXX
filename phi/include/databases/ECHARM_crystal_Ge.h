//
//  ECHARM_crystal_Ge.h
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

#ifndef _ECHARM_crystal_Ge_h
#define _ECHARM_crystal_Ge_h
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

class ECHARM_crystal_Ge:public ECHARM_crystal
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_crystal_Ge(int vMillerPl[3],int vMillerAx[3]);
    virtual ~ECHARM_crystal_Ge();
    
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_Ge*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_crystal_Ge&);    
    
public:
    
    int operator==(const ECHARM_crystal_Ge&) const;
    int operator!=(const ECHARM_crystal_Ge&) const;
    
public:
    
    ECHARM_crystal_Ge(ECHARM_crystal_Ge&);
    ECHARM_crystal_Ge(const ECHARM_crystal_Ge&);
    const ECHARM_crystal_Ge & operator=(const ECHARM_crystal_Ge&);
    
private:
};

#endif
