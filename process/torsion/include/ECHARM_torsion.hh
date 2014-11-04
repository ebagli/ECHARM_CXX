//
//  ECHARM_undulator.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_undulator_h
#define _ECHARM_undulator_h

#include "ECHARM_displacement.hh"

class ECHARM_undulator: public ECHARM_displacement
{
public:
    ECHARM_undulator(double,double,double,bool);
    virtual ~ECHARM_undulator();
    
    virtual void Init(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void ComputeDispl(ECHARM_3vec*,ECHARM_3vec*);
    virtual void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);
    
protected:
    double fAmplitude;
    double fPeriod;
    double fPhase;
        
public:
#include "ECHARM_undulator.hxx"
};
#endif