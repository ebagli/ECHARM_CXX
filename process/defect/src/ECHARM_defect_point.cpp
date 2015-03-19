//
//  ECHARM_defect_point.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//
//  Computer Physics Communications 141 (2001) 230–246
//  Eq. (16) and (2)
//

#ifdef _ECHARM_defect_point_h

#include "ECHARM_defect_point.hh"

ECHARM_defect_point::ECHARM_defect_point(double defect_density){
    fTotalProbThetaSS = 0.3;
    fInitialProb = fTotalProbThetaSS;
    fDefectDensity = defect_density;
    fName = "defect_point";
    fPosDef = new ECHARM_3vec();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect_point::~ECHARM_defect_point(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_point::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    UpdateConstants(strip,part);
    fTotalProbThetaSS = fInitialProb * fDefectDensity / strip->GetCrystal()->GetNucleiDensity();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_point::DoAfterInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    fTotalProbThetaSS = fInitialProb;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_point::UpdateAtDSinceLastProcess(ECHARM_strip* strip,ECHARM_particle* part,double timestep){
	fPosDef->Set(part->GetPos());
	fPosDef->AddX(strip->GetCrystal()->GetPeriodX()*0.5);
	fPosDef->AddY(strip->GetCrystal()->GetPeriodY()*0.5);
	fPosDef->AddZ(strip->GetCrystal()->GetPeriodZ()*0.5);
	fAtDSinceLastProgress += strip->GetAtD()->Get(fPosDef)*timestep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect_point::UpdateElDSinceLastProcess(ECHARM_strip* strip,ECHARM_particle* part,double timestep){
	fPosDef->Set(part->GetPos());
	fPosDef->AddX(strip->GetCrystal()->GetPeriodX()*0.5);
	fPosDef->AddY(strip->GetCrystal()->GetPeriodY()*0.5);
	fPosDef->AddZ(strip->GetCrystal()->GetPeriodZ()*0.5);
	fElDSinceLastProgress += strip->GetElD()->Get(fPosDef)*timestep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

