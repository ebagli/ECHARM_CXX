//
//  ECHARM_3vec.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

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
    for(int i=0;i<3;i++) vVector->Set(i,fSize[i]/GetModule());
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
    for(int i=0;i<3;i++) Set(i,fSize[i]/GetModule());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Add(ECHARM_3vec* vec,double vScaleFactor = 1.){
    for(int i=0;i<3;i++) Set(i,fSize[i]+vec->Get(i)*vScaleFactor);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::AddInverse(ECHARM_3vec* vec,double vScaleFactor = 1.){
    for(int i=0;i<3;i++) Set(i,1./(1./fSize[i]+1./vec->Get(i)*vScaleFactor));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Zero(){
    fSize[0] = 0.;
    fSize[1] = 0.;
    fSize[2] = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::Rotate(double dphi,double dtheta){
    double r = GetModule();
    double theta = GetTheta();
    double phi = GetPhi();
    
    theta += dtheta;
    phi += dphi;
    
    fSize[0] = r * sin(theta) * cos(phi);
    fSize[1] = r * sin(theta) * sin(phi);
    fSize[2] = r * cos(theta);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_3vec::RotateInv(double dphi,double dtheta){
    double r = GetModule();
    double theta = GetTheta();
    double phi = GetPhi();
    
    theta += dtheta;
    phi += dphi;
    
    fSize[0] = r * sin(cPiHalf-theta) * cos(-phi);
    fSize[1] = r * sin(cPiHalf-theta) * sin(-phi);
    fSize[2] = r * cos(cPiHalf-theta);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
