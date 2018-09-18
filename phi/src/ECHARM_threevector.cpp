//
//  ECHARM_threevector.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//
ECHARM_threevector::ECHARM_threevector()
{
    InitializePointersThreeVector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ECHARM_threevector::ECHARM_threevector(double Size[3])
{
    InitializePointersThreeVector();
    Set(Size);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_threevector::ECHARM_threevector(double X, double Y, double Z)
{
    InitializePointersThreeVector();
    Set(X,Y,Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_threevector::~ECHARM_threevector()
{
    if(&fSize) {delete[] &fSize;};
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::Set(double Size[3])
{
    for(int vIndex=0;vIndex<3;vIndex++) fSize[vIndex] = Size[vIndex];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::Set(double X, double Y, double Z)
{
    fSize[0] = X;
    fSize[1] = Y;
    fSize[2] = Z;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::InitializePointersThreeVector()
{
    for(int vIndex=0;vIndex<3;vIndex++) fSize[vIndex] = 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::Set(std::ifstream* File_In)
{
    if(File_In)
    {
        if(File_In->good()) *File_In >> fSize[0];
        if(File_In->good()) *File_In >> fSize[1];
        if(File_In->good()) *File_In >> fSize[2];
    }
    else std::cout << "ECHARM_threevector ERROR - file does not exist" << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::PrintThreeVector()
{
    std::cout << "       ";
    std::cout << std::setw(10) << std::setprecision(3) << fSize[0];
    std::cout << std::setw(10) << std::setprecision(3) << fSize[1];
    std::cout << std::setw(10) << std::setprecision(3) << fSize[2];
    std::cout << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::PrintThreeVector(double MoltiplicationFactor)
{
    std::cout << "       ";
    std::cout << std::setw(10) << std::setprecision(3) << fSize[0] * MoltiplicationFactor;
    std::cout << std::setw(10) << std::setprecision(3) << fSize[1] * MoltiplicationFactor;
    std::cout << std::setw(10) << std::setprecision(3) << fSize[2] * MoltiplicationFactor;
    std::cout << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_threevector& ECHARM_threevector::operator=(const ECHARM_threevector& right)
{
    if (this != &right)
        for(int i=0;i<3;i++)
            fSize[i] = right.fSize[i];
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_threevector::ScalarProduct(ECHARM_threevector* vVector)
{
    double vScalarProduct = 0.0;
    for(int i=0;i<3;i++) vScalarProduct += fSize[i] * vVector->fSize[i];
    return vScalarProduct;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_threevector::ScaleModuleTo(double vModule)
{
    double vScaleFactor = vModule / GetModule();
    fSize[0] *= (vScaleFactor);
    fSize[1] *= (vScaleFactor);
    fSize[2] *= (vScaleFactor);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_threevector* ECHARM_threevector::VectorProduct(ECHARM_threevector *vVector)
{
    ECHARM_threevector* vVectorProduct = new ECHARM_threevector();
    vVectorProduct->Set(0, fSize[1] * vVector->fSize[2] - fSize[2] * vVector->fSize[1]);
    vVectorProduct->Set(1, fSize[2] * vVector->fSize[0] - fSize[0] * vVector->fSize[2]);
    vVectorProduct->Set(2, fSize[0] * vVector->fSize[1] - fSize[1] * vVector->fSize[0]);
    return vVectorProduct;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_threevector* ECHARM_threevector::ConstantMoltiplication(double MoltiplicationFactor)
{
    ECHARM_threevector *vVector = new ECHARM_threevector();
    for(int i=0;i<3;i++) vVector->Set(i, fSize[i] * MoltiplicationFactor);
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_threevector* ECHARM_threevector::NormalizeVector()
{
    ECHARM_threevector *vVector = new ECHARM_threevector();
    for(int i=0;i<3;i++) vVector->Set(i, fSize[i]/GetModule());
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_threevector::operator==(const ECHARM_threevector& right) const
{
    return (this == (ECHARM_threevector*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_threevector::operator!=(const ECHARM_threevector& right) const
{
    return (this != (ECHARM_threevector*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
