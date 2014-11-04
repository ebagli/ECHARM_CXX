//
//  ECHARM_process.cpp
//  
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_process_h

#include "ECHARM_process.hh"

ECHARM_process::ECHARM_process(std::string name){
    fName = name;
    fInitialized = false;
    fEnded = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_process::~ECHARM_process(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::DoOnStrip(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::DoOnParticle(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::DoBeforeInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::DoAfterInteraction(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::Init(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::End(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_process::Print(ECHARM_strip*,ECHARM_particle*,ECHARM_info_save*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process::ComputeAvgAtD(ECHARM_strip* strip,ECHARM_particle* part){
    double vAvgAtD = (strip->GetAtD()->Get(part->GetPos()) + strip->GetAtD()->Get(part->GetPosPre()))*0.5;
    if(vAvgAtD == 0.){
        vAvgAtD = 1.E-10;
    }
    return vAvgAtD;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process::ComputeAvgElD(ECHARM_strip* strip,ECHARM_particle* part){
    double vAvgElD = (strip->GetElD()->Get(part->GetPos()) + strip->GetElD()->Get(part->GetPosPre()))*0.5;
    if(vAvgElD == 0.){
        vAvgElD = 1.E-10;
    }
    return vAvgElD;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_process::ComputeAvgDen(ECHARM_strip* strip,ECHARM_particle* part){
    double vAvgDen = ComputeAvgAtD(strip,part) + ComputeAvgElD(strip,part);
    return vAvgDen;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
