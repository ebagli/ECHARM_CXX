//
//  ECHARM_kernel.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_kernel.hh"

ECHARM_kernel::ECHARM_kernel(ECHARM_particle* particle, ECHARM_strip* strip){
    fStrip = strip;
    fPart = particle;
    fTimeTimeStepMax = 2. * micrometer;
    fTimeTimeStepMin = 200. * AA;
    fTransverseVariationMax = 2.E-2 * AA;
    
    fPosHalf = new ECHARM_3vec(0.,0.,0.);
    fMomHalf = new ECHARM_3vec(0.,0.,0.);

    fBRperStepTotal = new ECHARM_3vec(0.,0.,0.);
    fTimeStepTotal = 0.;
    
#ifdef ROOT_
    bSaveTrajStatus = false;
    fTree = new TTree("traj","DYNECHARM Simulation");
    fTree->Branch("step",&fTimeStepSave,"posX/D:posY/D:posZ/D:angX/D:angY/D:momZ/D");
    fTree->Branch("strip",&fBRstepSave,"br/D");
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_kernel::~ECHARM_kernel(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_kernel::Print(){
    fStrip->Print();
    fPart->Print();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::Interaction(){
    
    bool bPartIsIn = true;
    fTimeStepTotal = 0.;
    fBRperStepTotal->Zero();

#ifdef ROOT_
    if(bSaveTrajStatus){
        fPart->PrintToStruct(fTimeStepSave);
        fTree->Fill();
    }
#endif

    do {
        fPart->SavePos();
        
        fPart->SaveMom();
        
        bPartIsIn = fStrip->IsIn(fPart->GetPos());
        
        bPartIsIn = UpdateStep();
        
        DoOnStrip();
            
        DoStep();
            
        DoOnParticle();

#ifdef ROOT_
        if(bSaveTrajStatus){
            fBRstepSave = fStrip->GetBR()->GetX();
            fPart->PrintToStruct(fTimeStepSave);
            fTree->Fill();
        }
#endif

    } while(bPartIsIn);
    
    fBRperStepTotal->ConstantMoltiplication(1./fTimeStepTotal);
    for(int vIndex=0;vIndex<3;vIndex++){
        if(fBRperStepTotal->Get(vIndex)!=0.){
            fPart->GetMom()->Add(vIndex, fStrip->GetDim()->GetZ() * fPart->GetMomVel() / fBRperStepTotal->Get(vIndex));
        }
    }
    
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoOnStrip(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    fStrip->ResetBR();

    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->DoOnStrip(fStrip,fPart);
    }
    fBRperStepTotal->Add(fStrip->GetBR(),fTimeStep);

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoOnParticle(){
    std::vector<ECHARM_process*>::iterator myProcess;

    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->DoOnParticle(fStrip,fPart);
    }
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::Init(){
    std::vector<ECHARM_process*>::iterator myProcess;
    
    for(myProcess = fProcesses.begin();
        myProcess != fProcesses.end();
        myProcess++){
        (*myProcess)->Init(fStrip,fPart);
    }
    return 0;
}

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
    if(fStrip->IsBentZ()){
        fMomHalf->SubtractZ(kBR * 0.5 / fStrip->GetBR()->GetZ());
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
    if(fStrip->IsBentZ()){
        fPart->GetMom()->SubtractZ(kBR / fStrip->GetBR()->GetZ());
    }
    
    fTimeStepTotal += fTimeStep;

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_kernel::DoStraightStep(){
    fPart->GetPos()->AddX(fPart->GetMom()->GetX() / fPart->GetMomMod() * fTimeStep );
    fPart->GetPos()->AddY(fPart->GetMom()->GetY() / fPart->GetMomMod() * fTimeStep );
    fPart->GetPos()->AddZ(fPart->GetMom()->GetZ() / fPart->GetMomMod() * fTimeStep );
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::UpdateStep(){
    if(fPart->GetMom()->GetX() != 0.0 || fPart->GetMom()->GetY() != 0.0){
        double xy2 = fSquare(fPart->GetMom()->GetX()) + fSquare(fPart->GetMom()->GetY());
        
        fTimeStep = fabs(fTransverseVariationMax * fPart->GetBeta() * fPart->GetMomMod() / fSquareRoot(xy2));

        if(fTimeStep < fTimeTimeStepMin) fTimeStep = fTimeTimeStepMin;
    
        else if(fTimeStep > fTimeTimeStepMax) fTimeStep = fTimeTimeStepMax;
    }
    else{
        fTimeStep = fTimeTimeStepMin;
    }

    if((fPart->GetPos()->GetZ() + fTimeStep) > GetStrip()->GetDim()->GetZ() * 0.5){
        fTimeStep = (GetStrip()->GetDim()->GetZ() * 0.5 - fPart->GetPos()->GetZ());
        return false;
    }
    
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_kernel::SetTransverseVariationMax(double transvarmax){
    fTransverseVariationMax = transvarmax;
    fTimeTimeStepMax = fSquareRoot( transvarmax * fPart->GetBeta() * fPart->GetMomMod() / fStrip->GetEFX()->GetMax() );

    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_kernel::GetTransverseVariationMax(){
    return fSquare( fTimeTimeStepMax / (fPart->GetBeta() * fPart->GetMomMod()) * fStrip->GetEFX()->GetMax());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
