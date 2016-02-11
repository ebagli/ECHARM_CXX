//
//  ECHARM_defect.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _ECHARM_defect_h

#include "ECHARM_defect.hh"

ECHARM_defect::ECHARM_defect(double num,double prob,bool sudden = true):
ECHARM_displacement(num,prob,sudden){
    
    SetName("defect");
    bRandomPosition = true;
    fPoissonRatio = 0.42;
    fBurger = new ECHARM_3vec(1. * AA,0.,0.);
    fLine = new ECHARM_3vec(0.,1.,0.);
    fHotLimit = new ECHARM_3vec(0.,1.,0.);
    
    fLimitsHalf->SetX(2. * micrometer);
    fLimitsHalf->SetY(2. * micrometer);
    fLimitsHalf->SetZ(2. * micrometer);
    
    fHotLimit->SetX(0.1 * micrometer);
    fHotLimit->SetY(0.1 * micrometer);
    fHotLimit->SetZ(0.1 * micrometer);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_defect::~ECHARM_defect(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_defect::IsInHotZone(){
    if((fPosTemp->IsInCube(fHotLimit)) &&
       (fPosTempPre->IsInCube(fHotLimit)) ){
        return true;
    }
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::Init(ECHARM_strip* strip,ECHARM_particle* part,ECHARM_info_save*){
    if(bVecStored==false){
        fBoxX->SetPar(1,1.*centimeter*centimeter/strip->GetDim()->GetZ()*fArea*0.5);
        if(bBoxYzero == true){
            fBoxY->SetPar(1,0.);
        }
        else{
            fBoxY->SetPar(1,1.*centimeter*0.5);
        }
        fBoxZ->SetPar(1,strip->GetDim()->GetZ()*0.5);
        
        if(fBurger->GetModule()==0.){
            fBurger->SetX(strip->GetCrystal()->GetPeriodX());
        }
        
        if(bVecStored==false){
            fNumSteps[0] = 32;
            fNumSteps[1] = 32;
            fNumSteps[2] = 1;
        }
        Store();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::ComputeDispl(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    double x = partpos->GetX() - defpos->GetX();
    double z = partpos->GetZ() - defpos->GetZ();
    
    double dx = 0.0;
    double dz = 0.0;
    double dy = 0.0;
    
    double burgerEdge = GetBurgerEdge();
    double burgerScrew = GetBurgerScrew();
    
    if(x!=0. &&
       z!=0.){
        double xz2 = x * x + z * z;
        
        if(burgerEdge!=0.){
            dx = atan2(x , z ) ;
            dx += ( z * x / xz2 / 2.0 / ( 1.0 - fPoissonRatio ) );
            dx *= ( burgerEdge );
            dx /= ( 2. * cPi );
            
            dz = ( ( 1.0 - 2.0 * fPoissonRatio) * log(xz2));
            dz += ( ( x * x - z * z ) / xz2 );
            dz *= ( burgerEdge );
            dz /= ( 8. * cPi );
            dz /= ( 1. - fPoissonRatio );
        }
        
        if(burgerScrew!=0.){
            dy = atan2( x , z ) ;
            dy *= ( burgerScrew );
            dy /= ( 2. * cPi );
        }
        
    }
    fDispl->SetX(dx);
    fDispl->SetZ(dz);
    fDispl->SetY(dy);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::ComputeBR(ECHARM_3vec* partpos,ECHARM_3vec* defpos){
    
    double x = partpos->GetX() - defpos->GetX();
    double z = partpos->GetZ() - defpos->GetZ();
    
    double burgerEdge = GetBurgerEdge();
    double burgerScrew = GetBurgerScrew();
    
    fBR->SetZ(0.);
    
    if(x==0. &&
       z==0.){
        fBR->SetX(0.);
        fBR->SetY(0.);
    }
    else{
        // (1 + (d/dz (b/(2*l)(arctan(z/x)+1/(2*(1-P))*x*z/(x*x+z*z))))^2)^1.5/ (d/dzdz (b/(2*l)(arctan(z/x)+1/(2*(1-P))*x*z/(x*x+z*z))))
        double xz2 = x*x + z*z;
        double p = fPoissonRatio;
        
        double a = 0.5 / (1. - p);

        double ddzdz = - 2. * x * z * (a * xz2 + 3. * x * x - z * z);
        ddzdz /= (a * xz2 * xz2 * xz2);
        ddzdz *= 2. * cPi * burgerEdge;

        double ddz = x * (a * xz2 + x * x - z * z);
        ddz /= (a * xz2 * xz2);
        ddz *= 2. * cPi * burgerEdge;

        double Rx = pow(1. + ddz * ddz,1.5);
        if(ddzdz!=0.){
            Rx /= ddzdz;
        }
        else{
            Rx = 1.E15;
        }

        fBR->SetX(Rx);
        
        // (1 + (d/dz (b/(2*l)(arctan(z/x))))^2)^1.5/ (d/dzdz (b/(2*l)(arctan(z/x))))
        double Ry1 = burgerScrew*burgerScrew+x*x;
        Ry1 /= fSquare(2.*cPi*xz2);
        Ry1 += 1.;
        
        double Ry2 = burgerScrew * x * z;
        double Ry = cPi * xz2 * xz2;
        
        if(Ry2!=0){
            Ry /= Ry2;
            Ry *= pow(Ry1,1.5);
        }
        else{
            Ry = 0.;
        }
        fBR->SetY(- Ry);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_defect::ComputeAnglesFromBurgerAndLineDirections(){
    
    ECHARM_3vec* xaxis;
    ECHARM_3vec* yaxis = fLine->NormalizeVectorTo();
    if(fLine->IsParallel(fBurger)){
        xaxis = new ECHARM_3vec(-yaxis->GetY(),yaxis->GetX(),yaxis->GetZ());
    }
    else{
        xaxis = fBurger->VectorProductTo(fLine);
    }
    ECHARM_3vec* zaxis = xaxis->VectorProductTo(yaxis);
    
    xaxis->NormalizeVector();
    yaxis->NormalizeVector();
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

#endif
