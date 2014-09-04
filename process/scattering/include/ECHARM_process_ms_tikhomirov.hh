//
//  ECHARM_process_ms_tikhomirov.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_ms_tikhomirov_h
#define _ECHARM_process_ms_tikhomirov_h

#include "ECHARM_process_ms.hh"

class ECHARM_process_ms_tikhomirov: public ECHARM_process_ms
{
public:
    ECHARM_process_ms_tikhomirov();
    virtual ~ECHARM_process_ms_tikhomirov();
        
    virtual void Init(ECHARM_strip*,ECHARM_particle*);
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);

    double ComputeTheta2(ECHARM_strip*,ECHARM_particle*,double);

    double ComputeThetaSS(ECHARM_strip*,ECHARM_particle*,double);
    double ComputeXS_SSconstant(ECHARM_strip*,ECHARM_particle*);
    double ComputeXS_SS(ECHARM_strip*,ECHARM_particle*,double);
    
    double ComputeThetaMin(ECHARM_strip*,ECHARM_particle*);
    double ComputeThetaMax(ECHARM_strip*,ECHARM_particle*);

protected:
    double fThetaMin;
    double fThetaMax;
    double fTotalProbThetaSS;
    double fXS_SSconstant;
};
#endif