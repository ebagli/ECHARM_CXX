//
//  ECHARM_defect.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_defect.hh"
#include "TH2D.h"
ECHARM_defect::ECHARM_defect(double num,bool sudden = true){
    
    bSudden = sudden;
    fDefNum = num;
    fArea = 1.;
    bVecStored = false;
    
    if(num < 1){
        fDefNum = 1;
        fArea = fSquareRoot(1./num);
    }
    
    fBoxX = new ECHARM_distribution_box(0.,0.);
    fBoxY = new ECHARM_distribution_box(0.,0.);
    fBoxZ = new ECHARM_distribution_box(0.,0.);
    
    for(int i=0;i<fDefNum;i++){
        fDefCenter.push_back(new ECHARM_3vec(0.,0.,0.));
        fDefAnglesPhi.push_back(0.);
        fDefAnglesTheta.push_back(0.);
    }
    
    fPoissonRatio = 0.42;
    
    fBurger = new ECHARM_3vec(0.,0.,0.);
    fDispl = new ECHARM_3vec(0.,0.,0.);
    fBR = new ECHARM_3vec(0.,0.,0.);
    fLimitsHalf = new ECHARM_3vec(0.05 * millimeter,0.05 * millimeter,0.05 * millimeter);
    
    fPosTemp = new ECHARM_3vec(0.,0.,0.);
    fPosTempPre = new ECHARM_3vec(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect::~ECHARM_defect(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::DoOnStrip(ECHARM_strip* strip,ECHARM_particle* part){
    
    for(int i0 = 0;i0 < fDefNum;i0++){

        fPosTemp->Set(part->GetPos());
        fPosTemp->Add(fDefCenter.at(i0),-1.);

        if(fabs(fPosTemp->GetX()) < (fLimitsHalf->GetX()) &&
           fabs(fPosTemp->GetY()) < (fLimitsHalf->GetY()) &&
           fabs(fPosTemp->GetZ()) < (fLimitsHalf->GetZ())){
            
            fPosTemp->Rotate(fDefAnglesPhi.at(i0),fDefAnglesTheta.at(i0));
            fPosTemp->Add(fLimitsHalf);
            
            fBR->SetX(fVecBRX->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()));
            fBR->SetY(fVecBRY->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()));
            fBR->SetZ(fVecBRZ->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()));
            
            fBR->RotateInv(fDefAnglesPhi.at(i0),fDefAnglesTheta.at(i0));
            fBR->SetZ(0.);
        }
        
        if(bSudden==false){
            strip->GetBR()->AddInverse(fBR);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::DoOnParticle(ECHARM_strip* strip,ECHARM_particle* part){
    
    for(int i0 = 0;i0 < fDefNum;i0++){
        
        fPosTemp->Set(part->GetPos());
        fPosTemp->Add(fDefCenter.at(i0),-1.);
        
        fPosTempPre->Set(part->GetPosPre());
        fPosTempPre->Add(fDefCenter.at(i0),-1.);
        
        if((fPosTemp->GetModule2()) < (fLimitsHalf->GetModule2()) &&
           (fPosTempPre->GetModule2()) < (fLimitsHalf->GetModule2())){
            
            fPosTemp->Rotate(fDefAnglesPhi.at(i0),fDefAnglesTheta.at(i0));
            fPosTemp->Add(fLimitsHalf);

            fPosTempPre->Rotate(fDefAnglesPhi.at(i0),fDefAnglesTheta.at(i0));
            fPosTempPre->Add(fLimitsHalf);

            fDispl->SetX(fVecDisplX->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()) - fVecDisplX->GetVal2d(fPosTempPre->GetX(),fPosTempPre->GetZ()));
            fDispl->SetY(fVecDisplY->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()) - fVecDisplY->GetVal2d(fPosTempPre->GetX(),fPosTempPre->GetZ()));
            fDispl->SetZ(fVecDisplY->GetVal2d(fPosTemp->GetX(),fPosTemp->GetZ()) - fVecDisplY->GetVal2d(fPosTempPre->GetX(),fPosTempPre->GetZ()));
            
            fDispl->RotateInv(fDefAnglesPhi.at(i0),fDefAnglesTheta.at(i0));
            fDispl->SetZ(0.);
        }
        
        if(bSudden==true){
            part->GetPos()->Add(fDispl);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::Init(ECHARM_strip* strip,ECHARM_particle* part){
    if(bVecStored==false){
        fBoxX->SetPar(1,1.*centimeter*fArea*0.5);
        fBoxY->SetPar(1,1.*centimeter*fArea*0.5);
        fBoxZ->SetPar(1,strip->GetDim()->GetZ()*0.5);
        
        fBurger->Set(strip->GetCrystal()->GetPeriodX(),0.,0.);
        Store();
    }
    
    for(int i0 = 0;i0 < fDefNum;i0++){
        fDefCenter.at(i0)->SetX(fBoxX->GenerateNumber());
        fDefCenter.at(i0)->SetY(fBoxY->GenerateNumber());
        fDefCenter.at(i0)->SetZ(fBoxZ->GenerateNumber());
        fDefAnglesPhi.at(i0) = drand48() * c2Pi;
        fDefAnglesTheta.at(i0) = acos(2.* drand48() - 1.);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::Store(){
    std::vector<double> vecBRX;
    std::vector<double> vecBRY;
    std::vector<double> vecBRZ;
    std::vector<double> vecDisplX;
    std::vector<double> vecDisplY;
    std::vector<double> vecDisplZ;
    
    int fNumSteps[3];
    fNumSteps[0] = 256;
    fNumSteps[1] = 256;
    fNumSteps[2] = 1;
    
    double fLimitsHalfVecBR[3];
    fLimitsHalfVecBR[0] = fLimitsHalf->GetX()*2.;
    fLimitsHalfVecBR[1] = fLimitsHalf->GetY()*2.;
    fLimitsHalfVecBR[2] = fLimitsHalf->GetZ()*2.;
    
    double fStep[3];
    fStep[0] = 2.*fLimitsHalf->Get(0)/fNumSteps[0];
    fStep[1] = 2.*fLimitsHalf->Get(1)/fNumSteps[1];
    fStep[2] = 1;
    
    fVecBRX = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecBRY = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecBRZ = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    
    fVecDisplX = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecDisplY = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    fVecDisplZ = new ECHARM_periodicvector(fNumSteps,fLimitsHalfVecBR);
    
    ECHARM_3vec* zero = new ECHARM_3vec(0.,0.,0.);
    
    for(int i1=0;i1<fNumSteps[1];i1++){
        fPosTemp->SetZ(double(i1) * fStep[1] - fLimitsHalf->Get(1));
        for(int i0=0;i0<fNumSteps[0];i0++){
            fPosTemp->SetX(double(i0) * fStep[0] - fLimitsHalf->Get(0));
            
            ComputeBR(fPosTemp,zero);
            vecBRX.push_back(fBR->GetX());
            vecBRY.push_back(fBR->GetY());
            vecBRZ.push_back(fBR->GetZ());
            
            CompDispl(fPosTemp,zero);
            vecDisplX.push_back(fDispl->GetX());
            vecDisplY.push_back(fDispl->GetY());
            vecDisplZ.push_back(fDispl->GetZ());
        }
    }
    
    fVecBRX->Set(vecBRX);
    fVecBRY->Set(vecBRY);
    fVecBRZ->Set(vecBRZ);
    
    fVecDisplX->Set(vecDisplX);
    fVecDisplY->Set(vecDisplY);
    fVecDisplZ->Set(vecDisplZ);
    
    bVecStored = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::CompDispl(ECHARM_3vec*,ECHARM_3vec*){
    fDispl->SetX(0.);
    fDispl->SetY(0.);
    fDispl->SetZ(0.);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::ComputeBR(ECHARM_3vec*,ECHARM_3vec*){
    fBR->SetX(0.);
    fBR->SetY(0.);
    fBR->SetZ(0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
