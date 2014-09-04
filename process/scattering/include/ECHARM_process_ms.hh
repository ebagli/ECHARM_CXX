//
//  ECHARM_process_ms.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_ms_h
#define _ECHARM_process_ms_h

#include "ECHARM_process.hh"
#include "ECHARM_distribution.hh"

class ECHARM_process_ms: public ECHARM_process
{
public:
    ECHARM_process_ms();
    virtual ~ECHARM_process_ms();
    
    void DoOnStrip(ECHARM_strip*,ECHARM_particle*);
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*);

    virtual void Init(ECHARM_strip*,ECHARM_particle*);
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);


    double ComputeStdDev(ECHARM_strip*,ECHARM_particle*,double);
    double ComputeThetaMS(ECHARM_strip*,ECHARM_particle*);
    double ComputeLengthMod(ECHARM_strip*,ECHARM_particle*);
    virtual double ComputeThetaMin(ECHARM_strip*,ECHARM_particle*);
    virtual double ComputeThetaMax(ECHARM_strip*,ECHARM_particle*);

protected:
    double fStdDev;

    double fConst;
    ECHARM_distribution* fDistr;
};
#endif