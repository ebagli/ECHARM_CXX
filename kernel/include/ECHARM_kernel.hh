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
#include "ECHARM_beam.hh"
#include "ECHARM_process.hh"

class ECHARM_kernel
{
public:
    ECHARM_kernel(ECHARM_strip*);
    virtual ~ECHARM_kernel();
    
    double GetTransverseVariationMax();
    bool SetTransverseVariationMax(double);
        
    bool UpdateStep();
    int DoStep();
    
    int DoOnStrip();
    int DoOnParticle();

    int DoBeforeInteraction();
    int Interaction();
    int DoAfterInteraction();

    int Init();
    int End();
    int Print();

protected:
    bool bSavePartIn;
    bool bSavePartOut;
    
    ECHARM_particle* fPart;
    ECHARM_info_save* fInfo;

    ECHARM_strip* fStrip;
    std::vector<ECHARM_process*> fProcesses;
    
    
    double fTimeTimeStepMax;
    double fTimeTimeStepMin;
    double fTransverseVariationMax;
   
    bool bSaveTrajStatus;
    double bSaveTrajStep;
    double bSaveTrajStepTemp;

    // Temporary variables
protected:
    ECHARM_3vec* fMomHalf;
    ECHARM_3vec* fPosHalf;

    double fTimeStep;
    double fTimeStepTotal;
    bool bPartIsIn;

    
#include "ECHARM_kernel.hxx"
};
#endif