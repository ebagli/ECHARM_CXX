//
//  ECHARM_process.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_h
#define _ECHARM_process_h

#include "ECHARM_strip.hh"
#include "ECHARM_particle.hh"
#include "ECHARM_info_save.hh"

class ECHARM_process
{
public:
    ECHARM_process(std::string);
    virtual ~ECHARM_process();
    
    virtual void DoOnStrip(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void DoOnParticle(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    
    virtual void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void DoAfterInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    virtual void Init(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void End(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    virtual void Print(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    virtual double ComputeAvgAtD(ECHARM_strip*,ECHARM_particle*);
    virtual double ComputeAvgElD(ECHARM_strip*,ECHARM_particle*);
    virtual double ComputeAvgDen(ECHARM_strip*,ECHARM_particle*);
    
protected:
    std::string fName;
    bool fInitialized;
    bool fEnded;
    
    double fStepLengthSinceLastProgress;
    double fAtDSinceLastProgress;
    double fElDSinceLastProgress;

#include "ECHARM_process.hxx"

};
#endif