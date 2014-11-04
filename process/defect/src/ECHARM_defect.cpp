//
//  ECHARM_defect.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_defect.hh"
#include "TH2D.h"
ECHARM_defect::ECHARM_defect(double num,double prob,bool sudden = true):
ECHARM_displacement(num,prob,sudden){
    
    SetName("defect");
    bRandomPosition = true;
    fPoissonRatio = 0.42;
    fBurger = 1. * AA;
    
    fLimitsHalf->SetX(2. * micrometer);
    fLimitsHalf->SetY(2. * micrometer);
    fLimitsHalf->SetZ(2. * micrometer);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect::~ECHARM_defect(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::DoBeforeInteraction(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
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
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::Init(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    if(bVecStored==false){
        fBoxX->SetPar(1,1.*centimeter*fArea*0.5);
        fBoxY->SetPar(1,0.);
        fBoxZ->SetPar(1,strip->GetDim()->GetZ()*0.5);
        
        if(fBurger==0.){
            fBurger = strip->GetCrystal()->GetPeriodX();
        }
        
        Store();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::ComputeDispl(ECHARM_3vec*,ECHARM_3vec*){
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

void ECHARM_defect::ComputeAnglesFromBurgerAndLineDirections(ECHARM_3vec* burger,ECHARM_3vec* line){
    
    ECHARM_3vec* xaxis = burger->NormalizeVectorTo();
    ECHARM_3vec* yaxis = line->NormalizeVectorTo();
    ECHARM_3vec* zaxis = burger->VectorProductTo(line);
    zaxis->NormalizeVector();
    
    double theta = 0.;
    double phi = 0.;
    double psi = 0.;
    
    if(fabs(xaxis->GetZ()) != 1.){
        theta = -asin(xaxis->GetZ());
        double costheta = cos(theta);
        
        psi = atan2(yaxis->GetZ()/costheta,zaxis->GetZ()/costheta);
        phi = atan2(xaxis->GetY()/costheta,xaxis->GetX()/costheta);
    }
    else{
        phi = 0.;
        if(xaxis->GetZ() == -1.){
            theta = cPiHalf;
            psi = atan2(+yaxis->GetX(),+zaxis->GetX());
        }
        else{
            theta = -cPiHalf;
            psi = atan2(-yaxis->GetX(),-yaxis->GetX());
        }
    }
  
    SetAng(phi,theta,psi);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

