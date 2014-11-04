//
//  ECHARM_particle.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_particle

#ifndef _ECHARM_particle_h
#define _ECHARM_particle_h
#include <vector>
#include <math.h>

#include "ECHARM_constants.hh"
#include "ECHARM_3vec.hh"

class ECHARM_particle
{
public:
    
    ECHARM_particle();
    ECHARM_particle(double,double);

    virtual ~ECHARM_particle();
    
    double GetKineticEnergy();
    double GetEnergy();
    double GetBeta();
    double GetGamma();
    double GetMomMod();
    double GetMomVel();
    double GetStepLength();

    void Print();
    
private:
    double fZ;
    double fMass;             
    ECHARM_3vec *fPos;
    ECHARM_3vec *fMom;
    
    ECHARM_3vec* fPosPre;
    ECHARM_3vec* fMomPre;

    double fStepLengthSinceLastProgress;
    double fAtDSinceLastProgress;
    double fElDSinceLastProgress;

#include "ECHARM_particle.hxx"
};

#endif
