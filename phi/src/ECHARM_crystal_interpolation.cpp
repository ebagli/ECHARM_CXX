//
//  ECHARM_crystal_interpolation.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//



ECHARM_crystal_interpolation::ECHARM_crystal_interpolation()
{
    InitializePointersCrystalInterpolation();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_interpolation::ECHARM_crystal_interpolation(ECHARM_cell *cell, ECHARM_miller *miller, ECHARM_atom *atom, ECHARM_lattice *lattice)
{
    InitializePointersCrystalInterpolation();
    SetCell(cell);
    SetMiller(miller);
    AddBase(atom,lattice);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_interpolation::ECHARM_crystal_interpolation(ECHARM_crystal *crystal,bool bCalculateAxial)
{
    InitializePointersCrystalInterpolation();
    SetCell(crystal->GetCell());
    SetMiller(crystal->GetMiller());
    for(unsigned int i=0;i<crystal->GetNumberOfBases();i++)
        AddBase(crystal->GetAtom(i),crystal->GetLattice(i));
    
    ComputeCrystalAverageParameters();
    
    SetElectricCharacteristicPlanar(crystal->FindPlanarElectricCharacteristic(0),0);
    SetElectricCharacteristicPlanar(crystal->FindPlanarElectricCharacteristic(1),1);
    SetElectricCharacteristicPlanar(crystal->FindPlanarElectricCharacteristic(2),2);
    SetElectricCharacteristicPlanar(crystal->FindPlanarElectricCharacteristic(3),3);

    if(bCalculateAxial){
    SetElectricCharacteristicAxial(crystal->FindAxialElectricCharacteristic(0),0);
    SetElectricCharacteristicAxial(crystal->FindAxialElectricCharacteristic(1),1);
    SetElectricCharacteristicAxial(crystal->FindAxialElectricCharacteristic(2),2);
    SetElectricCharacteristicAxial(crystal->FindAxialElectricCharacteristic(3),3);
    SetElectricCharacteristicAxial(crystal->FindAxialElectricCharacteristic(4),4);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_interpolation::ECHARM_crystal_interpolation(ECHARM_crystal_interpolation *crystal)
{
    InitializePointersCrystalInterpolation();
    SetCell(crystal->GetCell());
    SetMiller(crystal->GetMiller());
    for(unsigned int i=0;i<crystal->GetNumberOfBases();i++)
        AddBase(crystal->GetAtom(i),crystal->GetLattice(i));
    
    ComputeCrystalAverageParameters();
    
    SetElectricCharacteristicPlanar(crystal->GetPlanarElectricCharacteristicVector(0),0);
    SetElectricCharacteristicPlanar(crystal->GetPlanarElectricCharacteristicVector(1),1);
    SetElectricCharacteristicPlanar(crystal->GetPlanarElectricCharacteristicVector(2),2);
    SetElectricCharacteristicPlanar(crystal->GetPlanarElectricCharacteristicVector(3),3);

    SetElectricCharacteristicAxial(crystal->GetAxialElectricCharacteristicVector(0),0);
    SetElectricCharacteristicAxial(crystal->GetAxialElectricCharacteristicVector(1),1);
    SetElectricCharacteristicAxial(crystal->GetAxialElectricCharacteristicVector(2),2);
    SetElectricCharacteristicAxial(crystal->GetAxialElectricCharacteristicVector(3),3);
    SetElectricCharacteristicAxial(crystal->GetAxialElectricCharacteristicVector(4),4);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_crystal_interpolation::~ECHARM_crystal_interpolation()
{
    if (&fAtom)         { delete &fAtom; }
    if (&fLattice)         { delete &fLattice; }
    if (&fMiller)         { delete &fMiller; }
    if (&fCell)         { delete &fCell; }

    if (&fIntegrationStepNumberPlanar) { delete &fIntegrationStepNumberPlanar; }
    if (&fIntegrationStepNumberAxialX) { delete &fIntegrationStepNumberAxialX; }
    if (&fIntegrationStepNumberAxialY) { delete &fIntegrationStepNumberAxialY; }
    if (&fDirectPeriodPlanar) { delete &fDirectPeriodPlanar; }
    if (&fDirectPeriodAxialX) { delete &fDirectPeriodAxialX; }
    if (&fDirectPeriodAxialY) { delete &fDirectPeriodAxialY; }
    if (&fReciprocalPeriodPlanar) { delete &fReciprocalPeriodPlanar; }
    if (&fReciprocalPeriodAxialX) { delete &fReciprocalPeriodAxialX; }
    if (&fReciprocalPeriodAxialY) { delete &fReciprocalPeriodAxialY; }
    if (&fElectricFieldMaximum) { delete &fElectricFieldMaximum; }
    if (&fPotentialMaximum) { delete &fPotentialMaximum; }
    
    if (&fInterpolationFunction) { delete &fInterpolationFunction; }

    
    if (&fPlanarPotential) { delete &fPlanarPotential; }
    if (&fPlanarAtomicDensity) { delete &fPlanarAtomicDensity; }
    if (&fPlanarElectronDensity) { delete &fPlanarElectronDensity; }
    if (&fPlanarElectricFieldX) { delete &fPlanarElectricFieldX; }
    if (&fAxialPotential) { delete &fAxialPotential; }
    if (&fAxialAtomicDensity) { delete &fAxialAtomicDensity; }
    if (&fAxialElectronDensity) { delete &fAxialElectronDensity; }
    if (&fAxialElectricFieldX) { delete &fAxialElectricFieldX; }
    if (&fAxialElectricFieldY) { delete &fAxialElectricFieldY; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_interpolation::InitializePointersCrystalInterpolation()
{
    InitializePointersCrystal();
    
    fInterpolationFunction = new ECHARM_interpolation();
    
    fPlanarPotential.clear();
    fPlanarAtomicDensity.clear();
    fPlanarElectronDensity.clear();
    fPlanarElectricFieldX.clear();
    
    fAxialPotential.clear();
    fAxialAtomicDensity.clear();
    fAxialElectronDensity.clear();
    fAxialElectricFieldX.clear();
    fAxialElectricFieldY.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_crystal_interpolation& ECHARM_crystal_interpolation::operator=(const ECHARM_crystal_interpolation& right)
{
    if (this != &right)
    {
        fAtom = right.fAtom;
        fLattice = right.fLattice;
        fCell = right.fCell;
        fMiller = right.fMiller;
        
        fIntegrationStepNumberPlanar = right.fIntegrationStepNumberPlanar;
        fIntegrationStepNumberAxialX = right.fIntegrationStepNumberAxialX;
        fIntegrationStepNumberAxialY = right.fIntegrationStepNumberAxialY;
        
        fDirectPeriodPlanar = right.fDirectPeriodPlanar;
        fDirectPeriodAxialX = right.fDirectPeriodAxialX;
        fDirectPeriodAxialY = right.fDirectPeriodAxialY;
        
        fReciprocalPeriodPlanar = right.fReciprocalPeriodPlanar;
        fReciprocalPeriodAxialX = right.fReciprocalPeriodAxialX;
        fReciprocalPeriodAxialY = right.fReciprocalPeriodAxialY;
        
        fElectricFieldMaximum = right.fElectricFieldMaximum;
        fPotentialMaximum = right.fPotentialMaximum;
        
        fPlanarPotential =  right.fPlanarPotential;
        fPlanarAtomicDensity = right.fPlanarAtomicDensity;
        fPlanarElectronDensity = right.fPlanarElectronDensity;
        fPlanarElectricFieldX = right.fPlanarElectricFieldX;
        
        fAxialPotential = right.fAxialPotential;
        fAxialAtomicDensity = right.fAxialAtomicDensity;
        fAxialElectronDensity = right.fAxialElectronDensity;
        fAxialElectricFieldX = right.fAxialElectricFieldX;
        fAxialElectricFieldY = right.fAxialElectricFieldY;
        
        fInterpolationFunction = right.fInterpolationFunction;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_interpolation::operator==(const ECHARM_crystal_interpolation& right) const
{
    return (this == (ECHARM_crystal_interpolation*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_crystal_interpolation::operator!=(const ECHARM_crystal_interpolation& right) const
{
    return (this != (ECHARM_crystal_interpolation*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetPotentialMaximum()
{
    if(fPotentialMaximum==DBL_MAX){
        fPotentialMaximum = *std::max_element(fPlanarPotential.begin(),fPlanarPotential.end()) - *std::min_element(fPlanarPotential.begin(),fPlanarPotential.end());}
    
    return fPotentialMaximum;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetPotentialMinimum()
{
    if(fPotentialMinimum==DBL_MAX){
        fPotentialMinimum = *std::min_element(fPlanarPotential.begin(),fPlanarPotential.end());
    }
    return fPotentialMinimum;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetElectricFieldMaximum()
{
    if(fElectricFieldMaximum==DBL_MAX){
    fElectricFieldMaximum = *std::max_element(fPlanarElectricFieldX.begin(),fPlanarElectricFieldX.end());
    }
    return fElectricFieldMaximum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetPotentialMaximumAxial()
{
    if(fPotentialMaximum==DBL_MAX){
   fPotentialMaximum = *std::max_element(fAxialPotential.begin(),fAxialPotential.end()) - *std::min_element(fAxialPotential.begin(),fAxialPotential.end());
    }
    return fPotentialMaximum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetElectricFieldMaximumAxial()
{
    if(fElectricFieldMaximum==DBL_MAX){
   fElectricFieldMaximum = *std::max_element(fAxialElectricFieldX.begin(),fAxialElectricFieldX.end());
    }
    return fElectricFieldMaximum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetPlanarElectricCharacteristicInterpolation(double vX, std::vector<double> & vVector)
{
    double x = GetValueInPeriodicUnit(vX,fDirectPeriodPlanar);
        
    double vStepX = fDirectPeriodPlanar / ( fIntegrationStepNumberPlanar - 1 );
    long vInt[4];
    vInt[1] = int( x / vStepX );
    if( (vInt[1]) == (fIntegrationStepNumberPlanar - 1) ){
        vInt[0] = fIntegrationStepNumberPlanar - 2;
        vInt[2] = 0;
        vInt[3] = 1;
    }
    else if(vInt[1] == (fIntegrationStepNumberPlanar - 2) )
    {
        vInt[0] = fIntegrationStepNumberPlanar - 3;
        vInt[2] = fIntegrationStepNumberPlanar - 1;
        vInt[3] = 0;
    }
    else if(vInt[1] == 0){
        vInt[0] = fIntegrationStepNumberPlanar - 1;
        vInt[2] = 1;
        vInt[3] = 2;
    }
    else{
        vInt[0] = vInt[1] - 1;
        vInt[2] = vInt[1] + 1;
        vInt[3] = vInt[1] + 2;
    }
    x -= vInt[1] * vStepX;

    if(vInt[1] > fIntegrationStepNumberPlanar) std::cout << "ECHARM_crystal_interpolation - ERROR: " << vInt[1] << " " << fIntegrationStepNumberPlanar << std::endl;

    if(x == 0.0) return vVector.at(vInt[1]);
    else
    {
        x /= vStepX;
        return fInterpolationFunction->FindInterpolate1D(vVector.at(vInt[0]),vVector.at(vInt[1]),vVector.at(vInt[2]),vVector.at(vInt[3]),x);
    }
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetAxialElectricCharacteristicInterpolation(double vX, double vY, std::vector<double> vVector)
{
    double x = GetValueInPeriodicUnit(vX,fDirectPeriodAxialX);
    double y = GetValueInPeriodicUnit(vY,fDirectPeriodAxialY);
    
    double vStepX = fDirectPeriodAxialX / ( fIntegrationStepNumberAxialX - 1 );
    long vIntX[2];
    if( (vIntX[0] = int( x / vStepX ) ) == (fIntegrationStepNumberAxialX - 1) ) vIntX[1] = 0;
    else vIntX[1] = vIntX[0] + 1;
    x -= vIntX[0] * vStepX;

    if(vIntX[0] > fIntegrationStepNumberAxialX) std::cout << "ECHARM_crystal_interpolation - ERROR Axial X 0: " << vIntX[0] <<  " " << fIntegrationStepNumberAxialX << std::endl;
    if(vIntX[1] > fIntegrationStepNumberAxialX) std::cout << "ECHARM_crystal_interpolation - ERROR Axial X 1: " << vIntX[1] <<  " " << fIntegrationStepNumberAxialX << std::endl;

    double vStepY = fDirectPeriodAxialY / ( fIntegrationStepNumberAxialY - 1 );
    long vIntY[2];
    if( (vIntY[0] = int( y / vStepY ) ) == (fIntegrationStepNumberAxialY - 1) ) vIntY[1] = 0;
    else vIntY[1] = vIntY[0] + 1;
    y -= vIntY[0] * vStepY;

    if(vIntY[0] > fIntegrationStepNumberAxialY) std::cout << "ECHARM_crystal_interpolation - ERROR Axial Y 0: " << vIntY[0] <<  " " << fIntegrationStepNumberAxialY << std::endl;
    if(vIntY[1] > fIntegrationStepNumberAxialY) std::cout << "ECHARM_crystal_interpolation - ERROR Axial Y 1: " << vIntY[1] <<  " " << fIntegrationStepNumberAxialY << std::endl;
    
    if(x == 0.0 && y == 0.0) return vVector.at(ComputeAxialVectorIndex(vIntX[0],vIntY[0],fIntegrationStepNumberAxialX));
    else
    {
        x /= vStepX;
        y /= vStepY;
        return fInterpolationFunction->FindInterpolate2D(vVector.at(ComputeAxialVectorIndex(vIntX[0],vIntY[0],fIntegrationStepNumberAxialX)),vVector.at(ComputeAxialVectorIndex(vIntX[1],vIntY[0],fIntegrationStepNumberAxialX)),vVector.at(ComputeAxialVectorIndex(vIntX[0],vIntY[1],fIntegrationStepNumberAxialX)),vVector.at(ComputeAxialVectorIndex(vIntX[1],vIntY[1],fIntegrationStepNumberAxialX)),x,y);
    }
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetPlanarElectricCharacteristic(double x, unsigned int vType)
{
    switch (vType) {
        case 0:
            return GetPlanarElectricCharacteristicInterpolation(x,fPlanarPotential);
            break;
        case 1:
            return GetPlanarElectricCharacteristicInterpolation(x,fPlanarAtomicDensity);
            break;
        case 2:
            return GetPlanarElectricCharacteristicInterpolation(x,fPlanarElectronDensity);
            break;
        case 3:
            return GetPlanarElectricCharacteristicInterpolation(x,fPlanarElectricFieldX);
            break;
    }
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_crystal_interpolation::GetAxialElectricCharacteristic(double x, double y, unsigned int vType)
{
    switch (vType) {
        case 0:
            return GetAxialElectricCharacteristicInterpolation(x,y,fAxialPotential);
            break;
        case 1:
            return GetAxialElectricCharacteristicInterpolation(x,y,fAxialAtomicDensity);
            break;
        case 2:
            return GetAxialElectricCharacteristicInterpolation(x,y,fAxialElectronDensity);
            break;
        case 3:
            return GetAxialElectricCharacteristicInterpolation(x,y,fAxialElectricFieldX);
            break;
        case 5:
            return GetAxialElectricCharacteristicInterpolation(x,y,fAxialElectricFieldY);
            break;
    }
    return 0.0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_interpolation::ReadPlanarElectricCharacteristicFromFileInterpolation(std::string FileInName, unsigned int vType)
{
    if(vType == 0) fPlanarPotential = ReadPlanarElectricCharacteristicFromFile(FileInName);
    if(vType == 3) fPlanarElectricFieldX = ReadPlanarElectricCharacteristicFromFile(FileInName);
    if(vType == 1) fPlanarAtomicDensity = ReadPlanarElectricCharacteristicFromFile(FileInName);
    if(vType == 2) fPlanarElectronDensity = ReadPlanarElectricCharacteristicFromFile(FileInName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_interpolation::ReadAxialElectricCharacteristicFromFileInterpolation(std::string FileInName, unsigned int vType)
{
    if(vType == 0) fAxialPotential = ReadAxialElectricCharacteristicFromFile(FileInName);
    if(vType == 3) fAxialElectricFieldX = ReadAxialElectricCharacteristicFromFile(FileInName);
    if(vType == 4) fAxialElectricFieldY = ReadAxialElectricCharacteristicFromFile(FileInName);
    if(vType == 1) fAxialAtomicDensity = ReadAxialElectricCharacteristicFromFile(FileInName);
    if(vType == 2) fAxialElectronDensity = ReadAxialElectricCharacteristicFromFile(FileInName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal_interpolation::GetPlanarElectricCharacteristicVector(unsigned int vType)
{
    switch (vType) {
        case 0:
            return fPlanarPotential;
            break;
        case 1:
            return fPlanarAtomicDensity;
            break;
        case 2:
            return fPlanarElectronDensity;
            break;
        case 3:
            return fPlanarElectricFieldX;
            break;
    }
    std::vector<double> vVector;
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<double> ECHARM_crystal_interpolation::GetAxialElectricCharacteristicVector(unsigned int vType)
{
    switch (vType) {
        case 0:
            return fAxialPotential;
            break;
        case 1:
            return fAxialAtomicDensity;
            break;
        case 2:
            return fAxialElectronDensity;
            break;
        case 3:
            return fAxialElectricFieldX;
            break;
        case 5:
            return fAxialElectricFieldY;
            break;
    }
    
    std::vector<double> vVector;
    return vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_interpolation::SetElectricCharacteristicPlanar(std::vector<double> vVector, unsigned int vType)
{
    if(vType == 0) fPlanarPotential = vVector;
    else if(vType == 3) fPlanarElectricFieldX =vVector;
    else if(vType == 1) fPlanarAtomicDensity = vVector;
    else if(vType == 2) fPlanarElectronDensity = vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_crystal_interpolation::SetElectricCharacteristicAxial(std::vector<double> vVector, unsigned int vType)
{
    if(vType == 0) fAxialPotential = vVector;
    else if(vType == 3) fAxialElectricFieldX = vVector;
    else if(vType == 4) fAxialElectricFieldY = vVector;
    else if(vType == 1) fAxialAtomicDensity = vVector;
    else if(vType == 2) fAxialElectronDensity = vVector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......






