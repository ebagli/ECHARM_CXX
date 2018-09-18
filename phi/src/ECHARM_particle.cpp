//
//  ECHARM_particle.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_particle::ECHARM_particle()
{
    InitializePointersParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_particle::ECHARM_particle(double Z,
                                 double Mass,
                                 ECHARM_threevector* Momentum,
                                 ECHARM_threevector* Position)
{
    InitializePointersParticle();
    fZ = Z;
    fMass = Mass;
    fMomentumVector = Momentum;
    fPositionVector = Position;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_particle::~ECHARM_particle()
{
    if (&fZ)         { delete &fZ; }
    if (&fMass)         { delete &fMass; }
    if (&fMomentumVector)         { delete &fMomentumVector; }
    if (&fPositionVector)         { delete &fPositionVector; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_particle& ECHARM_particle::operator=(const ECHARM_particle& right)
{
    if (this != &right)
    {
        InitializePointersParticle();
        fZ = right.fZ;
        fMass = right.fMass;
        fMomentumVector = right.fMomentumVector;
        fPositionVector = right.fPositionVector;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_particle::PrintParticleProperties()
{
    std::cout << "ECHARM_particle - Print Properties" << std::endl;
    std::cout << "Z                               " << std::setw(12) << std::setprecision(6) << fZ << std::endl;  
    std::cout << "Mass                       [eV] " << std::setw(12) << std::setprecision(6) << fMass << std::endl;  
    std::cout << "Momentum                   [eV] " << std::setw(12) << std::setprecision(6) << fMomentumVector->GetModule() << std::endl;
    std::cout << "Energy                     [eV] " << std::setw(12) << std::setprecision(6) << GetEnergy() << std::endl;
    std::cout << "Gamma                           " << std::setw(12) << std::setprecision(6) << GetGamma() << std::endl;
    std::cout << "Beta                            " << std::setw(12) << std::setprecision(6) << GetBeta() << std::endl;
    std::cout << "MomentumVelocity           [eV] " << std::setw(12) << std::setprecision(6) << GetMomentumVelocity() << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_particle::PrintParticleOn(ECHARM_Particle_Save &vParticle)
{
    vParticle.x = GetPositionVector()->GetX();
    vParticle.y = GetPositionVector()->GetY();
    vParticle.z = GetPositionVector()->GetZ();
    vParticle.px = GetMomentumVector()->GetX();
    vParticle.py = GetMomentumVector()->GetY();
    vParticle.pz = GetMomentumVector()->GetZ();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_particle::InitializePointersParticle()
{
    fZ = 0.0;
    fMass = 0.0;
    fMomentumVector = new ECHARM_threevector();
    fPositionVector = new ECHARM_threevector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_particle::operator==(const ECHARM_particle& right) const
{
    return (this == (ECHARM_particle*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_particle::operator!=(const ECHARM_particle& right) const
{
    return (this != (ECHARM_particle*) &right);
}