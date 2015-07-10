//
//  ECHARM_beam.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_beam_h

#include "ECHARM_beam.hh"
#include "ECHARM_distribution_box.hh"
#include "ECHARM_distribution_const.hh"

ECHARM_beam::ECHARM_beam(){
    fParticle = new ECHARM_particle(0.,0.);
    
    fDistrParticles = new ECHARM_distribution_box(0.,0.);
    
    fDistrMomentumX = new ECHARM_distribution_box(0.,0.);
    fDistrMomentumY = new ECHARM_distribution_box(0.,0.);
    fDistrMomentumZ = new ECHARM_distribution_box(0.,0.);
    
    fDistrBeamSizeX = new ECHARM_distribution_box(0.,0.);
    fDistrBeamSizeY = new ECHARM_distribution_box(0.,0.);
    fDistrBeamSizeZ = new ECHARM_distribution_box(0.,0.);

    fDistrPositionX =  new ECHARM_distribution_box(0.,0.);
    fDistrPositionY =  new ECHARM_distribution_box(0.,0.);
    fDistrPositionZ =  new ECHARM_distribution_const(0.);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam::ECHARM_beam(ECHARM_particle* particle,double perc = 1.){
    fParticle = new ECHARM_particle(0.,0.);

    fParticles.push_back(particle);
    fPercentages.push_back(perc);
    
    fDistrParticles = new ECHARM_distribution_box(0.,0.);
    
    fDistrMomentumX = new ECHARM_distribution_box(0.,0.);
    fDistrMomentumY = new ECHARM_distribution_box(0.,0.);
    fDistrMomentumZ = new ECHARM_distribution_box(0.,0.);

    fDistrBeamSizeX = new ECHARM_distribution_box(0.,0.);
    fDistrBeamSizeY = new ECHARM_distribution_box(0.,0.);
    fDistrBeamSizeZ = new ECHARM_distribution_box(0.,0.);

    fDistrPositionX =  new ECHARM_distribution_box(0.,0.);
    fDistrPositionY =  new ECHARM_distribution_box(0.,0.);
    fDistrPositionZ =  new ECHARM_distribution_const(0.);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam::~ECHARM_beam(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::Print(){
    double vPercSum = 0.;
    std::vector<double>::iterator itPerc;
    std::vector<ECHARM_particle*>::iterator itPart;
    
    for(itPerc = fPercentages.begin();itPerc != fPercentages.end();itPerc++){
        vPercSum += (*itPerc);
    }
    
    for(itPart = fParticles.begin();itPart != fParticles.end();itPart++){
        (*itPart)->Print();
    }
    
    for(itPerc = fPercentages.begin();itPerc != fPercentages.end();itPerc++){
        std::cout << (*itPerc)/vPercSum << std::endl;
    }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::AddParticle(ECHARM_particle* particle,double perc = 1.){
    fParticles.push_back(particle);
    fPercentages.push_back(perc);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::DistrPosFromStrip(ECHARM_strip* strip){
    fDistrPositionX->SetPar(0,strip->GetCrystal()->GetPeriodX()*0.5);
    fDistrPositionX->SetPar(1,strip->GetCrystal()->GetPeriodX()*0.5);

    fDistrPositionY->SetPar(0,strip->GetCrystal()->GetPeriodY()*0.5);
    fDistrPositionY->SetPar(1,strip->GetCrystal()->GetPeriodY()*0.5);

    fDistrPositionZ->SetPar(0,-strip->GetDim()->GetZ()*0.5);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::GenerateParticle(){
    
    double vPercSum = 0.;
    std::vector<double>::iterator itPerc;
    std::vector<ECHARM_particle*>::iterator itPart;
    
    for(itPerc = fPercentages.begin();itPerc != fPercentages.end();itPerc++){
        vPercSum += (*itPerc);
    }
    
    fDistrParticles->SetPar(0,vPercSum*0.5);
    fDistrParticles->SetPar(1,vPercSum*0.5);
    
    double vPartNumber = fDistrParticles->GenerateNumber();
    double vPartPercSum = 0.;
    int vPartIndex = 0;
    
    for(unsigned int i=0;i<fPercentages.size();i++){

        if(vPartNumber < (fPercentages.at(i) + vPartPercSum) &&
           vPartNumber > vPartPercSum){
            vPartIndex = i;
        }
        vPartPercSum += fPercentages.at(i);
    }
    
    fParticle->SetZ((fParticles.at(vPartIndex))->GetZ());
    fParticle->SetMass((fParticles.at(vPartIndex))->GetMass());
    
    fParticle->GetMom()->SetX(fDistrMomentumX->GenerateNumber());
    fParticle->GetMom()->SetY(fDistrMomentumY->GenerateNumber());
    fParticle->GetMom()->SetZ(fDistrMomentumZ->GenerateNumber());
    
    fParticle->GetPos()->SetX(fDistrPositionX->GenerateNumber());
    fParticle->GetPos()->SetY(fDistrPositionY->GenerateNumber());
    fParticle->GetPos()->SetZ(fDistrPositionZ->GenerateNumber());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif