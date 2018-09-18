//
//  ECHARM_multiple_scattering.cpp
//
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_multiple_scattering::ECHARM_multiple_scattering()
{
    InitializePointersMultipleScattering();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_multiple_scattering::ECHARM_multiple_scattering(ECHARM_crystal *Crystal,ECHARM_particle *Particle)
{
    InitializePointersMultipleScattering();
    SetParticle(Particle);
    SetCrystal(Crystal);
    SetRadiationLength("tsai");
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_multiple_scattering::~ECHARM_multiple_scattering()
{
    if (&fNuclearScatteringOutgoingDistribution) delete (&fNuclearScatteringOutgoingDistribution);
    if (&fElectronScatteringOutgoingDistribution) delete (&fElectronScatteringOutgoingDistribution);
    if (&fSingleElectronScatteringOutgoingDistribution) delete (&fSingleElectronScatteringOutgoingDistribution);
    
    if (&fNuclearScatteringModel) delete (&fNuclearScatteringModel);
    if (&fElectronScatteringModel) delete (&fElectronScatteringModel);
    if (&fSingleScatteringModel) delete (&fSingleScatteringModel);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


const ECHARM_multiple_scattering& ECHARM_multiple_scattering::operator=(const ECHARM_multiple_scattering& right)
{
    if (this != &right)
    {
        InitializePointersMultipleScattering();
        
        fNuclearScatteringOutgoingDistribution = right.fNuclearScatteringOutgoingDistribution;
        fElectronScatteringOutgoingDistribution = right.fElectronScatteringOutgoingDistribution;
        fSingleElectronScatteringOutgoingDistribution = right.fSingleElectronScatteringOutgoingDistribution;
        
        fNuclearScatteringModel = right.fNuclearScatteringModel;
        fElectronScatteringModel = right.fElectronScatteringModel;
        fSingleScatteringModel = right.fSingleScatteringModel;
    }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering::InitializePointersMultipleScattering()
{
    InitializePointersMultipleScatteringFunctions();
    fNuclearScatteringOutgoingDistribution = new ECHARM_distribution(1);
    fElectronScatteringOutgoingDistribution = new ECHARM_distribution(1);
    fSingleElectronScatteringOutgoingDistribution = new ECHARM_distribution(1);
    
    fElectronScatteringModel = 4;
    fNuclearScatteringModel = 3;
    fSingleScatteringModel = 5;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_multiple_scattering::operator==(const ECHARM_multiple_scattering& right) const
{
    return (this == (ECHARM_multiple_scattering*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_multiple_scattering::operator!=(const ECHARM_multiple_scattering& right) const
{
    return (this != (ECHARM_multiple_scattering*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering::UpdateNuclearScatteringOutgoingDistribution(double *vParameters)
{
    fNuclearScatteringOutgoingDistribution->SetDistributionParameter(1,EvaluateScatteringTransverseEnergyVariation(fNuclearScatteringModel,vParameters));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering::UpdateElectronScatteringOutgoingDistribution(double *vParameters)
{
    fElectronScatteringOutgoingDistribution->SetDistributionParameter(1,EvaluateScatteringTransverseEnergyVariation(fElectronScatteringModel,vParameters));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_multiple_scattering::UpdateSingleElectronScatteringOutgoingDistribution(double *vParameters)
{
    fSingleElectronScatteringOutgoingDistribution->SetDistributionParameter(1,EvaluateScatteringTransverseEnergyVariation(fSingleScatteringModel,vParameters));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoScatteringPlanar(ECHARM_distribution *vDistribution, unsigned int vCrystalComponent)
{
    double vEnergyTotal = GetParticle()->GetMomentumVector()->GetModule();
    double vEnergyVariation = vDistribution->GenerateNumber();
    
    vEnergyVariation *= GetCrystal()->GetPlanarElectricCharacteristic(GetParticle()->GetPositionVector()->GetX(),vCrystalComponent);
    vEnergyTotal += vEnergyVariation;

    if(vEnergyTotal>0.){
        double vRandomAngle = 2 * M_PI * drand48();
        GetParticle()->GetMomentumVector()->AddX( vEnergyVariation * cos(vRandomAngle) );
        GetParticle()->GetMomentumVector()->AddY( vEnergyVariation * sin(vRandomAngle) );
        GetParticle()->GetMomentumVector()->ScaleModuleTo(vEnergyTotal);
    }
    else return false;
    
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoScatteringAxial(ECHARM_distribution *vDistribution, unsigned int vCrystalComponent)
{
    double vEnergyTotal = GetParticle()->GetMomentumVector()->GetModule();
    double vEnergyVariation = vDistribution->GenerateNumber();
    
    vEnergyTotal += vEnergyVariation;
    if(vEnergyTotal>0.){
        double vRandomAngle = 2 * M_PI * drand48();
        GetParticle()->GetMomentumVector()->AddX( vEnergyVariation * cos(vRandomAngle) );
        GetParticle()->GetMomentumVector()->AddY( vEnergyVariation * sin(vRandomAngle) );
        GetParticle()->GetMomentumVector()->ScaleModuleTo(vEnergyTotal);
    }
    else return false;
    
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoNuclearScatteringPlanar(double *vParameters)
{
    return DoScatteringPlanar(fNuclearScatteringOutgoingDistribution,1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoNuclearScatteringAxial(double *vParameters)
{
    return DoScatteringAxial(fNuclearScatteringOutgoingDistribution,1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoElectronScatteringPlanar(double *vParameters)
{
    return DoScatteringPlanar(fElectronScatteringOutgoingDistribution,2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoElectronScatteringAxial(double *vParameters)
{
    return DoScatteringAxial(fElectronScatteringOutgoingDistribution,2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoSingleScatteringPlanar(double *vParameters)
{
    double vProbability = EvaluateSingleScatteringProbabilityBiryukov();
    unsigned int vSingleScatteringNumber = int(vProbability);
    if(vSingleScatteringNumber >= 1)
        for(unsigned int i=0;i<vSingleScatteringNumber;i++)
            DoScatteringPlanar(fSingleElectronScatteringOutgoingDistribution,2);
    else if(fSingleElectronScatteringOutgoingDistribution->GenerateNumberBox(0.5,0.5) < vProbability)
        DoScatteringPlanar(fSingleElectronScatteringOutgoingDistribution,2);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

bool ECHARM_multiple_scattering::DoSingleScatteringAxial(double *vParameters)
{
    DoScatteringAxial(fSingleElectronScatteringOutgoingDistribution,2);
    return true;
}


