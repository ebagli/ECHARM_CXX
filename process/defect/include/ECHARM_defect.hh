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
    
    virtual void Init(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void ComputeDispl(ECHARM_3vec*,ECHARM_3vec*);
    virtual void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);
    virtual bool IsInHotZone();

    void ComputeAnglesFromBurgerAndLineDirections();
    double GetAngleBurgerLine() {return fBurger->GetAngle(fLine);}
    virtual double GetBurgerEdge() {return sin(GetAngleBurgerLine())*fBurger->GetModule();}
    virtual double GetBurgerScrew() {return cos(GetAngleBurgerLine())*fBurger->GetModule();}
    
protected:
    double fPoissonRatio;
    ECHARM_3vec* fBurger;
    ECHARM_3vec* fLine;

    ECHARM_3vec* fHotLimit;

public:
#include "ECHARM_defect.hxx"
};
#endif
