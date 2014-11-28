//
//  ECHARM_radiation_noparts.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_radiation_noparts_h
#define _ECHARM_radiation_noparts_h

#include "ECHARM_process.hh"
#define MAX_STEP_NUM 16382

class ECHARM_radiation_noparts: public ECHARM_process
{
public:
    ECHARM_radiation_noparts();
    ECHARM_radiation_noparts(int,int);
    virtual ~ECHARM_radiation_noparts();
    
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    void DoAfterInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    void Store();
    void PrintTrajToFile(std::string);
    
    double ComputeRadEmProb(ECHARM_strip*,ECHARM_particle*,double);
    
private:
    double fAngColl;
    double fStepMaxLength;
    int fAngXbins;
    int fAngYbins;

    double fInitialAngleX;
    double fInitialAngleY;
    
    bool bSliceTraj;
    
    int fStepNum;
    double fStep[MAX_STEP_NUM];
    double fVelX[MAX_STEP_NUM];
    double fVelY[MAX_STEP_NUM];
    double fAccX[MAX_STEP_NUM];
    double fAccY[MAX_STEP_NUM];
    double fVelPreSctX[MAX_STEP_NUM];
    double fVelPreSctY[MAX_STEP_NUM];
    
public:
#include "ECHARM_radiation_noparts.hxx"
};
#endif