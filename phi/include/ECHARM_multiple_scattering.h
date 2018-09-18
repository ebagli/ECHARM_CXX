//
//  ECHARM_multiple_scattering.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_multiple_scattering

#include "ECHARM_distribution.h"

#ifndef _ECHARM_multiple_scattering_h
#define _ECHARM_multiple_scattering_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cstddef>

#ifndef _ECHARM_multiple_scattering_functions_h
#include "ECHARM_multiple_scattering_functions.h"
#endif


class ECHARM_multiple_scattering: public ECHARM_multiple_scattering_functions
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_multiple_scattering();
    ECHARM_multiple_scattering(ECHARM_crystal *Crystal,ECHARM_particle *Particle);
    
    virtual ~ECHARM_multiple_scattering();
    
    //
    // Retrieval methods
    //
    ECHARM_distribution* GetNuclearScatteringOutgoingDistribution() {return fNuclearScatteringOutgoingDistribution;};
    ECHARM_distribution* GetElectronScatteringOutgoingDistribution() {return fElectronScatteringOutgoingDistribution;};
    ECHARM_distribution* GetSingleElectronScatteringOutgoingDistribution() {return fSingleElectronScatteringOutgoingDistribution;};
    
    unsigned int GetNuclearScatteringModel() {return fNuclearScatteringModel;};
    unsigned int GetElectronScatteringModel() {return fElectronScatteringModel;};
    unsigned int GetSingleScatteringModel() {return fSingleScatteringModel;};

    //
    // Set methods
    //    
    void SetNuclearScatteringOutgoingDistribution(ECHARM_distribution* distribution) {fNuclearScatteringOutgoingDistribution = distribution;};
    void SetElectronScatteringOutgoingDistribution(ECHARM_distribution* distribution) {fElectronScatteringOutgoingDistribution = distribution;};
    void SetSingleElectronScatteringOutgoingDistribution(ECHARM_distribution* distribution) {fSingleElectronScatteringOutgoingDistribution = distribution;};
    
    void SetNuclearScatteringModel(unsigned int vType) {fNuclearScatteringModel = vType;};
    void SetElectronScatteringModel(unsigned int vType) {fElectronScatteringModel = vType;};
    void SetSingleScatteringModel(unsigned int vType) {fSingleScatteringModel = vType;};
    
    void UpdateNuclearScatteringOutgoingDistribution(double *vParameters = NULL);
    void UpdateElectronScatteringOutgoingDistribution(double *vParameters = NULL);
    void UpdateSingleElectronScatteringOutgoingDistribution(double *vParameters = NULL);
    
    //
    // Calculate scattering methods
    //
    bool DoScatteringPlanar(ECHARM_distribution *vDistribution, unsigned int vCrystalComponent);
    bool DoScatteringAxial(ECHARM_distribution *vDistribution, unsigned int vCrystalComponent);
    
    bool DoNuclearScatteringPlanar(double *vParameters = NULL);
    bool DoNuclearScatteringAxial(double *vParameters = NULL);
    
    bool DoElectronScatteringPlanar(double *vParameters = NULL);
    bool DoElectronScatteringAxial(double *vParameters = NULL);
    
    bool DoSingleScatteringPlanar(double *vParameters = NULL);
    bool DoSingleScatteringAxial(double *vParameters = NULL);
    bool DoNuclearReaction() {return 1;};
    
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_multiple_scattering*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_multiple_scattering&);
    
    //
    // Calculate methods
    //

public:
    
    int operator==(const ECHARM_multiple_scattering&) const;
    int operator!=(const ECHARM_multiple_scattering&) const;
    
public:
    
    ECHARM_multiple_scattering(ECHARM_multiple_scattering&);
    ECHARM_multiple_scattering(const ECHARM_multiple_scattering&);
    const ECHARM_multiple_scattering & operator=(const ECHARM_multiple_scattering&);
    void InitializePointersMultipleScattering();
    
private:
    ECHARM_distribution* fNuclearScatteringOutgoingDistribution;
    ECHARM_distribution* fElectronScatteringOutgoingDistribution;
    ECHARM_distribution* fSingleElectronScatteringOutgoingDistribution;
    
    unsigned int fSingleScatteringModel;
    unsigned int fNuclearScatteringModel;
    unsigned int fElectronScatteringModel;
};

#endif
