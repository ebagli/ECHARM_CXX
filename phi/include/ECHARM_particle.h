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
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

#ifndef _ECHARM_constants_h
#include "ECHARM_constants.h"
#endif

#ifndef _ECHARM_threevector_h
#include "ECHARM_threevector.h"
#endif

#ifndef _ECHARM_save_structure_h
#include "ECHARM_save_structure.h"
#endif

class ECHARM_particle
{
public:
    
    //
    // Constructor to Build an element directly;
    //
    ECHARM_particle();
    
    ECHARM_particle(double Z,
                    double Mass,
                    ECHARM_threevector* Momentum,
                    ECHARM_threevector* Position
                    );

    virtual ~ECHARM_particle();
    
    //
    // Retrieval methods
    //
    double GetZ() const {return fZ;}     
    double GetMass() const {return fMass;}    
    double GetMomentum() const {return fMomentumVector->GetModule();}
    double GetMomentumVelocity() const {return fMomentumVector->GetModule()*GetBeta();}
    double GetEnergy() const {return fSquareRoot(fSquare(double(fMomentumVector->GetModule()))+fSquare(double(fMass)));}
    double GetBeta() const {return fMomentumVector->GetModule()/GetEnergy();}
    double GetGamma() const {return GetEnergy()/fMass;}

    ECHARM_threevector *GetMomentumVector() const {return fMomentumVector;}
    ECHARM_threevector *GetPositionVector() const {return fPositionVector;}

    //
    // Set methods
    //
    void SetZ(double Z) {fZ=Z;}
    void SetMass(double Mass) {fMass=Mass;}
    void SetMomentum(ECHARM_threevector* Momentum) {fMomentumVector=Momentum;}
    void SetMomentumVector(ECHARM_threevector* Momentum) {fMomentumVector = Momentum;}
    void SetPositionVector(ECHARM_threevector* Position) {fPositionVector = Position;}
   
    //
    // Printing methods
    //
    friend std::ostream& operator<<(std::ostream&, ECHARM_particle*);    
    friend std::ostream& operator<<(std::ostream&, ECHARM_particle&);    
    void PrintParticleProperties();
    void PrintParticleOn(ECHARM_Particle_Save &vParticle);

    //
    // Calculate methods
    //
    
public:
    
    int operator==(const ECHARM_particle&) const;
    int operator!=(const ECHARM_particle&) const;
    
public:
    
    ECHARM_particle(ECHARM_particle&);
    ECHARM_particle(const ECHARM_particle&);
    const ECHARM_particle & operator=(const ECHARM_particle&);
    void InitializePointersParticle();
    
private:  
    double fZ;            
    double fMass;             
    ECHARM_threevector *fPositionVector;
    ECHARM_threevector *fMomentumVector;
};

#endif
