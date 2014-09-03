//
//  ECHARM_defect.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_defect_h
#define _ECHARM_defect_h

#include "ECHARM_process.hh"
#include "ECHARM_distribution_box.hh"

class ECHARM_defect: public ECHARM_process
{
public:
    ECHARM_defect(double,bool);
    virtual ~ECHARM_defect();
    
    void DoOnStrip(ECHARM_strip*,ECHARM_particle*);
    void DoOnParticle(ECHARM_strip*,ECHARM_particle*);
    void Init(ECHARM_strip*,ECHARM_particle*);

    void Store();

    virtual void CompDispl(ECHARM_3vec*,ECHARM_3vec*);
    virtual void ComputeBR(ECHARM_3vec*,ECHARM_3vec*);

    
protected:
    ECHARM_3vec* fBurger;
    double fPoissonRatio;

    ECHARM_3vec* fDispl;
    ECHARM_3vec* fBR;

private:
    bool bSudden;

    ECHARM_3vec* fLimitsHalf;

    int fDefNum;
    double fArea;
    std::vector<ECHARM_3vec*> fDefCenter;
    std::vector<double> fDefAnglesPhi;
    std::vector<double> fDefAnglesTheta;

    ECHARM_distribution_box* fBoxX;
    ECHARM_distribution_box* fBoxY;
    ECHARM_distribution_box* fBoxZ;


private:
    ECHARM_3vec* fPosTemp;
    ECHARM_3vec* fPosTempPre;

    bool bVecStored;
    ECHARM_periodicvector* fVecBRX;
    ECHARM_periodicvector* fVecBRY;
    ECHARM_periodicvector* fVecBRZ;
    
    ECHARM_periodicvector* fVecDisplX;
    ECHARM_periodicvector* fVecDisplY;
    ECHARM_periodicvector* fVecDisplZ;
    
public:
#include "ECHARM_defect.hxx"
};
#endif