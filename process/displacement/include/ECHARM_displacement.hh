//
//  ECHARM_displacement.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_displacement_h
#define _ECHARM_displacement_h

#include "ECHARM_process.hh"
#include "ECHARM_strip.hh"
#include "ECHARM_periodicvector.hh"
#include "ECHARM_distribution_box.hh"

class ECHARM_displacement: public ECHARM_process
{
public:
    ECHARM_displacement(double,double,bool);
    virtual ~ECHARM_displacement();
    
    void DoOnStrip(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    
    virtual void DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    virtual void Init(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);
    
    virtual bool IsInHotZone() {return false;};
    
    void Print(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*);

    void SetLimitStrip(ECHARM_strip*);

    void EvalArea(int);

    void Store();

    virtual void ComputeDispl(ECHARM_3vec*,ECHARM_3vec*);
    virtual void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);

    void SetAng(double,double,double);
    void SetAngPhi(double);
    void SetAngTheta(double);
    void SetAngPsi(double);
    
    void SetPos(ECHARM_3vec*);
    
    
protected:
    std::vector<ECHARM_3vec*> fCenter;
    std::vector<double> fAngPhi;
    std::vector<double> fAngTheta;
    std::vector<double> fAngPsi;
    std::vector<bool> fDefIsOn;

    ECHARM_3vec* fDispl;
    ECHARM_3vec* fDisplPre;
    ECHARM_3vec* fBR;

protected:
    bool bSudden;
    bool bRandomAngle;
    bool bRandomPosition;
    
    ECHARM_3vec* fLimitsHalf;

    int fNum;
    double fArea;
    double fProb;
    double fNumberOfPointsMax;
    double fNumberOfPointsTop;
    
    ECHARM_distribution* fBoxX;
    ECHARM_distribution* fBoxY;
    ECHARM_distribution* fBoxZ;
    bool bBoxYzero;

protected:
    ECHARM_3vec* fPosTemp;
    ECHARM_3vec* fPosTempPre;
    ECHARM_3vec* fZero;

    bool bVecStored;
    bool bTabVal;
    int fNumSteps[3];

    ECHARM_periodicvector* fVecCRX;
    ECHARM_periodicvector* fVecCRY;
    ECHARM_periodicvector* fVecCRZ;

    ECHARM_periodicvector* fVecBRX;
    ECHARM_periodicvector* fVecBRY;
    ECHARM_periodicvector* fVecBRZ;
    
    ECHARM_periodicvector* fVecDisplX;
    ECHARM_periodicvector* fVecDisplY;
    ECHARM_periodicvector* fVecDisplZ;
    
public:
#include "ECHARM_displacement.hxx"
};
#endif
