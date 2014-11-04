//
//  ECHARM_kernel.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_kernel.hh"

ECHARM_kernel::ECHARM_kernel(ECHARM_strip* strip){
    fStrip = strip;
    
    fTimeTimeStepMin = 1.E2 * AA;
    SetTransverseVariationMax(2.E-2 * AA);
    bPartIsIn = true;
    
    fPosHalf = new ECHARM_3vec(0.,0.,0.);
    fMomHalf = new ECHARM_3vec(0.,0.,0.);
    
    fTimeStepTotal = 0.;
    
    bSaveTrajStatus = false;
    bSavePartIn = false;
    bSavePartOut = false;
    
    bSaveTrajStep = 1. * micrometer;
    bSaveTrajStepTemp = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_kernel::~ECHARM_kernel(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoBeforeInteraction(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->DoBeforeInteraction(fStrip,fPart,fInfo);
    }
    
    fInfo->GetDispl()->Zero();
    fInfo->GetBR()->Zero();
    
    bPartIsIn = true;
    fTimeStepTotal = 0.;
    bSaveTrajStepTemp = 0.;
    
    fPart->ResetStepLengthSinceLastProcess();
    fPart->ResetAtDSinceLastProcess();
    fPart->ResetElDSinceLastProcess();
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::Interaction(){
    
    if(bSavePartIn){
        fInfo->SavePartIn(fPart);
    }
    
    DoBeforeInteraction();
    
    do {
        bPartIsIn = fStrip->IsIn(fPart->GetPos());
        
        bPartIsIn = UpdateStep();
        
        DoOnStrip();
        
        DoStep();
        
        DoOnParticle();
        
        fInfo->AddAvgAtD(fStrip->GetAtD()->Get(fPart->GetPos()) * fTimeStep);
        fInfo->AddAvgElD(fStrip->GetElD()->Get(fPart->GetPos()) * fTimeStep);
        
        if(bSaveTrajStatus)
            if((fTimeStepTotal + bSaveTrajStep) > bSaveTrajStepTemp){
                {
                    fInfo->SavePart(fPart,fStrip->GetAtD()->Get(fPart->GetPos()),fStrip->GetElD()->Get(fPart->GetPos()));
                    bSaveTrajStepTemp += bSaveTrajStep;
                }
            }
    } while(bPartIsIn);
    
    DoAfterInteraction();
    
    if(bSavePartOut){
        fInfo->SavePartOut(fPart);
    }
    
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoAfterInteraction(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->DoAfterInteraction(fStrip,fPart,fInfo);
    }
    
    fInfo->GetBR()->ConstantMoltiplication(1./fTimeStepTotal);
    
    for(int vIndex=0;vIndex<3;vIndex++){
        if(fInfo->GetBR()->Get(vIndex)!=0.){
            fPart->GetMom()->Add(vIndex, fStrip->GetDim()->GetZ() * fPart->GetMomVel() / fInfo->GetBR()->Get(vIndex));
        }
    }
    
    fPart->GetPos()->Add(fInfo->GetDispl());
    
    return 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::Init(){
    
    std::vector<ECHARM_process*>::iterator myProcess;
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->Init(fStrip,fPart,fInfo);
    }
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::End(){
    
    std::vector<ECHARM_process*>::iterator myProcess;
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->End(fStrip,fPart,fInfo);
    }
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::Print(){
    
#ifdef ROOT_
    fStrip->PrintECtoTH();
#endif
    
    fStrip->Print();
    
    std::vector<ECHARM_process*>::iterator myProcess;
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->Print(fStrip,fPart,fInfo);
    }
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoOnParticle(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    fPart->SaveMom();
    
    fInfo->GetDispl()->Add(fPart->GetPos(),-1.);
    
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->DoOnParticle(fStrip,fPart,fInfo);
    }
    
    fInfo->GetDispl()->Add(fPart->GetPos(),+1.);
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoOnStrip(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    fPart->SavePos();
    
    fStrip->ResetBR();
    
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->DoOnStrip(fStrip,fPart,fInfo);
    }
    
    fInfo->GetBR()->Add(fStrip->GetBR(),fTimeStep);
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoStep(){
    //http://www.physics.drexel.edu/~valliere/PHYS305/Diff_Eq_Integrators/Verlet_Methods/Verlet/
    
    fMomHalf->Set(fPart->GetMom());
    fPosHalf->Set(fPart->GetPos());
    
    double kPos = fTimeStep / fPart->GetMomMod();
    double kMom = fTimeStep / fPart->GetBeta();
    double kBR = fTimeStep * fPart->GetMomVel();
    double Z = fPart->GetZ();
    
    fPosHalf->AddX(fPart->GetMom()->GetX() * kPos * 0.5);
    fPosHalf->AddY(fPart->GetMom()->GetY() * kPos * 0.5);
    fPosHalf->AddZ(fPart->GetMom()->GetZ() * kPos * 0.5);
    
    fMomHalf->AddX(Z * fStrip->GetEFX()->Get(fPart->GetPos()) * kMom * 0.5);
    fMomHalf->AddY(Z * fStrip->GetEFY()->Get(fPart->GetPos()) * kMom * 0.5);
    fMomHalf->AddZ(Z * fStrip->GetEFZ()->Get(fPart->GetPos()) * kMom * 0.5);
    
    if(fStrip->IsBentX()){
        fMomHalf->SubtractX(kBR * 0.5 / fStrip->GetBR()->GetX());
    }
    if(fStrip->IsBentY()){
        fMomHalf->SubtractY(kBR * 0.5 / fStrip->GetBR()->GetY());
    }
    
    fPart->GetPos()->AddX(fMomHalf->GetX() * kPos );
    fPart->GetPos()->AddY(fMomHalf->GetY() * kPos );
    fPart->GetPos()->AddZ(fMomHalf->GetZ() * kPos );
    
    fPart->GetMom()->AddX(Z * fStrip->GetEFX()->Get(fPosHalf) * kMom );
    fPart->GetMom()->AddY(Z * fStrip->GetEFY()->Get(fPosHalf) * kMom );
    fPart->GetMom()->AddZ(Z * fStrip->GetEFZ()->Get(fPosHalf) * kMom );
    
    if(fStrip->IsBentX()){
        fPart->GetMom()->SubtractX(kBR / fStrip->GetBR()->GetX());
    }
    if(fStrip->IsBentY()){
        fPart->GetMom()->SubtractY(kBR / fStrip->GetBR()->GetY());
    }
    
    fTimeStepTotal += fTimeStep;
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::UpdateStep(){
    if(fPart->GetMom()->GetX() != 0.0 || fPart->GetMom()->GetY() != 0.0){
        double xy2 = fSquare(fPart->GetMom()->GetX()) + fSquare(fPart->GetMom()->GetY());
        
        fTimeStep = fabs(fTransverseVariationMax * fPart->GetBeta() * fPart->GetMomMod() / fSquareRoot(xy2));
        
        if(fTimeStep < fTimeTimeStepMin) fTimeStep = fTimeTimeStepMin;
        
        if(fTimeStep > fTimeTimeStepMax) fTimeStep = fTimeTimeStepMax;
    }
    else{
        fTimeStep = fTimeTimeStepMin;
    }
    
    if((fPart->GetPos()->GetZ() + fTimeStep) > (GetStrip()->GetDim()->GetZ() * 0.5)){
        fTimeStep = (GetStrip()->GetDim()->GetZ() * 0.5 - fPart->GetPos()->GetZ());
        return false;
    }
    
    fPart->UpdateStepLengthSinceLastProcess();
    fPart->UpdateAtDSinceLastProcess(fStrip->GetAtD()->Get(fPart->GetPos())*fTimeStep);
    fPart->UpdateElDSinceLastProcess(fStrip->GetElD()->Get(fPart->GetPos())*fTimeStep);

    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::SetTransverseVariationMax(double transvarmax){
    fTransverseVariationMax = transvarmax;
    
    double maxEF = fStrip->GetEFX()->GetMax() - fStrip->GetEFX()->GetMin();
    double maxEFY = fStrip->GetEFX()->GetMax() - fStrip->GetEFX()->GetMin();
    if(maxEFY > maxEF){
        maxEF = maxEFY;
    }
    
    if(maxEF != 0.){
        fTimeTimeStepMax = fSquareRoot( transvarmax * fPart->GetBeta() * fPart->GetMomMod() / maxEF );
    }
    else{
        fTimeTimeStepMax = fTimeTimeStepMin * 20.;
    }
    
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetTransverseVariationMax(){
    return fSquare( fTimeTimeStepMax / (fPart->GetBeta() * fPart->GetMomMod()) * fStrip->GetEFX()->GetMax());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
