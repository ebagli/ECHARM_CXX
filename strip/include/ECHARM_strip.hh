//
//  ECHARM_strip.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_strip
//

#ifndef _ECHARM_strip_h
#define _ECHARM_strip_h
#include "ECHARM_crystal.hh"
#include "ECHARM_EC.hh"
#include "ECHARM_3vec.hh"

class ECHARM_strip{
public:
    ECHARM_strip();

    virtual ~ECHARM_strip();
    
    ECHARM_EC* GetEF(int);

    void Print();
    void PrintGeometry();

#ifdef ROOT_
    void PrintECtoTH();
#endif
    
    bool IsIn(ECHARM_3vec*);
    bool IsBent(int);
    
protected:
    ECHARM_3vec* fDim; // Dimensions
    ECHARM_3vec* fPos; // Dimensions
    ECHARM_3vec* fBR; // Bending radiuses
    ECHARM_3vec* fBRconst; // Bending radiuses
    ECHARM_3vec* fAL; // Angles between crystal miller direction and physical volume
    
    ECHARM_crystal* fCrystal;
    
    ECHARM_EC* fPot;
    ECHARM_EC* fAtD;
    ECHARM_EC* fElD;
    ECHARM_EC* fEFX;
    ECHARM_EC* fEFY;
    ECHARM_EC* fEFZ;
    /* 
     Reference system:
     (X,Y,Z) centered in (0.,0.,0.)
    */
    
#include "ECHARM_strip.hxx"
};
#endif
