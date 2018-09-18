//
//  ECHARM_simulation.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_simulation_h
#define _ECHARM_simulation_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

#ifndef _ECHARM_strip_h
#include "ECHARM_strip.h"
#endif

#ifndef _ECHARM_particle_h
#include "ECHARM_particle.h"
#endif

class ECHARM_simulation
{
public:
    
    //
    // Constructor to Build directly
    //
    ECHARM_simulation();
    
    virtual ~ECHARM_simulation();
    
    //
    // Retrieval methods
    //
    ECHARM_strip* GetStrip() const {return fStrip;};
    ECHARM_particle* GetParticle() const {return fParticle;};

    //
    // Set methods
    //
    void SetParticle(ECHARM_particle* particle) {fParticle = particle;};
    void SetStrip(ECHARM_strip* strip) {fStrip = strip;};
    void SetStripAndParticle(ECHARM_strip* strip,ECHARM_particle* particle)
    {
        SetStrip(strip);
        SetParticle(particle);
    };

    //
    // Printing methods
    //    
    friend std::ostream& operator<<(std::ostream&, ECHARM_simulation*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_simulation&);
    void PrintChannelingProperties(std::vector<double> vVector = std::vector<double>());
    
    //
    // Check methods
    //
    double GetTransverseEnergyPlanar();
    double GetTransverseEnergyToDechannel();

    //
    // Calculation Methods
    //
    double EvaluateMaximumPotential(std::vector<double> vVector = std::vector<double>());
    double EvaluateEffectiveInterplanarDistance(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalRadius(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalPotential(std::vector<double> vVector = std::vector<double>());
    double EvaluateLindhardAngle(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalAngle(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalMomentum(std::vector<double> vVector = std::vector<double>());
    double EvaluateOscillationPeriod(std::vector<double> vVector = std::vector<double>());
    double EvaluateGeometricEfficiency(std::vector<double> vVector = std::vector<double>());
    double EvaluatePotentialWellCentre(std::vector<double> vVector = std::vector<double>());
    
    double EvaluateCriticalRadiusAxial(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalPotentialAxial(std::vector<double> vVector = std::vector<double>());
    double EvaluateLindhardAngleAxial(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalAngleAxial(std::vector<double> vVector = std::vector<double>());
    double EvaluateCriticalMomentumAxial(std::vector<double> vVector = std::vector<double>());

    void ResetMaximumPotential() {fMaximumPotential = DBL_MAX;};
    //
    // Calculation Methods
    //

    double EvaluateMaximumChannelingAngle(std::vector<double> vVector = std::vector<double>());
    double EvaluateMaximumChannelingMomentum(std::vector<double> vVector = std::vector<double>());

    double GetPlanarElectricCharacteristicParticleReferenceFrame(double x, unsigned int vType);
    double GetAxialElectricCharacteristicParticleReferenceFrame(double x, double y, unsigned int vType);
    std::vector<double> FindPlanarElectricCharacteristicParticleReferenceFrame(unsigned int vType,std::string vOptions = "");
    std::vector<double> FindAxialElectricCharacteristicParticleReferenceFrame(unsigned int vType,std::string vOptions = "");
    
    //
    // Check Methods
    //
   
    bool StripIsBentX() {return (fStrip->GetCurvatureRadius()->GetX() != 0.0);};
    bool StripIsBentY() {return (fStrip->GetCurvatureRadius()->GetY() != 0.0);};
    
    bool IsInChanneling(double vTransverseEnergy,double vCriticalEnergy) {return (vTransverseEnergy < vCriticalEnergy);};
    bool IsInChannelingPlanar() {return IsInChanneling(GetTransverseEnergyPlanar(),EvaluateMaximumPotential());};
    
public:
    
    int operator==(const ECHARM_simulation&) const;
    int operator!=(const ECHARM_simulation&) const;
    
public:
    
    ECHARM_simulation(ECHARM_simulation&);
    ECHARM_simulation(const ECHARM_simulation&);
    const ECHARM_simulation & operator=(const ECHARM_simulation&);
    void InitializePointersChanneling();
    
private:
    ECHARM_strip* fStrip;
    ECHARM_particle* fParticle;
    double fMaximumPotential;
};

#endif
