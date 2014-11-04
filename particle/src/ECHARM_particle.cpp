//
//  ECHARM_particle.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

#include "ECHARM_particle.hh"

ECHARM_particle::ECHARM_particle(){
    fZ = 0.;
    fMass = 0.;
    
    fMom = new ECHARM_3vec(0.,0.,0.);
    fPos = new ECHARM_3vec(0.,0.,0.);
    
    fPosPre = new ECHARM_3vec(0.,0.,0.);
    fMomPre = new ECHARM_3vec(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ECHARM_particle::ECHARM_particle(double Z,
                                 double Mass){
    fZ = Z;
    fMass = Mass;
    
    fMom = new ECHARM_3vec(0.,0.,0.);
    fPos = new ECHARM_3vec(0.,0.,0.);

    fPosPre = new ECHARM_3vec(0.,0.,0.);
    fMomPre = new ECHARM_3vec(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_particle::~ECHARM_particle(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_particle::Print(){
    std::cout << "ECHARM_particle - Print Properties" << std::endl;
    std::cout << "Z                               " << std::setw(12) << std::setprecision(6) << fZ << std::endl;  
    std::cout << "Mass                      [MeV] " << std::setw(12) << std::setprecision(6) << fMass/MeV << std::endl;
    std::cout << "Momentum                  [GeV] " << std::setw(12) << std::setprecision(6) << GetMomMod()/GeV << std::endl;
    std::cout << "Energy                    [GeV] " << std::setw(12) << std::setprecision(6) << GetEnergy()/GeV << std::endl;
    std::cout << "Kinetic Energy            [GeV] " << std::setw(12) << std::setprecision(6) << GetKineticEnergy()/GeV << std::endl;
    std::cout << "Gamma                           " << std::setw(12) << std::setprecision(6) << GetGamma() << std::endl;
    std::cout << "Beta                            " << std::setw(12) << std::setprecision(6) << GetBeta() << std::endl;
    std::cout << "MomentumVelocity          [GeV] " << std::setw(12) << std::setprecision(6) << GetMomVel()/GeV << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetKineticEnergy() {
    return (0.5 * fMass * fSquare(GetBeta()));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetEnergy() {
    return fSquareRoot(fSquare(fMom->GetModule())+fSquare(fMass));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetBeta() {
    return fMom->GetModule()/GetEnergy();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetGamma() {
    return GetEnergy()/fMass;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetMomMod() {
    return fMom->GetModule();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetMomVel() {
    return fMom->GetModule()*GetBeta();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_particle::GetStepLength(){
    double x = fPos->GetX() - fPosPre->GetX();
    double y = fPos->GetY() - fPosPre->GetY();
    double z = fPos->GetZ() - fPosPre->GetZ();
    
    return fSquareRoot(x*x+y*y+z*z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
