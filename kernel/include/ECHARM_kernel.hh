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
    
    bool UpdateTransverseVariationMax(double);
        
    int UpdateStep();
    int DoStep();
    
    int DoOnStrip();
    int DoOnParticle();
    int UpdateProcesses();

    int DoBeforeInteraction();
    int Interaction();
    int DoAfterInteraction();

    int Init();
    int End();
    int Print();

    bool IsInChanneling();
    void CheckChannelingCondition();

    double GetTransverseEnergy();
    double GetPotential();
    double GetKineticEnergy();
    double GetAtD();
    double GetElD();
    double GetElectricFieldX();

    void SetSaveTrajStep(double);
    void SaveTrajStep();
    
protected:
    bool bSavePartIn;
    bool bSavePartOut;
    
    ECHARM_particle* fPart;
    ECHARM_info_save* fInfo;

    ECHARM_strip* fStrip;
    std::vector<ECHARM_process*> fProcesses;
    
    double fTimeStepMax;
    double fTimeStepMin;
    double fTransverseVariationMax;
   
    bool bSaveTrajStatus;
    double bSaveTrajStep;
    double bSaveTrajStepTemp;

    bool bExitOnDechanneling;
    // Temporary variables
    double fOverrideMaxPotential;
    bool bOverrideMaxPotential;

protected:
    bool bDEBUG;
    ECHARM_3vec* fMomHalf;
    ECHARM_3vec* fPosHalf;

    double fTimeStep;
    double fTimeStepTotal;
    int bPartIsIn;
    int fStepNumber;
    
    bool bHasBeenInChanneling;

    double fMachineError;

#include "ECHARM_kernel.hxx"
};
#endif
