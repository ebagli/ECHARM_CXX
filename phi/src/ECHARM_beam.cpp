//
//  ECHARM_beam.cpp
//  
//
//  Created by Enrico Bagli on 04/06/12.
//  Copyright 2012 Enrico Bagli. All rights reserved.
//

ECHARM_beam::ECHARM_beam()
{
    InitializePointersBeam();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_beam::~ECHARM_beam()
{
    if (&fPositionDistributionX)         { delete &fPositionDistributionX; }
    if (&fPositionDistributionY)         { delete &fPositionDistributionY; }
    if (&fPositionDistributionZ)         { delete &fPositionDistributionZ; }
    if (&fMomentumDistributionX)         { delete &fMomentumDistributionX; }
    if (&fMomentumDistributionY)         { delete &fMomentumDistributionY; }
    if (&fMomentumDistributionZ)         { delete &fMomentumDistributionZ; }
    if (&fParticleArray)         { delete &fParticleArray; }
    if (&fPercentage)         { delete &fPercentage; }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const ECHARM_beam& ECHARM_beam::operator=(const ECHARM_beam& right)
{
    if (this != &right)
    {
        InitializePointersBeam();
        fPositionDistributionX = right.fPositionDistributionX;
        fPositionDistributionY = right.fPositionDistributionY;
        fPositionDistributionZ = right.fPositionDistributionY;
        fMomentumDistributionX = right.fMomentumDistributionX;
        fMomentumDistributionY = right.fMomentumDistributionY;
        fMomentumDistributionZ = right.fMomentumDistributionY;
        fParticleArray = right.fParticleArray;
        fPercentage = right.fPercentage;
     }
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::PrintBeamProperties()
{ 
    std::cout << "ECHARM_beam - Print Properties" << std::endl;
    PrintBeamGeometricalProperties();
    PrintParticleArray();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::PrintParticleArray()
{
    for(unsigned int i=0;i<fParticleArray.size();i++)
    {
        std::cout << "ECHARM_beam - Print Particle " << i << " with percentage " << fPercentage.at(i) <<" Properties"<< std::endl;
        fParticleArray.at(i)->PrintParticleProperties();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::PrintBeamGeometricalProperties()
{ 
    std::cout << "ECHARM_beam - Print Geometrical Properties" << std::endl;
    fPositionDistributionX->PrintDistributionProperties();
    fPositionDistributionY->PrintDistributionProperties();
    fPositionDistributionZ->PrintDistributionProperties();
    fMomentumDistributionX->PrintDistributionProperties();
    fMomentumDistributionY->PrintDistributionProperties();
    fMomentumDistributionZ->PrintDistributionProperties();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::AddParticle(ECHARM_particle *particle,float percentage)
{
    fParticleArray.push_back(particle);
    fPercentage.push_back(percentage);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ECHARM_particle *ECHARM_beam::GenerateParticle()
{
    double vProbability = drand48();
    double vTotalPercentage = 0.0;
    bool bExitLoop = false;
    unsigned int vIndex = 0;
    for(unsigned int i=0;i<fPercentage.size();i++)
    {
        if(!bExitLoop)
        if(vProbability<(vTotalPercentage+fPercentage.at(i)))
           {
               vIndex = i;
               fParticleArray.at(vIndex)->GetPositionVector()->SetX(fPositionDistributionX->GenerateNumber());
               fParticleArray.at(vIndex)->GetPositionVector()->SetY(fPositionDistributionY->GenerateNumber());
               fParticleArray.at(vIndex)->GetPositionVector()->SetZ(fPositionDistributionZ->GenerateNumber());
               fParticleArray.at(vIndex)->GetMomentumVector()->SetX(fMomentumDistributionX->GenerateNumber());
               fParticleArray.at(vIndex)->GetMomentumVector()->SetY(fMomentumDistributionY->GenerateNumber());
               fParticleArray.at(vIndex)->GetMomentumVector()->SetZ(fMomentumDistributionZ->GenerateNumber());
               bExitLoop = true;
           }
        vTotalPercentage +=fPercentage.at(i);
    }
    
    return fParticleArray.at(vIndex);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::InitializePointersBeam()
{
    fPositionDistributionX->InitializePointersRandom();
    fPositionDistributionY->InitializePointersRandom();
    fPositionDistributionZ->InitializePointersRandom();
    fMomentumDistributionX->InitializePointersRandom();
    fMomentumDistributionY->InitializePointersRandom();
    fMomentumDistributionZ->InitializePointersRandom();

    fPercentage.clear();
    fParticleArray.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_beam::operator==(const ECHARM_beam& right) const
{
    return (this == (ECHARM_beam*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int ECHARM_beam::operator!=(const ECHARM_beam& right) const
{
    return (this != (ECHARM_beam*) &right);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ECHARM_beam::DeleteParticle(unsigned int vIndex)
{
    std::vector<ECHARM_particle*> vParticleArray;
    std::vector<float> vPercentage;

    if(vIndex<fParticleArray.size())
    {
        for(unsigned int i=0;i<vIndex;i++)
        {
            vParticleArray.push_back(fParticleArray.at(i));
            vPercentage.push_back(fPercentage.at(i));
        }
        for(unsigned int i=vIndex+1;i<fParticleArray.size();i++)
        {
            vParticleArray.push_back(fParticleArray.at(i));
            vPercentage.push_back(fPercentage.at(i));
        }
        fParticleArray.clear();
        for(unsigned int i=0;i<(vParticleArray.size());i++)
        {
            fParticleArray.push_back(vParticleArray.at(i));
        }
    }
}



