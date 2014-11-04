//
//  ECHARM_defect.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_defect_h
#define _ECHARM_defect_h

#include "ECHARM_displacement.hh"

class ECHARM_defect: public ECHARM_displacement
{
public:
    ECHARM_defect(double,double,bool);
    virtual ~ECHARM_defect();
    
    virtual void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void Init(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void ComputeDispl(ECHARM_3vec*,ECHARM_3vec*);
    virtual void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);
    
    void ComputeAnglesFromBurgerAndLineDirections(ECHARM_3vec*,ECHARM_3vec*);

protected:
    double fPoissonRatio;
    double fBurger;
    
public:
#include "ECHARM_defect.hxx"
};
#endif