//
//  ECHARM_process_ss.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_ss_h
#define _ECHARM_process_ss_h

#include "ECHARM_process_ms_tikhomirov.hh"

class ECHARM_process_ss: public ECHARM_process_ms_tikhomirov
{
public:
    ECHARM_process_ss();
    virtual ~ECHARM_process_ss();
    
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);
};
#endif