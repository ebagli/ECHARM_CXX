//
//  ECHARM_EC_intrp.hh
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#ifdef OPENMP_
#include <omp.h>
#endif

#ifndef _ECHARM_EC_intrp_h
#define _ECHARM_EC_intrp_h

#include "ECHARM_EC.hh"
#include "ECHARM_periodicvector.hh"

class ECHARM_EC_intrp: public ECHARM_EC
{
public:
    ECHARM_EC_intrp(std::string,ECHARM_crystal*,int = 512,int = 1,int = 1);
    ~ECHARM_EC_intrp();

#ifdef ROOT_
    virtual void PrintToTH(std::string = "");
#endif

    void Store(ECHARM_EC*);

public:
    virtual double Get(double,double,double);
    
private:
    ECHARM_periodicvector* fVec;
    
    int fNumSteps[3];
    double fStep[3];

#include "ECHARM_EC_intrp.hxx"
};

#endif
