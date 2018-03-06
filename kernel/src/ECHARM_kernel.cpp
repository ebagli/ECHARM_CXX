//
//  ECHARM_kernel.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifdef _ECHARM_kernel_h

#include "ECHARM_kernel.hh"

ECHARM_kernel::ECHARM_kernel(ECHARM_strip* strip){
    fStrip = strip;
    
    fTimeStepMin = 2.E2 * AA;
    fTransverseVariationMax = 2.E-2 * AA;
    bPartIsIn = true;
    bHasBeenInChanneling = false;
    
    fPosHalf = new ECHARM_3vec(0.,0.,0.);
    fMomHalf = new ECHARM_3vec(0.,0.,0.);
    
    fTimeStepTotal = 0.;
    
    bSaveTrajStatus = false;
    bSavePartIn = false;
    bSavePartOut = false;
    bExitOnDechanneling = false;
    
    bSaveTrajStep = 1. * micrometer;
    bSaveTrajStepTemp = 0.;
    
    fOverrideMaxPotential = DBL_MAX;
    bOverrideMaxPotential = false;
    
    fMachineError = 1. * AA;
    
    bStoreDensity = true;
    
    bDEBUG = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_kernel::~ECHARM_kernel(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_kernel::SetSaveTrajStep(double aDouble) {
    bSaveTrajStep = aDouble;
    fMachineError = 0.05 * bSaveTrajStep;
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
        (*myProcess)->ResetSinceLastProcess();
    }
    
    fInfo->GetDispl()->Zero();
    fInfo->GetBR()->Zero();
    
    bHasBeenInChanneling = false;
    bPartIsIn = true;
    fTimeStepTotal = 0.;
    bSaveTrajStepTemp = 0.;
    UpdateTransverseVariationMax(fTransverseVariationMax);
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::Interaction(){
    
    if(bSavePartIn){
        fInfo->SavePartIn(fPart);
    }
    
    DoBeforeInteraction();
    
    fInfo->SetChInitial(IsInChanneling());
    fInfo->SetMass(fPart->GetMass()/MeV);
    fInfo->SetCharge(fPart->GetZ());
    
    bool bExit = false;
    
    fStepNumber = 0;
    
    do {
        //bPartIsIn = int(fStrip->IsIn(fPart->GetPos()));
        
        bPartIsIn = UpdateStep();
        
        DoOnStrip();
        
        DoStep();
        
        DoOnParticle();
        
        UpdateProcesses();
        
        if(fPart->GetMom()->GetModule() == 0) bExit = true;
        
        if(bStoreDensity){
            fInfo->AddAvgAtD(fStrip->GetAtD()->Get(fPart->GetPos()) * fTimeStep);
            fInfo->AddAvgElD(fStrip->GetElD()->Get(fPart->GetPos()) * fTimeStep);
        }
        
        CheckChannelingCondition();
        
        if(bPartIsIn==0){
            bExit = true;
        }
        else if(bExitOnDechanneling ==  true){
            if(fInfo->GetChTimes()==0){
                bExit = true;
            }
            else if(fInfo->GetChTimes()>0 && fInfo->GetDechTimes()==fInfo->GetChTimes()){
                bExit = true;
            }
        }
        
        if(bSaveTrajStatus && (bPartIsIn==2 || bPartIsIn==0)){
            fInfo->SavePart(fPart,GetAtD(),GetElD(),GetPotential(),GetElectricFieldX(),GetKineticEnergy());
        }
        
        fStepNumber++;
        
    } while(bExit == false);
    
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

int ECHARM_kernel::UpdateProcesses(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->UpdateAtDSinceLastProcess(fStrip,fPart,fTimeStep);
        (*myProcess)->UpdateElDSinceLastProcess(fStrip,fPart,fTimeStep);
        (*myProcess)->UpdateStepLengthSinceLastProcess(fTimeStep);
    }
    
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
    
    double kMomModule = fPart->GetMomMod();
    double kPos = fTimeStep / kMomModule;
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
    fPart->GetMom()->ScaleModule(kMomModule);

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoStepOld(){
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

int ECHARM_kernel::UpdateStep(){
    if(fPart->GetMom()->GetX() != 0.0 || fPart->GetMom()->GetY() != 0.0){
        double xy2 = fSquare(fPart->GetMom()->GetX()) + fSquare(fPart->GetMom()->GetY());
        
        if(xy2!=0.){
            fTimeStep = fabs(fTransverseVariationMax * fPart->GetBeta() * fPart->GetMomMod() / fSquareRoot(xy2));
            
            if(fTimeStep < fTimeStepMin) fTimeStep = fTimeStepMin;
            
            if(fTimeStep > fTimeStepMax) fTimeStep = fTimeStepMax;
        }
        else{
            fTimeStep = fTimeStepMin;
        }
        
    }
    else{
        fTimeStep = fTimeStepMin;
    }
    
    if((fPart->GetPos()->GetZ() + fTimeStep) > (GetStrip()->GetDim()->GetZ() * 0.5)){
        fTimeStep = (GetStrip()->GetDim()->GetZ() * 0.5 - fPart->GetPos()->GetZ());
        return 0;
    }
    
    if(bSaveTrajStatus){
        if(bSaveTrajStepTemp==0){
            bSaveTrajStepTemp += bSaveTrajStep;
            return 2;
        }
        else if((fTimeStepTotal + fTimeStep) > bSaveTrajStepTemp){
            fTimeStep = bSaveTrajStepTemp - fTimeStepTotal;
            bSaveTrajStepTemp += bSaveTrajStep;
            return 2;
        }
    }
    
    return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_kernel::CheckChannelingCondition(){
    bool bIsInChanneling = IsInChanneling();
    if(!bHasBeenInChanneling && bIsInChanneling){
        bHasBeenInChanneling = true;
        fInfo->AddChTimes();
    }
    else if(bHasBeenInChanneling && !bIsInChanneling){
        bHasBeenInChanneling = false;
        fInfo->AddDechTimes();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetElD(){
    fPart->GetPos()->Add(fInfo->GetDispl(),-1.);
    double vPot = fStrip->GetElD()->Get(fPart->GetPos());
    fPart->GetPos()->Add(fInfo->GetDispl(),1.);
    return vPot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetAtD(){
    fPart->GetPos()->Add(fInfo->GetDispl(),-1.);
    double vPot = fStrip->GetAtD()->Get(fPart->GetPos());
    fPart->GetPos()->Add(fInfo->GetDispl(),1.);
    return vPot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetElectricFieldX(){
    fPart->GetPos()->Add(fInfo->GetDispl(),-1.);
    double vVal = fPart->GetZ() * fStrip->GetEFX()->Get(fPart->GetPos());
    fPart->GetPos()->Add(fInfo->GetDispl(),1.);
    return vVal;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetPotential(){
    fPart->GetPos()->Add(fInfo->GetDispl(),+1.);
    double vPot = fPart->GetZ() * fStrip->GetPot()->Get(fPart->GetPos());
    fPart->GetPos()->Add(fInfo->GetDispl(),-1.);
    return vPot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetKineticEnergy(){
    double vPot =  0.5 * fPart->GetMomVel() * fSquare(fPart->GetAngX());
    return vPot;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetTransverseEnergy(){
    return GetPotential() + GetKineticEnergy();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::IsInChanneling(){
    double vEn = GetTransverseEnergy();
    
    double vPotMax = 0.;
    
    if(bOverrideMaxPotential == true){
        vPotMax = fOverrideMaxPotential;
    }
    else{
        vPotMax = fPart->GetZ() * fStrip->GetPot()->ComputeMax();
        if(fPart->GetZ() < 0){
            vPotMax = fPart->GetZ() * fStrip->GetPot()->ComputeMin();
        }
        
        if(fStrip->IsBentX()){
            vPotMax -= fabs(fPart->GetMomVel() / fabs(fStrip->GetBR()->GetX()) * fStrip->GetCrystal()->GetPeriodX() );
        }
        if(fStrip->IsBentY()){
            vPotMax -= fabs(fPart->GetMomVel() / fabs(fStrip->GetBR()->GetY()) * fStrip->GetCrystal()->GetPeriodY() );
        }
    }
    
    if(vEn<vPotMax){
        return true;
    }
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::UpdateTransverseVariationMax(double transvarmax){
    fTransverseVariationMax = transvarmax;
    
    double maxEFX = fStrip->GetEFX()->ComputeMax();
    double maxEFY = fStrip->GetEFY()->ComputeMax();
    
    double maxEF = maxEFX;
    if(maxEFY > maxEF){
        maxEF = maxEFY;
    }
    
    if(maxEF != 0.){
        fTimeStepMax = fSquareRoot( transvarmax * fPart->GetBeta() * fPart->GetMomMod() / fabs(maxEF) );
    }
    else{
        fTimeStepMax = fTimeStepMin * 20.;
    }
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
