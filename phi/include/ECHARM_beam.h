//
//  ECHARM_beam.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_beam

#ifndef _ECHARM_beam_h
#define _ECHARM_beam_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

#ifndef _ECHARM_particle_h
#include "ECHARM_particle.h"
#endif

#ifndef _ECHARM_distribution_h
#include "ECHARM_distribution.h"
#endif

class ECHARM_beam
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_beam();
    
    virtual ~ECHARM_beam();
    
    //
    // Retrieval methods
    //    
    ECHARM_distribution* GetSizeDistributionX() {return fPositionDistributionX;};
    ECHARM_distribution* GetSizeDistributionY() {return fPositionDistributionY;};
    ECHARM_distribution* GetSizeDistributionZ() {return fPositionDistributionZ;};
    ECHARM_distribution* GetMomentumDistributionX() {return fMomentumDistributionX;};
    ECHARM_distribution* GetMomentumDistributionY() {return fMomentumDistributionY;};
    ECHARM_distribution* GetMomentumDistributionZ() {return fMomentumDistributionZ;};
    
    int GetNumberOfParticles() {return fParticleArray.size();};
    std::vector<ECHARM_particle*> GetParticles() {return fParticleArray;};
    std::vector<float> GetParticlesPercentages() {return fPercentage;};
    
    //
    // Set methods
    //
    void AddParticle(ECHARM_particle *particle,float percentage);
    void DeleteParticle(unsigned int vIndex);
   
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_beam*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_beam&);    
    void PrintParticleArray();
    void PrintBeamProperties();
    void PrintBeamGeometricalProperties();

    //
    // Calculate methods
    //
    void ResetParticlesInitialVector();
    ECHARM_particle *GenerateParticle();
    
public:
    
    int operator==(const ECHARM_beam&) const;
    int operator!=(const ECHARM_beam&) const;
    
public:
    
    ECHARM_beam(ECHARM_beam&);
    ECHARM_beam(const ECHARM_beam&);
    const ECHARM_beam & operator=(const ECHARM_beam&);
    void InitializePointersBeam();
    
private:   
    std::vector<float> fPercentage;
    std::vector<ECHARM_particle*> fParticleArray;

    ECHARM_distribution* fPositionDistributionX;
    ECHARM_distribution* fPositionDistributionY;
    ECHARM_distribution* fPositionDistributionZ;

    ECHARM_distribution* fMomentumDistributionX;
    ECHARM_distribution* fMomentumDistributionY;
    ECHARM_distribution* fMomentumDistributionZ;
};

#endif
