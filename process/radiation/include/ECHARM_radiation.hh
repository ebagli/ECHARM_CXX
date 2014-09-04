//
//  ECHARM_radiation.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_radiation_h
#define _ECHARM_radiation_h

#include "ECHARM_process.hh"
#define MAX_STEP_NUM 16382

class ECHARM_radiation: public ECHARM_process
{
public:
    ECHARM_radiation(int,double,double,int,int);
    virtual ~ECHARM_radiation();
    
    void DoOnStrip(ECHARM_strip*,ECHARM_particle*);
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*);
    void DoAfterInteraction(ECHARM_strip*,ECHARM_particle*);
    void Init(ECHARM_strip*,ECHARM_particle*);

    void Store();
    void PrintTrajToFile(std::string);
    
    double ComputeRadEmProb(ECHARM_strip*,ECHARM_particle*,double);
    
private:
    double fAngColl;
    double fStepMaxLength;
    int fAngXbins;
    int fAngYbins;

    int fEnBins;
    double fEnMin;
    double fEnMax;
    double fEnStep;
    std::vector<double> fRadEmProb;

    int fStepNum;
    double fStep[MAX_STEP_NUM];
    double fVelX[MAX_STEP_NUM];
    double fVelY[MAX_STEP_NUM];
    double fAccX[MAX_STEP_NUM];
    double fAccY[MAX_STEP_NUM];
    double fVelPreSctX[MAX_STEP_NUM];
    double fVelPreSctY[MAX_STEP_NUM];
    
public:
#include "ECHARM_radiation.hxx"
};
#endif