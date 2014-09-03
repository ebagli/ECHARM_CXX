//
//  ECHARM_process_cpc141_2001_doublegauss.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_cpc141_2001_doublegauss_h
#define _ECHARM_process_cpc141_2001_doublegauss_h

#include "ECHARM_process_cpc141_2001.hh"

class ECHARM_process_cpc141_2001_doublegauss: public ECHARM_process_cpc141_2001
{
public:
    ECHARM_process_cpc141_2001_doublegauss();
    virtual ~ECHARM_process_cpc141_2001_doublegauss();
    
    double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);
    double ComputeStdDevMod(ECHARM_strip*,ECHARM_particle*);
};
#endif