//
//  ECHARM_displacement.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifdef _ECHARM_displacement_h

#include "ECHARM_displacement.hh"
#ifdef ROOT_
#include "TH2D.h"
#endif

ECHARM_displacement::ECHARM_displacement(double num,double prob,bool sudden = true):
ECHARM_process("displacement"){
    
    bSudden = sudden;
    fNum = num;
    fProb = prob;
    bRandomAngle = false;
    bRandomPosition = false;
    
    fArea = 1.;
    bVecStored = false;
    bTabVal = true;
    bBoxYzero = true;
    
    fNumberOfPointsMax = 100;
    fNumberOfPointsTop = 10000;

    EvalArea(num);

    fNumSteps[0] = 2048;
    fNumSteps[1] = 64;
    fNumSteps[2] = 1;
    
    fBoxX = new ECHARM_distribution_box(0.,0.);
    fBoxY = new ECHARM_distribution_box(0.,0.);
    fBoxZ = new ECHARM_distribution_box(0.,0.);
    
    for(int i=0;i<fNum;i++){
        fCenter.push_back(new ECHARM_3vec(0.,0.,0.));
        fAngPhi.push_back(0.);
        fAngTheta.push_back(0.);
        fAngPsi.push_back(0.);
        fDefIsOn.push_back(true);
    }
    
    fDispl = new ECHARM_3vec(0.,0.,0.);
    fDisplPre = new ECHARM_3vec(0.,0.,0.);
    fBR = new ECHARM_3vec(0.,0.,0.);
    fLimitsHalf = new ECHARM_3vec(1. * meter,1. * meter,1. * meter);
    
    fPosTemp = new ECHARM_3vec(0.,0.,0.);
    fPosTempPre = new ECHARM_3vec(0.,0.,0.);
    fZero = new ECHARM_3vec(0.,0.,0.);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_displacement::~ECHARM_displacement(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::EvalArea(int num){
    if(num <= 0){
        std::cout << "ECHARM_displacement:EvalArea - ERROR: Number of defects per cm2 less than zero" << std::endl;
    }
    else if(num < 1 && num>0){
        fNum = 1;
        fArea = fSquareRoot(1./num);
    }
    else if(num<fNumberOfPointsMax){
        fNum = num;
    }
    else if(num>=fNumberOfPointsMax && num<fNumberOfPointsTop){
        fNum = fNumberOfPointsMax;
        fArea = double(fNumberOfPointsMax)/double(num);
    }
    else{
        fNum = fNumberOfPointsMax/fNumberOfPointsTop*num;
        fArea = double(fNumberOfPointsMax)/double(fNumberOfPointsTop);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::SetAng(double phi,double theta,double omega){
    SetAngPhi(phi);
    SetAngTheta(theta);
    SetAngPsi(omega);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::SetAngPhi(double phi){
    for(int i=0;i<fNum;i++){
        fAngPhi.at(i) = phi;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::SetAngTheta(double theta){
    for(int i=0;i<fNum;i++){
        fAngTheta.at(i) = theta;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::SetAngPsi(double omega){
    for(int i=0;i<fNum;i++){
        fAngPsi.at(i) = omega;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::SetPos(ECHARM_3vec* pos){
    for(int i=0;i<fNum;i++){
        fCenter.at(i)->Set(pos);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::SetLimitStrip(ECHARM_strip* strip){
    fLimitsHalf->SetX(strip->GetDim()->GetX()*0.5);
    fLimitsHalf->SetY(strip->GetDim()->GetY()*0.5);
    fLimitsHalf->SetZ(strip->GetDim()->GetZ()*0.5);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::DoOnStrip(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    
    if(bSudden==false){
        for(int i0 = 0;i0 < fNum;i0++){
            if(fDefIsOn.at(i0)){
                fPosTemp->Set(part->GetPos());
                fPosTemp->Add(fCenter.at(i0),-1.);
                fPosTemp->Rotate(fAngPhi.at(i0),fAngTheta.at(i0),fAngPsi.at(i0));

                if(fPosTemp->IsInCube(fLimitsHalf)){
                    
                    fPosTemp->Add(fLimitsHalf);
                    
                    if(bTabVal == true){
                        fBR->SetX(fVecBRX->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()));
                        fBR->SetY(fVecBRY->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()));
                        fBR->SetZ(fVecBRZ->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()));
                    }
                    else{
                        ComputeBR(fPosTemp,fZero);
                    }

                    fBR->Rotate(-fAngPsi.at(i0),-fAngTheta.at(i0),-fAngPhi.at(i0));
                    fBR->SetZ(0.);

                    strip->GetBR()->AddInverse(fBR);
                }
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save* info){
    if(bSudden==true){
        for(int i0 = 0;i0 < fNum;i0++){
            
            if(fDefIsOn.at(i0)==true){
                fPosTemp->Set(part->GetPos());
                fPosTemp->Add(fCenter.at(i0),-1.);

                fPosTempPre->Set(part->GetPosPre());
                fPosTempPre->Add(fCenter.at(i0),-1.);

                if((fPosTemp->IsInCube(fLimitsHalf)) &&
                   (fPosTempPre->IsInCube(fLimitsHalf)) ){

                    bool bIsInHotZone = IsInHotZone();
                    
                    fPosTemp->Rotate(-fAngPsi.at(i0),-fAngTheta.at(i0),-fAngPhi.at(i0));
                    fPosTempPre->Rotate(-fAngPsi.at(i0),-fAngTheta.at(i0),-fAngPhi.at(i0));

                    if(bTabVal == true && bIsInHotZone == false){
                        fPosTemp->Add(fLimitsHalf);
                        fPosTempPre->Add(fLimitsHalf);
                        
                        fDispl->SetX(fVecDisplX->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()) - fVecDisplX->GetVal2d(fPosTempPre->GetX(),fPosTempPre->GetZ()));
                        fDispl->SetY(fVecDisplY->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()) - fVecDisplY->GetVal2d(fPosTempPre->GetX(),fPosTempPre->GetZ()));
                        fDispl->SetZ(fVecDisplZ->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()) - fVecDisplZ->GetVal2d(fPosTempPre->GetX(),fPosTempPre->GetZ()));
                    }
                    else{
                        ComputeDispl(fPosTempPre,fZero);
                        fDisplPre->Set(fDispl);
                        ComputeDispl(fPosTemp,fZero);
                        fDispl->Add(fDisplPre,-1.);
                    }
                    
                    fDispl->Rotate(fAngPhi.at(i0),fAngTheta.at(i0),fAngPsi.at(i0));
                    fDispl->SetZ(0.);
                    part->GetPos()->Add(fDispl);
                }
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    for(int i0 = 0;i0 < fNum;i0++){
        if(bRandomPosition == true){
            fCenter.at(i0)->SetX(fBoxX->GenerateNumber());
            fCenter.at(i0)->SetY(fBoxY->GenerateNumber());
            fCenter.at(i0)->SetZ(fBoxZ->GenerateNumber());
        }
        if(bRandomAngle == true){
            fAngPhi.at(i0) = drand48() * c2Pi;
            fAngTheta.at(i0) = acos(2.* drand48() - 1.);
        }
        
        double vRandom = drand48();
                
        if(vRandom<fProb){
            fDefIsOn.at(i0) = true;
        }
        else{
            fDefIsOn.at(i0) = false;
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::Init(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    if(bVecStored==false){
        fBoxX->SetPar(1,strip->GetDim()->GetX()*fArea*0.5);
        if(bBoxYzero == true){
            fBoxY->SetPar(1,0.);
        }
        else{
            fBoxY->SetPar(1,strip->GetDim()->GetY()*0.5);
        }
        fBoxZ->SetPar(1,strip->GetDim()->GetZ()*0.5);
        
        if(bVecStored==false){
            fNumSteps[0] = 32;
            fNumSteps[1] = 32;
            fNumSteps[2] = 1;
        }
        Store();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::Print(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
#ifdef ROOT_
    std::string BRX = "_BRX";
    std::string BRY = "_BRY";

    fVecBRX->PrintToTH2(GetName() + BRX);
    fVecBRY->PrintToTH2(GetName() + BRY);
    
    std::string CRX = "_CRX";
    std::string CRY = "_CRY";
    
    fVecCRX->PrintToTH2(GetName() + CRX);
    fVecCRY->PrintToTH2(GetName() + CRX);

    std::string displX = "_displX";
    std::string displY = "_displY";
    std::string displZ = "_displZ";
    
    fVecDisplX->PrintToTH2(GetName() + displX);
    fVecDisplY->PrintToTH2(GetName() + displY);
    fVecDisplZ->PrintToTH2(GetName() + displZ);
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::Store(){
    std::vector<double> vecCRX;
    std::vector<double> vecCRY;
    std::vector<double> vecCRZ;
    std::vector<double> vecBRX;
    std::vector<double> vecBRY;
    std::vector<double> vecBRZ;
    std::vector<double> vecDisplX;
    std::vector<double> vecDisplY;
    std::vector<double> vecDisplZ;
        
    double fLimitsHalfVecBR[3];
    fLimitsHalfVecBR[0] = fLimitsHalf->GetX()*2.;
    fLimitsHalfVecBR[1] = fLimitsHalf->GetY()*2.;
    fLimitsHalfVecBR[2] = fLimitsHalf->GetZ()*2.;
    
    double fStep[3];
    fStep[0] = 2.*fLimitsHalf->Get(0)/fNumSteps[0];
    fStep[1] = 2.*fLimitsHalf->Get(1)/fNumSteps[1];
    fStep[2] = 1;
    
    fVecCRX = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecCRY = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecCRZ = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);

    fVecBRX = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecBRY = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecBRZ = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    
    fVecDisplX = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecDisplY = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecDisplZ = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    
    for(int i1=0;i1<fNumSteps[1];i1++){
        fPosTemp->SetZ(double(i1) * fStep[1] - fLimitsHalf->Get(1));
        for(int i0=0;i0<fNumSteps[0];i0++){
            fPosTemp->SetX(double(i0) * fStep[0] - fLimitsHalf->Get(0));
            
            ComputeBR(fPosTemp,fZero);
            if(fBR->GetX()!=0.){
                vecCRX.push_back(1./fBR->GetX());
            }
            else{
                vecCRX.push_back(0.);
            }

            if(fBR->GetY()!=0.){
                vecCRY.push_back(1./fBR->GetY());
            }
            else{
                vecCRY.push_back(0.);
            }

            if(fBR->GetZ()!=0.){
                vecCRZ.push_back(1./fBR->GetZ());
            }
            else{
                vecCRZ.push_back(0.);
            }

            vecBRX.push_back(fBR->GetX());
            vecBRY.push_back(fBR->GetY());
            vecBRZ.push_back(fBR->GetZ());
            
            ComputeDispl(fPosTemp,fZero);
            vecDisplX.push_back(fDispl->GetX());
            vecDisplY.push_back(fDispl->GetY());
            vecDisplZ.push_back(fDispl->GetZ());
        }
    }
    
    fVecCRX->Set(vecCRX);
    fVecCRY->Set(vecCRY);
    fVecCRZ->Set(vecCRZ);

    fVecBRX->Set(vecBRX);
    fVecBRY->Set(vecBRY);
    fVecBRZ->Set(vecBRZ);
    
    fVecDisplX->Set(vecDisplX);
    fVecDisplY->Set(vecDisplY);
    fVecDisplZ->Set(vecDisplZ);
    
    bVecStored = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::ComputeDispl(ECHARM_3vec*,ECHARM_3vec*){
    fDispl->SetX(0.);
    fDispl->SetY(0.);
    fDispl->SetZ(0.);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_displacement::ComputeBR(ECHARM_3vec*,ECHARM_3vec*){
    fBR->SetX(0.);
    fBR->SetY(0.);
    fBR->SetZ(0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
