//
//  ECHARM_manager.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_manager.hh"

ECHARM_manager::ECHARM_manager(ECHARM_beam* beam, ECHARM_info_save *info){
    
    fBeam = beam;
    fInfo = info;
    
    fTimeStepTotal = 0.;

    fInfo->Reset();
    
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_manager::~ECHARM_manager(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_manager::Go(){
    
    fInfo->Reset();

    fTimeStepTotal = 0.;
    
    fBeam->GenerateParticle();
        
    std::vector<ECHARM_kernel*>::iterator myKernel;

    for(myKernel = fKernel.begin();
        myKernel != fKernel.end();
        myKernel++){

        fBeam->GetGeneratedParticle()->GetPos()->SetZ(-(*myKernel)->GetStrip()->GetDim()->GetZ()*0.5);

        (*myKernel)->Interaction();
        
        fTimeStepTotal += (*myKernel)->GetTimeStepTotal();
    }
    
    fInfo->DivideAvgAtD(fTimeStepTotal);
    
    fInfo->DivideAvgElD(fTimeStepTotal);
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_manager::Init(){
    std::vector<ECHARM_kernel*>::iterator myKernel;
    
    for(myKernel = fKernel.begin();
        myKernel != fKernel.end();
        myKernel++){
        
        (*myKernel)->SetParticle(fBeam->GetGeneratedParticle());
        (*myKernel)->SetInfo(fInfo);
        (*myKernel)->Init();
    }
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_manager::End(){
    std::vector<ECHARM_kernel*>::iterator myKernel;
    
    for(myKernel = fKernel.begin();
        myKernel != fKernel.end();
        myKernel++){
        (*myKernel)->End();
    }
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_manager::Print(){
    
    fBeam->Print();

    std::vector<ECHARM_kernel*>::iterator myKernel;
    
    for(myKernel = fKernel.begin();
        myKernel != fKernel.end();
        myKernel++){
        (*myKernel)->Print();
    }
    

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
