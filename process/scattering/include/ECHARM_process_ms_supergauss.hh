//
//  ECHARM_process_ms_supergauss.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_process_ms_supergauss_h
#define _ECHARM_process_ms_supergauss_h

#include "ECHARM_process_ms.hh"

class ECHARM_process_ms_supergauss: public ECHARM_process_ms
{
public:
    ECHARM_process_ms_supergauss();
    virtual ~ECHARM_process_ms_supergauss();
    
    virtual double ComputeThetaScattering(ECHARM_strip*,ECHARM_particle*);

public:
    void SetR(double r) {fR=r;}
    double GetR() {return fR;}

    void SetA(double A) {fA=A;}
    double GetA() {return fA;}

protected:
    double fA;
    double fR;
};
#endif
