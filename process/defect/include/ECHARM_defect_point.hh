//
//  ECHARM_defect_point.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_defect_point_h
#define _ECHARM_defect_point_h

#include "ECHARM_process_ss.hh"

class ECHARM_defect_point: public ECHARM_process_ss
{
public:
    ECHARM_defect_point(double);
    virtual ~ECHARM_defect_point();
        
    void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    void DoAfterInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);

private:
    double fDefectDensity;
    double fInitialProb;
};
#endif