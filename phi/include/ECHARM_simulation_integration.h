//
//  ECHARM_simulation_integration.h
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ECHARM_simulation_integration_h
#define _ECHARM_simulation_integration_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstddef>

#ifndef _ECHARM_simulation_h
#include "ECHARM_simulation.h"
#endif

class ECHARM_simulation_integration: public ECHARM_simulation
{
public:
    
    //
    // Constructor to Build directly
    //
    ECHARM_simulation_integration();
    ECHARM_simulation_integration(ECHARM_strip* strip, ECHARM_particle* particle);
    
    virtual ~ECHARM_simulation_integration();
    
    //
    // Retrieval methods
    //
    
    double GetStepLength() {return fStepLength;}
    double GetStepLengthMinPlanar() {return fStepLengthMin;}
    double GetTransverseVariationMax() {return fTransverseVariationMax;}
    unsigned int GetIntegrationMethod() {return fIntegrationMethod;};
    
    
    double GetStepLengthMax();
    double GetTransverseVariationMin();
    
    double GetStepLengthMaxAxial();
    double GetTransverseVariationMinAxial();
   
    //
    // Set methods
    //
    void SetStepLength(double vStepLength) {fStepLength = vStepLength;};
    void SetStepLengthMin(double vStepLengthMin) {fStepLengthMin = vStepLengthMin;};
    void SetTransverseVariationMax(double vTransverseVariationMax) {fTransverseVariationMax = vTransverseVariationMax;};
    void SetIntegrationMethod(unsigned int vIntegrationMethod) {fIntegrationMethod = vIntegrationMethod;};
    
    //
    // Calculate methods
    //
    void UpdateStepLengthPlanar();
    void UpdateStepLengthPlanarMin() {SetStepLength(fStepLengthMin);};
    void UpdateStepLengthAxial();

    void DoIntegrationStepPlanarNewton();
    void DoIntegrationStepAxialNewton();

    void DoIntegrationStepPlanarVelocityVerlet();
    void DoIntegrationStepAxialVelocityVerlet();

    void DoStraightStep();

    void DoIntegrationStepPlanar(unsigned int vIntegrationMethod);
    void DoIntegrationStepPlanar() {DoIntegrationStepPlanar(fIntegrationMethod);};
    void DoIntegrationStepAxial(unsigned int vIntegrationMethod);
    void DoIntegrationStepAxial() {DoIntegrationStepAxial(fIntegrationMethod);};

    void IntegrateParticleTrajectoryPlanar(unsigned int vIntegrationMethod);
    void IntegrateParticleTrajectoryPlanar() {IntegrateParticleTrajectoryPlanar(fIntegrationMethod);};
    void IntegrateParticleTrajectoryAxial(unsigned int vIntegrationMethod);
    void IntegrateParticleTrajectoryAxial() {IntegrateParticleTrajectoryAxial(fIntegrationMethod);};
    
    
    //
    // Printing methods
    //    
    friend std::ostream& operator<<(std::ostream&, ECHARM_simulation_integration*);
    friend std::ostream& operator<<(std::ostream&, ECHARM_simulation_integration&);
    void PrintChannelingSimulationProperties();
    
public:
    
    int operator==(const ECHARM_simulation_integration&) const;
    int operator!=(const ECHARM_simulation_integration&) const;
    
public:
    
    ECHARM_simulation_integration(ECHARM_simulation_integration&);
    ECHARM_simulation_integration(const ECHARM_simulation_integration&);
    const ECHARM_simulation_integration & operator=(const ECHARM_simulation_integration&);
    void InitializePointersChannelingSimulation();

private:

    unsigned int fIntegrationMethod;
    
    double fStepLength;
    double fStepLengthMin;
    double fTransverseVariationMax;
};

#endif
