//
//  ECHARM_undulator.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifdef _ECHARM_undulator_h

#include "ECHARM_undulator.hh"

ECHARM_undulator::ECHARM_undulator(double ampl,double period,double phase,bool sudden = false):
ECHARM_displacement(1,1.,sudden){
    
    fAmplitude = ampl;
    fPeriod = period;
    fPhase = phase;
    
    fNumSteps[0] = 8;
    fNumSteps[1] = 8192;
    fNumSteps[2] = 1;

    fCenter.at(0)->SetX(0.);
    fCenter.at(0)->SetY(0.);
    fCenter.at(0)->SetZ(0.);

    SetName("undulator");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_undulator::~ECHARM_undulator(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_undulator::Init(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    if(bVecStored==false){
        SetLimitStrip(strip);
        Store();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_undulator::ComputeDispl(ECHARM_3vec* partpos,ECHARM_3vec*){
    
    fDispl->SetX(fAmplitude * sin(fPhase + partpos->GetZ() / fPeriod * c2Pi));
    fDispl->SetY(0.);
    fDispl->SetZ(0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_undulator::ComputeBR(ECHARM_3vec* partpos,ECHARM_3vec*){
    
    double fx = 0.;
    
    if(partpos->GetZ() != 0.){
        double a1 = 2. * cPi * partpos->GetZ() / fPeriod + fPhase;
        double a2 = 2. * cPi * fAmplitude / fPeriod;
        fx = - 1. / sin(a1) / fSquare(a2) * pow ( fSquare( a2 * cos(a1) ) + 1. , 1.5 ) ;
    }
    
    fBR->SetX(fx);
    fBR->SetY(0.);
    fBR->SetZ(0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif