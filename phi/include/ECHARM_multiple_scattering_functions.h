//
//  ECHARM_multiple_scattering_functions.h
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
//  Short class description:
//   Class ECHARM_multiple_scattering_functions

#ifndef _ECHARM_multiple_scattering_functions_h
#define _ECHARM_multiple_scattering_functions_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cstddef>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

#ifndef _ECHARM_particle_h
#include "ECHARM_particle.h"
#endif

#ifndef _ECHARM_crystal_h
#include "ECHARM_crystal.h"
#endif

#ifdef ROOT_
#include "TH1.h"
#endif

class ECHARM_multiple_scattering_functions
{
public:
    
    //
    // Constructor to Build an element directly; no reference to isotopes
    //
    ECHARM_multiple_scattering_functions();
    ECHARM_multiple_scattering_functions(ECHARM_crystal *Crystal,ECHARM_particle *Particle);
    
    virtual ~ECHARM_multiple_scattering_functions();
    
    //
    // Retrieval methods
    //
    double GetCrossedMaterialLength() const {return fCrossedMaterialLength;};
    double GetRadiationLength() const {return fRadiationLength;};
    ECHARM_particle* GetParticle() const {return fParticle;}     
    ECHARM_crystal* GetCrystal() const {return fCrystal;}
    
    //
    // Set methods
    //
    void SetCrossedMaterialLength(double vCrossedMaterialLength) {fCrossedMaterialLength = vCrossedMaterialLength;};
    
    void SetRadiationLength(double RadiationLength) {fRadiationLength = RadiationLength;}
    void SetRadiationLength(std::string Type);     
    void SetParticle(ECHARM_particle *Particle) {fParticle = Particle;}     
    void SetCrystal(ECHARM_crystal *Crystal) {fCrystal = Crystal;}
 
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_multiple_scattering_functions*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_multiple_scattering_functions&);    
    void PrintMultipleScatteringProperties();
    
#ifdef ROOT_
    void PrintMultipleScatteringFunctionTH1(unsigned int vType);
    void PrintMultipleScatteringDistributionTH1(ECHARM_distribution* vDistribution);
#endif
    
    //
    // Calculate methods
    //
    double EvaluateInverseRadiationLengthTsai(); //!< Y.S. Tsai, Rev. Mod. Phys. 46, 815 (1974).
    double EvaluateRadiationLengthTsai(); //!< Y.S. Tsai, Rev. Mod. Phys. 46, 815 (1974).
    double EvaluateInverseRadiationLengthJackson(); //!< Jackson (1978).
    double EvaluateRadiationLengthJackson(); //!< Jackson (1978).

    double EvaluateMeanEnergyTransfer();

    double EvaluateBetheBlochLogarithmicTerm();
    double EvaluateBetheBlochDensityEffectTerm();
    double EvaluateBetheBlochMeanEnergyLoss();
    double EvaluateBetheBlochScatteringAngle();
    double EvaluateElectronMaximumKineticTransfer();
    
    double EvaluateMultipleScatteringAngleTaratin();
    double EvaluateMultipleScatteringAngleHighland();
    double EvaluateMultipleScatteringAngleUrban();
    double EvaluateMultipleScatteringAngleLynch(double fF = 0.96);

    double EvaluateMultipleScatteringTransverseEnergyVariationTaratin() {return EvaluateMultipleScatteringAngleTaratin() * fParticle->GetMomentumVector()->GetZ();};
    double EvaluateMultipleScatteringTransverseEnergyVariationHighland() {return EvaluateMultipleScatteringAngleHighland() * fParticle->GetMomentumVector()->GetZ();};
    double EvaluateMultipleScatteringTransverseEnergyVariationUrban() {return EvaluateMultipleScatteringAngleUrban() * fParticle->GetMomentumVector()->GetZ();};
    double EvaluateMultipleScatteringTransverseEnergyVariationLynch(double fF = 0.96) {return EvaluateMultipleScatteringAngleLynch(fF) * fParticle->GetMomentumVector()->GetZ();};
    
    double EvaluateScatteringAngle(unsigned int vType, double *vParameters = NULL);
    double EvaluateScatteringTransverseEnergyVariation(unsigned int vType, double *vParameters = NULL);

    double EvaluateSingleScatteringProbabilityBiryukov();
    double EvaluateSingleScatteringEnergyVariationConstantBiryukov();
    double EvaluateSingleScatteringEnergyVariationMeanBiryukov();
    double EvaluateSingleScatteringEnergyVariationVarianceBiryukov();
    double EvaluateSingleScatteringEnergyVariationBiryukov();
    double EvaluateSingleScatteringAngleBiryukov() {return EvaluateSingleScatteringEnergyVariationBiryukov() * fParticle->GetMomentumVector()->GetZ();}

public:
    
    int operator==(const ECHARM_multiple_scattering_functions&) const;
    int operator!=(const ECHARM_multiple_scattering_functions&) const;
    
public:
    
    ECHARM_multiple_scattering_functions(ECHARM_multiple_scattering_functions&);
    ECHARM_multiple_scattering_functions(const ECHARM_multiple_scattering_functions&);
    const ECHARM_multiple_scattering_functions & operator=(const ECHARM_multiple_scattering_functions&);
    void InitializePointersMultipleScatteringFunctions();
    
private:
    double fCrossedMaterialLength;
    double fRadiationLength;
    ECHARM_particle *fParticle;             
    ECHARM_crystal *fCrystal;
};

#endif
