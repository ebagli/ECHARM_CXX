//
//  ECHARM_3vec.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
#ifdef _ECHARM_3vec_h

#include "ECHARM_3vec.hh"
#include <sstream>
#include <math.h>

ECHARM_3vec::ECHARM_3vec(){
    fSize[0] = 0.;
    fSize[1] = 0.;
    fSize[2] = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec::ECHARM_3vec(double X, double Y, double Z){
    Set(X,Y,Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec::~ECHARM_3vec(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_3vec::IsParallel(ECHARM_3vec* vVector){
    if((fSize[1] * vVector->Get(2) - fSize[2] * vVector->Get(1) == 0.)&&
       (fSize[2] * vVector->Get(0) - fSize[0] * vVector->Get(2) == 0.)&&
       (fSize[0] * vVector->Get(1) - fSize[1] * vVector->Get(0) == 0.)
       ){
        return true;
    }
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_3vec::IsInCube(ECHARM_3vec* vec){
    if((fabs(fSize[0]) < fabs(vec->GetX())) &&
       (fabs(fSize[1]) < fabs(vec->GetY())) &&
       (fabs(fSize[2]) < fabs(vec->GetZ()))){
        return true;
    }
    
    return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Print(){
    std::cout << "       ";
    std::cout << std::setw(10) << std::setprecision(3) << fSize[0];
    std::cout << std::setw(10) << std::setprecision(3) << fSize[1];
    std::cout << std::setw(10) << std::setprecision(3) << fSize[2];
    std::cout << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Print(double MoltiplicationFactor){
    std::cout << "       ";
    std::cout << std::setw(10) << std::setprecision(3) << fSize[0] * MoltiplicationFactor;
    std::cout << std::setw(10) << std::setprecision(3) << fSize[1] * MoltiplicationFactor;
    std::cout << std::setw(10) << std::setprecision(3) << fSize[2] * MoltiplicationFactor;
    std::cout << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::string ECHARM_3vec::PrintAsString(double vScaleFactor = 1.){
    std::stringstream vSS;
    vSS << round(fSize[0]/vScaleFactor) << "_" << round(fSize[1]/vScaleFactor) << "_" << round(fSize[2]/vScaleFactor);
    return vSS.str();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_3vec::ScalarProduct(ECHARM_3vec* vVector){
    double vScalarProduct = 0.0;
    for(unsigned int i=0;i<3;i++){
        vScalarProduct += fSize[i] * vVector->fSize[i];
    }
    return vScalarProduct;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_3vec::ScalarProduct(double vec[3]){
    double vScalarProduct = 0.0;
    for(unsigned int i=0;i<3;i++){
        vScalarProduct += fSize[i] * vec[i];
    }
    return vScalarProduct;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_3vec::GetAngle(ECHARM_3vec* vVector){
    double vScalarProduct = this->ScalarProduct(vVector);
    double vMagnitude = vVector->GetModule() * this->GetModule();
    return acos(vScalarProduct/vMagnitude);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_3vec::GetPhi(){
    return acos(fSize[2]/GetModule());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_3vec::GetTheta(){
    if(fSize[0] != 0.){
        return atan2(fSize[1],fSize[0]);
    }
    else{
        return 0.;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec* ECHARM_3vec::ScaleModuleTo(double vModule){
    ECHARM_3vec* vVector = new ECHARM_3vec();
    double vScaleFactor = vModule / GetModule();
    for(int i=0;i<3;i++) vVector->Set(i, fSize[i] * vScaleFactor);
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec* ECHARM_3vec::VectorProductTo(ECHARM_3vec *vVector){
    ECHARM_3vec* vVectorProduct = new ECHARM_3vec();
    vVectorProduct->SetX(fSize[1] * vVector->fSize[2] - fSize[2] * vVector->fSize[1]);
    vVectorProduct->SetY(fSize[2] * vVector->fSize[0] - fSize[0] * vVector->fSize[2]);
    vVectorProduct->SetZ(fSize[0] * vVector->fSize[1] - fSize[1] * vVector->fSize[0]);
    return vVectorProduct;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec* ECHARM_3vec::ConstantMoltiplicationTo(double MoltiplicationFactor){
    ECHARM_3vec *vVector = new ECHARM_3vec();
    for(int i=0;i<3;i++) vVector->Set(i, fSize[i] * MoltiplicationFactor);
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec* ECHARM_3vec::NormalizeVectorTo(){
    ECHARM_3vec *vVector = new ECHARM_3vec();
    double module = GetModule();
    for(int i=0;i<3;i++) vVector->Set(i,fSize[i]/module);
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_3vec* ECHARM_3vec::AddTo(ECHARM_3vec* vec,double vScaleFactor = 1.){
    ECHARM_3vec *vVector = new ECHARM_3vec();
    for(int i=0;i<3;i++) vVector->Set(i,fSize[i]+vec->Get(i)*vScaleFactor);
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::ScaleModule(double vModule){
    double vScaleFactor = vModule / GetModule();
    fSize[0] *= (vScaleFactor);
    fSize[1] *= (vScaleFactor);
    fSize[2] *= (vScaleFactor);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::VectorProduct(ECHARM_3vec *vVector){
    SetX(fSize[1] * vVector->fSize[2] - fSize[2] * vVector->fSize[1]);
    SetY(fSize[2] * vVector->fSize[0] - fSize[0] * vVector->fSize[2]);
    SetZ(fSize[0] * vVector->fSize[1] - fSize[1] * vVector->fSize[0]);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::ConstantMoltiplication(double MoltiplicationFactor){
    for(int i=0;i<3;i++) Set(i, fSize[i] * MoltiplicationFactor);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::NormalizeVector(){
    ScaleModule(1.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Add(ECHARM_3vec* vec,double vScaleFactor = 1.){
    for(int i=0;i<3;i++) Set(i,fSize[i]+vec->Get(i)*vScaleFactor);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::AddInverse(ECHARM_3vec* vec,double vScaleFactor = 1.){
    for(int i=0;i<3;i++) {
        double val = 0.;
        if(fSize[i]!=0.){
            val += 1./fSize[i];
        }
        if(vec->Get(i)!=0.){
            val += 1./vec->Get(i)*vScaleFactor;
        }
        if(val!=0.){
            Set(i,1./val);
        }
        else{
            Set(i,0.);
        }
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Zero(){
    fSize[0] = 0.;
    fSize[1] = 0.;
    fSize[2] = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Rotate(double phi,double theta,double psi){
    if(psi == 0.){
        Rotate(phi,theta);
    }
    else{
        double a11 = + cos(psi)*cos(phi) - cos(theta)*sin(phi)*sin(psi);
        double a12 = + cos(psi)*sin(phi) + cos(theta)*cos(phi)*sin(psi);
        double a13 = + sin(psi)*sin(theta);
        
        double a21 = - sin(psi)*cos(phi) - cos(theta)*sin(phi)*cos(psi);
        double a22 = - sin(psi)*sin(phi) + cos(theta)*cos(phi)*cos(psi);
        double a23 = + cos(psi)*sin(theta);
        
        double a31 = + sin(theta)*sin(phi);
        double a32 = - sin(theta)*cos(phi);
        double a33 = + cos(theta);
        
        
        double x = fSize[0] * a11 + fSize[1] * a12 + fSize[2] * a13;
        double y = fSize[0] * a21 + fSize[1] * a22 + fSize[2] * a23;
        double z = fSize[0] * a31 + fSize[1] * a32 + fSize[2] * a33;
        
        fSize[0] = x;
        fSize[1] = y;
        fSize[2] = z;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Rotate(double phi,double theta){
    if(theta == 0.){
        Rotate(phi);
    }
    else{
        double a11 = + cos(phi);
        double a12 = + sin(phi);
        double a13 = 0.;
        
        double a21 = - cos(theta)*sin(phi);
        double a22 = + cos(theta)*cos(phi);
        double a23 = + sin(theta);
        
        double a31 = + sin(theta)*sin(phi);
        double a32 = - sin(theta)*cos(phi);
        double a33 = + cos(theta);
        
        
        double x = fSize[0] * a11 + fSize[1] * a12 + fSize[2] * a13;
        double y = fSize[0] * a21 + fSize[1] * a22 + fSize[2] * a23;
        double z = fSize[0] * a31 + fSize[1] * a32 + fSize[2] * a33;
        
        fSize[0] = x;
        fSize[1] = y;
        fSize[2] = z;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Rotate(double phi){
    if(phi != 0.){
        double a11 = + cos(phi);
        double a12 = + sin(phi);
        double a13 = 0.;
        
        double a21 = - sin(phi);
        double a22 = + cos(phi);
        double a23 = 0.;
        
        double a31 = 0.;
        double a32 = 0.;
        double a33 = 1.;
        
        
        double x = fSize[0] * a11 + fSize[1] * a12 + fSize[2] * a13;
        double y = fSize[0] * a21 + fSize[1] * a22 + fSize[2] * a23;
        double z = fSize[0] * a31 + fSize[1] * a32 + fSize[2] * a33;
        
        fSize[0] = x;
        fSize[1] = y;
        fSize[2] = z;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif