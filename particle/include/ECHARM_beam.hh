//
//  ECHARM_beam.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//  Class ECHARM_beam

#ifndef _ECHARM_beam_h
#define _ECHARM_beam_h

#include "ECHARM_particle.hh"
#include "ECHARM_distribution.hh"
#include "ECHARM_strip.hh"
#include "ECHARM_3vec.hh"

class ECHARM_beam
{
public:
    
    ECHARM_beam();
    ECHARM_beam(ECHARM_particle*,double);

    virtual ~ECHARM_beam();
    
    void GenerateParticle();
    
    void AddParticle(ECHARM_particle*,double);
    
    void DistrPosFromStrip(ECHARM_strip*);
    
    void Print();
    
protected:
    ECHARM_particle* fParticle;
    
    std::vector<ECHARM_particle*> fParticles;
    std::vector<double> fPercentages;

    ECHARM_distribution* fDistrParticles;

    ECHARM_distribution* fDistrPositionX;
    ECHARM_distribution* fDistrMomentumX;

    ECHARM_distribution* fDistrPositionY;
    ECHARM_distribution* fDistrMomentumY;

    ECHARM_distribution* fDistrPositionZ;
    ECHARM_distribution* fDistrMomentumZ;

#include "ECHARM_beam.hxx"
};

#endif
