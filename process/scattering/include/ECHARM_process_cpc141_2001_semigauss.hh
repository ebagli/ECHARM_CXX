//
//  ECHARM_process_cpc141_2001_semigauss.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_cpc141_2001_semigauss_h
#define _ECHARM_process_cpc141_2001_semigauss_h

#include "ECHARM_process_cpc141_2001.hh"

class ECHARM_process_cpc141_2001_semigauss: public ECHARM_process_cpc141_2001
{
public:
    ECHARM_process_cpc141_2001_semigauss();
    virtual ~ECHARM_process_cpc141_2001_semigauss();

    virtual double ComputeE(ECHARM_strip*,ECHARM_particle*,double);
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);
};
#endif
