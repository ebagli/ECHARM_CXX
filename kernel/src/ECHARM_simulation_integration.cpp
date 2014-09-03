//
//  ECHARM_simulation_integration.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ECHARM_simulation_integration.h" 

ECHARM_simulation_integration::ECHARM_simulation_integration()
{
    InitializePointersChannelingSimulation();
}

ECHARM_simulation_integration::ECHARM_simulation_integration(ECHARM_strip* strip, ECHARM_particle* particle)
{
    InitializePointersChannelingSimulation();
    SetStrip(strip);
    SetParticle(particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_simulation_integration::~ECHARM_simulation_integration()
{
    if(&fIntegrationMethod) delete (&fIntegrationMethod);
    if(&fStepLength) delete (&fStepLength);
    if(&fStepLengthMin) delete (&fStepLengthMin);
    if(&fTransverseVariationMax) delete (&fTransverseVariationMax);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::InitializePointersChannelingSimulation()
{
    InitializePointersChanneling();
    
    fIntegrationMethod = 0;
 
    fStepLengthMin = 2.0E-8;
    fTransverseVariationMax = 2.0E-13;
    fStepLength = fStepLengthMin;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_simulation_integration::operator==(const ECHARM_simulation_integration& right) const
{
    return (this == (ECHARM_simulation_integration*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_simulation_integration::operator!=(const ECHARM_simulation_integration& right) const
{
    return (this != (ECHARM_simulation_integration*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetStepLengthMax()
{
    double vStepLengthMax = 0.0;
    vStepLengthMax = fSquareRoot( fTransverseVariationMax * GetParticle()->GetMomentumVelocity() / GetStrip()->GetCrystal()->GetElectricFieldMaximum() );
    return vStepLengthMax;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetStepLengthMaxAxial()
{
    double vStepLengthMax = 0.0;
    vStepLengthMax = fSquareRoot( fTransverseVariationMax * GetParticle()->GetMomentumVelocity() / GetStrip()->GetCrystal()->GetElectricFieldMaximumAxial() );
    return vStepLengthMax;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetTransverseVariationMin()
{
    double vTransverseVariationMin = 0.0;
    vTransverseVariationMin = fSquare( fStepLengthMin / GetParticle()->GetMomentumVelocity() * GetStrip()->GetCrystal()->GetElectricFieldMaximum() );
    return vTransverseVariationMin;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetTransverseVariationMinAxial()
{
    double vTransverseVariationMin = 0.0;
    vTransverseVariationMin = fSquare( fStepLengthMin / GetParticle()->GetMomentumVelocity() * GetStrip()->GetCrystal()->GetElectricFieldMaximumAxial() );
    return vTransverseVariationMin;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::UpdateStepLengthPlanar()
{
    if( GetParticle()->GetMomentumVector()->GetX() != 0.0)
        fStepLength = fabs(fTransverseVariationMax / GetParticle()->GetMomentumVector()->GetX() * GetParticle()->GetMomentumVector()->GetZ());
    else fStepLength = fStepLengthMin;
    
    if( fStepLength < fStepLengthMin ) fStepLength = fStepLengthMin;
    else if( fStepLength > GetStepLengthMax() ) fStepLength = GetStepLengthMax();
    
    if((GetParticle()->GetPosVector()->GetZ() + fStepLength) > GetStrip()->GetDim()->GetZ()){
        fStepLength = GetStrip()->GetDim()->GetZ()*0.00001;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::UpdateStepLengthAxial()
{
    if( (GetParticle()->GetMomentumVector()->GetX() != 0) || ((GetParticle()->GetMomentumVector()->GetY()!=0)))
        fStepLength = fabs(fTransverseVariationMax * GetParticle()->GetMomentumVector()->GetZ() / fSquareRoot(fSquare(GetParticle()->GetMomentumVector()->GetX())+fSquare(GetParticle()->GetMomentumVector()->GetY())));
    else fStepLength = fStepLengthMin;
    
    if( fStepLength < fStepLengthMin ) fStepLength = fStepLengthMin;
    else if( fStepLength > GetStepLengthMax() ) fStepLength = GetStepLengthMaxAxial();
    
    if((GetParticle()->GetPosVector()->GetZ() + fStepLength) > GetStrip()->GetDim()->GetZ()){
        fStepLength = GetStrip()->GetDim()->GetZ()*0.00001;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_simulation_integration& ECHARM_simulation_integration::operator=(const ECHARM_simulation_integration& right)
{
    if (this != &right)
    {
        InitializePointersChannelingSimulation();
        
        SetStrip(right.GetStrip());
        SetParticle(right.GetParticle());
        
        fIntegrationMethod = right.fIntegrationMethod;
        
        fStepLength = right.fStepLength;
        fStepLengthMin = right.fStepLengthMin;
        fTransverseVariationMax = right.fTransverseVariationMax;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepPlanarNewton()
{
    GetParticle()->GetPosVector()->AddX( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength()  );
    GetParticle()->GetPosVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength() );
    
    
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),3) / GetParticle()->GetBeta() ) * GetStepLength() );
    
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetX() ) * GetStepLength() );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetY() ) * GetStepLength() );
    
    GetParticle()->GetPosVector()->AddZ(GetStepLength());
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepAxialNewton()
{
    GetParticle()->GetPosVector()->AddX( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength()  );
    GetParticle()->GetPosVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength() );
    
    
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),3) / GetParticle()->GetBeta() ) * GetStepLength() );
    
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetX() ) * GetStepLength() );
    
    GetParticle()->GetMomentumVector()->AddY( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),4) / GetParticle()->GetBeta() ) * GetStepLength() );
    
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetY() ) * GetStepLength() );
    
    GetParticle()->GetPosVector()->AddZ(GetStepLength());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepPlanarVelocityVerlet()
{
    double vPosXhalf = GetParticle()->GetPosVector()->GetX();
    double vMomXhalf = GetParticle()->GetMomentumVector()->GetX();
    
    double vStepLength = GetStepLength();
    double vHalfStepLength = vStepLength / 2.0;
    
    vPosXhalf += ( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * vHalfStepLength );
    vMomXhalf += ( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),3) / GetParticle()->GetBeta() ) * vHalfStepLength );
    if( StripIsBentX() ) vMomXhalf -= ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  * vHalfStepLength / GetStrip()->GetCurvatureRadius()->GetX() );
    
    GetParticle()->GetPosVector()->AddX( vMomXhalf / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(vPosXhalf,3) / GetParticle()->GetBeta() ) * vStepLength );
        
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() * vStepLength / GetStrip()->GetCurvatureRadius()->GetX());
    
    GetParticle()->GetPosVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() * vStepLength / GetStrip()->GetCurvatureRadius()->GetY());
    
    GetParticle()->GetPosVector()->AddZ(vStepLength);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepAxialVelocityVerlet()
{
    double vPosXhalf = GetParticle()->GetPosVector()->GetX();
    double vMomXhalf = GetParticle()->GetMomentumVector()->GetX();
    
    double vPosYhalf = GetParticle()->GetPosVector()->GetY();
    double vMomYhalf = GetParticle()->GetMomentumVector()->GetY();
    
    double vStepLength = GetStepLength();
    double vHalfStepLength = vStepLength / 2.0;
 
    vPosXhalf += ( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * vHalfStepLength );
    vMomXhalf += ( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),3) / GetParticle()->GetBeta() ) * vHalfStepLength );
    if( StripIsBentX() ) vMomXhalf -= ( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  / GetStrip()->GetCurvatureRadius()->GetX() ) * vHalfStepLength);
    
    vPosYhalf += ( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * vHalfStepLength );
    vMomYhalf += ( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),4) / GetParticle()->GetBeta() ) * vHalfStepLength );
    if( StripIsBentY() ) vMomYhalf -= ( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  / GetStrip()->GetCurvatureRadius()->GetY() ) * vHalfStepLength);
 
    GetParticle()->GetPosVector()->AddX( vMomXhalf  / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(vPosXhalf,vPosYhalf,3) / GetParticle()->GetBeta() ) * vStepLength );
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetX() ) * vStepLength);

    GetParticle()->GetPosVector()->AddY( vMomYhalf  / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    GetParticle()->GetMomentumVector()->AddY(  ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(vPosXhalf,vPosYhalf,4) / GetParticle()->GetBeta() ) * vStepLength );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetY() ) * vStepLength);

