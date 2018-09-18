//
//  ECHARM_simulation_integration.cpp
//
//
//  Created by Enrico Bagli on 31/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


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
    vStepLengthMax = pow( fTransverseVariationMax * GetParticle()->GetMomentumVelocity() / GetStrip()->GetCrystal()->GetElectricFieldMaximum() , 0.5 );
    return vStepLengthMax;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetStepLengthMaxAxial()
{
    double vStepLengthMax = 0.0;
    vStepLengthMax = pow( fTransverseVariationMax * GetParticle()->GetMomentumVelocity() / GetStrip()->GetCrystal()->GetElectricFieldMaximumAxial() , 0.5 );
    return vStepLengthMax;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetTransverseVariationMin()
{
    double vTransverseVariationMin = 0.0;
    vTransverseVariationMin = pow( fStepLengthMin / GetParticle()->GetMomentumVelocity() * GetStrip()->GetCrystal()->GetElectricFieldMaximum() , 2.0 );
    return vTransverseVariationMin;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double ECHARM_simulation_integration::GetTransverseVariationMinAxial()
{
    double vTransverseVariationMin = 0.0;
    vTransverseVariationMin = pow( fStepLengthMin / GetParticle()->GetMomentumVelocity() * GetStrip()->GetCrystal()->GetElectricFieldMaximumAxial() , 2.0 );
    return vTransverseVariationMin;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::UpdateStepLengthPlanar()
{
    if( GetParticle()->GetMomentumVector()->GetX() != 0.0)
        fStepLength = fabs(fTransverseVariationMax / GetParticle()->GetMomentumVector()->GetX() * GetParticle()->GetMomentumVector()->GetZ());
    else fStepLength = fStepLengthMin;
    
    if( fStepLength < fStepLengthMin ) fStepLength = fStepLengthMin;
    if( fStepLength > GetStepLengthMax() ) fStepLength = GetStepLengthMax();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::UpdateStepLengthAxial()
{
    if( (GetParticle()->GetMomentumVector()->GetX() != 0) || ((GetParticle()->GetMomentumVector()->GetY()!=0)))
        fStepLength = fabs(fTransverseVariationMax * GetParticle()->GetMomentumVector()->GetZ() / pow(pow(GetParticle()->GetMomentumVector()->GetX(),2.0)+pow(GetParticle()->GetMomentumVector()->GetY(),2.0),0.5));
    else fStepLength = fStepLengthMin;
    
    if( fStepLength < fStepLengthMin ) fStepLength = fStepLengthMin;
    if( fStepLength > GetStepLengthMax() ) fStepLength = GetStepLengthMaxAxial();
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
    GetParticle()->GetPositionVector()->AddX( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength()  );
    GetParticle()->GetPositionVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength() );
    
    
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),3) / GetParticle()->GetBeta() ) * GetStepLength() );
    
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetX() ) * GetStepLength() );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetY() ) * GetStepLength() );
    
    GetParticle()->GetPositionVector()->AddZ(GetStepLength());
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepAxialNewton()
{
    GetParticle()->GetPositionVector()->AddX( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength()  );
    GetParticle()->GetPositionVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * GetStepLength() );
    
    
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),GetParticle()->GetPositionVector()->GetY(),3) / GetParticle()->GetBeta() ) * GetStepLength() );
    
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetX() ) * GetStepLength() );
    
    GetParticle()->GetMomentumVector()->AddY( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),GetParticle()->GetPositionVector()->GetY(),4) / GetParticle()->GetBeta() ) * GetStepLength() );
    
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetY() ) * GetStepLength() );
    
    GetParticle()->GetPositionVector()->AddZ(GetStepLength());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepPlanarVelocityVerlet()
{
    double vPosXhalf = GetParticle()->GetPositionVector()->GetX();
    double vMomXhalf = GetParticle()->GetMomentumVector()->GetX();
    
    double vStepLength = GetStepLength();
    double vHalfStepLength = vStepLength / 2.0;
    
    vPosXhalf += ( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * vHalfStepLength );
    vMomXhalf += ( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),3) / GetParticle()->GetBeta() ) * vHalfStepLength );
    if( StripIsBentX() ) vMomXhalf -= ( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  * vHalfStepLength / GetStrip()->GetCurvatureRadius()->GetX() );
    
    GetParticle()->GetPositionVector()->AddX( vMomXhalf / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetPlanarElectricCharacteristic(vPosXhalf,3) / GetParticle()->GetBeta() ) * vStepLength );
        
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() * vStepLength / GetStrip()->GetCurvatureRadius()->GetX());
    
    GetParticle()->GetPositionVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() * vStepLength / GetStrip()->GetCurvatureRadius()->GetY());
    
    GetParticle()->GetPositionVector()->AddZ(vStepLength);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoIntegrationStepAxialVelocityVerlet()
{
    double vPosXhalf = GetParticle()->GetPositionVector()->GetX();
    double vMomXhalf = GetParticle()->GetMomentumVector()->GetX();
    
    double vPosYhalf = GetParticle()->GetPositionVector()->GetY();
    double vMomYhalf = GetParticle()->GetMomentumVector()->GetY();
    
    double vStepLength = GetStepLength();
    double vHalfStepLength = vStepLength / 2.0;
 
    vPosXhalf += ( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * vHalfStepLength );
    vMomXhalf += ( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),GetParticle()->GetPositionVector()->GetY(),3) / GetParticle()->GetBeta() ) * vHalfStepLength );
    if( StripIsBentX() ) vMomXhalf -= ( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  / GetStrip()->GetCurvatureRadius()->GetX() ) * vHalfStepLength);
    
    vPosYhalf += ( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * vHalfStepLength );
    vMomYhalf += ( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),GetParticle()->GetPositionVector()->GetY(),4) / GetParticle()->GetBeta() ) * vHalfStepLength );
    if( StripIsBentY() ) vMomYhalf -= ( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  / GetStrip()->GetCurvatureRadius()->GetY() ) * vHalfStepLength);
 
    GetParticle()->GetPositionVector()->AddX( vMomXhalf  / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    GetParticle()->GetMomentumVector()->AddX( ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(vPosXhalf,vPosYhalf,3) / GetParticle()->GetBeta() ) * vStepLength );
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetX() ) * vStepLength);

    GetParticle()->GetPositionVector()->AddY( vMomYhalf  / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    GetParticle()->GetMomentumVector()->AddY(  ( GetParticle()->GetZ() * GetStrip()->GetCrystal()->GetAxialElectricCharacteristic(vPosXhalf,vPosYhalf,4) / GetParticle()->GetBeta() ) * vStepLength );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( (GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() / GetStrip()->GetCurvatureRadius()->GetY() ) * vStepLength);

    GetParticle()->GetPositionVector()->AddZ(vStepLength);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_simulation_integration::DoStraightStep()
{    
    double vStepLength = GetStepLength();
    
    GetParticle()->GetPositionVector()->AddX( GetParticle()->GetMomentumVector()->GetX() / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    if( StripIsBentX() ) GetParticle()->GetMomentumVector()->SubtractX( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta()  * vStepLength / GetStrip()->GetCurvatureRadius()->GetX() );
    
    GetParticle()->GetPositionVector()->AddY( GetParticle()->GetMomentumVector()->GetY() / GetParticle()->GetMomentumVector()->GetZ() * vStepLength );
    if( StripIsBentY() ) GetParticle()->GetMomentumVector()->SubtractY( GetParticle()->GetMomentumVector()->GetZ() * GetParticle()->GetBeta() * vStepLength / GetStrip()->GetCurvatureRadius()->GetY());
    
    GetParticle()->GetPositionVector()->AddZ(vStepLength);
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
        if(GetParticle()->GetPositionVector()->GetZ() > GetStrip()->GetDimension()->GetZ()) bIntegrationEnd = true;
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
        if(GetParticle()->GetPositionVector()->GetZ() > GetStrip()->GetDimension()->GetZ()) bIntegrationEnd = true;
    } while (bIntegrationEnd != true);
}

