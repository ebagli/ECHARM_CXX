//
//  ECHARM_kernel.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_kernel_h
#define _ECHARM_kernel_h

#include "ECHARM_3vec.hh"
#include "ECHARM_strip.hh"
#include "ECHARM_particle.hh"
#include "ECHARM_process.hh"

class ECHARM_kernel
{
public:
    ECHARM_kernel(ECHARM_particle*,ECHARM_strip*);
    virtual ~ECHARM_kernel();
    
    double GetTransverseVariationMax();
    bool SetTransverseVariationMax(double);

    void Print();
    
    virtual bool UpdateStep();
    
    virtual int DoStep();
    virtual int DoStraightStep();
    
    int DoOnStrip();
    
    int DoOnParticle();
    
    int Init();
    
    bool Interaction();

protected:
    ECHARM_strip* fStrip;
    ECHARM_particle* fPart;
    std::vector<ECHARM_process*> fProcesses;
    
    double fTimeStep;
    
    double fTimeTimeStepMax;
    double fTimeTimeStepMin;
    double fTransverseVariationMax;
   
    // Temporary variables
protected:
    ECHARM_3vec* fMomHalf;
    ECHARM_3vec* fPosHalf;
    ECHARM_3vec* fBRperStepTotal;
    double fTimeStepTotal;

#ifdef ROOT_
    bool bSaveTrajStatus;
    ECHARM_Particle_Save fTimeStepSave;
    double fBRstepSave;
    TTree* fTree;
#endif
    
#include "ECHARM_kernel.hxx"
};
#endif