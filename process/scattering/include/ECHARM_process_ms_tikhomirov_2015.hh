//
//  ECHARM_process_ms_tikhomirov_2015.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_ms_tikhomirov_2015_h
#define _ECHARM_process_ms_tikhomirov_2015_h

#include "ECHARM_process_ms.hh"

class ECHARM_process_ms_tikhomirov_2015: public ECHARM_process_ms
{
public:
    ECHARM_process_ms_tikhomirov_2015();
    virtual ~ECHARM_process_ms_tikhomirov_2015();
        
    virtual void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);

    double ComputeTheta1(ECHARM_strip*,ECHARM_particle*);
    double ComputeTheta2(ECHARM_strip*,ECHARM_particle*,double);

    double ComputeThetaSS(ECHARM_strip*,ECHARM_particle*,double);
    double ComputeXS_SSconstant(ECHARM_strip*,ECHARM_particle*);
    double ComputeXS_SS(ECHARM_strip*,ECHARM_particle*);
    
    double ComputeThetaMin(ECHARM_strip*,ECHARM_particle*);
    double ComputeThetaMax(ECHARM_strip*,ECHARM_particle*);

    inline void SetTotalProbThetaSS(double sigmass) {fTotalProbThetaSS = sigmass;}

    void UpdateConstants(ECHARM_strip*,ECHARM_particle*,double);
    
protected:
    double fEnergyStored;
    double fTheta1;
    double fTheta2;
    double fThetaMin;
    double fThetaMax;
    double fTotalProbThetaSS;
    double fXS_SSconstant;
    double fXS_SS;
};
#endif