//    std::cout << GetParticle()->GetPosVector()->GetX() << std::endl;
//    std::cout << GetParticle()->GetPosVector()->GetY() << std::endl;
//    std::cout << GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),0) << std::endl;
//    std::cout << GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),1) << std::endl;
//    std::cout << GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),2) << std::endl;
//    std::cout << GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),3) << std::endl;
//    std::cout << GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPosVector()->GetX(),GetParticle()->GetPosVector()->GetY(),4) << std::endl;
//    while(!getchar());
    GetParticle()->GetPosVector()->AddZ(vStepLength);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoStraightStep()
{    
    double vStepLength = GetStepLength();
    
    GetParticle()->GetPosVector()->AddX( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  * vStepLength / GetStrip()->GetCurvatureRadius()->GetX() );
    
    GetParticle()->GetPosVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() * vStepLength / GetStrip()->GetCurvatureRadius()->GetY());
    
    GetParticle()->GetPosVector()->AddZ(vStepLength);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepPlanar(unsigned int vIntegrationMethod)
{
    if(vIntegrationMethod == 0) DoIntegrationStepPlanarVelocityVerlet();
    if(vIntegrationMethod == 1) DoIntegrationStepPlanarNewton();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepAxial(unsigned int vIntegrationMethod)
{
    if(vIntegrationMethod == 0) DoIntegrationStepAxialVelocityVerlet();
    if(vIntegrationMethod == 1) DoIntegrationStepAxialNewton();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::IntegrateParticleTrajectoryPlanar(unsigned int vIntegrationMethod)
{
    bool bIntegrationEnd = false;
    do
    {
        UpdateStepLengthPlanar();
        DoIntegrationStepPlanar(vIntegrationMethod);
        if(GetParticle()->GetPosVector()->GetZ() > GetStrip()->GetDim()->GetZ()) bIntegrationEnd = true;
    } while (bIntegrationEnd != true);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::IntegrateParticleTrajectoryAxial(unsigned int vIntegrationMethod)
{
    bool bIntegrationEnd = false;
    do
    {
        UpdateStepLengthAxial();
        DoIntegrationStepAxial(vIntegrationMethod);
        if(GetParticle()->GetPosVector()->GetZ() > GetStrip()->GetDim()->GetZ()) bIntegrationEnd = true;
    } while (bIntegrationEnd != true);
}

