//
//  ECHARM_manager.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_manager_h
#define _ECHARM_manager_h

#include "ECHARM_info_save.hh"
#include "ECHARM_kernel.hh"
#include "ECHARM_beam.hh"

class ECHARM_manager
{
public:
    ECHARM_manager(ECHARM_beam*,ECHARM_info_save*);
    virtual ~ECHARM_manager();
    
    int Init();
    int Go();
    int End();

    int Print();

    int GenerateParticle();

protected:
    ECHARM_beam* fBeam;
    ECHARM_info_save* fInfo;

    std::vector<ECHARM_kernel*> fKernel;

    double fTimeStepTotal;
    bool bSaveTrajStatus;
    
#include "ECHARM_manager.hxx"
};
#endif