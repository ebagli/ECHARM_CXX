//
//  ECHARM_info_save.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_info_save_h

#include "ECHARM_info_save.hh"

ECHARM_info_save::ECHARM_info_save(){
    fDispl = new ECHARM_3vec(0.,0.,0.);
    fBR = new ECHARM_3vec(0.,0.,0.);
    fBeamSize = new ECHARM_3vec(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_info_save::~ECHARM_info_save(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::SetRadEmEn(int vEnBin,double vEnMin,double vEnStep){
    for(int i0=0;i0<vEnBin;i0++){
        fRadEmProb.push_back(0.);
        fRadEmEn.push_back(vEnMin + vEnStep * i0);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::AddRadEmEn(double val){
    fRadEmEn.push_back(val);
    fRadEmProb.push_back(0.);
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::Reset(){
    fDispl->Zero();
    fBR->Zero();
    fBeamSize->Zero();

    fAvgAtD = 0.;
    fAvgElD = 0.;

    fChInitial = 0;
    fChTimes = 0;
    fDechTimes = 0;
    
    fMass = 0.;
    fCharge = 0.;
    
    fPartNum = 0.;

    fEmittedPhEn.clear();

    for(unsigned int i0=0;i0<fRadEmProb.size();i0++){
        fRadEmProb.at(i0) = 0.;
    }
    
    fPartVec.clear();
    fAtD.clear();
    fElD.clear();
    fDisplX.clear();
    fDisplY.clear();
    fDisplZ.clear();

    fPot.clear();
    fEFX.clear();
    fKin.clear();

    fChTimesTot.clear();
    fDechTimesTot.clear();
    fChInitialTot.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::Print(){
    std::cout << fPartIn.posx << " " << fPartIn.posy << " " << fPartIn.posz << std::endl;
    std::cout << fPartOut.posx << " " << fPartOut.posy << " " << fPartOut.posz << std::endl;
    std::cout << fAvgAtD << " " << fAvgElD  << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::SavePartIn(ECHARM_particle* part) {
    SavePartStruct(part,fPartIn);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::SavePartOut(ECHARM_particle* part) {
    SavePartStruct(part,fPartOut);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::SavePart(ECHARM_particle* part,double atd,double eld,double pot,double efx,double kin) {
    SavePartStruct(part,fPart);
    fPartVec.push_back(fPart);
    fAtD.push_back(atd);
    fElD.push_back(eld);
    fDisplX.push_back(fDispl->GetX());
    fDisplY.push_back(fDispl->GetY());
    fDisplZ.push_back(fDispl->GetZ());
    fChTimesTot.push_back(fChTimes);
    fDechTimesTot.push_back(fDechTimes);
    fChInitialTot.push_back(fChInitial);


    fPot.push_back(pot);
    fEFX.push_back(efx);
    fKin.push_back(kin);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_info_save::SavePartStruct(ECHARM_particle* part,ECHARM_Particle_Save& save){
        save.posx = part->GetPos()->GetX() / AA;
        save.posy = part->GetPos()->GetY() / AA;
        save.posz = part->GetPos()->GetZ() / millimeter;
        save.angx = part->GetAngX() / microrad;
        save.angy = part->GetAngY() / microrad;
        save.momz = part->GetMom()->GetZ() / GeV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
