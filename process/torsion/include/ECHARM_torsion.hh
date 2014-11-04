//
//  ECHARM_torsion.h
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_torsion_h
#define _ECHARM_torsion_h

#include "ECHARM_process.hh"
#include "ECHARM_distribution_gauss.hh"

class ECHARM_torsion: public ECHARM_process
{
public:
    ECHARM_torsion(double,double,double,double);
    virtual ~ECHARM_torsion();
    
    void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    void DoAfterInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

protected:
    double fTorsionX; // µrad/mm
    double fTorsionY; // µrad/mm
    
    double fX;
    double fY;
    
    ECHARM_distribution_gauss* fDistrX;
    ECHARM_distribution_gauss* fDistrY;
public:
#include "ECHARM_torsion.hxx"
};
#endif