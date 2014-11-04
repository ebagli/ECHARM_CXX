//
//  ECHARM_process_cpc141_2001.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_cpc141_2001_h
#define _ECHARM_process_cpc141_2001_h

#include "ECHARM_process_ms.hh"

class ECHARM_process_cpc141_2001: public ECHARM_process_ms
{
public:
    ECHARM_process_cpc141_2001();
    virtual ~ECHARM_process_cpc141_2001();
        
    virtual void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);

    double ComputeE(ECHARM_strip*,ECHARM_particle*,double);

    double ComputeThetaSS(ECHARM_strip*,ECHARM_particle*);

    
protected:
    double fA;
    double fB;
    double fE;
};
#endif