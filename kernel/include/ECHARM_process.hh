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

class ECHARM_process
{
public:
    ECHARM_process(std::string);
    virtual ~ECHARM_process();
    
    virtual void DoOnStrip(ECHARM_strip*,ECHARM_particle*);
    virtual void DoOnParticle(ECHARM_strip*,ECHARM_particle*);
    virtual void DoAfterInteraction(ECHARM_strip*,ECHARM_particle*);
    virtual void Init(ECHARM_strip*,ECHARM_particle*);
    
    inline std::string GetName() {return fName;};
    
protected:
    std::string fName;
};
#endif