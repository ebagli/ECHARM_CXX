//
//  ECHARM_manager.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_manager_h

#include "ECHARM_manager.hh"

ECHARM_manager::ECHARM_manager(ECHARM_beam* beam, ECHARM_info_save *info){
    
    fBeam = beam;
    fInfo = info;
    
    fTimeStepTotal = 0.;
    fNumberOfParticlesPrint = 1;
    fNumberOfParticles = 0;
    
    fInfo->Reset();
    
    bSaveTrajStatus = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_manager::ECHARM_manager(ECHARM_beam* beam){

    fBeam = beam;
    fInfo = new ECHARM_info_save();

    fTimeStepTotal = 0.;

    fInfo->Reset();

    bSaveTrajStatus = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_manager::~ECHARM_manager(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_manager::RunDYNECHARM(ECHARM_file_save* info_save,int vNumberOfParticles = 0){
    if(vNumberOfParticles != 0){
        fNumberOfParticles = vNumberOfParticles;
    }

    Init();
    
#pragma omp single
    {
        Print();
    }
    
#pragma omp for schedule(dynamic)
    for(int iPart=0;iPart<vNumberOfParticles;iPart++){
        
        Go();
        
#pragma omp critical
        {
            fInfo->SetPartNum(iPart);
            info_save->Save(fInfo);
            if((iPart%fNumberOfParticlesPrint)==0){
                std::cout << "Particle - " << iPart << std::endl;
            }
            
        }
    }
    End();
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_manager::Go(){
    
    fInfo->Reset();

    fTimeStepTotal = 0.;
    
    fBeam->GenerateParticle();
    fInfo->GetBeamSize()->SetX(fBeam->GetDistrBeamSizeX()->GenerateNumber());
    fInfo->GetBeamSize()->SetY(fBeam->GetDistrBeamSizeY()->GenerateNumber());
    fInfo->GetBeamSize()->SetZ(fBeam->GetDistrBeamSizeZ()->GenerateNumber());

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
        
        //(*myKernel)->SetSaveTrajStep(bSaveTrajStatus);
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

#endif
